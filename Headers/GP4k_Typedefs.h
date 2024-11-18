#ifndef GP4K_TYPEDEFS_H
#define GP4K_TYPEDEFS_H

/* This file is meant only for typedefs that are used by several files, to avoid including a whole class declaration
 * and potential recursive includes, when only a typedef is required; If a typedef is used by an unique class, keep
 * it in its header.
 */

#include <QString>
#include <QMap>

/**
 * @brief Represent the state of a button.
 *
 * Meant to cast from double values (from QGamepad::buttonXChanged as instance) to a more pertinent info about the state
 * of a button. The value 8 for SHIFTED is not random: it's meant to be used as an offset in CharSet Collections for
 * caps characters. This collection is 8+8 length (8 caps off / 8 caps on), so for a given position, adding the offset
 * SHIFTED will allow to use use caps characters.
 */
enum ShiftState_t { NOT_SHIFTED, SHIFTED };

/**
 * @brief Structure holding position and size data of a widget
 *
 * Holds the X and Y coordinates, and the width (SizeX) and heigth (Size Y)
 * of a widget.
 */
struct placement_t {
    int X;
    int Y;
    int SizeX;
    int SizeY;
};

/**
 * @brief Enum holding the two possible radius for a tile
 */
enum radius_t {INNER, OUTER};

/**
 * @brief Represent the manufacturer of the gamepads.
 */
enum brand_t { XBOX, PLAYSTATION, NINTENDO};

/**
 * @brief Represents the two only possible order for the icon and the label in a GuideWidget.
 */
enum LabelPosition_t { LABEL_TOP, LABEL_BOTTOM, LABEL_RIGHT, LABEL_LEFT};

#define DEFAULT_TILE 9U
#endif // GP4K_TYPEDEFS_H
