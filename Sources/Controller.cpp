/* Controller.cpp */

#include "Headers/Controller.h"
#include "Headers/GP4k_TilesMapping.h"
#include "Headers/GP4k_ButtonsMapping.h"
#include "Headers/TileGroupWidget.h"

#include <cmath>

#include <QApplication>
#include <QDebug>
#include <QKeyEvent>
#include <QLoggingCategory>
#include <QtGamepad/QGamepad>
#include <QTextEdit>

/**
 * @def BORDER_DEAD_ZONE
 * @brief Defines the deadzone around the stick border.
 *
 * @details It's mainly needed to compensate factory default of controllers: my own Nintend switch pro
 * can have a Radius of 0.99 at the border for instance. A higher value is chosen to prevent unwanted types,
 * in cases the user take the stick a bit away when moving it around the border quickly.
 */
#define BORDER_DEAD_ZONE  0.3F

/**
 * @def HALF_CIRCLE_ANGLE_IN_DEGREE
 * @brief Constant representing the angle for half a circle in degree
 */
#define HALF_CIRCLE_ANGLE_IN_DEGREE 180U

/**
 * @def RADIAN_TO_DEGREE_FACTOR
 * @brief A constant factor used for radian-degree conversion.
 */
#define RADIAN_TO_DEGREE_FACTOR HALF_CIRCLE_ANGLE_IN_DEGREE / M_PI

/**
 * @def ANGLE_IN_DEGREE
 * @brief Macrofunction used to convert an angle from radian to degree.
 */
#define ANGLE_IN_DEGREE(angle) angle*RADIAN_TO_DEGREE_FACTOR + HALF_CIRCLE_ANGLE_IN_DEGREE

Controller::Controller(QWidget *parent)
    : QWidget{parent}
    , _SelectedController(nullptr)
    , _AxisPosition({{0, 0}, {0, 0}})
    , _Angles({-1, -1})
    , _Radius({CENTER, CENTER})
    , _SelectedTiles({0, DEFAULT_TILE})
    , _ShiftKeyState(NOT_SHIFTED)
    , _CapsLockState(false)

