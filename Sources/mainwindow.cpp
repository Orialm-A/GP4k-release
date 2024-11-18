#include "Headers/mainwindow.h"
#include "Headers/Controller.h"
#include "Headers/GP4k_Typedefs.h"
#include "Headers/GuideWidget.h"

#include "Headers/TileGroupWidget.h"
#include "Headers/TextFieldWidget.h"
#include "Headers/ImageWidget.h"
#include "Headers/GP4k_GuiMapping.h"
#include "Headers/GP4k_ButtonsMapping.h"

#include <QFrame>
#include <QVector>
#include <QTextEdit>
#include <QMap>
#include <QString>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setMinimumSize(WINDOW_SIZE_X, WINDOW_SIZE_Y);
    setMaximumSize(WINDOW_SIZE_X, WINDOW_SIZE_Y);

    Controller* GP4k_Controller = new Controller(this);
    const brand_t ControllerBrand = GP4k_Controller->GetBrand();

    ImageWidget* Sticks = new ImageWidget(":/Resources/Icons/Sticks.svg", this);
    TileGroupWidget* OuterTileGroup = new OuterTileGroupWidget(this);
    InnerTileGroupWidget* InnerTileGroup = new InnerTileGroupWidget(this);
    QTextEditCustom* TextField = new QTextEditCustom(this);
    QVector<GuideWidget*> ButtonsGuides = {
        new GuideWidget(&Button_Y, ControllerBrand, this),
        new GuideWidget(&Button_X, ControllerBrand, this),
        new GuideWidget(&Button_LB, ControllerBrand, this),
        new GuideWidget(&Button_RB, ControllerBrand, this),
        new GuideWidget(&Button_LT, ControllerBrand, this),
        new GuideWidget(&Dpad_UP, ControllerBrand, this),
        new GuideWidget(&Dpad_DOWN, ControllerBrand, this),
        new GuideWidget(&Dpad_LEFT, ControllerBrand, this),
        new GuideWidget(&Dpad_RIGHT, ControllerBrand, this)
    };

    InnerTileGroup->SetGeometryOnGrid(Placements["InnerTileGroup"]);
    OuterTileGroup->SetGeometryOnGrid(Placements["OuterTileGroup"]);
    TextField->SetGeometryOnGrid(Placements["TextField"]);
    Sticks->SetGeometryOnGrid(Placements["Sticks"]);
    for (auto& Guide : ButtonsGuides){
        Guide->SetGeometryOnGrid(Placements[Guide->GetIconName()]);
    }

    if(ControllerBrand == XBOX){
        ImageWidget* DpadCenter = new ImageWidget(":/Resources/Icons/Xbox/center.svg", this);
        DpadCenter->SetGeometryOnGrid(Placements["DpadCenter"]);
    }else if(ControllerBrand == PLAYSTATION){
        ImageWidget* DpadCenter = new ImageWidget(":/Resources/Icons/Playstation/center.svg", this);
        DpadCenter->SetGeometryOnGrid(Placements["DpadCenter"]);
    }

    connect(GP4k_Controller, &Controller::TypeToTextField, TextField, &QTextEditCustom::insertPlainText);
    connect(GP4k_Controller, &Controller::SendOrderToTextField, TextField, &QTextEditCustom::OrderReceived);
    for (auto& Guide : ButtonsGuides){
        connect(GP4k_Controller, &Controller::ToggleTextsOnShift, Guide, &GuideWidget::SetGuideText);
    }
    connect(GP4k_Controller, &Controller::ToggleTextsOnShift, OuterTileGroup, &TileGroupWidget::SetTileText);
    connect(GP4k_Controller, &Controller::ToggleOuterSelectedTile, OuterTileGroup, &TileGroupWidget::SetTileSelected);
    connect(GP4k_Controller, &Controller::ToggleInnerSelectedTile, InnerTileGroup, &InnerTileGroupWidget::SetTileSelected);
    connect(GP4k_Controller, &Controller::ResetCenterBackgrounds, InnerTileGroup, &InnerTileGroupWidget::ResetTiles);
    connect(GP4k_Controller, &Controller::ToggleTextsOnShift, InnerTileGroup, &InnerTileGroupWidget::SetTileText);
    connect(GP4k_Controller, &Controller::UpdateInnerTiles, InnerTileGroup, &InnerTileGroupWidget::SetTileText);
    connect(GP4k_Controller, &Controller::UpdateSuggestionTile, InnerTileGroup, &InnerTileGroupWidget::SetSuggestionTile);

    GP4k_Controller->InitializeTilesContent();
}

MainWindow::~MainWindow()
{

}


