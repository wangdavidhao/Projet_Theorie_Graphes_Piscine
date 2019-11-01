#ifndef PARETO_H_INCLUDED
#define PARETO_H_INCLUDED

#include<iostream>


/**
 * \file        Pareto.h
 * \date       Du 15/04 au 21/04
 * \brief      Class Pareto : contient les attributs et les fonctions utiles
**/
//Class Pareto qui se compose d'un bool selection, le poids1 total d'une solution et le poids2 d'une solution
class Pareto
{
public:
    //Constructeur
    Pareto(int id,bool selection,float poids1,float poids2);

    //Destructeur
    ~Pareto();
    //Differents get pour recuperer les données de la class

    /**
    \brief Recupere le cout 1 (financier)
    \return Retourne le cout 1
    */
    float getPoids1()const
    {

        return m_poids1;
    }

    /**
    \brief Recupere le cout 2 (environnemental)
    \return Retourne le cout 2
    */
    float getPoids2()const
    {
        return m_poids2;
    }

    /**
    \brief Recupere le bool de selection
    \return Retourne le bool de selection
    */
    bool getSelection()const
    {
        return m_selection;
    }

    /**
    \brief Permet de modifier le bool de selection de la clase
    */
    void setSelection(bool new_selection)
    {
        m_selection=new_selection;
    }
    int getId()const
    {
        return m_id;
    }

    //Affichage des donnees de la class
    void afficherparetopoids()const;
private:

    float m_poids1;//cout total du poids financier
    float m_poids2;//Cout total du poids environnemental

    bool m_selection;//Bool pour différencier les solutions dominees et non dominees
    int m_id;

};

#endif // PARETO_H_INCLUDED
