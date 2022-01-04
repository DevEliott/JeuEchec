#pragma once
#include "Echiquier.hpp"
#include "Piece.hpp"

#include <QObject>


namespace modele
{
    class Jeu : public QObject
	{
        Q_OBJECT

	public:
        Jeu() = default;
		~Jeu() = default;

        Echiquier& getEchiquier() { return echiquier_; }
        bool& deplacementFait() { return deplacementFait_; }
        bool& partieTerminee() { return partieTerminee_; }
        void effectuerSonTour();
        void effectuerDeplacement();

	private:
		Echiquier echiquier_;
		bool deplacementFait_ = false;
		bool partieTerminee_ = false;

        bool case1DejaCliquee_ = false;
        std::pair<int, int> case1_;
        std::pair<int, int> case2_;

    signals:
        void envoyerReponse(bool tourFait, QString reponse,
                            std::pair<int, int> anciennePiece = {0, 0},
                            std::pair<int, int> pieceBougee = {0, 0});
        void casesValides(std::vector<std::pair<int, int>> casesValides);
        void repeindre();
        void plusDeDeuxRois();
        void promotion(std::pair<int, int>);
        void mat(bool);
        void pat(bool);

    public slots:
        void recevoirCaseCliquee(std::pair<int, int> caseCliquee);
        void recevoirCaseDecliquee();
	};
}
