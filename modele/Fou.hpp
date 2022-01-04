#pragma once
#include "./Echiquier.hpp"
#include "./Piece.hpp"


namespace modele
{
    class Fou : public Piece
    {
    public:
        Fou(int x, int y, bool couleur) : Piece::Piece(x, y)
        {
            estBlanc_ = couleur;
            nom_ = "Fou";
        }
        virtual void trouverDeplacementsSemiValides(Echiquier& echiquier) override;
    };
}
