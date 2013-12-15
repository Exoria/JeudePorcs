#include "Case.hpp"

Case::Case(const Map* map, const bool libre, const float source_largeur, const float source_hauteur,
           const float source_x, const float source_y, const int colonne, const int ligne, const string chemin_image):
    _map(map), _libre(libre), _source_largeur(source_largeur), _source_hauteur(source_hauteur),
    _source_x(source_x), _source_y(source_y), _colonne(colonne), _ligne(ligne), _chemin_image(chemin_image)
{
    this->init();
}

Case::~Case()
{
    al_destroy_bitmap(this->_image);
}

void Case::init()
{
    char* tmp = (char*)malloc(this->_chemin_image.size());
    strcpy(tmp, this->_chemin_image.c_str());

    this->_image = al_load_bitmap(tmp);
    if (!this->_image)
        fprintf(stderr, "impossible de charger l'image pour la bitmap correspondante à cette case !\n");

    free(tmp);
}

void Case::dessiner_case(ALLEGRO_DISPLAY *display)
{
    float dest_largeur = map.get_largeur_case();
    float dest_hauteur = map.get_hauteur_case();
    float dest_x = this->_colonne * dest_largeur;
    float dest_y = this->_ligne * dest_hauteur;

    al_set_target_bitmap(al_get_backbuffer(display));
    al_draw_scaled_bitmap(this->_image, this->_source_x, this->_source_y, this->_source_hauteur, this->_source_largeur,
                          dest_x, dest_y, dest_hauteur, dest_largeur, 0);
}

//////////////
// SETTEURS //
//////////////

void Case::set_chemin_image(const string chemin_image)
{
    this->_chemin_image = chemin_image;
    this->init();
}
