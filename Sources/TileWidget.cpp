#include <QString>
#include <QVector>

#include "Headers/TileWidget.h"
#include "Headers/GP4k_GuiMapping.h"
#include "Headers/GP4k_TilesMapping.h"
#include "qdebug.h"

/* "non-POD static" Warning : Ignored as it's a const on purpose and not meant to be accessed in write at runtime */
const QVector TileAngles{0, 0, 90, 90, 180, 180, 270, 270};

TileWidget::TileWidget(radius_t Radius, const uint8_t Index, QWidget *parent)
    : QWidget{parent}
    , _IsAvailable(true)
{
    _BackgroundFile = QString(":/Resources/tile_");

    if(Radius == INNER){
        _BackgroundFile.append("inner_");
    }else{
        _BackgroundFile.append("outer_");
    }

    if(Index % 2 == 0){
        _BackgroundFile.append("axes");
    }else{
        _BackgroundFile.append("diag");
    }
    _BackgroundAngle = TileAngles[Index];

    _BackgroundFile.append(".svg");

    _Background = new QLabel(this);
    _Background->setScaledContents(true);
    loadBackgroundImage(_BackgroundFile);

    QString DefaultText;
    if(Radius == INNER){
        const CharGroup_t CharsToDisplay = InnerTilesChars[0][0];
        const uint8_t NumberOfChar = CharsToDisplay.length();
        DefaultText = (Index < NumberOfChar) ? CharsToDisplay[Index] : "";
    }else{
        DefaultText = OuterTilesTexts[0][Index];
    }

    QFont font;
    font.setFamily(GLOBAL_FONT);
    font.setPointSize(GLOBAL_FONT_SIZE);
    font.setWeight(QFont::ExtraBold);
    setFont(font);

    _Text = new QLabel(this);
    _Text->setAlignment(Qt::AlignCenter);
    _Text->setStyleSheet("background: transparent;");
    _Text->setText(DefaultText);
    _Text->setFont(font);
}


void TileWidget::SetGeometryOnGrid(const placement_t WidgetPlacement)
{
    int X = WidgetPlacement.X*CELL_SIZE;
    int Y = WidgetPlacement.Y*CELL_SIZE;
    int SizeX = WidgetPlacement.SizeX*CELL_SIZE;
    int SizeY = WidgetPlacement.SizeY*CELL_SIZE;
    QWidget::setGeometry(X, Y, SizeX, SizeY);
    _Background->setGeometry(rect());
    _Text->setGeometry(rect());
}

void TileWidget::SetText(const QString NewText){
    _Text->setText(NewText);
}

void TileWidget::loadBackgroundImage(const QString imagePath) {
    QPixmap pixmap(imagePath);
    qDebug() << imagePath;
    Q_ASSERT(!pixmap.isNull());
    int BackgroundAngle = _BackgroundAngle;
    if (BackgroundAngle != 0) {
        QTransform rotationTransform;
        rotationTransform.rotate(BackgroundAngle);
        pixmap = pixmap.transformed(rotationTransform);
    }
    _Background->setPixmap(pixmap);
}

void TileWidget::SetBackground(bool SetSelected, bool SetAvailable){
    QString BackgroundFile = _BackgroundFile;

    if(!SetAvailable){
        BackgroundFile.insert(27,"_unavailable");
    }else if(SetSelected){
        BackgroundFile.insert(27,"_selected");
    }
    SetAvailability(SetAvailable);
    loadBackgroundImage(BackgroundFile);
}

bool TileWidget::GetAvailability(void) const{
    return _IsAvailable;
}

void TileWidget::SetAvailability(const bool IsAvailable){
    _IsAvailable = IsAvailable;
}
