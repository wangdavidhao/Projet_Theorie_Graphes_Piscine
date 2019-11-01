#include "pareto.h"

/**
 * \file       pareto.cpp
 * \date       Du 15/04 au 21/04
 * \brief      Utile pour l'optimisation : permet de determiner les solutions dominees et non dominees et d'afficher la fontiere de pareto
**/


/**
* \brief Constructeur
*/
Pareto::Pareto(int id,bool selection,float poids1,float poids2)
    : m_id{id},m_selection{selection},m_poids1{poids1},m_poids2{poids2}
{}


/**
* \brief Destructeur
*/
Pareto::~Pareto() {}


/**
* \brief Affichage des donnees de la class
*/
void Pareto::afficherparetopoids()const
{
    std::cout<<m_id<<"  "<<m_selection<<"  "<<m_poids1<<"  "<<m_poids2<<std::endl;
}
