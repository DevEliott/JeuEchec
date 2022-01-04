#pragma once
#include <utility>

namespace modele
{
    class Echiquier;
    class Deplacement
    {
    public:
        virtual void trouverDeplacementsSemiValides(Echiquier& echiquier) = 0;
        virtual ~Deplacement() = default;
    };
}
