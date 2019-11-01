#include"arete.h"

/**
 * \file       arete.cpp
 * \date       Du 15/04 au 21/04
 * \brief      Permet de constuire une arete et de l'afficher
 *
**/

/**
 \brief Constructeur
*/
Arete::Arete() {}

/**
 \brief Constructeur
*/
Arete::Arete(int id_arete, Sommet* sommet_initial, Sommet* sommet_final,float cout_env,float cout_fin) :
    m_id{id_arete}, sommet_init{sommet_initial}, sommet_final{sommet_final},m_cout_env{cout_env},m_cout_fin{cout_fin}
{}

/**
 \brief Destructeur
*/
Arete::~Arete() {}

/**
    \brief Affiche l'id de l'arete
*/
void Arete::afficherArete()const
{
    std::cout<<"id: "<<m_id;
}

/**
 \brief Affiche l'id des sommets initiaux
 */
void Arete::afficherSommetsInitiaux() const
{
    std::cout<<"  sommet 1:  "<<this->sommet_init->getId();
}

/**
 \brief Affiche l'id des sommets finaux
 */
void Arete::afficherSommetsFinaux() const
{
    std::cout<<"  sommet 2:  "<<this->sommet_final->getId();
}

/**
 \brief Recupere l'id des aretes
 \return Retourne l'id de l'arete
 */
int Arete::getId( )const
{
    return m_id;
}

/**
 \brief Affiche le cout 2 (cout environnemental)
 */
void Arete::afficherCoutEnv()const
{
    std::cout<<"  poids 1:  "<<m_cout_env;
}

/**
 \brief Affiche le cout 1 (cout financier)
 */
void Arete::afficherCoutFin()const
{
    std::cout<<"  poids 2:  "<<m_cout_fin;
}
