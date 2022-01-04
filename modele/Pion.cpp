#include "Pion.hpp"
#include <cmath>
#include <iostream>


void modele::Pion::trouverDeplacementsSemiValides(Echiquier& echiquier)
{
    deplacementsSemiValides_.clear();
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            //regarder pour juste avancer
            if (i == x_ && j != y_ && echiquier.getPiece(i, j) == nullptr)
            {
                if (estBlanc_)
                {
                    if (j - y_ == 2 && premierDeplacement_)
                        deplacementsSemiValides_.push_back({i, j});
                    else if (j - y_ == 1)
                        deplacementsSemiValides_.push_back({i, j});
                }
                else
                {
                    if (j - y_ == -2 && premierDeplacement_)
                        deplacementsSemiValides_.push_back({i, j});
                    else if (j - y_ == -1)
                        deplacementsSemiValides_.push_back({i, j});
                }
            }
            //regarder pour capturer
            else if (i != x_ && j != y_ && echiquier.getPiece(i, j) != nullptr
                     && echiquier.getPiece(i, j)->estBlanc() != estBlanc_)
            {
                if (estBlanc_)
                {
                    if (std::abs(i - x_) == 1 && j - y_ == 1)
                        deplacementsSemiValides_.push_back({i, j});
                }
                else
                {
                    if (std::abs(i - x_) == 1 && j - y_ == -1)
                        deplacementsSemiValides_.push_back({i, j});
                }
            }
        }
    }
}
