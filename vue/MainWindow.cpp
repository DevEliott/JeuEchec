#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include <QDialog>


vue::MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    vueJeu_ = new QGraphicsScene(this);
    ui->graphicsView->setScene(vueJeu_);

    jeu_ = std::make_unique<modele::Jeu>();
    initialiserEchiquierUi();
    placerPiecesUi();

    dialogMat_ = new DialogMat(this);
    QObject::connect(dialogMat_, &vue::DialogMat::boutonValiderAppuye,
                     this, &vue::MainWindow::afficherMenuDemarer);

    dialogPat_ = new DialogPat(this);
    QObject::connect(dialogPat_, &vue::DialogPat::boutonValiderAppuye,
                     this, &vue::MainWindow::afficherMenuDemarer);

    menuDemarrer_ = new MenuDemarrer(this);
    QObject::connect(menuDemarrer_, &vue::MenuDemarrer::boutonValiderAppuye,
                     this, &vue::MainWindow::recevoirValidationMenuDemarrer);

    afficherMenuDemarer();
}


vue::MainWindow::~MainWindow()
{
    delete ui;
}


void vue::MainWindow::initialiserEchiquierUi()
{
    int x = 0;
    int y = 0;
    bool caseNoire;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (i % 2 == 0 && j % 2 == 0) {
                caseNoire = true;
            }
            else if (i % 2 != 0 && j % 2 == 0) {
                caseNoire = false;
            }
            else if (i % 2 != 0 && j % 2 != 0) {
                caseNoire = true;
            }
            else
            {
                caseNoire = false;
            }

            CaseUI* caseUi = new CaseUI(x, std::abs(y - 525), i, j); //inverse les y
            caseUi->setRect(x, std::abs(y - 525), 75, 75); // pour en-bas au lieu d'en haut

            if (caseNoire)
                caseUi->setBrush(QBrush(colorNoir));
            else
                caseUi->setBrush(QBrush(colorBlanc));

            cases_[i][j] = caseUi;
            vueJeu_->addItem(caseUi);
            vueJeu_->addItem(&caseUi->getPixmap());
            QObject::connect(caseUi, &vue::CaseUI::caseCliquee,
                             jeu_.get(), &modele::Jeu::recevoirCaseCliquee);

            QObject::connect(caseUi, &vue::CaseUI::caseDecliquee,
                             jeu_.get(), &modele::Jeu::recevoirCaseDecliquee);


            y += 75;
            if (y == 600) // 8 cases de 75 pixels
            {
                x += 75;
                y = 0;
            }
        }
    }

    updateLabelTour();
    updateUiEchec();

    ui->labelValidite->setText("");
    ui->labelValidite->setStyleSheet("QLabel { background-color : white}");
}


void vue::MainWindow::updateUiEchec()
{
    if (jeu_->getEchiquier().EchecBlanc() || jeu_->getEchiquier().EchecNoir())
    {
        if (jeu_->getEchiquier().matBlanc())
             ui->labelEchec->setText(QString("Echec et mat des Blancs"));
        else if (jeu_->getEchiquier().matNoir())
            ui->labelEchec->setText(QString("Echec et mat des Noirs"));
        else if (jeu_->getEchiquier().EchecBlanc())
            ui->labelEchec->setText(QString("Echec des Blancs"));
        else if (jeu_->getEchiquier().EchecNoir())
            ui->labelEchec->setText(QString("Echec des Noirs"));
        ui->labelEchec->setFrameShadow(QFrame::Raised);
        ui->labelEchec->setStyleSheet("QLabel { background-color : red}");
    }
    else if (jeu_->getEchiquier().patBlanc())
        ui->labelEchec->setText(QString("Pat des Blancs"));
    else if (jeu_->getEchiquier().patNoir())
        ui->labelEchec->setText(QString("Pat des Noirs"));
    else
    {
        ui->labelEchec->setText(QString("Pas d'echec"));
        ui->labelEchec->setStyleSheet("QLabel { background-color : white}");
        ui->labelEchec->setFrameShadow(QFrame::Sunken);
    }
}


void vue::MainWindow::updateLabelTour()
{
    if (jeu_->getEchiquier().blancAJouer())
    {
        ui->labelTour->setText(QString("Au tour des Blancs"));
        ui->labelTour->setStyleSheet("QLabel { background-color : rgb(240, 217, 183)}");
    }

    else
    {
        ui->labelTour->setText(QString("Au tour des Noirs"));
        ui->labelTour->setStyleSheet("QLabel { background-color : rgb(180, 136, 102)}");
    }
}


void vue::MainWindow::placerPiecesUi()
{
    QString couleur;
    QString nom;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (jeu_->getEchiquier().getPiece(i, j) != nullptr)
            {
                if (jeu_->getEchiquier().getPiece(i, j)->estBlanc())
                    couleur = "Blanc";
                else if (!jeu_->getEchiquier().getPiece(i, j)->estBlanc())
                    couleur = "Noir";

                nom = QString::fromStdString(
                            jeu_->getEchiquier().getPiece(i, j)->getNom());

                cases_[i][j]->setPixmap(
                            QString(":/images/") + nom + couleur + QString(".svg"));
            }
        }
    }
}


