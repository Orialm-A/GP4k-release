#include "Headers/ImageWidget.h"
#include "Headers/GP4k_GuiMapping.h"

ImageWidget::ImageWidget(const QString& ImagePath, QWidget *parent)
    : QLabel(parent)
{
    QPixmap SticksIcon(ImagePath);
    setPixmap(SticksIcon);
    setScaledContents(true); // Ensures the image scales to the label's size
}

void ImageWidget::SetGeometryOnGrid(const placement_t& WidgetPlacement)
{
    int X = WidgetPlacement.X * CELL_SIZE;
    int Y = WidgetPlacement.Y * CELL_SIZE;
    int SizeX = WidgetPlacement.SizeX * CELL_SIZE;
    int SizeY = WidgetPlacement.SizeY * CELL_SIZE;
    setGeometry(X, Y, SizeX, SizeY);
}
