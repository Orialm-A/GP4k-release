#include "Headers/TextFieldWidget.h"
#include "Headers/GP4k_GuiMapping.h"
#include "qapplication.h"
#include "qevent.h"


QTextEditCustom::QTextEditCustom(QWidget *parent)
    : QTextEdit(parent)  // Call the base class constructor with 'parent'
{
    QFont font;
    font.setFamily(GLOBAL_FONT);
    font.setPointSize(GLOBAL_FONT_SIZE);
    setFont(font);
}

void QTextEditCustom::SetGeometryOnGrid(placement_t WidgetPlacement){
    int X = WidgetPlacement.X*CELL_SIZE;
    int Y = WidgetPlacement.Y*CELL_SIZE;
    int SizeX = WidgetPlacement.SizeX*CELL_SIZE;
    int SizeY = WidgetPlacement.SizeY*CELL_SIZE;
    QWidget::setGeometry(X, Y, SizeX, SizeY);
}

void QTextEditCustom::OrderReceived(const Qt::Key Key){
    QKeyEvent pressEvent(QEvent::KeyPress, Key, Qt::NoModifier, " ");
    QKeyEvent releaseEvent(QEvent::KeyRelease, Key, Qt::NoModifier, " ");
    QApplication::sendEvent(this, &pressEvent);
    QApplication::sendEvent(this, &releaseEvent);
}
