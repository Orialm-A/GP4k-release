#ifndef TEXTFIELDWIDGET_H
#define TEXTFIELDWIDGET_H

#include <QTextEdit>
#include "Headers/GP4k_Typedefs.h"

/**
 * @brief The TextFieldWidget class Holds the text field of GP4k
 *
 * @details This class extends QLabel to provide additional functionality, such as setting its geometry
 * using a grid map instead of pixel coordinates.
 */
class QTextEditCustom : public QTextEdit  // Inherits from QTextEdit
{
    Q_OBJECT

public slots:
    /**
     * @brief Handle the special instructions like backspace or others related button features
     * @param Key They key associated to the action to perform.
     * @see GP4k_ButtonsMapping.h
     */
    void OrderReceived(const Qt::Key Key);

public:
    /**
     * @brief QTextEditCustom Constructor
     * @param parent Pointer to the parent widget (optional).
     */
    explicit QTextEditCustom(QWidget *parent = nullptr);

    /**
     * @brief SetGeometryOnGrid place the widget in the window using the grid map instead of the pixel map.
     * @param WidgetPlacement The placement parameters of the widget.
     */
    void SetGeometryOnGrid(placement_t WidgetPlacement);
};

#endif // TEXTFIELDWIDGET_H
