#include <iostream>
#include "Graphe.h"
#include "Sommet.h"
#include "Arrete.h"
#include "svg.h"


char menu()
{
    char choix;
    std::cout<<"1. Cr\202er Afficher les donn\202es du graphe en console"<<std::endl;
    std::cout<<"2. Charger le graphe SVG"<<std::endl;
    std::cout<<"3. Sauvegarder les indices"<<std::endl;
    std::cout<<"4. Tester la vuln\202rabilit\202 du r\202seau"<<std::endl;
    std::cout<<"5. Changer le système de ponderation"<<std::endl;



    do
    {
        std::cin>>choix;
    }while(choix != '1' && choix != '2' && choix != '3'&& choix != '4');

    return choix;
}




int main()
{
    Graphe graphe{"graphe_cycle5_topo.txt"};
    char choix;
    bool quit = 0;


    do{
        choix = menu();
        switch(choix){
            case '1' :
                        graphe.rechercher_afficher_CC();
                        break;

            case '2' :  graphe.afficherGraphe();
                        break;

            case '3' :  graphe.vulnerabilite();
                        break;
            case '4' :
                        break;
            default :   printf("Ne fonctionne pas \n");

                        break;
        }
    }while(!quit);

    return 0;
}
