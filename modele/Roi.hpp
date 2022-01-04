#pragma once
#include "./Echiquier.hpp"
#include "./Piece.hpp"

#include <iostream>


namespace modele
{
    class Roi : public Piece
    {
    public:
        static inline int compteurInstance = 0;
        Roi(int x, int y, bool couleur) : Piece::Piece(x, y)
        {
            estBlanc_ = couleur;
            nom_ = "Roi";
            compteurInstance += 1;
//            if (compteurInstance > 2)
//                throw std::string("Le jeu a tente de creer un nouveau Roi, alors qu'il y en a deja 2 sur l'echiquier.");
        }
        bool estEnEchec(Echiquier& echiquier);
        virtual void trouverDeplacementsSemiValides(Echiquier& echiquier) override;
        virtual void trouverDeplacementsValides(Echiquier& echiquier) override;
    };
}
