/* GP4k_ButtonsMapping */

#ifndef GP4K_MAPPINGBUTTONS_H
#define GP4K_MAPPINGBUTTONS_H

#include <QString>
#include <QMap>

#include "Headers/GP4k_Typedefs.h"

/**
 * @brief Describe the type of feature used, to adapt to behavior in switchs.
 */
enum FeatureType_t{ PUNCTUATION,
                    TEXT_CONTROL,
                    WORD_CONNECTOR,
                    SHIFT_TYPE,
                    NO_CHAR_CAT
};

/**
 * @brief Describe a feature that can be triggered by a button.
 * @member
 */
struct feature_t{
    /**
     * @brief Text displayed by ButtonsGuide on GUI.
     */
    QString Text;

    /**
     * @brief The Key associated to the feature, to be sent to the text field.
     */
    Qt::Key Key;

    /**
     * @brief The type of the feature.
     */
    FeatureType_t FeatureType;

    // Define operator== as a member function
    /**
     * @brief operator ==
     * @param other The feature_t to be compared to.
     * @return True if the two features are identical, false else.
     */
    bool operator==(const feature_t& other) const {
        return (this->Text == other.Text);
    }
};

/**
 * @def color_t
 * @brief A map holding 3 colors, depending on the brand.
 */
using color_t = QMap<brand_t, QString>;

/**
 * @brief The colors associated to the button Y or equivalent on other brand controllers.
 */
inline const color_t ColorsY =  {{XBOX, "color: #FEB504;"},
                                {PLAYSTATION, "color: #40E2A0;"},
                                {NINTENDO, "color: #FFFFFF;"}};

/**
 * @brief The colors associated to the button X or equivalent on other brand controllers.
 */
inline const color_t ColorsX =  {{XBOX, "color: #009FEB;"},
                                {PLAYSTATION, "color: #FF69F8;"},
                                {NINTENDO, "color: #FFFFFF;"}};

/**
 * @brief The default white colors when a button don't have a specific color
 */
inline const color_t ColorsW =  {{XBOX, "color: #FFFFFF;"},
                                {PLAYSTATION, "color: #FFFFFF;"},
                                {NINTENDO, "color: #FFFFFF;"}};

/**
 * @brief The implemented button's feature SPACE
 */
inline const feature_t SPACE       = {"SPACE", Qt::Key_Space, TEXT_CONTROL};

/**
 * @brief The implemented button's feature BACKSPACE
 */
inline const feature_t BACKSPACE   = {"BACKSPACE", Qt::Key_Backspace, TEXT_CONTROL};

/**
 * @brief The implemented button's feature MOVE_LEFT
 */
inline const feature_t MOVE_LEFT   = {"MOVE LEFT", Qt::Key_Left, TEXT_CONTROL};

/**
 * @brief The implemented button's feature MOVE_RIGHT
 */
inline const feature_t MOVE_RIGHT  = {"MOVE RIGHT", Qt::Key_Right, TEXT_CONTROL};

/**
 * @brief The implemented button's feature SHIFT
 */
inline const feature_t SHIFT       = {"SHIFT /\nCAPSLOCK", Qt::Key_Shift, SHIFT_TYPE};


/**
 * @brief The implemented button's character COMMA ,
 */
inline const feature_t COMMA        = {"□,", Qt::Key_Comma, PUNCTUATION};

/**
 * @brief The implemented button's character PERIOD .
 */
inline const feature_t PERIOD       = {"□.", Qt::Key_Period, PUNCTUATION};

/**
 * @brief The implemented button's character EXCLAM !
 */
inline const feature_t EXCLAM       = {"□!", Qt::Key_Exclam, PUNCTUATION};

/**
 * @brief The implemented button's character QUESTION ?
 */
inline const feature_t QUESTION     = {"□?", Qt::Key_Question, PUNCTUATION};

/**
 * @brief The implemented button's character HYPHEN -
 */
inline const feature_t HYPHEN       = {"□-", Qt::Key_hyphen, WORD_CONNECTOR};

/**
 * @brief The implemented button's character APOSTROPHE '
 */
inline const feature_t APOSTROPHE   = {"□’", Qt::Key_Apostrophe, WORD_CONNECTOR};

/**
 * @brief The implemented button's character COLON :
 */
inline const feature_t COLON        = {"□:", Qt::Key_Colon, PUNCTUATION};

/**
 * @brief The implemented button's character SEMI COLON ;
 */
inline const feature_t SEMI_COLON   = {"□;", Qt::Key_Semicolon, PUNCTUATION};

/**
 * @brief The PhysicalButton_t describe what's associated to controller button
 *
 * @details The PhysicalButton_t describe what's associated to controller button.
 * It's where the code should be modified to remap a button, and the attribute
 * Features. In the Controller class, the signals are associated to PhysicalButton_t
 * instances to make the code independant of the remappings here.
 */
struct PhysicalButton_t{
    /**
     * @brief Features associated to this button.
     */
    QVector<feature_t> Features;

    /**
     * @brief The colors associated to this button on the 3 controllers.
     */
    color_t Colors;

    /**
     * @brief The name of the icon of this button, used to retrieve the svg file.
     */
    QString IconName;

    /**
     * @brief Describe where the label is placed compared to the icon on the GUI.
     */
    LabelPosition_t LabelPosition;
};


/* ------------------ User code starts here  ------------------
 * To remap a Button, change the assigned Feature by swapping
 * features in the FIRST and SECOND columns.
 * Available Features are:
 *  - BACKSPACE
 *  - SPACE
 *  - MOVE_LEFT
 *  - MOVE_RIGHT
 *  - SHIFT
 *  - COMMA
 *  - PERIOD
 *  - EXCLAM
 *  - QUESTION
 *  - APOSTROPHE
 *  - HYPHEN
 *  - SEMI_COLON
 *  - COLON
 *  The name of the buttons are those used
 *  Qt signals and visible on the Xbox          These columns
 *  Controller.                           |-----------------------|
 *                                        |   FIRST      SECOND   |
 *                                        |-----------|-----------|           */
inline const PhysicalButton_t Button_X  ={{BACKSPACE , BACKSPACE  }, ColorsX, "X", LABEL_LEFT};
inline const PhysicalButton_t Button_Y  ={{SPACE     , SPACE      }, ColorsY, "Y", LABEL_TOP};
inline const PhysicalButton_t Button_LB ={{MOVE_LEFT , MOVE_LEFT  }, ColorsW, "LB", LABEL_LEFT};
inline const PhysicalButton_t Button_RB ={{MOVE_RIGHT, MOVE_RIGHT }, ColorsW, "RB", LABEL_RIGHT};
inline const PhysicalButton_t Button_LT ={{SHIFT     , SHIFT      }, ColorsW, "LT", LABEL_RIGHT};
inline const PhysicalButton_t Dpad_UP   ={{COMMA      , PERIOD    }, ColorsW, "UP", LABEL_TOP};
inline const PhysicalButton_t Dpad_DOWN ={{EXCLAM     , QUESTION  }, ColorsW, "DOWN", LABEL_BOTTOM};
inline const PhysicalButton_t Dpad_LEFT ={{APOSTROPHE , HYPHEN    }, ColorsW, "LEFT", LABEL_LEFT};
inline const PhysicalButton_t Dpad_RIGHT={{SEMI_COLON , COLON     }, ColorsW, "RIGHT", LABEL_RIGHT};

/* ------------------ User code ends here ------------------ */



#endif // GP4K_MAPPINGBUTTONS_H
