#pragma once
#include "./Echiquier.hpp"
#include "./Piece.hpp"


namespace modele
{
    class Pion : public Piece
    {
    public:
        Pion(int x, int y, bool couleur) : Piece::Piece(x, y)
        {
            estBlanc_ = couleur;
            nom_ = "Pion";
        }
        virtual void trouverDeplacementsSemiValides(Echiquier& echiquier) override;
        bool& premierDeplacement() { return premierDeplacement_; }
    private:
        bool premierDeplacement_ = true;
    };
}
