/* Controller.h */

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QtGamepad/QGamepad>
#include <QVector>
#include <QWidget>
#include <QTextEdit>
#include <QMap>

#include "Headers/Autocomplete.h"
#include "Headers/GP4k_ButtonsMapping.h"
#include "Headers/GP4k_Typedefs.h"

/**
 * @brief Represents the joysticks on the gamepad.
 */
enum stick_t {
    STICK_LEFT,
    STICK_RIGHT
};

/**
 * @brief describe if a stick is at the border or not.
 */
enum StickPosition_t : uint8_t{
    CENTER = 0,
    BORDER = 1
};

/**
 * @brief Represents the axes of a joystick.
 */
enum axis_t { X_AXIS, Y_AXIS };

/**
 * @brief The Controller class handles gamepad input.
 *
 * This class is responsible for handling input from a gamepad, tracking joystick positions,
 * calculating angles and tile selections, and updating elements on the GUI.
 */
class Controller : public QWidget
{
    Q_OBJECT

signals:
    /**
     * @brief Signal emitted to set the background of an outer tile.
     * @param Tile The index of the tile in its group.
     */
    void ToggleOuterSelectedTile(uint8_t Tile);

    /**
     * @brief Signal emitted to set the background of an inner tile.
     * @param Tile The index of the tile in its group.
     */
    void ToggleInnerSelectedTile(uint8_t Tile);

    /**
     * @brief Signal emitted to
     * @param Index The Index of the character set to switch to for the right TileGroup.
     * @param Caps The offset to use caps or not.
     */

    /**
     * @brief Signal emitted to change the characters of the inner tile group.
     * @param ShiftKey the state of the shift key.
     * @param CharGroup Index of the selected char group.
     */
    void UpdateInnerTiles(ShiftState_t ShiftKey, uint8_t CharGroup);

    /**
     * @brief Signal emitted to change the suggestions tiles status.
     * @param TileIndex The index of the suggestion tile.
     * @param Suggestion The suggestion to display, or "" if no suggestion.
     */
    void UpdateSuggestionTile(uint8_t TileIndex, QString Suggestion);

    /**
     * @brief Signal emitted to make all the tiles of inner group available and unselected.
     */
    void ResetCenterBackgrounds(void);

    /**
     * @brief Signal emitted to type a character in the text field.
     * @param Text The character to type.
     */
    void TypeToTextField(QString Text);

    /**
     * @brief Signal emitted to send special instructions to the text field, such as moving the cursor.
     * @param Key The key associated to this instruction.
     */
    void SendOrderToTextField(Qt::Key Key);

    /**
     * @brief Signal emitted to switch all concerned text on the UI depending on the shift state.
     * @param ShiftKey the state of the Shift Key.
     * @param CharGroup the current char group. Only the inner tile group use this parameter.
     */
    void ToggleTextsOnShift(ShiftState_t ShiftKey, uint8_t CharGroup);

public: // Methods
    /**
     * @brief Constructor for the Controller class.
     */
    explicit Controller(QWidget *parent = nullptr);

    /**
     * @brief Getter for the controller brand.
     * @return the controller brand.
     */
    brand_t GetBrand(void) const;

    /**
     * @brief forces the GUI to be coherent at initialization.
     *
     * @details forces the GUI to be coherent at initialization:
     * - First CharGroup selected on the outer TileGroup
     * - Suggestions Tiles blacken
     */
    void InitializeTilesContent(void);

private: // Methods
    /**
     * @brief Checks if the connected gamepad is in the forbidden controllers list.
     * @param controllerName Name of the gamepad.
     * @return False if the controller is in the forbidden list, true else.
     * @see _ForbiddenControllers
     *
     * @todo Rework it to automatically detect if a controller has 2 sticks and the 12 buttons.
     */
    bool IsItAllowed(const QString &controllerName) const;

    /**
     * @brief Determine the brand of the Controller.
     * @param controllerName Name of the gamepad.
     * @return The brand of the controller.
     */
    brand_t WhatsTheBrand(const QString &controllerName) const;

    /**
     * @brief Try to autodetect the controller brand by seeking for keywords.
     * @param controllerName Name of the gamepad.
     * @return The detected brand of the controller, or Xbox as default.
     */
    brand_t ControllerBrandAutodetect(const QString &controllerName) const;

    /**
     * @brief Set the letter to send to the text field.
     * @param CharTileIndex The char tile selected.
     * @param CharGroup The current char group.
     */
    void CharTileSelected(uint8_t CharTileIndex, uint8_t CharGroup);

    /**
     * @brief Send the selected suggestion to the TextField.
     * @param TileIndex The index of the selected tile.
     */
    void TypeSuggestion(uint8_t TileIndex);

    /**
     * @brief Updates the axis value when the joystick is moved.
     * @param joystick The joystick that triggered the update.
     * @param Axis Which axis (X or Y) is updated.
     * @param AxisValue New value of the axis.
     */
    void UpdateAxis(stick_t Joystick, axis_t Axis, double AxisValue);

    /**
     * @brief Updates the radius when the joystick is moved.
     * @param joystick The joystick that triggered the update.
     */
    void UpdateRadius(stick_t Joystick);

