#include "Headers/GuideWidget.h"
#include <QHBoxLayout>
#include "Headers/GP4k_ButtonsMapping.h"
#include "Headers/GP4k_GuiMapping.h"
#include "qdebug.h"

GuideWidget::GuideWidget(const PhysicalButton_t* Button,
                         const brand_t Brand,
                         QWidget *parent)
    : QWidget(parent)
    , _PhysicalButton(Button)
{
    _Icon = new QLabel(this);
    _Icon->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    SetIcon(Brand);

    QFont font;
    font.setFamily(GLOBAL_FONT);
    font.setPointSize(GLOBAL_FONT_SIZE);
    font.setWeight(QFont::ExtraBold);
    _Label = new QLabel(this);
    _Label->setFont(font);
    SetGuideText(NOT_SHIFTED);
    _Label->setStyleSheet(_PhysicalButton->Colors[Brand]);

    const LabelPosition_t Position = Button->LabelPosition;
    QBoxLayout *layout = nullptr;
    if (Position == LABEL_TOP || Position == LABEL_BOTTOM) {
        layout = new QVBoxLayout(this);
    } else {
        layout = new QHBoxLayout(this);
    }

    switch (Position) {
    case LABEL_LEFT:
        layout->addWidget(_Label);
        layout->addWidget(_Icon, 0, Qt::AlignVCenter);
        _Label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        break;
    case LABEL_RIGHT:
        layout->addWidget(_Icon);
        layout->addWidget(_Label, 0, Qt::AlignVCenter);
        _Label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        break;
    case LABEL_TOP:
        layout->addWidget(_Label);
        layout->addWidget(_Icon, 0, Qt::AlignHCenter);
        _Label->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
        break;
    case LABEL_BOTTOM:
        layout->addWidget(_Icon, 0, Qt::AlignHCenter);
        layout->addWidget(_Label);
        _Label->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
        break;
    default:
        // Position is enum type LabelPosition_t: No other possible option
        break;
    }

    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    setLayout(layout);
}

void GuideWidget::SetGeometryOnGrid(const placement_t WidgetPlacement) {
    int X = WidgetPlacement.X*CELL_SIZE;
    int Y = WidgetPlacement.Y*CELL_SIZE;
    int SizeX = WidgetPlacement.SizeX*CELL_SIZE;
    int SizeY = WidgetPlacement.SizeY*CELL_SIZE;
    setGeometry(X, Y, SizeX, SizeY);
}

void GuideWidget::SetIcon(const brand_t Brand){
    QString IconPath = ":/Resources/Icons/";

    switch (Brand) {
    case XBOX:
        IconPath.append("Xbox/");
        break;
    case PLAYSTATION:
        IconPath.append("Playstation/");
        break;
    case NINTENDO:
        IconPath.append("Nintendo/");
        break;
    default:
        /* Prevent crashes when a controller is not
         * connected, so the user have the opportunity
         * to see it and the GUI.
         */
        IconPath.append("Xbox/");
        break;
    }

    IconPath.append(_PhysicalButton->IconName);
    IconPath.append(".svg");


    QPixmap pixmap(IconPath);
    qDebug() << IconPath;
    Q_ASSERT(!pixmap.isNull());

    int width = 2*CELL_SIZE;
    int height = 2*CELL_SIZE;
    _Icon->setPixmap(pixmap.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void GuideWidget::SetGuideText(const ShiftState_t ShiftKey){
    _Label->setText(_PhysicalButton->Features[ShiftKey].Text);
}

QString GuideWidget::GetIconName(void) const{
    return _PhysicalButton->IconName;
}