{
    QLoggingCategory::setFilterRules(QStringLiteral("qt.gamepad.debug=false"));
    QList<int> controllers_list = QGamepadManager::instance()->connectedGamepads();
    if (controllers_list.isEmpty()) {
        qDebug() << "No controller detected";
        return;
    }

    int Controller_SelectedController_ID = -1;

    for (auto current_controller_ID : controllers_list){
        QString current_controller_name = QGamepadManager::instance()->gamepadName(current_controller_ID);
        if (!IsItAllowed(current_controller_name)){
            qDebug() << current_controller_name << "Is not allowed.";
        }else{
            Controller_SelectedController_ID = current_controller_ID;
            _Brand = WhatsTheBrand(current_controller_name);
            qDebug() << current_controller_name << "(" << _Brand << ") Will be used...";
            break;
        }
    }

    if(Controller_SelectedController_ID == -1){
        qDebug() << "No supported controller detected";
        return;
    }

    _SelectedController = new QGamepad(Controller_SelectedController_ID, this);
    qDebug() << "Controller connected!";

    _Autocompleter = new Autocomplete();

    connect(_SelectedController, &QGamepad::axisLeftXChanged, this, [this](double Value){
        UpdateAxis(STICK_LEFT, X_AXIS, Value);
    });

    connect(_SelectedController, &QGamepad::axisLeftYChanged, this, [this](double Value){
        UpdateAxis(STICK_LEFT, Y_AXIS, Value);
    });

    connect(_SelectedController, &QGamepad::axisRightXChanged, this, [this](double Value){
        UpdateAxis(STICK_RIGHT, X_AXIS, Value);
    });

    connect(_SelectedController, &QGamepad::axisRightYChanged, this, [this](double Value){
        UpdateAxis(STICK_RIGHT, Y_AXIS, Value);
    });

    connect(_SelectedController, &QGamepad::buttonYChanged, this, [this](double Value){
            const ShiftState_t ShiftKey = _ShiftKeyState;
            const brand_t Brand = _Brand;
            const feature_t Feature = (Brand == XBOX) ? Button_Y.Features[ShiftKey] : Button_X.Features[ShiftKey];
            ButtonPressed(Feature, Value);
    });

    connect(_SelectedController, &QGamepad::buttonXChanged, this, [this](double Value){
            const ShiftState_t ShiftKey = _ShiftKeyState;
            const brand_t Brand = _Brand;
            const feature_t Feature = (Brand == XBOX) ? Button_X.Features[ShiftKey] : Button_Y.Features[ShiftKey];
            ButtonPressed(Feature, Value);
    });


    connect(_SelectedController, &QGamepad::buttonDownChanged, this, [this](double Value){
            const ShiftState_t ShiftKey = _ShiftKeyState;
            const feature_t Feature = Dpad_DOWN.Features[ShiftKey];
            ButtonPressed(Feature, Value);
    });

    connect(_SelectedController, &QGamepad::buttonUpChanged, this, [this](double Value){
            const ShiftState_t ShiftKey = _ShiftKeyState;
            const feature_t Feature = Dpad_UP.Features[ShiftKey];
            ButtonPressed(Feature, Value);
    });

    connect(_SelectedController, &QGamepad::buttonLeftChanged, this, [this](double Value){
            const ShiftState_t ShiftKey = _ShiftKeyState;
            const feature_t Feature = Dpad_LEFT.Features[ShiftKey];
            ButtonPressed(Feature, Value);
    });

    connect(_SelectedController, &QGamepad::buttonRightChanged, this, [this](double Value){
            const ShiftState_t ShiftKey = _ShiftKeyState;
            const feature_t Feature = Dpad_RIGHT.Features[ShiftKey];
            ButtonPressed(Feature, Value);
    });

    connect(_SelectedController, &QGamepad::buttonL2Changed, this, [this](double Value){
            const ShiftState_t ShiftKey = _ShiftKeyState;
            const feature_t Feature = Button_LT.Features[ShiftKey];
            ButtonPressed(Feature, Value);
    });

    connect(_SelectedController, &QGamepad::buttonL1Changed, this, [this](bool Value){
            const ShiftState_t ShiftKey = _ShiftKeyState;
            const feature_t Feature = Button_LB.Features[ShiftKey];
            ButtonPressed(Feature, Value);
    });

    connect(_SelectedController, &QGamepad::buttonR1Changed, this, [this](bool Value){
            const ShiftState_t ShiftKey = _ShiftKeyState;
            const feature_t Feature = Button_RB.Features[ShiftKey];
            ButtonPressed(Feature, Value);
    });
}

bool Controller::IsItAllowed(const QString &controllerName) const{
    return !_ForbiddenControllers.contains(controllerName);
}

brand_t Controller::WhatsTheBrand(const QString &controllerName) const{
    // if(_TestedControllers.contains(controllerName)){return _TestedControllers[controllerName];}
    // else{return ControllerBrandAutodetect(controllerName);}
    return (_TestedControllers.contains(controllerName)) ? _TestedControllers[controllerName] : ControllerBrandAutodetect(controllerName);
}

brand_t Controller::ControllerBrandAutodetect(const QString &controllerName) const{
    const QMap<QString, brand_t> BrandKeywords{
        {"x-box", XBOX}, {"xbox", XBOX}, {"microsoft", XBOX},
        {"playstation", PLAYSTATION}, {"dualshock", PLAYSTATION}, {"dual shock", PLAYSTATION}, {"dualsense", PLAYSTATION},
        {"dual sense", PLAYSTATION}, {"ps", PLAYSTATION}, {"sony", PLAYSTATION},
        {"switch", NINTENDO}, {"nintendo", NINTENDO}
    };
    for (const QString& Keyword : BrandKeywords.keys()) {
        if(controllerName.contains(Keyword, Qt::CaseInsensitive)){return BrandKeywords[Keyword];}
    }
    return XBOX; // Default return to ensure the demo can run.
}

void Controller::UpdateAxis(const stick_t Stick, const axis_t Axis, const double AxisValue){
    _AxisPosition[Stick][Axis] = AxisValue;
    UpdateRadius(Stick);
}

void Controller::UpdateRadius(const stick_t Stick){
    const StickPosition_t Radius = NormalizeRadius(Stick);
    if(Radius == BORDER){
        UpdateAngle(Stick);
    }else{
        StickReleased(Radius, Stick);
    }
    _Radius[Stick] = Radius;
}

