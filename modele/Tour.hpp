#pragma once
#include "./Echiquier.hpp"
#include "./Piece.hpp"


namespace modele
{
    class Tour : public Piece
    {
    public:
        Tour(int x, int y, bool couleur) : Piece::Piece(x, y)
        {
            estBlanc_ = couleur;
            nom_ = "Tour";
        }
        virtual void trouverDeplacementsSemiValides(Echiquier& echiquier) override;
    };
}
