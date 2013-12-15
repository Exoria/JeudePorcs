#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED
#include <stdexcept>
#include "Case.hpp"
#include <cmath>
using namespace std;

class Case;

class Map {
    public:
        Map(const float largeur_case, const float hauteur_case, const int nb_colonnes, const int nb_lignes, const string textures);
        virtual ~Map();

        const bool ajouter_case(Case* une_case);
        void dessiner(ALLEGRO_DISPLAY* display);

        // GETTEURS
        const float get_largeur_case() const {return this->_largeur_case;};
        const float get_hauteur_case() const {return this->_hauteur_case;};
        const Case* get_case(const float pos_x, const float pos_y);

    private:
        const float _largeur_case;
        const float _hauteur_case;
        const int   _nb_colonnes;
        const int   _nb_lignes;
        Case** _cases;
        ALLEGRO_BITMAP* _textures;
};

#endif // MAP_HPP_INCLUDED
