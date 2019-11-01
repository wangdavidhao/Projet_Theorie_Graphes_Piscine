#ifndef SOMMET_H
#define SOMMET_H
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>



/**
 * \file        Sommet.h
 * \date       Du 15/04 au 21/04
 * \brief      Class Sommet : contient les attributs et les fonctions utiles pour gerer un sommet
 *
**/

class Sommet
{
public:

    //constructeur qui reçoit en params les données du sommet
    Sommet(int,double,double);
    Sommet(int id);
    Sommet();

    void afficherData() const;
    void afficherId() const;


    //int getM_id()const;
    int getDegre()const;
    int getId()const;


    /**
    \brief Recupere le coordonnee X du sommet
    \return Retourne la coordonnee X du sommet
    */
    double getX()const
    {
        return m_x;
    }
    /**
    \brief Recupere le coordonnee Y du sommet
    \return Retourne la coordonnee Y du sommet
    */
    double getY()const
    {
        return m_y;
    }

    void setId(int new_id)
    {
        m_id=new_id;
    }

    ~Sommet();

private:
    // Voisinage : liste d'adjacence
    std::vector<const Sommet*> m_voisins;

    // Données spécifiques du sommet
    int m_id; // Identifiant
    double m_x, m_y; // Position

};

#endif // SOMMET_H
