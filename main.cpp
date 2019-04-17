#include <iostream>
#include "graphe.h"

int main()
{
    Svgfile *svgout;
    graphe g{"broadway.txt"};
    g.afficher();
}
