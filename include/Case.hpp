#ifndef CASE_HPP
#define CASE_HPP

#include <allegro5/allegro.h>
#include <string>
#include <stdio.h>
#include "Map.hpp"
using namespace std;

class Case
{
    public:
        Case(const Map* ma_map, const bool libre, const float source_largeur, const float source_hauteur,
             const float source_x, const float source_y, const int colonne, const int ligne, const string chemin_image);
        ~Case();
        void dessiner_case(ALLEGRO_DISPLAY *display);

        // GETTEURS
        const ALLEGRO_BITMAP *get_image()          const {return this->_image;};
        const Map            *get_map()            const {return this->_map;};
        const bool            get_libre()          const {return this->_libre;};
        const float           get_source_largeur() const {return this->_source_largeur;};
        const float           get_source_hauteur() const {return this->_source_hauteur;};
        const float           get_source_x()       const {return this->_source_x;};
        const float           get_source_y()       const {return this->_source_y;};
        const int             get_colonne()        const {return this->_colonne;};
        const int             get_ligne()          const {return this->_ligne;};
        const string          get_chemin_image()   const {return this->_chemin_image;};

        // SETTEURS
        // pas de setteur pour le ALLEGRO_BITMAP, il faut changer le _chemin_image
        void set_map(const Map *ma_map)                     {this->_map = new Map(ma_map);};
        void set_libre(const bool libre)                    {this->_libre = libre;};
        void set_source_largeur(const float source_largeur) {this->_source_largeur = source_largeur;};
        void set_source_hauteur(const float source_hauteur) {this->_source_hauteur = source_hauteur;};
        void set_source_x(const float source_x)             {this->_source_x = source_x;};
        void set_source_y(const float source_y)             {this->_source_y = source_y;};
        void set_colonne(const int colonne)                 {this->_colonne = colonne;};
        void set_ligne(const int ligne)                     {this->_ligne = ligne;};
        void set_chemin_image(const string chemin_image);

    private:
        ALLEGRO_BITMAP *_image;
        Map   *_map;
        bool   _libre;
        float  _source_largeur;
        float  _source_hauteur;
        float  _source_x;
        float  _source_y;
        int    _colonne;
        int    _ligne;
        string _chemin_image;

        void init();
};

#endif // CASE_HPP
