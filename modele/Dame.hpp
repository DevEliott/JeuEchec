#pragma once
#include "./Echiquier.hpp"
#include "./Piece.hpp"


namespace modele
{
    class Dame : public Piece
    {
    public:
        Dame(int x, int y, bool couleur) : Piece::Piece(x, y)
        {
            estBlanc_ = couleur;
            nom_ = "Dame";
        }
        virtual void trouverDeplacementsSemiValides(Echiquier& echiquier) override;
    };
}
