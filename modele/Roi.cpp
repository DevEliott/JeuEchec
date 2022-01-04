#include "Roi.hpp"
#include "Cavalier.hpp"
#include <iostream>
#include <memory>


bool modele::Roi::estEnEchec(Echiquier& echiquier)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (echiquier.getPiece(i, j) != nullptr
				&& echiquier.getPiece(i, j) != echiquier.getPiece(x_, y_)
				&& echiquier.getPiece(i, j)->estBlanc() != estBlanc_)
			{
				if (dynamic_cast<Roi*>(echiquier.getPiece(i, j).get()))
                    if ((std::abs(i - x_) == 1 && std::abs(j - y_) == 0)	   //deplacement horizontal
                        || (std::abs(i - x_) == 0 && std::abs(j - y_) == 1)  //deplacement vertical
                        || (std::abs(i - x_) == 1 && std::abs(j - y_) == 1)) //deplacemetn diagonal
                        return true;
                else
                        continue;
				else
				{
					echiquier.getPiece(i, j)->trouverDeplacementsSemiValides(echiquier);
					if (echiquier.getPiece(i, j)->getDeplacementsSemiValides().size() > 0)
					{
						for (auto&& deplacement : echiquier.getPiece(i, j)->getDeplacementsSemiValides())
						{
							if (deplacement == this->getCoordonnees())
								return true;
						}
					}
				}
			}
		}
	}
	return false;
}

void modele::Roi::trouverDeplacementsSemiValides(Echiquier& echiquier)
{
	deplacementsSemiValides_.clear();
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
            if ((std::abs(i - x_) == 1 && std::abs(j - y_) == 0)	   //deplacement horizontal
                || (std::abs(i - x_) == 0 && std::abs(j - y_) == 1)  //deplacement vertical
                || (std::abs(i - x_) == 1 && std::abs(j - y_) == 1)) //deplacemetn diagonal
			{
				if (echiquier.getPiece(i, j) == nullptr)
					deplacementsSemiValides_.push_back({i, j});
				else if (estBlanc_ != echiquier.getPiece(i, j)->estBlanc())
					deplacementsSemiValides_.push_back({i, j});
			}
		}
	}
}

void modele::Roi::trouverDeplacementsValides(Echiquier& echiquier)
{
	deplacementsValides_.clear();
	trouverDeplacementsSemiValides(echiquier);
	auto deplacementsSemiValides = deplacementsSemiValides_;

	for (auto&& deplacementSemiValide : deplacementsSemiValides)
	{
		echiquier.getPieceTamponRoi() = std::move(echiquier.getPiece(deplacementSemiValide));
		auto coordonneesAvant = getCoordonnees();
		echiquier.getPiece(deplacementSemiValide) = std::move(echiquier.getPiece(x_, y_));
		x_ = deplacementSemiValide.first;
		y_ = deplacementSemiValide.second;
		echiquier.getCoordonneesRois()[estBlanc_] = getCoordonnees();

		if (!estEnEchec(echiquier))
			deplacementsValides_.push_back(deplacementSemiValide);

		echiquier.getPiece(coordonneesAvant) = std::move(echiquier.getPiece(deplacementSemiValide));
		echiquier.getPiece(deplacementSemiValide) = std::move(echiquier.getPieceTamponRoi());
		x_ = coordonneesAvant.first;
		y_ = coordonneesAvant.second;
		echiquier.getCoordonneesRois()[estBlanc_] = getCoordonnees();
	}
}
