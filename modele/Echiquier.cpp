#include "Echiquier.hpp"
#include "Roi.hpp"
#include "Dame.hpp"
#include "Tour.hpp"
#include "Fou.hpp"
#include "Cavalier.hpp"
#include "Pion.hpp"

#include <iostream>


modele::Echiquier::Echiquier()
{
    pieces_[0][0] = std::make_unique<Tour>(0, 0, true);
    pieces_[1][0] = std::make_unique<Cavalier>(1, 0, true);
    pieces_[2][0] = std::make_unique<Fou>(2, 0, true);
    pieces_[3][0] = std::make_unique<Dame>(3, 0, true);
    pieces_[4][0] = std::make_unique<Roi>(4, 0, true);
    pieces_[5][0] = std::make_unique<Fou>(5, 0, true);
    pieces_[6][0] = std::make_unique<Cavalier>(6, 0, true);
    pieces_[7][0] = std::make_unique<Tour>(7, 0, true);
    coordonneesRois_[true] = { 4, 0 };

    pieces_[0][7] = std::make_unique<Tour>(0, 7, false);
    pieces_[1][7] = std::make_unique<Cavalier>(1, 7, false);
    pieces_[2][7] = std::make_unique<Fou>(2, 7, false);
    pieces_[3][7] = std::make_unique<Dame>(3, 7, false);
    pieces_[4][7] = std::make_unique<Roi>(4, 7, false);
    pieces_[5][7] = std::make_unique<Fou>(5, 7, false);
    pieces_[6][7] = std::make_unique<Cavalier>(6, 7, false);
    pieces_[7][7] = std::make_unique<Tour>(7, 7, false);
    coordonneesRois_[false] = { 4, 7 };

    for (int i = 0; i < 8; i++)
        {
            pieces_[i][1] = std::make_unique<Pion>(i, 1, true);
            pieces_[i][6] = std::make_unique<Pion>(i, 6, false);
        }
}


void modele::Echiquier::verificationEchec()
{
    if (dynamic_cast<Roi*>(getPiece(getCoordonneesRois()[true]).get())->estEnEchec(*this))
        echecBlanc_ = true;
    else
        echecBlanc_ = false;
    if (dynamic_cast<Roi*>(getPiece(getCoordonneesRois()[false]).get())->estEnEchec(*this))
        echecNoir_ = true;
    else
        echecNoir_ = false;
}

void modele::Echiquier::verificationMat()
{
    getPiece(getCoordonneesRois()[true])->trouverDeplacementsValides(*this);
    if (getPiece(getCoordonneesRois()[true])->getDeplacementsValides().size() == 0)
    {
        if (echecBlanc_)
        {
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    if (getPiece(i, j) != nullptr
                            &&getPiece(i, j)->estBlanc() == getPiece(getCoordonneesRois()[true])->estBlanc())
                    {
                        getPiece(i, j)->trouverDeplacementsValides(*this);
                        if (getPiece(i, j)->getDeplacementsValides().size() != 0)
                        {
                            matBlanc_ = false;
                            return;
                        }
                    }

                }
            }
            matBlanc_ = true;
        }
        else if (!echecBlanc_)
        {
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    if (getPiece(i, j) != nullptr
                            &&getPiece(i, j)->estBlanc() == getPiece(getCoordonneesRois()[true])->estBlanc())
                    {
                        getPiece(i, j)->trouverDeplacementsValides(*this);
                        if (getPiece(i, j)->getDeplacementsValides().size() != 0)
                        {
                            patBlanc_ = false;
                            return;
                        }
                    }

                }
            }
            patBlanc_ = true;
        }
    }

    getPiece(getCoordonneesRois()[false])->trouverDeplacementsValides(*this);
    if (getPiece(getCoordonneesRois()[false])->getDeplacementsValides().size() == 0)
    {
        if (echecNoir_)
        {
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    if (getPiece(i, j) != nullptr
                     &&getPiece(i, j)->estBlanc() == getPiece(getCoordonneesRois()[false])->estBlanc())
                    {
                        getPiece(i, j)->trouverDeplacementsValides(*this);
                        if (getPiece(i, j)->getDeplacementsValides().size() != 0)
                        {
                            matNoir_ = false;
                            return;
                        }
                    }

                }
            }
            matNoir_ = true;
        }
        else if (!echecNoir_)
        {
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    if (getPiece(i, j) != nullptr
                     &&getPiece(i, j)->estBlanc() == getPiece(getCoordonneesRois()[false])->estBlanc())
                    {
                        getPiece(i, j)->trouverDeplacementsValides(*this);
                        if (getPiece(i, j)->getDeplacementsValides().size() != 0)
                        {
                            patNoir_ = false;
                            return;
                        }
                    }

                }
            }
            patNoir_ = true;
        }
    }
}
