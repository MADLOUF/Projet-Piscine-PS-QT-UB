#include <iostream>
#include "Graphe.h"
#include "Sommet.h"
#include "Arrete.h"
#include "svg.h"


char menu()
{
    system("cls");
    char choix;
    std::cout<<"1. Cr\202er un graphe"<<std::endl;
    std::cout<<"2. Afficher les donn\202es du graphe en console"<<std::endl;
    std::cout<<"3. Charger le graphe SVG"<<std::endl;
    std::cout<<"4. Sauvegarder les indices"<<std::endl;
    std::cout<<"5. Tester la vuln\202rabilit\202 du r\202seau"<<std::endl;
    std::cout<<"6. Charger la ponderation"<<std::endl;
    std::cout<<"7. Desactiver la ponderation"<<std::endl;
    std::cout<<"8. Activer les indices des sommets"<<std::endl;
    std::cout<<"9. Desactiver les indices des sommets"<<std::endl;

    do
    {
        std::cin>>choix;
    }while(choix != '1' && choix != '2' && choix != '3' && choix != '4' && choix != '5' && choix != '6' && choix != '7' && choix!= '8'&& choix!= '9');

    return choix;
}




int main()
{
    Graphe graphe;
    char choix;
    bool quit = 0;

    int test=0;

    std::string nomFichier1;
    std::string nomFichier2;


    do{
        choix = menu();
        switch(choix){

            case '1' :  std::cout<<std::endl;
                        std::cout<<"Rentrez le nom du graphe a charger"<<std::endl;
                        std::cin>>nomFichier1;
                        graphe.EffacerGraphe();
                        graphe.CreerGraphe(nomFichier1);
                        std::cout<<"Le graphe a bien \202t\202 cr\202\202"<<std::endl;
                        system("pause");
                        test=1;
                        break;

            case '2' :  graphe.afficher_Cd();
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

            case '3' :  if(test==1)
                        {
                            graphe.afficherGraphe();
                        }
                        else
                            std::cout<<"Vous n'avez pas chargé de graphe"<<std::endl;

                        system("pause");
                        break;

            case '4' :  graphe.Cd();
                        graphe.Cvp();
                        if(graphe.getPondere()==1)
                        {
                            graphe.Cp();
                            graphe.Ci();
                        }
                        graphe.Save();
                        system("pause");
                        break;
            case '5' :  graphe.vulnerabilite(); ///rappeler l'affichage pour mettre le num des aretes a jour
                        break;

            case '6' :  std::cout<<std::endl;
                        std::cout<<"Rentrez le nom du fichier de ponderation a charger"<<std::endl;
                        std::cin>>nomFichier2;
                        graphe.Load_ponderation(nomFichier2);
                        graphe.setPondere(1);
                        std::cout<<"La ponderation a bien \202t\202 charg\202e ! Afficher le graphe pour la voir."<<std::endl;
                        system("pause");
                        break;

            case '7' :  graphe.setPondere(0);
                        std::cout<<std::endl;
                        std::cout<<"Ponderation enlev\202e"<<std::endl;
                        std::cout<<std::endl;
                        system("pause");
                        break;

            case '8' :  graphe.Cd();
                        graphe.Cvp();
                        if(graphe.getPondere()==1)
                        {
                            graphe.Cp();
                            graphe.Ci();
                        }
                        graphe.setIndice(1);
                        std::cout<<"Les indices ont bien \202t\202 charg\202s ! Afficher le graphe pour les voir."<<std::endl;
                        system("pause");
                        break;

            case '9' :  graphe.setIndice(0);
                        std::cout<<std::endl;
                        std::cout<<"Indices enlev\202e"<<std::endl;
                        std::cout<<std::endl;
                        system("pause");
                        break;

            default :   printf("Ne fonctionne pas \n");

                        break;
        }
    }while(!quit);

    return 0;
}
