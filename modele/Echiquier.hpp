#pragma once
#include "Piece.hpp"

#include <memory>
#include <utility>
#include <array>
#include <map>
#include <QObject>


namespace modele
{
	class Echiquier : public QObject
	{
		Q_OBJECT

	public:
        Echiquier();
        ~Echiquier() = default;
        std::unique_ptr<Piece>& getPiece(int x, int y) { return pieces_[x][y]; }
        std::unique_ptr<Piece>& getPiece(std::pair<int, int> coordonnees) { return pieces_[coordonnees.first][coordonnees.second]; }
        std::map<bool, std::pair<int, int>>& getCoordonneesRois() { return coordonneesRois_; }
        std::unique_ptr<Piece>& getPieceTampon() { return pieceTampon_; }
        std::unique_ptr<Piece>& getPieceTamponRoi() { return pieceTamponRoi_; }
        bool& EchecBlanc() {return echecBlanc_;}
        bool& EchecNoir() {return echecNoir_;}
        bool& blancAJouer() { return blancAJouer_; }
        bool matBlanc() { return matBlanc_; }
        bool matNoir() { return matNoir_; }
        bool patBlanc() { return patBlanc_; }
        bool patNoir() { return patNoir_; }
        std::pair<int, int> getPromotionCoordoonees() { return promotionCoordoonees_; }
        void setPromotionCoordoonees(std::pair<int, int> coordonnees) { promotionCoordoonees_ = coordonnees; }
        bool& getPromotion() { return promotion_; }
        void verificationEchec();
        void verificationMat();

	private:
		std::unique_ptr<Piece> pieces_[8][8];
		std::unique_ptr<Piece> pieceTampon_;
		std::unique_ptr<Piece> pieceTamponRoi_;
		std::map<bool, std::pair<int, int>> coordonneesRois_;
        std::pair<int, int> promotionCoordoonees_;
        bool promotion_;

        bool echecBlanc_ = false;
        bool echecNoir_ = false;
        bool matBlanc_ = false;
        bool matNoir_ = false;
        bool patBlanc_ = false;
        bool patNoir_ = false;
        bool blancAJouer_ = true;
	};
}
