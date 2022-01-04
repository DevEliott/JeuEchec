#pragma once
#include "./Deplacement.hpp"
#include <string>
#include <vector>


namespace modele
{
    class Piece : public Deplacement
    {
    public:
        Piece() = default;
        Piece(int x, int y);
        virtual ~Piece() = default;
        int& getX() { return x_; }
        int& getY() { return y_; }
        std::pair<int, int> getCoordonnees() const { return { x_, y_ }; };
        std::string& getNom() { return nom_; }
        bool estBlanc() const { return estBlanc_; }

        std::vector<std::pair<int, int>> getDeplacementsSemiValides() const { return deplacementsSemiValides_; }
        std::vector<std::pair<int, int>> getDeplacementsValides() const { return deplacementsValides_; }
        bool peutBouger(Echiquier&echiquier, std::pair<int, int> arrivee);
        void bouger(Echiquier& echiquier, std::pair<int, int> arrivee);
        void promotion(Echiquier& echiquier, std::pair<int, int> arrivee);
        virtual void trouverDeplacementsValides(Echiquier& echiquier);

    protected:
        int x_ = 0;
        int y_ = 0;
        bool estBlanc_ = false;
        std::string nom_;
        std::vector<std::pair<int, int>> deplacementsSemiValides_;
        std::vector<std::pair<int, int>> deplacementsValides_;
    };
}
