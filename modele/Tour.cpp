#include "Tour.hpp"
#include <cmath>
#include <iostream>

void modele::Tour::trouverDeplacementsSemiValides(Echiquier& echiquier)
{
    deplacementsSemiValides_.clear();
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            int xVariation = 0;
            int yVariation = 0;
            if (i - x_ != 0 || j - y_ != 0)
            {
                if (x_ != i)
                {
                    if (i - x_ < 0)
                        xVariation = - 1;
                    else
                        xVariation = 1;
                    int k = 1;
                    for (; k <= std::abs(i - x_);)
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
                else if (y_ != j)
                {
                    if (j - y_ < 0)
                        yVariation = - 1;
                    else
                        yVariation = 1;
                    int k = 1;
                    for (; k <= std::abs(j - y_);)
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
}
