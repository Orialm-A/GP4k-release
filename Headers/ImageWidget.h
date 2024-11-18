#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QLabel>
#include "Headers/GP4k_Typedefs.h"

/**
 * @brief The ImageWidget class Used to add images to the GUI
 *
 * This class extends QLabel to provide additional functionality, such as setting its geometry
 * using a grid map instead of pixel coordinates.
 */
class ImageWidget : public QLabel
{
    Q_OBJECT
public:
    /**
     * @brief ImageWidget Constructor
     * @param ImagePath The path to the image file.
     * @param parent Pointer to the parent widget (optional).
     */
    explicit ImageWidget(const QString& ImagePath, QWidget *parent = nullptr);

    /**
     * @brief SetGeometryOnGrid Places the widget in the window using the grid map instead of the pixel map.
     * @param WidgetPlacement The placement parameters of the widget.
     */
    void SetGeometryOnGrid(const placement_t& WidgetPlacement);
};

#endif // IMAGEWIDGET_H
