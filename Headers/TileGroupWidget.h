#ifndef TILEGROUPWIDGET_H
#define TILEGROUPWIDGET_H

#include <QWidget>
#include <QVector>

#include "Headers/TileWidget.h"

#define NUMBER_OF_TILES 8U
#define MAX_TILE_INDEX NUMBER_OF_TILES - 1U

/**
 * @brief The TileGroupWidget class Holds the TileGroups displayed on the GUI
 *
 * @details A Tile group is a group of 8 tiles controlled by a given joystick. The association
 * to a joystick is don and the controller level.
 */
class TileGroupWidget : public QWidget
{
    Q_OBJECT
public: // Methods
    /**
     * @brief TileGroupWidget Constructor
     * @param Radius Indicate if the TileGroup is the inner or outer TileGroup.
     * @param parent Pointer to the parent widget (optional).
     * @details Radius is not supposed to be used when creating a TileGroup in mainwindow.cpp
     * It's used to specify if it's a outer or inner tile group. InnerTileGroup inherits from
     * TileGroup, and calls the TileGroup constructor with `Radius = INNER`: A developer should
     * invoke TileGroupWidget for outer tile group and InnerTileGroupWidget for...
     */
    explicit TileGroupWidget(radius_t Radius, QWidget *parent = nullptr);

    /**
     * @brief SetGeometryOnGrid place the widget in the window using the grid map instead of the pixel map.
     * @param WidgetPlacement The placement parameters of the widget.
     */
    void SetGeometryOnGrid(placement_t WidgetPlacement);

    /**
     * @brief This empty function is only meant to force TileGroupWidget to be a pure virtual class.
     */
    virtual void Empty(void) = 0;

public slots:
    /**
     * @brief Update the selected tile of the group.
     * @param TileIndex The index of the tile to be updated.
     */
    void SetTileSelected(uint8_t TileIndex);

    /**
     * @brief Changes the characters displayed on the tiles.
     *
     * @param CharSetIndex The index corresponding to the new character set.
     * @param SHIFT The current state of the SHIFT button, to use or not uppercase.
     */
    void SetTileText(ShiftState_t Shift);

protected: // Atributes
    /**
     * @brief A vector containing pointers to each tile widget in the Group.
     */
    QVector<TileWidget*> _Tiles;

    /**
     * @brief The index of the currently selected tile.
     */
    uint8_t _SelectedTile;
};


/* -------------------------------------------------------------- */


/**
 * @brief The child class of TileGroupWidget to handle its specificities.
 * @details This class extends TileGroupWidget to provide additional functionality
 * that are only related to the inner tile group, such as `ResetTiles` methods.
 * @see TileGroupWidget OuterTileGroupWidget
 */
class InnerTileGroupWidget : public TileGroupWidget{
    Q_OBJECT
public: // Methods
    /**
     * @brief InnerTileGroupWidget Constructor
     * @param parent Pointer to the parent widget (optional).
     */
    explicit InnerTileGroupWidget(QWidget *parent = nullptr);

public slots:
    /**
     * @brief Slot used to update a suggestion tile in the group.
     * @param TileIndex The index of the concerned suggestion tile.
     * @param Suggestion The suggestion to display. "" if no suggestion, so the background will be set to unavailable.
     */
    void SetSuggestionTile(const uint8_t TileIndex, const QString Suggestion);

    /**
     * @brief ResetTiles of the inner group.
     * @details Make all tiles of the inner group available and unselected.
     */
    void ResetTiles(void);

    /**
     * @brief Change the chars displayed in each tile of the group.
     * @param SHIFT The state the shift key to select lower or upper case characters.
     * @param CharGroupIndex The index of the char group to be displayed.
     */
    void SetTileText(const ShiftState_t SHIFT, const uint8_t CharGroupIndex);

private: // methods
    /**
     * @brief Make a tile available or not.
     * @param TileIndex The index of the concerned tile.
     * @param IsAvailable The expected state of the tile.
     */
    void SetTileAvailability(uint8_t TileIndex, bool IsAvailable);

    /**
     * @brief This empty function is only meant to force TileGroupWidget to be a pure virtual class.
     */
    void Empty(void);
};


/* -------------------------------------------------------------- */


/**
 * @brief The child class of TileGroupWidget for outer tile groups.
 * @details This class does not extends TileGroupWidget to provide
 * coherency when creating tiles groups on the GUI: Invoke OuterTileGroupWidget
 * or InnerTileGroupWidget only.
 * @see TileGroupWidget InnerTileGroupWidget
 */
class OuterTileGroupWidget : public TileGroupWidget{
public: // Methods
    /**
     * @brief OuterTileGroupWidget Constructor
     * @param parent Pointer to the parent widget (optional).
     */
    explicit OuterTileGroupWidget(QWidget *parent = nullptr);

private:
    /**
     * @brief This empty function is only meant to force TileGroupWidget to be a pure virtual class.
     */
    void Empty(void);
};
#endif // TILEGROUPWIDGET_H
