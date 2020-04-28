#include <iostream>
#include "Graphe.h"
#include "Sommet.h"
#include "Arrete.h"
#include "svg.h"

using namespace std;

int main()
{
    Graphe graphe{"graphe_cycle5_topo.txt"};
    graphe.afficherGraphe();
    graphe.rechercher_afficher_CC();
    return 0;
}
