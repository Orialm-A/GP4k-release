#ifndef GP4K_GUIMAPPING_H
#define GP4K_GUIMAPPING_H

#include <QString>
#include <QMap>
#include <QVector>

#include "Headers/GP4k_Typedefs.h"

/* ------------------ User code starts here  ------------------
 * Some elements on the GUI can be remapped by modifying the values
 * in this section. Please do not change elements out this "User Code"
 * section or I can't guaranty all the elements will display as expected.
 */

/**
 * @def CELL_SIZE
 * @brief Defines placements for UI elements in a cell-based grid system.
 * @details Positions and sizes of all components are based on an integer grid from Figma.
 * CELL_SIZE is the size of one grid cell. WINDOW_SIZE_X and WINDOW_SIZE_Y are
 * calculated based on this CELL_SIZE and are used to set the window size.
 * @default 28
 */
#define CELL_SIZE 20

/**
 * @def GLOBAL_FONT_SIZE
 * @brief Defines the font size used for the whole project.
 * @default CELL_SIZE * 6/10
 */
#define GLOBAL_FONT_SIZE CELL_SIZE * 6/10

/**
 * @def GLOBAL_FONT
 * @brief Defines the font used for the whole project.
 * @default "Raleway"
 */
#define GLOBAL_FONT "Raleway"

/**
 * @brief Defines the positions and size of all the the elements on the GUI.
 * @details This solution was prefered so the GUI can easily
 * be modified from an unique location. The numbers in it comes
 * from the grid layout drawn in Figma.
 * @note The default values are written in comment on each line.
 * The values are: Horizontal position, vertical position, horizontal size, vertical size.
 * All of the GUI (the window and the elements) are positioned relatively to their top left corner.
 */
/* ------------------ User code ends here ------------------ */

inline const QMap<QString, placement_t> Placements{
    {"TextField", {0, 0, 60, 4}}, // Default: {0, 0, 60, 4}
    {"OuterTileGroup", {15, 4, 30, 30}}, // Default: {15, 4, 30, 30}
    {"InnerTileGroup", {21, 10, 18, 18}}, // Default: {21, 10, 18, 18}
    {"X", {42, 22, 8, 2}}, // Default: {42, 22, 8, 2}
    {"Y", {48, 18, 6, 4}}, // Default: {48, 18, 6, 4}
    {"LB", {22, 4, 8, 2}}, // Default: {22, 4, 8, 2}
    {"RB", {30, 4, 8, 2}}, // Default: {30, 4, 8, 2}
    {"LT", {0, 4, 8, 2}}, // Default: {0, 4, 8, 2}
    {"UP", {6, 18, 6, 4}}, // Default: {6, 18, 6, 4}
    {"DOWN", {6, 24, 6, 4}}, // Default: {6, 24, 6, 4}
    {"LEFT", {0, 22, 8, 2}}, // Default: {0, 22, 8, 2}
    {"RIGHT", {10, 22, 8, 2}}, // Default: {10, 22, 8, 2}
    {"DpadCenter", {8, 22, 2, 2}}, // Default: {8, 22, 2, 2}
    {"Sticks", {27, 17, 6, 3}} // Default: {27, 17, 6, 3}
};

/**
 * @def WINDOW_SIZE_X
 * @brief Define the window's length in a cell-based grid system.
 *
 * @details WINDOW_SIZE_X is calculated based on the CELL_SIZE. The factors 60
 * comes from the Figma design and should not be changed.
 */
#define WINDOW_SIZE_X CELL_SIZE*60

/**
 * @def WINDOW_SIZE_Y
 * @brief Define the window's height in a cell-based grid system.
 *
 * @details WINDOW_SIZE_Y is calculated based on the CELL_SIZE. The factors 34
 * comes from the Figma design and should not be changed.
 */
#define WINDOW_SIZE_Y CELL_SIZE*34

/**
 * @def BUTTONS_GUIDE_HEIGHT
 * @brief The default Height of a Guide on the GUI.
 */
#define BUTTONS_GUIDE_HEIGHT 4

/**
 * @def BUTTONS_GUIDE_WIDTH
 * @brief The default width of a Guide on the GUI.
 */
#define BUTTONS_GUIDE_WIDTH 8

/**
 * @brief Hold the positions of the tiles relatively to their TileGroup's origin
 */
const inline QMap<radius_t, QVector<placement_t>> TileGroupsPlacements = {
    {INNER, {
                   { 0,  6,  6,  6},
                   { 2,  2,  6,  6},
                   { 6,  0,  6,  6},
                   {10,  2,  6,  6},
                   {12,  6,  6,  6},
                   {10, 10,  6,  6},
                   { 6, 12,  6,  6},
                   { 2, 10,  6,  6}
               }
    },
    {OUTER, {
                   { 0, 10, 10, 10},
                   { 3,  3,  9,  9},
                   {10,  0, 10, 10},
                   {18,  3,  9,  9},
                   {20, 10, 10, 10},
                   {18, 18,  9,  9},
                   {10, 20, 10, 10},
                   { 3, 18,  9,  9}
               }
    }
};

#endif // GP4K_GUIMAPPING_H