void vue::MainWindow::recevoirReponseDuJeu(bool tourFait, QString reponse,
                                           std::pair<int, int> ancien,
                                           std::pair<int, int> nouveau)
{
    if (tourFait)
    {
        QString ancienneImage = cases_[ancien.first][ancien.second]->getCheminImage();
        cases_[ancien.first][ancien.second]->effacerPixmap();
        cases_[nouveau.first][nouveau.second]->setPixmap(ancienneImage);

        ui->labelValidite->setText(reponse);
        ui->labelValidite->setStyleSheet("QLabel { background-color : rgb(124, 219, 77)}");

        updateLabelTour();
        updateUiEchec();
    }
    else
    {
        ui->labelValidite->setText(reponse);
        ui->labelValidite->setStyleSheet("QLabel { background-color : rgb(189, 25, 25)}");
    }
}

void vue::MainWindow::recevoirCasesValides(std::vector<std::pair<int, int>> casesValides)
{
    for (auto&& coordonnees : casesValides)
    {
        if (cases_[coordonnees.first][coordonnees.second]->getCheminImage() != "")
            cases_[coordonnees.first][coordonnees.second]->setBrush(QBrush(colorCapture));
        else
            cases_[coordonnees.first][coordonnees.second]->setBrush(QBrush(colorValide));
    }
}


void vue::MainWindow::recevoirRepeindre()
{
    bool caseNoire;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (i % 2 == 0 && j % 2 == 0) {
                caseNoire = true;
            }
            else if (i % 2 != 0 && j % 2 == 0) {
                caseNoire = false;
            }
            else if (i % 2 != 0 && j % 2 != 0) {
                caseNoire = true;
            }
            else
            {
                caseNoire = false;
            }

            if (jeu_->getEchiquier().EchecBlanc() || jeu_->getEchiquier().EchecBlanc())
            {
                if (jeu_->getEchiquier().getPiece(i, j) != nullptr
                    && jeu_->getEchiquier().getPiece(i, j)->getNom() == "Roi")
                    continue;
                else
                {
                    if (caseNoire)
                        cases_[i][j]->setBrush(QBrush(colorNoir));
                    else
                        cases_[i][j]->setBrush(QBrush(colorBlanc));
                }
            }
            else
            {
                if (caseNoire)
                    cases_[i][j]->setBrush(QBrush(colorNoir));
                else
                    cases_[i][j]->setBrush(QBrush(colorBlanc));
            }
        }
    }
}


void vue::MainWindow::afficherMenuDemarer()
{
    this->hide();
    menuDemarrer_->exec();
    this->show();
}

void vue::MainWindow::recevoirValidationMenuDemarrer()
{
    on_boutonNewgame_clicked();
}

void vue::MainWindow::on_boutonNewgame_clicked()
{
    jeu_ = std::make_unique<modele::Jeu>();
    initialiserEchiquierUi();
    placerPiecesUi();

    QObject::connect(jeu_.get(), &modele::Jeu::envoyerReponse,
                     this, &vue::MainWindow::recevoirReponseDuJeu);
    QObject::connect(jeu_.get(), &modele::Jeu::casesValides,
                     this, &vue::MainWindow::recevoirCasesValides);
    QObject::connect(jeu_.get(), &modele::Jeu::repeindre,
                     this, &vue::MainWindow::recevoirRepeindre);
    QObject::connect(jeu_.get(), &modele::Jeu::promotion,
                     this, &vue::MainWindow::recevoirPromotion);
    QObject::connect(jeu_.get(), &modele::Jeu::mat,
                     this, &vue::MainWindow::recevoirMatJeu);
    QObject::connect(this, &vue::MainWindow::envoyerMat,
                     dialogMat_, &vue::DialogMat::recevoirMatMainWindow);
    QObject::connect(jeu_.get(), &modele::Jeu::pat,
                     this, &vue::MainWindow::recevoirPatJeu);
    QObject::connect(this, &vue::MainWindow::envoyerPat,
                     dialogPat_, &vue::DialogPat::recevoirPatMainWindow);
}

void vue::MainWindow::recevoirPromotion(std::pair<int, int> coordonnees)
{
    QString couleur;
    QString nom;
    cases_[coordonnees.first][coordonnees.second]->effacerPixmap();
    if (jeu_->getEchiquier().getPiece(coordonnees)->estBlanc())
        couleur = "Blanc";
    else if (!jeu_->getEchiquier().getPiece(coordonnees)->estBlanc())
        couleur = "Noir";

    nom = QString::fromStdString(
                jeu_->getEchiquier().getPiece(coordonnees)->getNom());

    cases_[coordonnees.first][coordonnees.second]->setPixmap(
                QString(":/images/") + nom + couleur + QString(".svg"));
}

void vue::MainWindow::recevoirMatJeu(bool couleur)
{
    emit envoyerMat(couleur);
    dialogMat_->exec();
}

void vue::MainWindow::recevoirPatJeu(bool couleur)
{
    emit envoyerPat(couleur);
    dialogPat_->exec();
}
