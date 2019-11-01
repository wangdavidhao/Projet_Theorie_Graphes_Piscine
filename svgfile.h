#ifndef SVGFILE_H_INCLUDED
#define SVGFILE_H_INCLUDED
#include <string>
#include <fstream>
#include <set>


/**
 * \file        svgfile.h
 * \date       Du 15/04 au 21/04
 * \brief      Class Svgfile : contient les attributs et les fonctions utiles pour gerer l'affichage sur le svgout
**/

constexpr char defcol[] = "black";

class Svgfile
{
public:
    /** \brief Constructeur : ouverture du fichier output et mise en place des dimensions de l'écran
    */
    Svgfile(std::string _filename = "output.svg", int _width=1600, int _height=900);

    /** \brief Destructeur
    */
    ~Svgfile();

    /**
    \brief Fonction qui permet de dessiner un disque
    \param x de type double
    \param y de type double
    \param r (rayon) de type double
    \param color de type std::string
    */
    void addDisk(double x, double y, double r, std::string color=defcol);

    /**
    \brief Fonction qui permet de dessiner un cercle
    \param x de type double
    \param y de type double
    \param ep de type double
    \param r (rayon) de type double
    \param color de type std::string
    */
    void addCircle(double x, double y, double r, double ep, std::string color=defcol);


    /**
    \brief Fonction qui permet de dessiner un triangle
    \param x1 de type double
    \param x2 de type double
    \param x3 de type double
    \param y1 de type double
    \param y2 de type double
    \param y3 de type double
    \param colorFill de type std::string
    \param colorStroke de type std::string
    */
    void addTriangle(double x1, double y1, double x2, double y2,
                     double x3, double y3, std::string colorFill,
                     double thickness, std::string colorStroke);

    /**
    \brief Fonction qui permet de dessiner un triangle
    \param x1 de type double
    \param x2 de type double
    \param x3 de type double
    \param y1 de type double
    \param y2 de type double
    \param y3 de type double
    \param colorFill de type std::string
    */
    void addTriangle(double x1, double y1, double x2, double y2,
                     double x3, double y3, std::string colorFill=defcol);


    /**
    \brief Fonction qui permet de dessiner une ligne
    \param x1 de type double
    \param x2 de type double
    \param y1 de type double
    \param y2 de type double
    \param color de type std::string
    */
    void addLine(double x1, double y1, double x2, double y2, std::string color=defcol);

    /**
    \brief Fonction qui permet de dessiner une croix
    \param x de type double
    \param y de type double
    \param span de type double
    \param color de type std::string
    */
    void addCross(double x, double y, double span, std::string color=defcol);

    /**
    \brief Fonction qui permet d'écrire un texte
    \param x de type double
    \param y de type double
    \param text de type std::string
    \param color de type std::string
    */
    void addText(double x, double y, std::string text, std::string color=defcol);

    /**
    \brief Fonction qui permet d'écrire un texte
    \param x de type double
    \param y de type double
    \param val de type double
    \param color de type std::string
    */
    void addText(double x, double y, double val, std::string color=defcol);

    /**
    \brief Fonction qui permet d'afficher une grille
    \param span de type double
    \param numbering de type double
    \param color de type std::string
    */
    void addGrid(double span=100.0, bool numbering=true, std::string color="lightgrey");

    static std::string makeRGB(int r, int g, int b);

    // Type non copiable
    Svgfile(const Svgfile&) = delete;
    Svgfile& operator=(const Svgfile&) = delete;

private:
    std::string m_filename;
    std::ofstream m_ostrm;
    int m_width;
    int m_height;

    // Pour éviter les ouverture multiples
    static std::set<std::string> s_openfiles;
};


#endif // SVGFILE_H_INCLUDED
