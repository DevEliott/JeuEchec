#include "CaseUI.hpp"


vue::CaseUI::CaseUI(int xPixel, int yPixel, int x, int y)
{
    xPixel_ = xPixel;
    yPixel_ = yPixel;
                            
    x_ = x; // vraies coordonnees de la case
    y_ = y;
}

QString vue::CaseUI::getCheminImage() const
{
    return cheminImage_;
}

QGraphicsPixmapItem& vue::CaseUI::getPixmap()
{
    return pixmap_;
}

void vue::CaseUI::effacerPixmap()
{
    pixmap_.hide();
    cheminImage_ = "";
}

void vue::CaseUI::setPixmap(QString chemin)
{
    cheminImage_ = chemin;
    image_ = QImage(chemin);
    QImage scaled = image_.scaled(75, 75);
    pixmap_.setPixmap(QPixmap::fromImage(scaled));
    pixmap_.setPos(xPixel_, yPixel_);
    pixmap_.show();
}

void vue::CaseUI::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        if (!dejaCliquee)
        {
            dejaCliquee = true;
            emit caseCliquee( {x_, y_} );
        }
        else
            emit caseCliquee( {x_, y_} );
    }
    else if (event->buttons() == Qt::RightButton)
    {
        dejaCliquee = false;
        emit caseDecliquee( { x_, y_} );
    }
}
