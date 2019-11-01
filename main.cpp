//CORMIER EMMA JANOT CLEMENT WANG DAVID TD8//
//PROJET PISCINE THEORIE DES GRAPHES//
//DU 15/04/2019 AU 21/04/2019//

#include <iostream> //Bibliothèques
#include "graphe.h"
#include<string>
#include<algorithm>
#include"console.h"

//Fonction de blindage récupéré dans le cours 4
void saisie(int&x, std::string message)
{
    if(!message.empty())
        std::cout<<message;
    std::string ligne;
    bool correct;

    do
    {
        std::getline(std::cin, ligne);
        correct = ligne.size()>0 && ligne.size()<10;
        for (size_t i=0; correct && i<ligne.size(); ++i)
            if ( ligne[i]<'0' || ligne[i]>'9' )
                correct = false;
        if (!correct)
            std::cout << "Entier positif attendu: ";
    }
    while (!correct);
    x = std::stoul(ligne);

}




/**
 * \file       main
 * \date       Du 15/04 au 21/04
 * \brief      Entree du programme
**/

int main()
{
    Console *pConsole=NULL;
    pConsole=Console::getInstance();

    std::string nomFichier;
    std::string txt;
    std::string weight;
    std::string cast_nb;
    int nb,choix;

    std::cout<<"Saisissez le nom du fichier a charger :"<<std::endl;
    std::cin>> nomFichier;

    saisie(nb,"Saisissez le poids du fichier a charger :");

    cast_nb=std::to_string(nb);

    txt=nomFichier+".txt";
    weight=nomFichier+"_weights_"+cast_nb+".txt";

    graphe g{txt,weight};

    do
    {
        std :: cout<< std::endl<<std::endl;
        std :: cout << "1. Afficher les donnees du graphe sur la console" << std :: endl;
        std :: cout << "2. Dessiner le graphe"<< std :: endl;
        std :: cout << "3. Dessiner kruskal en fonction des couts 1 ou couts 2"<< std :: endl;
        std :: cout << "4. Afficher la frontiere de Pareto dans le SVG avec le nombre d'optimum dans la console"<< std :: endl;
        std::cout<<"0. Quitter le programme "<<std::endl;
        saisie(choix,"Quel est votre choix ?");
        system("cls");
        std::cout<<std::endl;

        switch(choix)
        {
        case 1:
            g.afficher(nomFichier);
            break;
        case 2:
        {
            Svgfile svgout;
            svgout.addGrid();
            g.dessinerGraphe(svgout,true);
        }
        break;
        case 3 :
        {
            Svgfile svgout;
            svgout.addGrid();
            bool poids;
            std :: cout << "Taper 0 pour un kruskal en fonction du cout fin ou 1 pour un kruskal en fonction du cout env : ";
            std :: cin >> poids;
            g.dessinerGraphePonderation(svgout, poids);
            g.dessinerGraphe(svgout,false);
        }
        break;
        case 4 :
        {
            std::vector<int> test;
            std::vector<std::vector<int>> matrice;
            std::vector<std::vector<int>> m;

            test=g.selectBinaire();
            matrice=g.binaireTrie(test);
            m=g.MatriceDeCasAretes(matrice);


            std::vector<std::vector<Arete*>> tabArete;

            tabArete=g.paretoSansConnexe(m);

            std::vector<std::vector<Arete*>> J;

            J=g.paretoSansConnexite(tabArete);

            std::vector<Pareto*>n;

            n=g.rechercheSolDominees(J);


            Svgfile svgout;
            svgout.addGrid();

            g.dessinerGraphe(svgout,false);
            g.dessinFrontiereDePareto(svgout,n,J);

        }

        break;
        }

    }
    while (choix!=0);

    //Lieu des tests

        /*std::vector<std::vector<int>> z;
        z=g.selectBinaireArbre();

        std::vector<std::vector<int>> y;
        y=g.MatriceDeCasAretes(z);

        std::vector<std::vector<Arete*>> tabArete2;
        tabArete2=g.paretoSansConnexePartie3(y);

        std::vector<std::vector<Arete*>> w;
        w=g.garderSommetLiesPartie3(tabArete2);*/


    return 0;
}