    /**
     * @brief Helper function to determine if the stick is at the border or not.
     * @param Stick The stick that triggered the update.
     * @return The narmalized Radius.
     */
    StickPosition_t NormalizeRadius(const stick_t Stick) const;

    /**
     * @brief Dispatcher function on stick releases.
     * @param NewRadius The newer to radius, to be compared to the current one.
     * @param Stick The stick that triggered the update.
     */
    void StickReleased(const StickPosition_t NewRadius, const stick_t Stick);

    /**
     * @brief Updates the angle of the joystick.
     * @param joystick The joystick that triggered the update.
     */
    void UpdateAngle(stick_t Joystick);

    /**
     * @brief Updates the selected tile based on the joystick's position.
     * @param joystick The joystick that triggered the update.
     */
    void UpdateSelectedTile(stick_t Joystick);

    /**
     * @brief Handle presses on analog buttons such as X or L1
     * @param Feature The feature_t triggered on button press.
     * @param State The State of the button (SHIFTED or NOT_SHIFTED).
     *
     * @details Signals are not the same for Xbox and Playstation Controller :
     *
     *  On Xbox controller:
     *  ------------------
     *
     *                                 Y --> QGamepad::buttonYChanged
     *  QGamepad::buttonXChanged <-- X   B --> QGamepad::buttonBChanged
     *                                 A --> QGamepad::buttonAChanged
     *
     * On Playstation controller:
     * -------------------------
     *
     *                                 △ --> QGamepad::buttonXChanged
     *  QGamepad::buttonYChanged <-- □   ○ -->
     *                                 ⨉ -->
     *
     * The reason is unknown, but the consequence is that pressing □ on
     * Dualsense will trigger the same behaviour than pressing Y on Xbox
     * controller.
     * The conditions in the `connect` Statement are here to prevent this,
     * and ensure that pressing the "top button" will trigger the same
     * behaviour whatever the brand is.
     */
    void ButtonPressed(const feature_t Features, double ButtonValue = 0.0);

    /**
     * @brief Requires an update of the autocompleter.
     * @param The Qt::Key that triggered this update.
     * @param The text to add to the autocompleter buffer, if pertinent.
     */
    void AutocompleterUpdate(Qt::Key Key, QString Text);

    /**
     * @brief Handler for shift button event.
     */
    void ShiftButton(void);

    /**
     * @brief Emits the event to type a char in the text field and call ToggleShift.
     * @param Letter the letter to type.
     */
    void TypeChar(QString Letter);

    /**
     * @brief Toggles the state if the shift key dependingly on the caps lock state.
     */
    void ToggleShift(void);

    /**
     * @brief Asks the Autocompleter for suggestions and updates the suggestion tiles.
     */
    void QueryingSuggestions(void);

private: // Attributes
    /**
     * @brief List of forbidden controllers.
     * @todo Add a menu to select the desired controller.
     *
     * @details It's meant to exclude non-pertinent devices recognized
     * as controller, such as the ASUS ROG Chakram. I found nothing to
     * automatically filter unadapted controllers.
     */
    const QMap<QString, brand_t> _TestedControllers = {
        {"Microsoft X-Box One S pad", XBOX},
        {"Sony Interactive Entertainment DualSense Wireless Controller", PLAYSTATION},
        {"Nintendo Co., Ltd. Pro Controller", NINTENDO}
    };

    /**
     * @brief List of forbidden controllers.
     * @todo Add a menu to select the desired controller.
     *
     * @details It's meant to exclude non-pertinent devices recognized
     * as controller, such as the ASUS ROG Chakram. I found nothing to
     * automatically filter unadapted controllers.
     */
    const QVector<QString> _ForbiddenControllers = {
        "ASUSTeK ROG CHAKRAM"
    };

    /**
     * @brief Pointer to the selected controller among the one physically connected.
     */
    QGamepad *_SelectedController;

    /**
     * @brief Stores the selected controller's brand.
     */
    brand_t _Brand;

    /**
     * @brief Stores current positions of the joysticks.
     *
     * 2*2 QVector, Indexed with [stick_t][axis_t].
     */
    QVector<QVector<double>> _AxisPosition;

    /**
     * @brief Stores the angle of the joysticks.
     *
     * 2*1 QVector, Indexed with [stick_t].
     */
    QVector<double> _Angles;

    /**
     * @brief Stores the radius of the joysticks.
     *
     * 2*1 QVector, Indexed with [stick_t].
     */
    QVector<double> _Radius;

    /**
     * @brief Stores the Index of the selected tile of the joysticks.
     *
     * 2*1 QVector, Indexed with [stick_t].
     */
    QVector<uint8_t> _SelectedTiles;

    /**
     * @brief Stores the State of the SHIFT key for upper or lower case.
     */
    ShiftState_t _ShiftKeyState;

    /**
     * @brief Stores the current State of the capslock key.
     */
    bool _CapsLockState;

    /**
     * @brief The controller's instance of Autocomplete.
     */
    Autocomplete* _Autocompleter;

    /**
     * @brief Holds the words suggested by autocompleter.
     */
    QVector<QString> _Suggestions;

};

#endif // CONTROLLER_H
