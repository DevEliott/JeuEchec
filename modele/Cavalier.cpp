#include "Cavalier.hpp"
#include <cmath>
#include <iostream>


void modele::Cavalier::trouverDeplacementsSemiValides(Echiquier& echiquier)
{
	deplacementsSemiValides_.clear();
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (i != x_ && j != y_ &&
				((std::abs(x_ - i) == 2 && std::abs(y_ - j) == 1)	   //deplacement 2 cases horizontale et 1 verticale
				 || (std::abs(x_ - i) == 1 && std::abs(y_ - j) == 2))) //deplacement 1 case horizontale et 2 verticales
			{
				if (echiquier.getPiece(i, j) == nullptr)
					deplacementsSemiValides_.push_back({i, j});
				else if (estBlanc_ != echiquier.getPiece(i, j)->estBlanc())
					deplacementsSemiValides_.push_back({i, j});
			}
		}
	}
}
