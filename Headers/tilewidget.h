/* tilewidget.h */
#ifndef TILEWIDGET_H
#define TILEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>

#define NUMBER_OF_TILES 8U

/**
 * @brief Graphical representation of a tile.
 * @relatesalso TileSetWidget
 *
 * This class represents an individual tile in the tile set. A tile is selected depending on the angle of the joysyick. These graphical representations are used to let the user know which character they're about to type.
 */
class TileWidget : public QWidget
{
    friend class TileSetWidget; /**< TileSetWidget can access private members of TileWidget */
    Q_OBJECT

public:
    /**
     * @brief Constructor for TileWidget
     *
     * Initializes a tile with the specified size, index, background image, and text.
     *
     * @param default_size The size of the tile.
     * @param index The index of the tile in the set.
     * @param tile_image The background image for the tile.
     * @param text The text displayed on the tile.
     * @param parent Pointer to the parent widget (optional).
     */
    explicit TileWidget(
        const int default_size,
        const uint8_t index,
        const QPixmap &tile_image,
        const QString &text,
        QWidget *parent);

    /**
     * @brief Updates the character displayed on the tile.
     *
     * @param UpdatedChar The new character to display.
     */
    void TileWidget_char_SET(QString UpdatedChar);

private:
    /**
     * @brief Label for displaying the background image.
     */
    QLabel *Tile_Background;

    /**
     * @brief Label for displaying the text on the tile.
     */
    QLabel *Tile_Text;

    /**
     * @brief The index of the tile in the set.
     */
    uint8_t Tile_Index;

    /**
     * @brief The X position of the tile.
     */
    double Tile_PositionX;

    /**
     * @brief The Y position of the tile.
     */
    double Tile_PositionY;

    /**
     * @brief The angle at which the tile is rotated.
     */
    uint16_t Tile_Angle;

    /**
     * @brief The size of the tile.
     */
    double Tile_Size;

    /**
     * @brief Updates the background image with rotation applied.
     *
     * @param pixmap The new background image.
     */
    void Tile_ChangeTileBackground(const QPixmap &pixmap);
};

#endif // TILEWIDGET_H
