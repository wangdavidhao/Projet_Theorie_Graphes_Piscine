#include <fstream>
#include <iostream>
#include "svgfile.h"
#include "graphe.h"
#include<sstream>
#include<algorithm>
#include"console.h"

/**
 * \file       graphe.cpp
 * \date       Du 15/04 au 21/04
 * \brief      Permet de gerer le graphe (chargement, affichage etc...)
 *
**/


/**
* \brief Constructeur : charge le graphe
* \param nomFichier1 de type string
* \param nomFichier2 de type string
*/
graphe::graphe(std::string nomFichier1,std::string nomFichier2)
{
    Console *pConsole=NULL;
    pConsole=Console::getInstance();

    std::ifstream ifs1{nomFichier1};
    std::ifstream ifs2{nomFichier2};

    std::cout<<"fichier : ";
    pConsole->setColor(COLOR_GREEN);
    std::cout<<nomFichier1<<std::endl;
    pConsole->setColor(COLOR_DEFAULT);
    std::cout<<"fichier poids : ";
    pConsole->setColor(COLOR_GREEN);
    std::cout<<nomFichier2<<std::endl;
    pConsole->setColor(COLOR_DEFAULT);

    if (!ifs1)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier1 );

    if (!ifs2)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier2 );

    int ordre;
    ifs1 >> ordre;
    if ( ifs1.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    int id;
    double x,y;
    //lecture des sommets
    for (int i=0; i<ordre; ++i)
    {
        ifs1>>id;
        if(ifs1.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        ifs1>>x;
        if(ifs1.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        ifs1>>y;
        if(ifs1.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        m_sommets.insert({id,new Sommet{id,x,y}});
    }
    int taille1;
    ifs1 >> taille1;
    if ( ifs1.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");

    int taille2;
    ifs2>> taille2;
    if ( ifs2.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");
    int nbrDePoids;
    ifs2>>nbrDePoids;


    int id_arete_fichier1;
    int id_arete_fichier2;

    Sommet* sommetIni;
    Sommet* sommetFin;
    int som1;
    int som2;
    float cout_env;
    float cout_fin;

    double Sx1,Sx2,Sy1,Sy2;

    //lecture des aretes
    if(taille1==taille2)
    {
        for (int i=0; i<taille1; ++i)
        {
            //lecture des ids des deux extrémités

            ifs1>>id_arete_fichier1;
            ifs1>>som1;
            ifs1>>som2;
            if(m_sommets.find(som1)!=m_sommets.end())
            {
                sommetIni=(m_sommets.find(som1))->second;
                Sx1=sommetIni->getX();
                Sy1=sommetIni->getY();
            }

            if(m_sommets.find(som2)!=m_sommets.end())
            {
                sommetFin=(m_sommets.find(som2))->second;
                Sx2=sommetFin->getX();
                Sy2=sommetFin->getY();
            }

            ifs2>>id_arete_fichier2;
            if(id_arete_fichier1==id_arete_fichier2)
            {
                ifs2>>cout_env;
                ifs2>>cout_fin;
            }

            mes_aretes.push_back(new Arete(id_arete_fichier1,new Sommet{som1,Sx1,Sy1},new Sommet{som2,Sx2,Sy2},cout_env,cout_fin));
        }
    }
}


/**
 * \brief       Fonction d'affichage des donnees du graphe dans la console
 * \details    On parcourt la liste des sommets et des aretes
 * \param      nomGraphe de type string
 */
void graphe::afficher(std::string nomGraphe) const
{
    std::cout<<"Voici les donnees du graphe : "<<nomGraphe<<std::endl;
    std::cout<<"ordre : "<<m_sommets.size()<<std::endl;
    for(auto it=m_sommets.cbegin(); it!=m_sommets.cend(); ++it)
    {
        std::cout<<"sommet :";
        it->second->afficherData();


    }
    std::cout<<std::endl;
    std::cout<<"nombre d'aretes : "<<mes_aretes.size()<<std::endl;
    for(size_t i=0; i<mes_aretes.size(); ++i)
    {
        mes_aretes[i]->afficherArete();
        mes_aretes[i]->afficherSommetsInitiaux();
        mes_aretes[i]->afficherSommetsFinaux();
        std::cout<<std::endl;


    }
    std::cout<<std::endl;
    std::cout<<"nombre d'aretes : "<<mes_aretes.size()<<std::endl;
    for(size_t i=0; i<mes_aretes.size(); ++i)
    {
        mes_aretes[i]->afficherArete();
        mes_aretes[i]->afficherCoutEnv();
        mes_aretes[i]->afficherCoutFin();
        std::cout<<std::endl;

    }


}


/**
 * \brief       Dessine le graphe (sommets + id d'aretes) sur le svgout
 * \param       &svgout de type Svgfile pour pouvoir afficher le graphe sur le svgout
 */
void graphe :: dessinerGraphe(Svgfile& svgout,bool a) const
{

    for(size_t i=0; i<mes_aretes.size(); ++i)
    {
        svgout.addLine(mes_aretes[i]->getSommetInitialX(), mes_aretes[i]->getSommetInitialY(),mes_aretes[i]->getSommetFinalX(), mes_aretes[i]->getSommetFinalY(), "black");
        svgout.addText((mes_aretes[i]->getSommetInitialX()+mes_aretes[i]->getSommetFinalX())/2,(mes_aretes[i]->getSommetInitialY()+mes_aretes[i]->getSommetFinalY())/2,mes_aretes[i]->getId(), "red");
    }
    for(auto it=m_sommets.cbegin(); it!=m_sommets.cend(); ++it)
    {
        svgout.addDisk(it->second->getX(),it->second->getY(),10,"white");
        svgout.addCircle(it->second->getX(),it->second->getY(),10,2,"black");
        if(it->first<10)
        {
            svgout.addText(it->second->getX()-3,it->second->getY()+5,it->second->getId(),"black");
        }
        else
            svgout.addText(it->second->getX()-9,it->second->getY()+5,it->second->getId(),"black");
    }
    if(a==true)
    {

        for(size_t i=0; i<mes_aretes.size(); ++i)
        {

            svgout.addLine((mes_aretes[i]->getSommetInitialX())+500, mes_aretes[i]->getSommetInitialY(),mes_aretes[i]->getSommetFinalX()+500, mes_aretes[i]->getSommetFinalY(), "black");

            svgout.addText((mes_aretes[i]->getSommetInitialX()+550+mes_aretes[i]->getSommetFinalX()+450)/2,(mes_aretes[i]->getSommetInitialY()+mes_aretes[i]->getSommetFinalY())/2,mes_aretes[i]->getCoutEnv(), "red");

            svgout.addText((mes_aretes[i]->getSommetInitialX()+560+mes_aretes[i]->getSommetFinalX()+460)/2,(mes_aretes[i]->getSommetInitialY()+mes_aretes[i]->getSommetFinalY())/2," ;", "red");

            svgout.addText((mes_aretes[i]->getSommetInitialX()+570+mes_aretes[i]->getSommetFinalX()+470)/2,(mes_aretes[i]->getSommetInitialY()+mes_aretes[i]->getSommetFinalY())/2,mes_aretes[i]->getCoutFinancier(), "red");

            for(auto it=m_sommets.cbegin(); it!=m_sommets.cend(); ++it)
            {


                svgout.addDisk(it->second->getX()+500,it->second->getY(),10,"white");
                svgout.addCircle(it->second->getX()+500,it->second->getY(),10,2,"black");
                if(it->first<10)
                {
                    svgout.addText(it->second->getX()+495,it->second->getY()+5,it->second->getId(),"black");
                }
                else
                    svgout.addText(it->second->getX()+495-3,it->second->getY()+5,it->second->getId(),"black");
            }
        }
    }



}

/**
 * \brief       Recupere le cout total environnement
 * \param       graphe <Arete*> graphe
 * \return      Retourne le cout environnemental total
 */
float graphe:: getPoidsTotalEnv(std::vector<Arete*> graphe) const
{
    float coutTotalPoidsEnv=0;
    for(size_t i=0; i<graphe.size(); ++i)
    {
        coutTotalPoidsEnv+=graphe[i]->getCoutEnv();
    }
    return coutTotalPoidsEnv;

}


/**
 * \brief       Recupere le cout total financier
 * \param       std::vector <Arete*> graphe
 * \return      Retourne le cout financier total
 */
float  graphe::getPoidsTotalFin(std::vector<Arete*> graphe) const
{
    float coutTotalPoidsFin=0;
    for(size_t i=0; i<graphe.size(); ++i)
    {
        coutTotalPoidsFin+=graphe[i]->getCoutFinancier();
    }
    return coutTotalPoidsFin;

}


/**
 * \brief       Dessine le graphe avec la ponderation apres Kruskal sur le svgout
 * \param       &svgout de type Svgfile pour pouvoir afficher le graphe sur le svgout
 * \param       &poids de type bool pour pouvoir afficher le graphe de Krukal en fonction du cout fin (poids = 0) ou en fonction du cout fin (poids = 1) svgout
 */
void graphe :: dessinerGraphePonderation(Svgfile& svgout, bool poids) const
{
    std::vector<Arete*> grapheApresTriEnv;
    std::vector<Arete*> grapheApresTriFin;
    //bool poids;
    grapheApresTriEnv=algoKruskal(mes_aretes,m_sommets.size(),mes_aretes.size(),poids);
    grapheApresTriFin=algoKruskal(mes_aretes,m_sommets.size(),mes_aretes.size(),poids);


    std::unordered_map<int,Sommet*> temp2;

    for(auto git=m_sommets.cbegin(); git!=m_sommets.cend(); ++git)
    {
        std::cout<<git->second->getId()<<std::endl;
        for(auto it=temp2.cbegin(); it!=m_sommets.cend(); ++it)
        {
            it->second->setId(git->second->getId());
        }
    }

    for(auto itr=temp2.cbegin(); itr!=temp2.cend(); ++itr)
    {
        std::cout<<itr->second->getId()<<std::endl;
    }

    for(auto it=temp2.cbegin(); it!=temp2.cend(); ++it)
    {
        svgout.addDisk((it->second->getX())+500,(it->second->getY()),5,"black");
    }

    float coutTotalPoidsEnv=0;
    float coutTotalPoidsFin=0;


    if (poids == 1 )
    {
        for(size_t i=0; i<grapheApresTriEnv.size(); ++i)
        {

            svgout.addLine((grapheApresTriEnv[i]->getSommetInitialX())+500, grapheApresTriEnv[i]->getSommetInitialY(),grapheApresTriEnv[i]->getSommetFinalX()+500, grapheApresTriEnv[i]->getSommetFinalY(), "black");

            svgout.addText((grapheApresTriEnv[i]->getSommetInitialX()+550+grapheApresTriEnv[i]->getSommetFinalX()+450)/2,(grapheApresTriEnv[i]->getSommetInitialY()+grapheApresTriEnv[i]->getSommetFinalY())/2,grapheApresTriEnv[i]->getCoutEnv(), "red");

            svgout.addText((grapheApresTriEnv[i]->getSommetInitialX()+560+grapheApresTriEnv[i]->getSommetFinalX()+460)/2,(grapheApresTriEnv[i]->getSommetInitialY()+grapheApresTriEnv[i]->getSommetFinalY())/2," ;", "red");

            svgout.addText((grapheApresTriEnv[i]->getSommetInitialX()+570+grapheApresTriEnv[i]->getSommetFinalX()+470)/2,(grapheApresTriEnv[i]->getSommetInitialY()+grapheApresTriEnv[i]->getSommetFinalY())/2,grapheApresTriEnv[i]->getCoutFinancier(), "red");
            for(auto it=m_sommets.cbegin(); it!=m_sommets.cend(); ++it)
            {
                svgout.addDisk(it->second->getX()+500,it->second->getY(),10,"white");
                svgout.addCircle(it->second->getX()+500,it->second->getY(),10,2,"black");
                if(it->first<10)
                {
                    svgout.addText(it->second->getX()+495,it->second->getY()+5,it->second->getId(),"black");
                }
                else
                    svgout.addText(it->second->getX()+495-3,it->second->getY()+5,it->second->getId(),"black");
            }

        }
        coutTotalPoidsEnv=getPoidsTotalEnv(grapheApresTriEnv);
        std::cout<<"Cout total :"<<coutTotalPoidsEnv<<std::endl;
        svgout.addText(590,25, "KRUSKAL POIDS 2 : ", "black");
        svgout.addText(595,45, "Cout total : ", "black");
        svgout.addText(670,45, "(", "black");
        svgout.addText(675,45, coutTotalPoidsEnv, "black");
        svgout.addText(690,45, ";", "black");
        coutTotalPoidsEnv=0;
        coutTotalPoidsFin=0;

        coutTotalPoidsFin=getPoidsTotalFin(grapheApresTriFin);
        std::cout<<"Cout total :"<<coutTotalPoidsFin<<std::endl;
        svgout.addText(695,45, coutTotalPoidsFin, "black");
        svgout.addText(715,45, ")", "black");
    }

    else
    {
        for(size_t i=0; i<grapheApresTriFin.size(); ++i)
        {

            svgout.addLine((grapheApresTriEnv[i]->getSommetInitialX())+500, grapheApresTriEnv[i]->getSommetInitialY(),grapheApresTriEnv[i]->getSommetFinalX()+500, grapheApresTriEnv[i]->getSommetFinalY(), "black");

            svgout.addText((grapheApresTriEnv[i]->getSommetInitialX()+550+grapheApresTriEnv[i]->getSommetFinalX()+450)/2,(grapheApresTriEnv[i]->getSommetInitialY()+grapheApresTriEnv[i]->getSommetFinalY())/2,grapheApresTriEnv[i]->getCoutEnv(), "red");

            svgout.addText((grapheApresTriEnv[i]->getSommetInitialX()+560+grapheApresTriEnv[i]->getSommetFinalX()+460)/2,(grapheApresTriEnv[i]->getSommetInitialY()+grapheApresTriEnv[i]->getSommetFinalY())/2," ;", "red");


            svgout.addText((grapheApresTriEnv[i]->getSommetInitialX()+570+grapheApresTriEnv[i]->getSommetFinalX()+470)/2,(grapheApresTriEnv[i]->getSommetInitialY()+grapheApresTriEnv[i]->getSommetFinalY())/2,grapheApresTriEnv[i]->getCoutFinancier(), "red");
            for(auto it=m_sommets.cbegin(); it!=m_sommets.cend(); ++it)
            {
                svgout.addDisk(it->second->getX()+500,it->second->getY(),10,"white");
                svgout.addCircle(it->second->getX()+500,it->second->getY(),10,2,"black");
                if(it->first<10)
                {
                    svgout.addText(it->second->getX()+495,it->second->getY()+5,it->second->getId(),"black");
                }
                else
                    svgout.addText(it->second->getX()+495-3,it->second->getY()+5,it->second->getId(),"black");
            }

        }

        coutTotalPoidsEnv=getPoidsTotalEnv(grapheApresTriEnv);
        svgout.addText(590,25, "KRUSKAL POIDS 1 : ", "black");
        std::cout<<"Cout total :"<<coutTotalPoidsEnv<<std::endl;
        svgout.addText(595,45, "Cout total : ", "black");
        svgout.addText(670,45, "(", "black");
        svgout.addText(675,45, coutTotalPoidsEnv, "black");
        svgout.addText(690,45, ";", "black");

        coutTotalPoidsEnv=0;
        coutTotalPoidsFin=0;

        coutTotalPoidsFin=getPoidsTotalFin(grapheApresTriFin);
        std::cout<<"Cout total :"<<coutTotalPoidsFin<<std::endl;
        svgout.addText(695,45, coutTotalPoidsFin, "black");
        svgout.addText(715,45, ")", "black");
    }

}


/**
 * \brief       Compare deux arêtes recues en paramètre, en fonction du poids environnemental
 * \param       a de type Arete*
 * \param       b de type Arete*
 * \return      Retourne le plus petit cout environnemental
*/
bool triMonAreteParPoidsEnv(const Arete* a, const Arete* b) //Fonction de comparaison entre deux aretes
{
    return a->getCoutEnv()<b->getCoutEnv();
}


/**
 * \brief       Compare deux arêtes recues en paramètre en fonction du poids financier
 * \param       a de type Arete*
 * \param       b de type Arete*
 * \return      Retourne le plus petit cout financier
*/
bool triMonAreteParPoidsFin(const Arete* a, const Arete* b)
{
    return a->getCoutFinancier()<b->getCoutFinancier();
}


/**
 * \brief       Fonction qui compare deux aretes recues en paramètre en fonction de l'id
 * \param       a de type Arete*
 * \param       b de type Arete*
 * \return      Retourne le plus petit id
*/
bool triMonAreteParId(const Arete* a,const Arete* b)
{
    return a->getId()>b->getId();
}


/**
 * \brief       Fonction qui trie un vecteur d'aretes recu en paramètre en fonction de l'id
 * \param       &vec de type vector<Arete*>
*/
void triMesAretesParId(std::vector<Arete*> &vec)
{
    std::sort(vec.begin(),vec.end(),triMonAreteParId);
}


/**
 * \brief       Fonction qui trie un vecteur d'aretes recu en paramètre en fonction du poids environnemental
 * \param       &vec de type vector<Arete*>
*/
void triMesAretesParPoidsEnv(std::vector<Arete*> &vec) //Fonction qui va trier un vecteur d'aretes
{
    std::sort(vec.begin(),vec.end(),triMonAreteParPoidsEnv);
}


/**
 * \brief       Fonction qui trie un vecteur d'aretes recu en paramètre en fonction du poids financier
 * \param       &vec de type vector<Arete*>
*/
void triMesAretesParPoidsFin(std::vector<Arete*> &vec)
{
    std::sort(vec.begin(),vec.end(),triMonAreteParPoidsFin);
}

/*void triFinalPoidsEnv(std::vector<Arete*> graphe)
{
    Arete*  temp;

    for(int i=0; i<graphe.size(); ++i)
    {
        for(int j=0; j<graphe.size(); ++j)
        {
            if((graphe[i]->getCoutEnv()==graphe[j]->getCoutEnv())&&(graphe[i]->getId()>graphe[j]->getId()))
            {
                temp=graphe[i];
                graphe[i]=graphe[j];
                graphe[j]=temp;
            }

        }
    }


}*/


/*void triFinalPoidsFin(std::vector<Arete*> graphe)
{
    Arete*  temp;


    for(int i=0; i<graphe.size(); ++i)
    {
        for(int j=0; j<graphe.size(); ++j)
        {
            if((graphe[i]->getCoutFinancier()==graphe[j]->getCoutFinancier())&&(graphe[i]->getId()<graphe[j]->getId()))
            {
                temp=graphe[i];
                graphe[i]=graphe[j];
                graphe[j]=temp;
            }

        }
    }


}*/

//void tri(std::vector<Arete*>graphe)
//{
//    Arete* t;
//    for(int i=0; i<graphe.size(); ++i)
//    {
//        for(int j=0; j<graphe.size(); ++j)
//        {
//            if(graphe[i]->getCoutFinancier()>graphe[j]->getCoutFinancier())
//            {
//                graphe[i]=graphe[j];
//            }
//            else if(graphe[i]->getCoutFinancier()==graphe[j]->getCoutFinancier())
//            {
//                if(graphe[i]->getId()>graphe[j]->getId())
//                {
//                    graphe[i]=graphe[j];
//                }else graphe[i]=graphe[i];
//            }else graphe[i]=graphe[i];
//        }
//    }
//}


/**
 * \brief       Algorithme de kruskal
 * \param       graphe de type vector<Arete*>,
 * \param       ordre de type int
 * \param       nb_aretes de type int
 * \param       poids de type bool
 * \return      Retourne l'arbre de poids minimum (vecteur d'arete)
*/
//Algorithme de Kruskal utilisé dans le pdf proposé par M. Fercoq sur campus
std::vector<Arete*> graphe::algoKruskal(std::vector<Arete*> graphe, int ordre, int nb_arete, bool poids)const
{
    std::vector<Arete*> arbre; //Vecteur de pointeur d'aretes
    std::vector<int*> connexe;  //Vecteur de pointeur d'int

    int indiceA=0; //indice arbre
    int indiceG=0; //indice graphe

    int s1,s2;

    Arete* u; //Arete temporaire

    for(int i=0; i<ordre-1; ++i) //Allocation de l'arbre pour ses n-1 aretes, n=ordre du graphe
    {
        arbre.push_back(new Arete());

    }

    for(size_t i=0; i<ordre; ++i) //Allocation du tableau connexe
    {
        connexe.push_back(new int());
    }

    for(size_t x=0; x<ordre; x++) //Initialisation des connexités
    {
        *connexe[x]=x;
    }

    if(poids==false) //tri par cout environnemental
    {
        triMesAretesParPoidsEnv(graphe);
        //triFinalPoidsEnv(graphe);

    }
    else  //tri par cout financier
    {
        triMesAretesParPoidsFin(graphe);
        //triFinalPoidsFin(graphe);


    }


    while((indiceA<ordre-1)&&(indiceG<nb_arete)) //Tant que les aretes de l'arbre et du graphe ne sont pas toutes traitées
    {
        u=graphe[indiceG];//On retourne l'arete numéro indiceG du graphe
        s1=u->getIdInit(); //On get les id
        s2=u->getIdFinal();

        if(*connexe[s1]==*connexe[s2]) //Cycle si s1 et s2 connexe
        {

        }
        else
        {
            arbre[indiceA]=u; //On insère l'arete à la position indiceA

            indiceA++; //On passe à l'arete suivante du graphe et de l'arbre

            int indice =*connexe[s2];
            for(size_t i=0; i<connexe.size(); ++i)
            {
                if(*connexe[i]==indice)
                {
                    *connexe[i]=*connexe[s1];
                }
            }
        }
        indiceG++; //On passe à l'arete suivante
    }
    /*if(indiceA<ordre-1)
        std::cout<<"Le graphe n'est pas connexe"<<std::endl;*/

    return arbre; //On retourne l'arbre de poids minimum
}


/**
 * \brief       Fonction qui remplit un vecteur avec des nombres binaires et qui va selectionner le nombre de "1" necessaire selon le graphe
 * \details     On remplit d'abord le vecteur avec des 1, ordre -1 fois puis on remplit la suite du vecteur avec des 0 jusqu'au nombre d'aretes
 * \return      On retourne le vecteur de int rempli avec la serie de binaire
*/
std::vector<int> graphe::selectBinaire()
{
    std::vector<int> binaire; //Vecteur de int
    for(size_t i=0; i<m_sommets.size()-1; ++i) //On remplit le vecteur avec des 1 ordre-1 fois
    {
        binaire.push_back(1);
    }
    for(size_t i=m_sommets.size()-1; i<mes_aretes.size(); ++i) //On remplit la suite du vecteur avec des 0 jusqu'à le nombre d'aretes
    {
        binaire.push_back(0);
    }

    return binaire; //On retourne le vecteur de int

}


/*/**
 * \brief       Fonction qui va retourner la suite binaire dans un vecteur de vecteur de int avec tous les cas qui ont n ou > n aretes (partie 3)
 * \details     On combine les fonctions selectBinaire avec binaireTrie
 * \return      On retourne le vecteur de vecteur de int rempli avec la série de binaire
*/
//Fonction qui va retourner la suite binaire dans un vecteur de vecteur de int avec tous les cas qui ont n ou > n aretes
/*std::vector<std::vector<int>> graphe::selectBinaireArbre()
{
    std::vector<std::vector<int>> tabBinaire;//Déclarations des variables
    std::vector<int> binaire;
    std::vector<int> temp;
    int cpt=0; //compteur=0

    while((cpt+m_sommets.size()-1)<=mes_aretes.size())
    {
        for(size_t i=0; i<m_sommets.size()-1+cpt; ++i)//On remplit le vecteur avec des 1 ordre-1 fois
        {
            binaire.push_back(1);

        }
        if((cpt+m_sommets.size()-1 ) != (mes_aretes.size()) )
        {
            for(size_t i=m_sommets.size()-1+cpt; i<mes_aretes.size(); ++i) //On remplit la suite du vecteur avec des 0 jusqu'à le nombre d'aretes
            {
                binaire.push_back(0);
            }
        }

        std::sort(binaire.begin(),binaire.end());

        do
        {
            //Boucle qui remplie le vecteur binaire
            for(size_t i=0; i<binaire.size(); ++i)
            {
                temp.push_back(binaire[i]);

            }
            tabBinaire.push_back(temp);// vecteur binaire se retrouve dans le vecteur tabbinairematrice
            temp.clear();//reinitialise le vecteur binaire



        }
        while ( std::next_permutation(binaire.begin(),binaire.end()) );
        binaire.clear();//On clear la variable temporaire
        cpt++; //incrémentation

    }

    return tabBinaire; //Return la table de vecteur de vecteur de int
}*/


/**
 * \brief       Fonction qui tri le vecteur binaire remplit avec des 0 et des 1 dans la fonction graphe::selectBinaire()
 * \param       tabBinaire de type vector<int>
 * \return      Retourne un vector de vector de int
*/
std::vector<std::vector<int>>graphe::binaireTrie(std::vector<int> tabBinaire)
{

    std::vector<std::vector<int>> tabBinaireMatrice;//vecteur de vecteur de type int pour stocker les différents cas de lot d'arete
    std::vector<int> binaire;//vecteur local pour remplir le vecteur de vecteur
    //int compteur=0;//compteur pour dterminer le nombre de colonne du tableau que l'on va creer

    std::sort(tabBinaire.begin(),tabBinaire.end());

    do
    {
        //Boucle qui remplie le vecteur binaire
        for(size_t i=0; i<tabBinaire.size(); ++i)
        {
            binaire.push_back(tabBinaire[i]);
        }
        tabBinaireMatrice.push_back(binaire);// vecteur binaire se retrouve dans le vecteur tabbinairematrice
        binaire.clear();//reinitialise le vecteur binaire

        //compteur++;// permet d'incrementer le compteur et de trouver le nombre de colonne de tabBinaireMatrice

    }
    while ( std::next_permutation(tabBinaire.begin(),tabBinaire.end()) );

    return tabBinaireMatrice;
}


/**
 * \brief       Fonction qui permet d'asssocier les "1" a des int selon leur position dans le vecteur qui seront des id d'aretes
 * \param       matrice de type std::vector<std::vector<int>>
  * \param       vecBinaire de type vector<int>
 * \return      Retourne un vecteur de vecteur de int
*/
//Fonction qui retourne un vecteur de vecteur de int qui va dire que les "1" vont représenter des int selon la position qui seront des id d'aretes
std::vector<std::vector<int>> graphe::MatriceDeCasAretes(std::vector<std::vector<int>> matrice)
{
    std::vector<std::vector<int>> SolutionsAdmissibles;
    std::vector <int> idAretes;

    for(size_t i=0; i<matrice.size(); ++i)
    {
        for(size_t y=0; y<mes_aretes.size(); ++y)
        {

            if(matrice[i][y]==1)
            {
                idAretes.push_back(mes_aretes.size()-1-y);
                //std::cout<<mes_aretes.size()-1-y;
                //cpt++;
            }
            //std::cout<<std::endl;


        }
        SolutionsAdmissibles.push_back(idAretes);
        idAretes.clear();
    }
    /*for(size_t i=0;i<SolutionsAdmissibles.size();++i)
    {
        for(size_t j=0;j<mes_aretes.size();++j)
        {
            std::cout<<SolutionsAdmissibles[i][j];
        }
        std::cout<<std::endl;
    }*/
    return SolutionsAdmissibles;
}

/**
 * \brief       Fonction qui remplace le vector de vector de int par un vector de vector d'aretes (on associe les int a des id d'arets)
 * \param       tabId de type std::vector<std::vector<int>>
 * \return      On retourne un vecteur de vecteur d'aretes
*/
std::vector<std::vector<Arete*>> graphe::paretoSansConnexe(std::vector<std::vector<int>> tabId)
{

    int b;
    std::vector<Arete*> tabArete;
    std::vector<std::vector<Arete*>> paretoSC;

    for(size_t i=0; i<tabId.size(); ++i) //On parcourt la table selon le nombre de vecteur de int
    {
        for(size_t j=0; j<m_sommets.size()-1; ++j) //Pour chaque vecteur de int on parcourt la suite de int
        {

            b=tabId[i][j]; //La variable b prend un int

            tabArete.push_back(mes_aretes[b]); //On push les int qui representent une suite d'id d'arete dans le vecteur d'arete tabArete
        }

        paretoSC.push_back(tabArete); //On push ce vecteur d'arete dans le vecteur de vecteur d'arete
        tabArete.clear(); //On clear la  variable temporaire
        b=0; //On clear la variable temporaire

    }
    std::cout<<"Nombre de solution avant connexite :"<<paretoSC.size()<<std::endl;
    /*std::cout << "capacity: " << (int) paretoSC.capacity() << '\n';
  std::cout << "max_size: " << (int) paretoSC.max_size() << '\n';*/

    return paretoSC; //On retourne un vecteur de vecetur d'aretes
}


/*/**
 * \brief
 * \param       tabId de type std::vector<std::vector<int>>
 * \return      On retourne un vecteur de vecetur d'aretes
*/
/*std::vector<std::vector<Arete*>> graphe::paretoSansConnexePartie3(std::vector<std::vector<int>> tabId)
{
    int cpt=0;
    int b=0; //Déclarations des variables
    std::vector<std::vector<Arete*>> paretoSC;
    std::vector<Arete*> tabArete;

    while(m_sommets.size()-1+cpt <=mes_aretes.size()) //Boucle qui va servir à parcourir chaque vecteur d'arete selon son nombre de int
    {
        for(size_t i=0; i<tabId.size(); ++i) //On parcourt la tab
        {

            if(tabId[i].size()==m_sommets.size()-1+cpt) //Si le vecteur de int a le meme nombre d'aretes
            {
                for(size_t j=0; j<m_sommets.size()-1+cpt; ++j) //Alors on parcourt le vecteur de int
                {
                    b=tabId[i][j]; //b prend le int du vecteur de vecteur de int
                    tabArete.push_back(mes_aretes[b]); //on push b(represente un id d'arete) dans mes tabArete
                }
                paretoSC.push_back(tabArete); //On le push dans un vecteur de vecteur d'arete
                tabArete.clear(); //On eefface les variables temporaires
                b=0;

            }
        }
        cpt++; //on incrémente jusqu'à le nombre d'aretes maximal
    }
    std::cout<<"Nombre de solutions avant connexite partie 3 : "<<paretoSC.size()<<std::endl;
    return paretoSC;


}*/

/*/**
 * \brief       Fonction qui vérifie si chaque arete relie un sommet (pour la partie 3)
  * \param       tabId de type std::vector<std::vector<Arete*>>
 * \return      On retourne un vecteur de vecteur d'arete
*/
/*std::vector<std::vector<Arete*>>graphe:: garderSommetLies(std::vector<std::vector<Arete*>> tabId)
{
    //Déclarations des variables
    std::vector<std::vector<Arete*>> paretoC;
    std::vector<Arete*>a;
    std::vector<int> id;

    //Variable buffer
    Arete* M;

    for(size_t i=0; i<tabId.size(); ++i) //On parcourt la table d'id depuis le vecteur de vecteur d'arete
    {
        for(size_t j=0; j<m_sommets.size()-1; ++j) //On parcourt dans le vecteur d'arete pour chaque arete
        {

            M=tabId[i][j];  //L'arete M prend une arete du vecteur d'arete

            id.push_back(M->getIdInit());//On get ses ids de sommets initial et final de l'arete
            id.push_back(M->getIdFinal());

            a.push_back(M); //On push dans le vecteur d'arete l'arete M

        }

        //Algo qui va tester la connexité, si tous les sommets sont reliés
        for(size_t i=0; i<id.size(); ++i)
        {
            for(size_t j=i+1; j<id.size(); ++j)
            {
                if(id[i]==id[j])
                {
                    id.erase(id.begin()+j); //Si le sommet y est deja on l'enlève
                }
            }

        }


        if(id.size()==m_sommets.size()) //Si le nombre de sommets différents est égal à l'ordre alors on l'ajoute
        {
            paretoC.push_back(a);
        }

        //On clear les variables temporaires
        id.clear();
        a.clear();
    }
    std::cout<<"Nombre de solution apres connexite  :"<<paretoC.size()<<std::endl;
    return paretoC;
}*/


/*/**
 * \brief
 * \param       tabId de type std::vector<std::vector<Arete*>>
 * \return      On retourne un vecteur de vecetur d'arete
*/
/*std::vector<std::vector<Arete*>>graphe:: garderSommetLiesPartie3(std::vector<std::vector<Arete*>> tabId)
{
    //Déclarations des variables
    std::vector<std::vector<Arete*>> paretoC;
    std::vector<Arete*>a;
    std::vector<int> id;

    //Variable buffer
    Arete* M;
    int cpt=0;

    while(m_sommets.size()-1+cpt <= mes_aretes.size())
    {
        for(size_t i=0; i<tabId.size(); ++i) //On parcourt la table d'id depuis le vecteur de vecteur d'arete
        {
            if(tabId[i].size()==m_sommets.size()-1+cpt)
            {
                for(size_t j=0; j<m_sommets.size()-1+cpt; ++j) //On parcourt dans le vecteur d'arete pour chaque arete
                {

                    M=tabId[i][j];  //L'arete M prend une arete du vecteur d'arete

                    id.push_back(M->getIdInit());//On get ses ids de sommets initial et final de l'arete
                    id.push_back(M->getIdFinal());

                    a.push_back(M); //On push dans le vecteur d'arete l'arete M

                }

                //Algo qui va tester la connexité, si tous les sommets sont reliés
                for(size_t i=0; i<id.size(); ++i)
                {
                    for(size_t j=i+1; j<id.size(); ++j)
                    {
                        if(id[i]==id[j])
                        {
                            id.erase(id.begin()+j); //Si le sommet y est deja on l'enlève
                        }
                    }

                }


                if(id.size()==m_sommets.size()) //Si le nombre de sommets différents est égal à l'ordre alors on l'ajoute
                {
                    paretoC.push_back(a);
                }

                //On clear les variables temporaires
                id.clear();
                a.clear();

            }


        }
        cpt++;
    }
    std::cout<<"Nombre de solution apres connexite partie 3 : "<<paretoC.size()<<std::endl;
    return paretoC;

}*/


/**
 * \brief       Fonction qui permet d'enlever tous les graphes qui font des cycles et assure que tous les sommets sont lies
 * \param       tabId de type std::vector<std::vector<Arete*>>
 * \return      On retourne un vecteur de vecteur d'arete
*/
std::vector<std::vector<Arete*>> graphe::paretoSansConnexite(std::vector<std::vector<Arete*>> tabId)
{

    std::vector<std::vector<Arete*>> grapheFinal;
    std::vector<Arete*> graphe;
    std::vector<Arete*> arbre; //Vecteur de pointeur d'aretes

    std::vector<int*> connexe;  //Vecteur de pointeur d'int


    unsigned int indiceA=0; //indice arbre
    unsigned int indiceG=0; //indice graphe

    unsigned int x,s1,s2;

    Arete* u;
    for(size_t i=0; i<m_sommets.size(); ++i) //Allocation du tableau connexe
    {
        connexe.push_back(new int());
    }



    for(size_t i=0; i<tabId.size(); ++i)
    {

        for(size_t i=0; i<m_sommets.size()-1; ++i) //Allocation de l'arbre pour ses n-1 aretes, n=ordre du graphe
        {
            arbre.push_back(new Arete());
        }


        for(x=0; x<m_sommets.size(); x++) //Initialisation des connexités
        {
            *connexe[x]=x;
        }

        graphe = tabId[i];
        while((indiceA<m_sommets.size()-1)&&(indiceG<graphe.size())) //Tant que les aretes de l'arbre et du graphe ne sont pas toutes traitées
        {

            u=graphe[indiceG];//On retourne l'arete numéro indiceG du graphe

            s1=u->getIdInit(); //On get les id
            s2=u->getIdFinal();


            if(*connexe[s1]!=*connexe[s2])
            {
                arbre[indiceA]=u; //On insère l'arete à la position indiceA
                indiceA++; //On passe à l'arete suivante du graphe et de l'arbre


                int indice =*connexe[s2];
                for(size_t i=0; i<connexe.size(); ++i)
                {
                    if(*connexe[i]==indice)
                    {
                        *connexe[i]=*connexe[s1];
                    }
                }
            }
            indiceG++; //On passe à l'arete suivante
        }

        indiceG=0;
        indiceA=0;

        unsigned int cpt=0;
        for(size_t i=0; i<graphe.size(); ++i)
        {
            for(size_t j=0; j<arbre.size(); ++j)
            {
                if(graphe[i]==arbre[j])
                {
                    cpt++;
                }
            }
        }


        if(cpt==graphe.size())
        {
            grapheFinal.push_back(arbre);
        }


        arbre.clear();

    }
    connexe.clear();
    //std::cout<<tabId.size()<<std::endl;
    std::cout<<"Nombre de solutions admissibles :"<<grapheFinal.size()<<std::endl;

    return grapheFinal;

}



/**
 * \brief       Fonction qui permet de trouver les solutions dominees et non dominees
 * \param       grahe de type std::vector<std::vector<Arete*>>
 * \return      On retourne un vecteur de Pareto
*/

//Sous programme qui prend en parametre une vecteur de vecteur d'arete et qui return un vecteur Pareto
std::vector<Pareto*>graphe::rechercheSolDominees(std::vector<std::vector<Arete*>> graphe)
{
    //Declaration des variables
    std::vector<Pareto*> n;//Utilisation de la classe Pareto
    std::vector<Pareto*> e;
    float poids[2];

    int c1=0;//compteur qui permet d'afficher le nombre de solution non dominee
    int c2=0;//Compteur qui permet d'afficher le nombre de solution dominee

    Console *pConsole=NULL;
    pConsole=Console::getInstance();


    for(size_t i=0; i<graphe.size(); ++i) // boucle for qui a pour but d'initialiser le vecteur n de type Pareto
    {
        poids[0]=getPoidsTotalFin(graphe[i]);
        poids[1]=getPoidsTotalEnv(graphe[i]);

        n.push_back(new Pareto(i,true,poids[0],poids[1]));//On initialise une variable de type Pareto qu'on insere dans le vecteur n(On initialise tout a true au depart)
        e.push_back(new Pareto(i,false,poids[0],poids[1]));//On initialise un autre vecteur pareto mais cette fois on l'initialise a false


    }

    for(size_t k=0; k<m_sommets.size(); ++k)
    {

        for(size_t i=0; i<n.size(); ++i) //Double boucle for pour pouvoir trier les solutions dominees (false) et non dominees (true)
        {
            for(size_t y=0; y<n.size(); ++y)
            {
                //Si la condition suivante est verifiee
                if(((n[i]->getPoids1()<n[y]->getPoids1())&&(n[i]->getPoids2()<n[y]->getPoids2()))||((n[i]->getPoids1()==n[y]->getPoids1())&&(n[i]->getPoids2()<n[y]->getPoids2()))||((n[i]->getPoids1()<n[y]->getPoids1())&&(n[i]->getPoids2()==n[y]->getPoids2())))
                {
                    n.erase(n.begin()+y);//on efface a l'emplacement y pour pouvoir selectionner que les solution non dominees

                }
            }
        }
    }

    for(size_t i=0; i<n.size(); ++i) //Boucle for pour pouvoir changer le bool des solution non dominees dans le vecteur e
    {
        e[n[i]->getId()]->setSelection(true);

    }


    for(size_t i=0; i<e.size(); ++i) //Boucle for pour compter le nombre de solution dominee et non dominee
    {
        if(e[i]->getSelection()==true)// si a l'emplacement e[i] le Bool se trouve a true
        {
            c1++;// Alors on incremente le compteur des solutions non dominees
        }
        else
            c2++;//Sinon c'est le compteur des solutions dominees qu'on incremente

    }
    //Affichage du nombre des differentes solutions :
    pConsole->setColor(COLOR_GREEN);
    std::cout<<"solutions non dominees : "<<c1<<std::endl;
    pConsole->setColor(COLOR_RED);
    std::cout<<"solutions dominees : "<<c2<<std::endl;
    pConsole->setColor(COLOR_DEFAULT);


    return e;//return le vecteur de Pareto n qui sera utilisé pour l'affichage en SVG
}

/**
 * \brief       Fonction qui permet de dessiner la frontiere (avec solutions dominees et non dominees)
 * \param       &svgout de type Svgfile
 * \param       p de type std::vector<Pareto*>
 * \param       g de type std::vector<std::vector<Arete*>>
*/

void graphe::dessinFrontiereDePareto(Svgfile &svgout,std::vector<Pareto*>p,std::vector<std::vector<Arete*>> g)const
{
    //Declaration des variables
    std::string couleur;                //Couleur des points sur le diagramme
    float taille;
    float x;                           //x et y sont les coordonnees des differents points
    float y;
    float coefm=10;                    //Coeficient qui permet d'agrandir l'echelle (l'espace entre deux points
    float poidsLePlusPetit[2];         //variable pour reoganiser l'affichage
    float x1;                          //Variable qui permet d'adapter l'affichage en fonction des different graphe en parametre
    float x2;
    float poidsmax[2];

    int tmp=0;
    //coordonnees transmisent en parametre au sous programme dessin arbre
    float coordx=0;
    float coordy=100;

    //On initialise des vector de float pourpar la suite trier par ordre croissant les poids
    std::vector<float> poids1;
    std::vector<float> poids2;
    for(size_t i=0; i<p.size(); ++i)
    {
        poids1.push_back(p[i]->getPoids1());
        poids2.push_back(p[i]->getPoids2());

    }
    //On trie dans l'ordre croissant le poids 1 et le poids 2
    std::sort(poids1.begin(),poids1.end());
    std::sort(poids2.begin(),poids2.end());

    //On stocke les poids 2 poids les plus petit qui seront la base de notre affichage
    poidsLePlusPetit[0]=poids1[0]*coefm;
    x1=620-poidsLePlusPetit[0];
    poidsLePlusPetit[1]=poids2[0]*coefm;
    x2=580+poidsLePlusPetit[1];

    //On stocke nos 2poids max pour pouvoir arreter les axes en fonction des valeur les plus grandes
    poidsmax[0]=poids1[poids1.size()-1];
    poidsmax[1]=poids2[poids2.size()-1];

    //dessin des deux axes
    svgout.addLine(600,x2-coefm*poidsmax[1]-20,600,610,"black");
    svgout.addLine(590,600,x1+coefm*poidsmax[0]+20,600,"black");

    //dessin des fleches au bout des axes
    svgout.addTriangle(x1+coefm*poidsmax[0]+10,605,x1+coefm*poidsmax[0]+10,595,x1+coefm*poidsmax[0]+20,600);
    svgout.addTriangle(600,x2-coefm*poidsmax[1]-20,605,x2-coefm*poidsmax[1]-10,595,x2-coefm*poidsmax[1]-10);
    //origine
    svgout.addText(590,613,"0","black");
    //noms des axes
    svgout.addText(x1+coefm*poidsmax[0]-20,615,"Cout1","black");
    svgout.addText(603,x2-coefm*poidsmax[1]+5,"Cout2","black");

    //legende du diagramme
    svgout.addDisk(610,625,5,"green");
    svgout.addText(620,625,"Solutions non dominees (frontiere de Pareto)","black");
    svgout.addDisk(610,645,3,"red");
    svgout.addText(620,645,"Solutions dominees","black");

    //boucle for pour afficher toute les solution de pareto
    for(size_t i=0; i<p.size(); ++i)
    {
        //si nous somme sur la frontiere de pareto condition valide
        if(p[i]->getSelection()==1)
        {

            tmp++;
            x=x1+coefm*(p[i]->getPoids1());
            y=x2 - coefm*(p[i]->getPoids2());
            taille=4;
            couleur="green";
            svgout.addText(x-10,y,tmp,"black");
            dessinPetitArbreCouvrant(svgout,g[i],tmp,x1,x2,poidsmax[0]);



        }
        //sinon
        else
        {
            x=x1+coefm*(p[i]->getPoids1());
            y=x2-coefm*(p[i]->getPoids2());
            couleur="red";
            taille=2;
        }

        svgout.addDisk(x,y,taille,couleur);
    }



}


/**
 * \brief       Fonction qui va dessiner les arbres couvrants
 * \param       &svgout de type Svgfile
 * \param       A de type std::vector<std::vector<Arete*>>
 * \param       x, y, poidsMax de type float
 * \param       k de type int
*/
//Sous programme pour affiche les schema des solution en cours d'elaboration
void graphe::dessinPetitArbreCouvrant(Svgfile& svgout,std::vector<Arete*> A,int k,float x, float y,float poidsMax)const
{
    //Initialisation des variables qui vont permetre de positioner les differents schemas
    float PointDeDepartX=0;
    float PointDeDepartY=25;

    if(k<6)
    {
        PointDeDepartX=x+10*poidsMax+50;
        PointDeDepartY=PointDeDepartY+k*100;
    }
    else if(k==6)
    {
        PointDeDepartX=x+10*poidsMax+100+75;
        PointDeDepartY=25+100;
    }
    else if((k>6)&&(k<11))
    {
        PointDeDepartX=x+10*poidsMax+100+75;
        PointDeDepartY= PointDeDepartY+(k-5)*100;

    }
    else
    {
        PointDeDepartX=x+10*poidsMax+100+225;
        PointDeDepartY= PointDeDepartY+(k-10)*100;

    }
    svgout.addText(PointDeDepartX,PointDeDepartY+5,k,"black");
    svgout.addText(PointDeDepartX+15,PointDeDepartY+5," :(","black");
    svgout.addText(PointDeDepartX+30,PointDeDepartY+5,getPoidsTotalEnv(A),"black");
    svgout.addText(PointDeDepartX+46,PointDeDepartY+5,",","black");
    svgout.addText(PointDeDepartX+50,PointDeDepartY+5,getPoidsTotalFin(A),"black");
    svgout.addText(PointDeDepartX+65,PointDeDepartY+5,")","black");
    for (size_t i=0; i<A.size(); ++i)
    {
        //on dessine les aretes de l'arbre
        svgout.addLine((A[i]->getSommetInitialX())/5+PointDeDepartX, (A[i]->getSommetInitialY())/5+PointDeDepartY,(A[i]->getSommetFinalX())/5+PointDeDepartX, (A[i]->getSommetFinalY())/5+PointDeDepartY, "black");

    }
    for(auto it=m_sommets.cbegin(); it!=m_sommets.cend(); ++it)
    {
        //on dessine les sommets de l'arbre
        svgout.addDisk((it->second->getX())/5+PointDeDepartX,(it->second->getY())/5+PointDeDepartY,2,"black");
    }
}




/**
 * \brief      Destructeur
*/
graphe::~graphe()
{
    //dtor
}



