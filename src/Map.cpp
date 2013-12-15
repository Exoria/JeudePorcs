#include "Map.hpp"

////////////
// PUBLIC //
////////////

Map::Map(const float largeur_case, const float hauteur_case, const int nb_colonnes, const int nb_lignes, const string textures)
:   _largeur_case(largeur_case)
,   _hauteur_case(hauteur_case)
,   _nb_colonnes(nb_colonnes)
,   _nb_lignes(nb_lignes)
,   _cases(NULL)
{
    this->_cases = new Case*[this->_nb_colonnes * this->_nb_lignes];
    for (int i = 0; i < this->_nb_colonnes; i++) {
        for (int j = 0; j < this->_nb_lignes; j++)
            this->_cases[j * this->_nb_colonnes + i] = NULL;
    }

    this->_textures = al_load_bitmap(textures.c_str());
    if (!this->_textures)
        fprintf(stderr, "Impossible de charger l'image pour la bitmap correspondante à cette case !\n");
}

Map::~Map()
{
    delete[] this->_cases;
}

const bool Map::ajouter_case(Case* une_case)
{
    bool retour = true;

    try {
        if (this->_cases[une_case->get_colonne() * this->_nb_colonnes + une_case->get_ligne()] == NULL)
            this->_cases[une_case->get_colonne() * this->_nb_colonnes + une_case->get_ligne()] = une_case;
        else
            retour = false;
    } catch (out_of_range oor) {
        retour = false;
    }

    return retour;
}

void Map::dessiner(ALLEGRO_DISPLAY* display)
{
    for (int i = 0; i < this->_nb_colonnes; i++) {
        for (int j = 0; j < this->_nb_lignes; j++)
            this->_cases[j * this->_nb_colonnes + i]->dessiner_case(display, this->_textures);
    }
}

// GETTEURS

const Case* Map::get_case(const float pos_x, const float pos_y) const
{
    int colonne = floor(pos_x / this->_largeur_case);
    int ligne   = floor(pos_y / this->_hauteur_case);

    if (colonne < 0 || colonne >= _nb_colonnes || ligne < 0 || ligne >= _nb_lignes)
		return NULL;

    return this->_cases[colonne * this->_nb_colonnes + ligne];
}
