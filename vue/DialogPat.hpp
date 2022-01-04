#pragma once

#include <QDialog>

namespace Ui {
class DialogPat;
}

namespace vue {

    class DialogPat : public QDialog
    {
        Q_OBJECT

    public:
        explicit DialogPat(QWidget *parent = nullptr);
        ~DialogPat();

    private:
        Ui::DialogPat *ui;

    public slots:
        void recevoirPatMainWindow(bool couleur);

    signals:
        void boutonValiderAppuye();
    private slots:
        void on_pushButton_clicked();
    };
}

