#include "./Piece.hpp"
#include "./Echiquier.hpp"
#include "Roi.hpp"
#include "Dame.hpp"
#include "Pion.hpp"
#include <iostream>

modele::Piece::Piece(int x, int y)
{
	x_ = x;
	y_ = y;
}

void modele::Piece::promotion(modele::Echiquier &echiquier, std::pair<int, int> arrivee)
{
    if (estBlanc_ && y_ == 7)
    {
        echiquier.getPiece(arrivee) = std::make_unique<Dame>(arrivee.first, arrivee.second, true);
        echiquier.setPromotionCoordoonees(arrivee);
        echiquier.getPromotion() = true;
    }
    else if (!estBlanc_ && y_ == 0)
    {
        echiquier.getPiece(arrivee) = std::make_unique<Dame>(arrivee.first, arrivee.second, false);
        echiquier.setPromotionCoordoonees(arrivee);
        echiquier.getPromotion() = true;
    }
}

void modele::Piece::trouverDeplacementsValides(Echiquier& echiquier)
{
    auto [xRoi, yRoi] = echiquier.getCoordonneesRois()[estBlanc_];
    deplacementsValides_.clear();
    trouverDeplacementsSemiValides(echiquier);
    auto deplacementsSemiValides = deplacementsSemiValides_;

    for (auto&& deplacementSemiValide : deplacementsSemiValides)
    {
        echiquier.getPieceTampon() = std::move(echiquier.getPiece(deplacementSemiValide));
        auto coordonneesAvant = getCoordonnees();
        echiquier.getPiece(deplacementSemiValide) = std::move(echiquier.getPiece(x_, y_));
        x_ = deplacementSemiValide.first;
        y_ = deplacementSemiValide.second;

        if (!dynamic_cast<Roi*>(echiquier.getPiece(xRoi, yRoi).get())->estEnEchec(echiquier))
            deplacementsValides_.push_back(deplacementSemiValide);

        echiquier.getPiece(coordonneesAvant) = std::move(echiquier.getPiece(x_, y_));
        echiquier.getPiece(x_, y_) = std::move(echiquier.getPieceTampon());
        x_ = coordonneesAvant.first;
        y_ = coordonneesAvant.second;
    }
}


bool modele::Piece::peutBouger(Echiquier& echiquier, std::pair<int, int> arrivee)
{
	trouverDeplacementsValides(echiquier);
	for (auto&& deplacement : deplacementsValides_)
	{
		if (arrivee == deplacement)
			return true;
	}
	return false;
}

void modele::Piece::bouger(Echiquier& echiquier, std::pair<int, int> arrivee)
{
	if (peutBouger(echiquier, arrivee))
	{
        echiquier.getPiece(arrivee) = std::move(echiquier.getPiece(x_, y_));
		x_ = arrivee.first;
		y_ = arrivee.second;
        if (nom_ == "Roi")
        {
            echiquier.getCoordonneesRois()[estBlanc_] = arrivee;
            return;
        }

        if (nom_ == "Pion")
        {
            if (dynamic_cast<Pion*>(echiquier.getPiece(arrivee).get())->premierDeplacement())
                dynamic_cast<Pion*>(echiquier.getPiece(arrivee).get())->premierDeplacement() = false;
            promotion(echiquier, arrivee);
        }
    }
    else
        throw std::string("Ne peut pas bouger!");
}
