#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED
#include<string>
#include<iostream>
#include"sommet.h"
/**
 * \file        arete.h
 * \date       Du 15/04 au 21/04
 * \brief      Class Arete : contient les attributs et les fonctions utiles pour gerer une arete
**/

class Arete
{

public:

    //Constructeur par défaut
    Arete();

    //Constructeur

    Arete(int id_arete, Sommet* sommet_initial, Sommet* sommet_final, float cout_env,float cout_fin);

    //Destructeur

    ~Arete();

    //Affiche l'id de l'arete

    void afficherArete()const;


    //brief Affiche l'id des sommets initiaux

    void afficherSommetsInitiaux()const;

    //Affiche l'id des sommets finaux
    void afficherSommetsFinaux()const;

    void afficherCoutFin()const;

    void afficherCoutEnv()const;

    /**
    \brief Recupere le cout 2 (environnemental)
    \return Retourne le cout 2
    */
    float getCoutEnv()const
    {

        return m_cout_env;
    }

    /**
    \brief Recupere le cout 1 (financier)
    \return Retourne le cout 1
    */
    float getCoutFinancier()const
    {

        return m_cout_fin;
    }


    int getId() const;

    /**
    \brief Recupere la coordonnee X du sommet initial
    \return Retourne la coordonnee X du sommet initial
    */
    double getSommetInitialX()const
    {
        return sommet_init->getX();
    }

    /**
    \brief Recupere la coordonnee Y du sommet initial
    \return Retourne la coordonnee Y du sommet initial
    */
    double getSommetInitialY()const
    {
        return sommet_init->getY();
    }

    /**
    \brief Recupere la coordonnee X du sommet final
    \return Retourne la coordonnee X du sommet final
    */
    double getSommetFinalX()const
    {
        return sommet_final->getX();
    }

    /**
    \brief Recupere la coordonnee Y du sommet final
    \return Retourne la coordonnee Y du sommet final
    */
    double getSommetFinalY()const
    {
        return sommet_final->getY();
    }

    /**
    \brief Recupere l'id du sommet initial
    \return Retourne l'id du sommet initial
    */
    int getIdInit()const
    {
        return sommet_init->getId();
    }

    /**
    \brief Recupere l'id du sommet final
    \return Retourne l'id du sommet final
    */
    int getIdFinal()const
    {
        return sommet_final->getId();
    }

private:

    double m_x1,m_y1;
    double m_x2,m_y2;

    Sommet* sommet_init;
    Sommet* sommet_final;

    float m_cout_env;
    float m_cout_fin;

    int m_id;

};

#endif // ARETE_H_INCLUDED
