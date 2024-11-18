#ifndef GUIDEWIDGET_H
#define GUIDEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QString>

#include "Headers/GP4k_Typedefs.h"
#include "Headers/GP4k_ButtonsMapping.h"

/**
 * @brief The GuideWidget class Handles the GUI component associating a button icon and feature
 * label to guide the user while using GP4k.
 */
class GuideWidget : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief GuideWidget Constructor.
     * @param Button The button to be displayed on the UI. It holds all the data about itself.
     * @param ControllerBrand The brand of the controller that should be used to select the icons.
     * @param parent Pointer to the parent widget (optional).
     */
    explicit GuideWidget(const PhysicalButton_t* Button,
                         const brand_t ControllerBrand,
                         QWidget *parent = nullptr);

    /**
     * @brief SetGeometryOnGrid place the widget in the window using the grid map instead of the pixel map.
     * @param WidgetPlacement The placement parameters of the widget.
     */
    void SetGeometryOnGrid(const placement_t WidgetPlacement);

    /**
     * @brief Getter for _IconName;
     * @return _IconName
     */
    QString GetIconName(void) const;

public slots:
    /**
     * @brief Set the text of the button code, accordingly the the shift key state.
     * @param ShiftKey The current state of the shift key.
     */
    void SetGuideText(const ShiftState_t ShiftKey);

private: // Attributes
    /**
     * @brief The associated physical button.
     */
    const PhysicalButton_t* _PhysicalButton;

    /**
     * @brief Holds the icon of the Button's Guide.
     */
    QLabel *_Icon;

    /**
     * @brief Holds the text of the Button's Guide.
     */
    QLabel *_Label;

private: // Methods
    /**
     * @brief SetIcon Used to set the icon.
     * @param Button The button that must be selected.
     * @param Brand The console that must me used for button design.
     */
    void SetIcon(const brand_t Brand);
};

#endif // GUIDEWIDGET_H
