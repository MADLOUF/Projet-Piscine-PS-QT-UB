#include <iostream>
#include "Graphe.h"
#include "Sommet.h"
#include "Arrete.h"
#include "svg.h"


char menu()
{
    char choix;
    std::cout<<"1. Afficher les donn\202es du graphe en console"<<std::endl;
    std::cout<<"2. Charger le graphe SVG"<<std::endl;
    std::cout<<"3. Sauvegarder les indices"<<std::endl;
    std::cout<<"4. Tester la vuln\202rabilit\202 du r\202seau"<<std::endl;
    std::cout<<"5. Charger la ponderation"<<std::endl;
    std::cout<<"6. Desactiver la ponderation"<<std::endl;



    do
    {
        std::cin>>choix;
    }while(choix != '1' && choix != '2' && choix != '3'&& choix != '4'&& choix != '5'&& choix != '6');

    return choix;
}




int main()
{
    Graphe graphe{"graphe_cycle5_topo.txt"};
    char choix;
    bool quit = 0;
    int test=0;
    std::string nomFichier2;


    do{
        choix = menu();
        switch(choix){
            case '1' :  graphe.afficher_Cd();
                        graphe.afficher_Cvp();
                        if(graphe.getPondere()==1)
                        {
                            graphe.afficher_Cp();
                            graphe.afficher_Ci();
                        }
                        else
                        {
                            std::cout<<std::endl;
                            std::cout<<"La ponderation n'est pas charg\202 ! Vous ne pouvez pas afficher Cp et Ci"<<std::endl;
                            std::cout<<std::endl;
                        }

                        graphe.rechercher_afficher_CC();
                        break;

            case '2' :  graphe.afficherGraphe();

                        break;

            case '3' :  graphe.vulnerabilite();
                        break;
            case '4' :
                        break;

            case '5' :  std::cout<<std::endl;
                        std::cout<<"Rentrez le nom du fichier de ponderation a charger"<<std::endl;
                        std::cin>>nomFichier2;
                        graphe.Load_ponderation(nomFichier2);
                        graphe.setPondere(1);
                        std::cout<<"La ponderation a bien \202t\202 charg\202 ! Afficher le graphe pour la voir."<<std::endl;
                        break;
            case '6' :  graphe.setPondere(0);
                        break;
            default :   printf("Ne fonctionne pas \n");

                        break;
        }
    }while(!quit);

    return 0;
}
