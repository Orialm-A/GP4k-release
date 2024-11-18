#ifndef TILEWIDGET_H
#define TILEWIDGET_H

#include <QWidget>
#include <QLabel>

#include "Headers/GP4k_Typedefs.h"

/**
 * @brief The TileWidget class Represents a tile on the GUI
 *
 * A Tile is uniquely a graphical component so the user know what they are about to do.
 */
class TileWidget : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief TileWidget Constructor.
     * @param Radius determine if the Tile is in the inner or outer TileGroup.
     * @param Index The index of the Tile in the TileGroup.
     * @param parent Pointer to the parent widget (optional).
     */
    explicit TileWidget(const radius_t Radius, const uint8_t Index, QWidget *parent = nullptr);

public: // Methods
    /**
     * @brief SetGeometryOnGrid place the widget in the window using the grid map instead of the pixel map.
     * @param WidgetPlacement The placement parameters of the widget.
     */
    void SetGeometryOnGrid(const placement_t WidgetPlacement);

    /**
     * @brief SetText Set the text displayed in the Tile.
     * @param NewText The text to display.
     */
    void SetText(const QString NewText);

    /**
     * @brief Set the background and available attributes of the tile accordingly to its state.
     * @param SetSelected If the tile is selected or not.
     * @param SetAvailable If the tile is available or not.
     */
    void SetBackground(bool SetSelected, bool SetAvailable);

    /**
     * @brief Availability getter.
     * @return true if the tile is available, false else.
     * @see _IsAvailable
     */
    bool GetAvailability(void) const;

    /**
     * @brief Availability setter.
     * @param IsAvailable The expected availability.
     * @see _IsAvailable
     */
    void SetAvailability(const bool IsAvailable);

private: // Attributes
    /**
     * @brief _BackgroundFile The path to the file for the background.
     * @details This path is stored as a Tile attribute so
     * there is no need to recreate it at each toggle.
     */
    QString _BackgroundFile;

    /**
     * @brief The background of the Tile.
     */
    QLabel* _Background;

    /**
     * @brief The text of the Tile.
     */
    QLabel* _Text;

    /**
     * @brief The angle of the Tile.
     * @details Necessary to set the correct rotation of the background,
     * so thep project do not require one *.svg per tile.
     */
    int _BackgroundAngle;

    /**
     * @brief indicates is the tile as available or not, i.e. if their is a character or a suggestion on it.
     */
    bool _IsAvailable;

private: // Methods
    /**
     * @brief loadBackgroundImage The method to set the background image with the correct rotation and placement.
     * @param imagePath The path to the background image.
     */
    void loadBackgroundImage(const QString imagePath);
};

#endif // TILEWIDGET_H
