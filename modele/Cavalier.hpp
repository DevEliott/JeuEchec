#pragma once
#include "./Echiquier.hpp"
#include "./Piece.hpp"


namespace modele
{
    class Cavalier : public Piece
    {
    public:
        Cavalier(int x, int y, bool couleur) : Piece::Piece(x, y)
        {
            estBlanc_ = couleur;
            nom_ = "Cavalier";
        }
        virtual void trouverDeplacementsSemiValides(Echiquier& echiquier) override;
    };
}