StickPosition_t Controller::NormalizeRadius(const stick_t Stick) const{
    const double PositionX = _AxisPosition[Stick][X_AXIS];
    const double PositionY = _AxisPosition[Stick][Y_AXIS];
    double Radius = sqrt(pow(PositionX, 2) + pow(PositionY, 2));
    /*
     * The stick radius varies across controllers and angles due to drift or manufacturing imperfections.
     * This condition normalizes the radius to distinguish between "on the border" and "at the center."
     */
    return (Radius >= static_cast<double>(BORDER) - BORDER_DEAD_ZONE) ? BORDER : CENTER;
}

void Controller::StickReleased(const StickPosition_t NewRadius, const stick_t Stick){
    const double CurrentRadius = _Radius[Stick];
    /*
         * The stick emits redundant X and Y signals during release, causing
         * repetitive radius calculations. This condition prevents unnecessary
         * operations and only applies to the right stick.
         */
    if(NewRadius != CurrentRadius && Stick == STICK_RIGHT){
        const uint8_t OuterTileIndex = _SelectedTiles[STICK_LEFT];
        const uint8_t InnerTileIndex = _SelectedTiles[STICK_RIGHT];
        /*
             * This index calculation take advantage of the placement of
             * the suggestions tiles: The 0, 2 or 3 last tiles,
             * depending on outer selected tile.
             */
        const uint8_t LastCharacterTileIndex = MAX_TILE_INDEX - GroupsSuggestionsMap[OuterTileIndex];
        (InnerTileIndex <= LastCharacterTileIndex) ? CharTileSelected(InnerTileIndex, OuterTileIndex) : TypeSuggestion(InnerTileIndex);
    }
}

void Controller::CharTileSelected(const uint8_t CharTileIndex, const uint8_t CharGroup){
    const ShiftState_t ShiftKey = _ShiftKeyState;
    const QString Letter = InnerTilesChars[ShiftKey][CharGroup][CharTileIndex];
    TypeChar(Letter);
    AutocompleterUpdate(Qt::Key_A, Letter); // Key_A is to trigger default case of AutocompleterUpdate
}

void Controller::UpdateAngle(const stick_t Stick){
    const double PositionX = _AxisPosition[Stick][X_AXIS];
    const double PositionY = _AxisPosition[Stick][Y_AXIS];
    const double AngleRadian = atan2(PositionY, PositionX);
    const double AngleDegree = ANGLE_IN_DEGREE(AngleRadian);
    _Angles[Stick] = AngleDegree;
    UpdateSelectedTile(Stick);
}

void Controller::UpdateSelectedTile(const stick_t Stick){

    const double Angle = _Angles[Stick];
    const double MovedAngle = std::fmod(Angle+22.5,360.0);
    const uint8_t NewTile = static_cast<uint8_t>(MovedAngle/45);
    const uint8_t CurrentTile = _SelectedTiles[Stick];

    if(CurrentTile != NewTile){
        _SelectedTiles[Stick] = NewTile;
        _Angles[Stick] = -1;
        if(Stick == STICK_LEFT){
            emit ToggleOuterSelectedTile(NewTile);
            emit ResetCenterBackgrounds();
            emit UpdateInnerTiles(_ShiftKeyState, NewTile);
            if(GroupsSuggestionsMap[NewTile] > 0){
                _Autocompleter->SetSkipLastChars(NewTile);
                QueryingSuggestions();
            }
            _SelectedTiles[STICK_RIGHT] = DEFAULT_TILE;
        }else{
            emit ToggleInnerSelectedTile(NewTile);
        }
    }
}

void Controller::ButtonPressed(feature_t Feature, const double ButtonValue){
    if(ButtonValue == 0.0){ // Triggered only when button is NOT_SHIFTED

        const FeatureType_t FeatureType = Feature.FeatureType;
        const Qt::Key Key = Feature.Key;
        const QString Text = Feature.Text;

        switch (FeatureType) {
        case TEXT_CONTROL: // Moves, space and backspace
            emit SendOrderToTextField(Key);
            AutocompleterUpdate(Key, Text);
            break;
        case PUNCTUATION: // Comma, period...
            /* Text is something like "□-" to prevent confusing
             * chars like , or ' on the GUI (there is no line).
             * The [1] allows to send uniquely the second position
             * in the string, which is the char that should actually
             * be typed in the text field.
             */
            TypeChar(Text[1]);
            ButtonPressed(SPACE);
            break;
        case WORD_CONNECTOR: // Hyphen and apostrophe
            TypeChar(Text[1]);
            AutocompleterUpdate(Key, Text[1]);
            break;
        case SHIFT_TYPE:
            ShiftButton();
            break;
        default:
            break;
        }
    }
}

