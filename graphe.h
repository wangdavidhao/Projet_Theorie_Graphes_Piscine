#ifndef GRAPHE_H
#define GRAPHE_H
#include <string>
#include <unordered_map>
#include "sommet.h"
#include "arete.h"
#include "svgfile.h"
#include<algorithm>
#include "pareto.h"

/**
 * \file        graphe.h
 * \date       Du 15/04 au 21/04
 * \brief      Class graphe : contient les attributs et les fonctions utiles pour gerer un graphe
**/
class graphe
{
public:

    //Constructeur qui charge le graphe en mémoire
    graphe(std::string,std::string);

    ~graphe();

    //Fonction d'affichage des données du graphe dans la console
    void afficher(std::string nomGraphe) const;

    //Fonction d'affichage des données du graphe dans la console
    void dessinerGraphe(Svgfile& svgout, bool a)const;
    //Fonction qui va dessiner le graphe avec la pondération après Kruskal
    void dessinerGraphePonderation(Svgfile& svgout, bool poids)const;

    //Algorithme de kruskal qui retourne un vecteur d'arete
    std::vector<Arete*> algoKruskal(std::vector<Arete*> graphe, int ordre, int nb_arete, bool poids)const;


    //Fonction qui va séléctionner le nombre de "1" nécéssaire selon le graphe et retourne un vecteur de int avec la série de binaire
    std::vector<int> selectBinaire();
    //Fonction qui retourne un vecteur de vecteur de int pour les différents lots d'aretes
    std::vector<std::vector<int>> binaireTrie(std::vector<int> tabBinaire);
    //Fonction qui retourne un vecteur de vecteur de int qui va dire que les "1" vont représenter des int selon la position qui seront des id d'aretes
    std::vector<std::vector<int>> MatriceDeCasAretes(std::vector<std::vector<int>> matrice);


    //Fonction Pareto qui retourne un vecteur de vecteur d'arete  et va convertir les int en id d'arete
    std::vector<std::vector<Arete*>>paretoSansConnexe(std::vector<std::vector<int>> tabId);
    //Fonction Pareto qui va enlever les cas non connexes
   // std::vector<std::vector<Arete*>>garderSommetLies(std::vector<std::vector<Arete*>> tabId);

    std::vector<std::vector<Arete*>> paretoSansConnexite(std::vector<std::vector<Arete*>> tabId);

    //Fonctions qui vont retourner le cout total en prenant en paramètre un vecteur d'aretes
    float getPoidsTotalEnv(std::vector<Arete*> graphe)const;
    float getPoidsTotalFin(std::vector<Arete*> graphe)const;

    //Sous programme qui prend en parametre une vecteur de vecteur d'arete et qui return un vecteur Pareto
    std::vector<Pareto*>rechercheSolDominees(std::vector<std::vector<Arete*>> graphe);

    //Sous programme qui affiche les solution dominees et non dominees( frontiere de Pareto) d'un graphe
    void dessinFrontiereDePareto(Svgfile &svgout,std::vector<Pareto*>p,std::vector<std::vector<Arete*>> g)const;
    //Sous programme qui affiche les arbres couvrants des solutions non dominees
    void dessinPetitArbreCouvrant(Svgfile& svgout,std::vector<Arete*> A,int k, float x,float y, float poidsMax)const;


    //partie 3
   /* std::vector<std::vector<int>> selectBinaireArbre();
    std::vector<std::vector<Arete*>> paretoSansConnexePartie3(std::vector<std::vector<int>> tabId);
    std::vector<std::vector<Arete*>> garderSommetLiesPartie3(std::vector<std::vector<Arete*>> tabId);*/



private:
    //Le réseau est constitué d'une collection de sommets
    std::unordered_map<int,Sommet*> m_sommets;//stockée dans une map (clé=id du sommet, valeur= pointeur sur le sommet)
    std::vector<Arete*> mes_aretes; //Un vecteur d'aretes est stocké dans le graphe

};

#endif // GRAPHE_H
