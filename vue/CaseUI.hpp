#ifndef CASEUI_HPP
#define CASEUI_HPP

#include "../modele/Echiquier.hpp"
#pragma warning(push, 0)
#include <QDebug>
#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QBrush>
#include <QImage>
#pragma pop()

#include <string>
#include <cmath>


namespace vue {

    class CaseUI : public QObject, public QGraphicsRectItem
    {
        Q_OBJECT

    public:
        CaseUI(int xPixel, int yPixel, int x, int y);
        ~CaseUI() = default;
        int& getX() {return x_; }
        int& getY() {return y_; }
        int& getXPixel_() {return xPixel_; }
        int& getYPixel_() {return yPixel_; }
        void setPixmap(QString chemin);
        QString getCheminImage() const;
        QGraphicsPixmapItem& getPixmap();
        void effacerPixmap();

        void mousePressEvent(QGraphicsSceneMouseEvent* event);

    private:
        int x_;
        int y_;
        int xPixel_;
        int yPixel_;
        QString cheminImage_;
        QGraphicsPixmapItem pixmap_;
        QImage image_;
        bool dejaCliquee = false;

    signals:
        void caseCliquee(std::pair<int, int>);
        void caseDecliquee(std::pair<int, int>);
        void repeindre();
    };
}

#endif // CASEUI_HPP
