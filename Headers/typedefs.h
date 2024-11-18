#ifndef TYPEDEFS_H
#define TYPEDEFS_H

/* This file is meant only for typedefs that could lead to recursive includes.
 * For example: buttonState_t defined in controller.h, a file inlcluding
 * tilesetwidget.h, but tilesetwidget.h also include controller.h to use
 * buttonState_t.
 * If this issue doesn't occur, keep the typedefs in the files they are used.
 */

#include <cstdint>

/**
 * @brief Represent the state of a button.
 *
 * Meant to cast from double values (from QGamepad::buttonXChanged as instance) to a more pertinent info about the state
 * of a button. The value 8 for PRESSED is not random: it's meant to be used as an offset in CharSet Collections for
 * caps characters. This collection is 8+8 length (8 caps off / 8 caps on), so for a given position, adding the offset
 * PRESSED will allow to use use caps characters.
 */
enum controller_buttons_state : uint8_t { PRESSED = 8, RELEASED = 0 };
using buttonState_t = controller_buttons_state;

#endif // TYPEDEFS_H
