#include "Case.hpp"

Case::Case()
{
}

Case::Case(const Map* ma_map, const bool libre, const float source_largeur, const float source_hauteur,
           const float source_x, const float source_y, const int colonne, const int ligne)
:   _map(ma_map)
,   _libre(libre)
,   _source_largeur(source_largeur)
,   _source_hauteur(source_hauteur)
,   _source_x(source_x)
,   _source_y(source_y)
,   _colonne(colonne)
,   _ligne(ligne)
{
}

Case::~Case()
{
}

void Case::dessiner_case(ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* bitmap)
{
    float dest_largeur = this->_map->get_largeur_case();
    float dest_hauteur = this->_map->get_hauteur_case();
    float dest_x = this->_colonne * dest_largeur;
    float dest_y = this->_ligne * dest_hauteur;

    al_set_target_bitmap(al_get_backbuffer(display));
    al_draw_scaled_bitmap(bitmap, this->_source_x, this->_source_y, this->_source_hauteur, this->_source_largeur,
                          dest_x, dest_y, dest_hauteur, dest_largeur, 0);
}
