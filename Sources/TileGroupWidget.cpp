#include <QDebug>

#include "Headers/TileGroupWidget.h"
#include "Headers/GP4k_GuiMapping.h"
#include "Headers/GP4k_Typedefs.h"
#include "Headers/GP4k_TilesMapping.h"

TileGroupWidget::TileGroupWidget(radius_t Radius, QWidget *parent)
    : QWidget{parent}
    , _SelectedTile(DEFAULT_TILE)
{
    for(uint8_t Position = 0; Position < NUMBER_OF_TILES; Position++){
        _Tiles.append(new TileWidget(Radius, Position, this));
        _Tiles[Position]->SetGeometryOnGrid(TileGroupsPlacements[Radius][Position]);
    }
}

void TileGroupWidget::SetGeometryOnGrid(placement_t WidgetPlacement)
{
    int X = WidgetPlacement.X*CELL_SIZE;
    int Y = WidgetPlacement.Y*CELL_SIZE;
    int SizeX = WidgetPlacement.SizeX*CELL_SIZE;
    int SizeY = WidgetPlacement.SizeY*CELL_SIZE;
    QWidget::setGeometry(X, Y, SizeX, SizeY);
}

void TileGroupWidget::SetTileSelected(uint8_t TileIndex){
    bool IsAvailable;
    if(_SelectedTile != DEFAULT_TILE ){
        IsAvailable = _Tiles[_SelectedTile]->GetAvailability();
        _Tiles[_SelectedTile]->SetBackground(false, IsAvailable);
    }
    if(TileIndex != DEFAULT_TILE ){
        IsAvailable = _Tiles[TileIndex]->GetAvailability();
        _Tiles[TileIndex]->SetBackground(true, IsAvailable);
    }
    _SelectedTile = TileIndex;
}

void TileGroupWidget::SetTileText(ShiftState_t SHIFT){
    const CharGroup_t NewCharSet = OuterTilesTexts[SHIFT];
    const uint8_t NumberOfTexts = NewCharSet.length();
    QString NewText;
    for(int TileIndex = 0; TileIndex < NumberOfTexts; TileIndex++){
        NewText = NewCharSet[TileIndex];
        _Tiles[TileIndex]->SetText(NewText);
    }
}


/* -------------------------------------------------------------- */


InnerTileGroupWidget::InnerTileGroupWidget(QWidget *parent)
    : TileGroupWidget(INNER, parent)
{

}

void InnerTileGroupWidget::SetSuggestionTile(const uint8_t TileIndex, const QString Suggestion){
    _Tiles[TileIndex]->SetText(Suggestion);
    const bool IsAvailable = (Suggestion == "") ? false : true;
    SetTileAvailability(TileIndex, IsAvailable);
}


void InnerTileGroupWidget::ResetTiles(){
    for(uint8_t i = 0; i < NUMBER_OF_TILES; i++){
        _Tiles[i]->SetBackground(false, true);
        _Tiles[i]->SetAvailability(true);
    }
}

void InnerTileGroupWidget::SetTileAvailability(uint8_t TileIndex, bool IsAvailable){
    _Tiles[TileIndex]->SetAvailability(IsAvailable);
    _Tiles[TileIndex]->SetBackground(false, IsAvailable);
}

void InnerTileGroupWidget::SetTileText(const ShiftState_t SHIFT, const uint8_t CharGroupIndex){
    const CharGroup_t NewCharSet = InnerTilesChars[SHIFT][CharGroupIndex];
    const uint8_t NumberOfTexts = NewCharSet.length();
    QString NewText;
    for(int TileIndex = 0; TileIndex < NumberOfTexts; TileIndex++){
        NewText = NewCharSet[TileIndex];
        _Tiles[TileIndex]->SetText(NewText);
    }
}

void InnerTileGroupWidget::Empty(void){
    // The implementation remains empty, as suggested by the name.
}

/* -------------------------------------------------------------- */

OuterTileGroupWidget::OuterTileGroupWidget(QWidget *parent)
    : TileGroupWidget(OUTER, parent)
{

}

void OuterTileGroupWidget::Empty(void){
    // The implementation remains empty, as suggested by the name.
}
