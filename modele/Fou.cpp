#include "Fou.hpp"
#include <cmath>
#include <iostream>

void modele::Fou::trouverDeplacementsSemiValides(Echiquier& echiquier)
{
	deplacementsSemiValides_.clear();
	int xVariation = 0;
	int yVariation = 0;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (std::abs(x_ - i) == std::abs(y_ - j) && i != x_ && j != y_)
			{
				if (i - x_ < 0)
					xVariation = -1; // variation des x vers le bas
				else if (i - x_ > 0)
					xVariation = 1; // variation des x vers le haut
				if (j - y_ < 0)
					yVariation = -1; // variation des y vers le bas
				else if (j - y_ > 0)
					yVariation = 1; // variation des y vers le haut

				// verification s'il y a une piece sur chaque case du déplacement qui indique un mouvement non valide,
				// à moins que ce soit la derniere case et donc indique un mouvement possible.
				int k = 1;
                for (; k <= std::abs(x_ - i);)
				{
					if (echiquier.getPiece(x_ + xVariation * k, y_ + yVariation * k) != nullptr)
					{
						k++;
						break;
					}
					k++;
				}
				if (x_ + xVariation * (k - 1) == i && y_ + yVariation * (k - 1) == j)
				{
					if (echiquier.getPiece(i, j) == nullptr)
						deplacementsSemiValides_.push_back({i, j});
					else if (estBlanc_ != echiquier.getPiece(i, j)->estBlanc())
						deplacementsSemiValides_.push_back({i, j});
				}
			}
		}
	}
}
