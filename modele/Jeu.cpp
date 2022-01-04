#include "Jeu.hpp"
#include "Roi.hpp"

#include <iostream>
#include <utility>


void modele::Jeu::recevoirCaseCliquee(std::pair<int, int> caseCliquee)
{
    if (!case1DejaCliquee_)
    {
        if (echiquier_.getPiece(caseCliquee) != nullptr)
        {
            if (echiquier_.getPiece(caseCliquee)->estBlanc() != echiquier_.blancAJouer())
                emit envoyerReponse(deplacementFait_,
                                    QString::fromStdString("Ce n'est pas une de tes pieces!"));

            else
            {
                case1_ = caseCliquee;
                case1DejaCliquee_ = true;
                echiquier_.getPiece(caseCliquee)->trouverDeplacementsValides(echiquier_);
                emit casesValides(echiquier_.getPiece(caseCliquee)->getDeplacementsValides());
            }
        }
        else
            emit envoyerReponse(deplacementFait_,
                                QString::fromStdString(std::string("La case est vide!")));
    }
    else
    {
        if (case1_ == caseCliquee)
        {
            case1DejaCliquee_ = false;
            emit envoyerReponse(deplacementFait_,
                 QString::fromStdString(std::string("A quoi ca sert de ce deplacer sur soi-meme?")));
            emit repeindre();
        }
        else
        {
            case2_ = caseCliquee;
            case1DejaCliquee_ = false;
            effectuerSonTour();
            emit repeindre();
            if (echiquier_.matBlanc() || echiquier_.matNoir())
            {
                if (echiquier_.matBlanc())
                    emit mat(true);
                else if (echiquier_.matNoir())
                    emit mat(false);
            }
            else if (echiquier_.patBlanc() || echiquier_.patNoir())
            {
                if (echiquier_.patBlanc())
                    emit pat(true);
                else if (echiquier_.patNoir())
                    emit pat(false);
            }
        }
    }
}

void modele::Jeu::recevoirCaseDecliquee()
{
    case1DejaCliquee_ = false;
    emit repeindre();
}


void modele::Jeu::effectuerSonTour()
{
    try
    {
        effectuerDeplacement();
        if (modele::Roi::compteurInstance > 2)
            emit plusDeDeuxRois();
    }
    catch (std::string& message)
    {
        emit envoyerReponse(deplacementFait_, QString::fromStdString(message),
                            case1_, case2_);
        return;
    }

    if (deplacementFait_)
    {
        echiquier_.blancAJouer() = !echiquier_.blancAJouer();
        emit envoyerReponse(deplacementFait_, QString("Deplacement fait!"),
                            case1_, case2_);
        if (echiquier_.getPromotion())
        {
            echiquier_.getPromotion() = false;
            emit promotion(echiquier_.getPromotionCoordoonees());
        }
        deplacementFait_ = false;
    }
}

void modele::Jeu::effectuerDeplacement()
{
    echiquier_.getPiece(case1_)->bouger(echiquier_, case2_);
    getEchiquier().verificationEchec();
    getEchiquier().verificationMat();
    deplacementFait() = true;
}
