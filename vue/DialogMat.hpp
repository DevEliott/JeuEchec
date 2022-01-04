#pragma once

#include <QDialog>

namespace Ui {
class DialogMat;
}


namespace vue {

    class DialogMat : public QDialog
    {
        Q_OBJECT

    public:
        explicit DialogMat(QWidget *parent = nullptr);
        ~DialogMat();

    private:
        Ui::DialogMat *ui;

    public slots:
        void recevoirMatMainWindow(bool couleur);
    private slots:
        void on_pushButton_clicked();
    signals:
        void boutonValiderAppuye();
    };
}
