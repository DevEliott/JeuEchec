#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP


#include "MenuDemarrer.hpp"
#include "DialogMat.hpp"
#include "DialogPat.hpp"
#include "CaseUI.hpp"
#include "../modele/Jeu.hpp"

#include <QMainWindow>
#include <QGraphicsScene>

#include <array>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace vue {

    class MainWindow : public QMainWindow
    {
        Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

        void initialiserEchiquierUi();
        void placerPiecesUi();
        void updateUiEchec();
        void updateLabelTour();

    private:
        Ui::MainWindow *ui;
        MenuDemarrer* menuDemarrer_;
        DialogMat* dialogMat_;
        DialogPat* dialogPat_;
        std::unique_ptr<modele::Jeu> jeu_;
        QGraphicsScene* vueJeu_;
        CaseUI* cases_[8][8];

        QColor colorBlanc = QColor::fromRgb(240, 217, 183);
        QColor colorNoir = QColor::fromRgb(180, 136, 102);
        QColor colorValide = QColor::fromRgb(0, 225, 0);
        QColor colorCapture = QColor::fromRgb(0, 225, 225);
        QColor colorEchec = Qt::red;


    private slots:
        void recevoirReponseDuJeu(bool tourFait, QString reponse,
                                  std::pair<int, int> anciennePiece = {0, 0},
                                  std::pair<int, int> pieceBougee = {0, 0});
        void recevoirCasesValides(std::vector<std::pair<int, int>>);
        void recevoirRepeindre();

        void afficherMenuDemarer();
        void recevoirValidationMenuDemarrer();

        void on_boutonNewgame_clicked();

        void recevoirPromotion(std::pair<int, int>);

        void recevoirMatJeu(bool couleur);
        void recevoirPatJeu(bool couleur);
    signals:
        void envoyerMat(bool);
        void envoyerPat(bool);
    };
}
#endif // MAINWINDOW_HPP
