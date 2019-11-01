#include <iostream>
#include <queue>
#include <stack>
#include<unordered_map>
#include<unordered_set>
#include "sommet.h"


/**
 * \file        sommet.cpp
 * \date       Du 15/04 au 21/04
 * \brief      Permet de constuire un sommet et de l'afficher
 *
**/


/**
 \brief Constructeur
*/
Sommet::Sommet(int id,double x,double y):m_id{id},m_x{x},m_y{y}
{
}

/**
 \brief Constructeur
*/
Sommet::Sommet(int id) : m_id{id} {}

/**
 \brief Constructeur
*/
Sommet::Sommet() {}

/**
 \brief Affiche coordonnees des sommets
*/
void Sommet::afficherData() const
{
    std::cout<<"    "<<m_id<<" : "<<"(x,y)=("<<m_x<<","<<m_y<<")"<<std::endl;
}

/**
 \brief Affiche l'id des sommetts
*/
void Sommet::afficherId() const
{
    std::cout<<m_id<<std::endl;
}

/*
std::unordered_map<int,int> Sommet::parcoursBFS() const
{
    std::unordered_map<int,int> l_pred;


    std::queue<const Sommet *> file_sommets;
    file_sommets.push(this);
    const Sommet* sommet;

    while(!(file_sommets.empty())) //tant que la file n'est pas vide
    {

        sommet=file_sommets.front(); //On accède au prochain élément et on l'enlève de la file, on nouveau sommet servira de départ
        file_sommets.pop();

        for(const auto &it : sommet->m_voisins)
        {
            if((l_pred.find(it->m_id) == l_pred.end())  &&  (it!=this))  //Si trouve un voisin et différent de lui-même
            {
                file_sommets.push(it);  //Ajout dans la file
                l_pred.insert({it->m_id, sommet->m_id});  //Ajout dans la map du sommet voisin juste après le sommet marqué
            }

        }

    }
    return l_pred;
}

std::unordered_map<int,int> Sommet::parcoursDFS() const
{
    std::unordered_map<int,int> l_pred;


    std::stack<const Sommet *> pile_sommets;
    pile_sommets.push(this);
    const Sommet* sommet;

    while(!(pile_sommets.empty())) //tant que la file n'est pas vide
    {

        sommet=pile_sommets.top(); //On accède au prochain élément et on l'enlève de la file, on nouveau sommet servira de départ
        pile_sommets.pop();

        for(const auto &it : sommet->m_voisins)
        {
            if((l_pred.find(it->m_id) == l_pred.end())  &&  (it!=this))  //Si trouve un voisin et différent de lui-même
            {
                pile_sommets.push(it);  //Ajout dans la file
                l_pred.insert({it->m_id, sommet->m_id});  //Ajout dans la map du sommet voisin juste après le sommet marqué
            }


        }

    }

    return l_pred;
}


std::unordered_set<int> Sommet::rechercherCC() const
{
    std::unordered_set<int> cc;
    std::unordered_map<int,int> l_pred;

    l_pred=parcoursBFS();



    for(const auto s : l_pred)  //Parcours de la map
    {

        cc.insert(s.first);  //On l'insère dans set

    }


    return cc;
}

*/

/**
 \brief Recupere l'id des sommetts
*/
int Sommet:: getId()const
{
    return m_id;
}

/**
 \brief Affiche le degre des sommets
 \param Retourne
*/
int Sommet::getDegre()const
{
    return m_voisins.size();
}

/**
 \brief Destructeur
*/
Sommet::~Sommet()
{
    //dtor
}
