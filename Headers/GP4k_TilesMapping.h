#ifndef GP4K_TILESMAPPING_H
#define GP4K_TILESMAPPING_H

#include <QVector>
#include <QString>
#include <QMap>

/**
 * @def EUR
 * @brief Unicode for €, as not present in the default Qt::Key enum.
 */
#define EUR 0x20ACU



/**
 * @def CharGroup_t
 * @brief define a group of characters to be displayed by the 8 tiles of a group.
 */
using CharGroup_t = QVector<QString>;

/* ------------------ User code starts here  ------------------
 * The characters associated to each tile can be switched here.
 * Be careful while modifying this file: There is no "protection"
 * preserving you from forgetting a character.
 * It's advised to modify this file only after running
 * `Python/Generating_Disposition/` scripts.
 */

/**
 * @brief The collection of char groups for the inner tiles.
 * @details a chargroup is selected with [ShiftKeyState][CharGroupIndex]
 * where ShiftKeyState and CharGroupIndex defined by the Controller at
 * runtime. A function requiring a chargroup will use it with a loop iterating
 * over it.
 */
inline const QVector<QVector<CharGroup_t>> InnerTilesChars = {
    { // NOT_SHIFTED
        {"t", "r", "s", "h", "e", "a"},
        {"q", "f", "l", "k", "b"},
        {"z", "g", "v", "x", "j"},
        {"o", "c", "i", "n", "d"},
        {"p", "u", "m", "w", "y"},
        {"1", "2", "3", "4", "5", "+", "/", "="},
        {"€", "#", "%", "&", "(", "[", "{", "<"},
        {"☺️", "☹️", "♥️", "✌️", "✨", "☀️", "☁️", "☕"},
     },
    { // SHIFTED
        {"T", "R", "S", "H", "E", "A"},
        {"Q", "F", "L", "K", "B"},
        {"Z", "G", "V", "X", "J"},
        {"O", "C", "I", "N", "D"},
        {"P", "U", "M", "W", "Y"},
        {"6", "7", "8", "9", "0", "\"","\\", "*"},
        {"$", "@", "^", "_", ")", "]", "}", ">"},
        {"☺️", "☹️", "♥️", "✌️", "✨", "☀️", "☁️", "☕"}
    }
};

/**
 * @brief The collection of char groups for the outer tiles.
 * @details a chargroup is selected with [ShiftKeyState]
 * where ShiftKeyState and CharGroupIndex defined by the Controller at
 * runtime. A function requiring a chargroup will use it with a loop iterating
 * over it.
 */
inline const QVector<CharGroup_t> OuterTilesTexts ={

    { // NOT_SHIFTED
        "t r s h e a",
         "q f l k b",
         "z g v x j",
         "o c i n d",
         "p u m w y",
         "1 2 3 + / =",
         "€ # ( ...",
         "emotes",
    },
    { // SHIFTED
        "T R S H E A",
         "Q F L K B",
         "Z G V X J",
         "O C I N D",
         "P U M W Y",
         "6 7 8 \" \\ *",
         "$ @ ) ...",
         "EMOTES"
    }

};

/**
 * @brief Defines the number of suggestion tiles of each different inner tile group.
 */
inline const QVector<uint8_t> GroupsSuggestionsMap = {2, 3, 3, 3, 3, 0, 0, 0};

/* ------------------ User code ends here ------------------ */

#endif // GP4K_TILESMAPPING_H