void Controller::AutocompleterUpdate(const Qt::Key Key, const QString Text){
    Autocomplete* Autocompleter = _Autocompleter;
    actions_t ResultOnBuffer = NOTHING;
    switch (Key) {
    case Qt::Key_Space:
        Autocompleter->ClearBuffer();
        ResultOnBuffer = CLEARED_BUFFER;
        break;
    case Qt::Key_Backspace:
        ResultOnBuffer = Autocompleter->ChangeCharacter("");
        break;
    case Qt::Key_Left:
    case Qt::Key_Right:
        ResultOnBuffer = Autocompleter->MoveBufferCursor(Key);
        break;
    default: // Any other character is likely a letter: Add it to the buffer
        ResultOnBuffer = Autocompleter->ChangeCharacter(Text);
        break;
    }

    if(ResultOnBuffer != NOTHING){
        QueryingSuggestions();
    }
}

void Controller::ShiftButton(){
        ShiftState_t ShiftKey = _ShiftKeyState;
        bool CapsLock = _CapsLockState;
        if(ShiftKey == NOT_SHIFTED){ ShiftKey = SHIFTED; } // Shift button no pressed, standard case
        else{
            if(CapsLock == false){ CapsLock = true; } // Shift button is pressed for the second time, we want to lock caps
            else{ // Caps are already locked, we want to unlock them and return to lower case
                CapsLock = false;
                ShiftKey = NOT_SHIFTED;
            }
        }
        _CapsLockState = CapsLock;
        _ShiftKeyState = ShiftKey;
        uint8_t CurrentCharGroup = _SelectedTiles[STICK_LEFT];
        emit ToggleTextsOnShift(ShiftKey, CurrentCharGroup);
}

brand_t Controller::GetBrand(void) const{
    return _Brand;
}

void Controller::TypeChar(const QString Letter){
    emit TypeToTextField(Letter);
    ToggleShift();
}

void Controller::ToggleShift(){
    const bool CapsLock = _CapsLockState;
    if(!CapsLock){
        _ShiftKeyState = NOT_SHIFTED;
        uint8_t CurrentCharGroup = _SelectedTiles[STICK_LEFT];
        emit ToggleTextsOnShift(_ShiftKeyState, CurrentCharGroup);
    }
}

void Controller::QueryingSuggestions(void){
    _Suggestions = _Autocompleter->GetSuggestions();
    const uint8_t NumberOfSuggestions = _Suggestions.length();
    const uint8_t CharGroup = _SelectedTiles[STICK_LEFT];
    const uint8_t NumberSuggestionTiles = GroupsSuggestionsMap[CharGroup];
    uint8_t SuggestionTileIndex;
    QString Suggestion;
    for(uint8_t suggestionIndex = 0; suggestionIndex < NumberSuggestionTiles; suggestionIndex++){
        SuggestionTileIndex = MAX_TILE_INDEX - suggestionIndex;
        if(suggestionIndex < NumberOfSuggestions){
            Suggestion = _Suggestions[suggestionIndex];
            emit UpdateSuggestionTile(SuggestionTileIndex, Suggestion);
        }else{
            emit UpdateSuggestionTile(SuggestionTileIndex, "");
        }
    }
}

void Controller::TypeSuggestion(const uint8_t TileIndex){
    const uint8_t SuggestionIndex = MAX_TILE_INDEX - TileIndex;
    if(SuggestionIndex < _Suggestions.length()){
        QString Suggestion = _Suggestions[SuggestionIndex];
        const uint8_t BufferIndex = _Autocompleter->GetBufferIndex();
        Suggestion.remove(0, BufferIndex);
        if(_CapsLockState == true){ Suggestion = Suggestion.toUpper();}
        emit TypeToTextField(Suggestion);
        ButtonPressed(SPACE);
    }
}

void Controller::InitializeTilesContent(void){
    emit ToggleOuterSelectedTile(0);
    QueryingSuggestions();
}
