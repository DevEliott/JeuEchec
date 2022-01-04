#pragma warning(push, 0)
#include <QDialog>


namespace Ui {
class MenuDemarrer;
}

namespace vue {


    class MenuDemarrer : public QDialog
    {
        Q_OBJECT

    public:
        explicit MenuDemarrer(QWidget *parent = nullptr);
        ~MenuDemarrer();

    private:
        Ui::MenuDemarrer *ui;

    private slots:
        void on_pushButton_Valider_clicked();

    signals:
        void boutonValiderAppuye();
    };
}
