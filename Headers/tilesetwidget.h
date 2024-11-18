/* tilesetwidget.h */
#ifndef TILESETWIDGET_H
#define TILESETWIDGET_H

#include "tilewidget.h"
#include "charsetcollections.h"
#include "typedefs.h"

#include <QWidget>
#include <QVector>

/**
 * @brief Graphical representation of the separation in 8 angles of a joystick.
 *
 * This class represents a set of tiles, each managed by a TileWidget.
 * It manages the visual display of tiles and updates their background
 * and characters dynamically based on user input.
 */
class TileSetWidget : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Constructor for TileSetWidget
     *
     * Initializes the tile set with the given character set, position, and size.
     *
     * @param letters The character set for the tiles.
     * @param position_X X coordinate for the tile set.
     * @param position_Y Y coordinate for the tile set.
     * @param size The size of the tile set.
     * @param parent Pointer to the parent widget (optional).
     */
    explicit TileSetWidget(charset_t letters, int position_X, int position_Y, int size, QWidget *parent = nullptr);

public slots:
    /**
     * @brief Changes the background of a tile based on its index.
     *
     * @param Index The index of the tile to be updated.
     */
    void TileSet_ChangeTileBackground(uint8_t Index);

    /**
     * @brief Changes the characters displayed on the tiles.
     *
     * @param Index The index corresponding to the new character set.
     */
    void TileSet_ChangeTilesChar(uint8_t Index, buttonState_t caps);

signals:
         // Define any signals if necessary in the future.

private:
    /**
     * @brief A vector containing pointers to each tile widget in the set.
     */
    QVector<TileWidget*> TileSet_Tiles;

    /**
     * @brief The set of characters currently displayed on the tiles.
     */
    QVector<QString> TileSet_Letters;

    /**
     * @brief The index of the currently selected tile.
     */
    uint8_t TileSet_SelectedTile;
};

#endif // TILESETWIDGET_H
