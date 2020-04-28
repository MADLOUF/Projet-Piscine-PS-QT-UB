#include "Graphe.h"
#include "Sommet.h"
#include "Arrete.h"
#include "svg.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <cmath>

Graphe::Graphe(std::string nomFichier)
{
    std::ifstream ifs{nomFichier};
            if (!ifs)
                throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
            ifs >> m_oriente;
            if (m_oriente==1)
            {
                std::cout<<m_oriente<<std::endl;
                std::cout<<"Le graphe est oriente "<<std::endl;
            }
            else
            {
                    std::cout<<m_oriente<<std::endl;
                std::cout<<"Le graphe est non-oriente "<<std::endl;
            }
            std::cout<<std::endl;

              if ( ifs.fail() )
                throw std::runtime_error("Probleme lecture orienté du graphe");
            int ordre;
            ifs >> ordre;
            std::cout<<"Ordre : "<<ordre<<std::endl;
            std::cout<< "Liste Sommet : "<< std::endl;
            if ( ifs.fail() )
                throw std::runtime_error("Probleme lecture ordre du graphe");

            for (int i=0; i<ordre; ++i)
                {m_sommets.push_back( new Sommet{ifs} );}

            int taille;
            ifs >> taille;
            std::cout<<std::endl;
            std::cout<<"taille : "<<taille<<std::endl;
            std::cout<< "Liste Arrete : "<< std::endl;
            if ( ifs.fail() )
                throw std::runtime_error("Probleme lecture ordre du graphe");
            for (int i=0; i<taille; ++i)
                {m_arretes.push_back( new Arrete{ifs} );}
                std::cout<<std::endl;
                DeterminerAdjacance();
}

Graphe::~Graphe()
{
                for (auto s : m_sommets)
                delete s;
}
int Graphe::getOrdre() const
{
    return (int)m_sommets.size();
}
 int Graphe::getTaille() const
{
    return (int)m_arretes.size();
}
 void Graphe::DeterminerAdjacance()
{
    if(m_oriente==1)///Pour un graphe orienté
           {
            for (int i =0 ; i<getOrdre();i++)///Parcours de la totalité des sommets
            {
                for (int y=0;y<getTaille();y++)///Parcours de la totalité des arretes
                {
                    if(m_sommets[i]->getID()==m_arretes[y]->getID1())
                    {
                           m_sommets[i]->Adjacent(m_arretes[y]->getID2());
                    }
                }
                m_sommets[i]->Adjtrie();
            }
          }
          else if (m_oriente==0)///Pour un graphe non orienté
          {
            for (int i =0 ; i<getOrdre();i++)
             {
                for (int y=0;y<getTaille();y++)
                {
                    if(m_sommets[i]->getID()==m_arretes[y]->getID1())
                    {
                           m_sommets[i]->Adjacent(m_arretes[y]->getID2());
                    }
                    else if (m_sommets[i]->getID()==m_arretes[y]->getID2())
                    {
                        m_sommets[i]->Adjacent(m_arretes[y]->getID1());
                    }
                }
                m_sommets[i]->Adjtrie();

            }

          }
         afficherAdjacance();
}
int Graphe::rechercheID(int ID)
{
     for (int i=0;i<getOrdre();++i)
            {
                if (ID==m_sommets[i]->getID())
                {
                    return i;
                }
            }
        return 0;
}
int Graphe::PoidsArrete(int ID1,int ID2)
{
                for (int i=0;i<getTaille();++i)
            {
                if(m_arretes[i]->getID1()==ID1&&m_arretes[i]->getID2()==ID2)
                {
                    return m_arretes[i]->getPoids();
                }
                else if(m_oriente==0&&m_arretes[i]->getID1()==ID2&&m_arretes[i]->getID2()==ID1)
                {
                    return m_arretes[i]->getPoids();
                }
            }
            return 0;
}
int Graphe::TotalCouleur()
{
    int compteur=0;
            for (int i=0;i<getOrdre();++i)
            {
               if(m_sommets[i]->getMarquage()==0)
               {
                   compteur++;
               }
            }
            if (compteur==0)/// s'il ny a plus de sommet  non coloriée return 1
            {
                return 1;
            }
            else
            {
                return 0;
            }

}
void Graphe::afficherAdjacance()
{
    for (int i =0 ; i<getOrdre();i++)
         {
             std::cout<<"Sommet "<<i<<" Adjacent :";
             m_sommets[i]->afficherAdj();
             std::cout<<std::endl;

         }
}
int Graphe::PlusPetiteLongueur(std::vector<std::vector<int>> parcours)
{
    int i = 99999;
            int stock;
            for(size_t y=0;y<parcours.size();++y)
            {
                if (i>parcours[y][0])
                {
                    i=parcours[y][0];
                    stock=y;
                }
            }
            return stock;
}
int Graphe::IDParcours(int somFinal)
{
     int longueur =9999;
            int position=0;
         for(size_t i=0;i<m_parcours.size();i++)
         {
             if(m_parcours[i][m_parcours[i].size()-1]==somFinal&&longueur>m_parcours[i][0])
             {
                 longueur=m_parcours[i][0];
                 position=i;
             }
         }
         return position;
}
int Graphe::NmbrAdjNonmarque(int ID)
{
    int compteur=0;
                    for (int i =0;i<m_sommets[rechercheID(ID)]->getDegre();++i) ///On recupere le degrée pour parcourir la totalité des sommets adjacents
                {
                if(m_sommets[rechercheID(m_sommets[ID]->getAdj(i))]->getMarquage()==0)///Si le sommet Adj n'est pas déja marqué
                    {
                        compteur++;
                    }
                 }
                 return compteur;
}
void Graphe::AlgoDijkstra(int SomInit,int Somfinal)
{
    std::cout<<std::endl;
            int Som=SomInit;
            int EtapeCompteur =1;
            m_sommets[Som]->setMarquage(1);
            std::vector<int> stock;
            std::vector<int> stock2;
            stock.push_back(0);
            stock.push_back(Som);
            m_parcours.push_back(stock);///Le sommet est à une longueur 0 de lui meme
            int NumParcours=0;

            while(m_sommets[rechercheID(Somfinal)]->getMarquage()==0)
            {
                std::cout<<"Etape N :"<<EtapeCompteur<<std::endl;
                ///Preparation à l'actualisation des sommets
                stock.clear();
                stock=m_parcours[NumParcours];
                stock2=stock;
                m_parcours[NumParcours].clear();
                m_parcours.erase(m_parcours.begin()+NumParcours);



                for (int i =0;i<m_sommets[rechercheID(Som)]->getDegre();++i) //Parcours de la totalité des adjacent
                {
                    stock=stock2;
                    if(m_sommets[rechercheID(m_sommets[Som]->getAdj(i))]->getMarquage()==0)//Adj uniquement non marqué
                    {
                        stock.push_back(m_sommets[Som]->getAdj(i));

                        stock[0]=stock[0]+PoidsArrete(stock[stock.size()-2],stock[stock.size()-1]);
                        m_parcours.push_back(stock);
                    }
                }
                for (size_t i=0;i<m_parcours.size();++i)
                {

                    std::cout<<" Num :"<< i <<" longueur :"<<m_parcours[i][0]<<" Parcours :";

                    for(size_t y =1; y<m_parcours[i].size();++y)
                    {
                       std::cout <<"->"<<m_parcours[i][y];
                    }
                    std::cout<<std::endl;
                }
                NumParcours=PlusPetiteLongueur(m_parcours);///On recupere le parcours avec la plus petite longueur
                std::cout<<"Numero du parcours"<<NumParcours<<std::endl;
                Som=m_parcours[NumParcours][m_parcours[NumParcours].size()-1];///On recupere le dernier sommet de ce parcours et on le marque
                m_sommets[Som]->setMarquage(1);
                EtapeCompteur++;


            }
            std::cout <<" L'algorithme de Dijkstra donne le plus court chemin pour aller du sommet "<<SomInit<<" au sommet "<<Somfinal<<" :"<<std::endl;
            for(size_t i=1;i<m_parcours[IDParcours(Somfinal)].size();++i)
            {
                std::cout <<" -> "<<m_parcours[IDParcours(Somfinal)][i];
            }
            std::cout<<std::endl;
            std::cout<<"Chemin de Longueur : "<<m_parcours[IDParcours(Somfinal)][0]<<std::endl;
}


void Graphe::Cd()
{

    double indice = 0;
    for (int i=0; i<getOrdre() ; i++)
    {

        indice = double(m_sommets[i]->getDegre())/(getOrdre()-1);
        m_sommets[i]->setCd(indice);



    }

}

void Graphe::afficher_Cd()
{
    Cd();
    std::cout<<std::endl;
    std::cout<<"Indice de centralit\202 de degr\202 par sommet :"<<std::endl;
    std::cout<<std::endl;
    for(size_t i=0;i<m_sommets.size();i++)
    {
        std::cout<<"Sommet "<<i<<": "<<m_sommets[i]->getCd()<<std::endl;

    }

}

void Graphe::Cvp()
{
    double L=0;///Lambda
    double L2=1;
    double L3=-1;
    int C=0;
    double Somme=0;
    std::vector<int> ListeADJ;
    while(L2>=L || L>L3)
   {
      L2=L-0.01;
      L3=L+0.01;

    for(int i =0;i<getOrdre();++i)///Faire la somme des indices de ses voisins
    {
        C=0;
        ListeADJ=m_sommets[i]->getAdjListe();
        for (int y=0;y<m_sommets[i]->getDegre();++y)
        {
            Somme=Somme+m_sommets[ListeADJ[y]]->getCvp();///Calcule de C=Somme(Cvp) des sommets adjacants
        }
        ListeADJ.clear();///On renitialise la liste d'adjacance pr les prochains sommets
        C=Somme;
        std::cout<<"somme : "<<Somme<<std::endl;
        m_sommets[i]->setC(C);
    }

    Somme=0;

    for(int i =0;i<getOrdre();++i)///Calculer Lambda = (Somme des C)^1/2
    {
       Somme=Somme+m_sommets[i]->getC();
    }

    L=pow(Somme,0.5);
    Somme=0;

    for(int i =0;i<getOrdre();++i)///Recalculer l'indice Cvp pour chaque sommet
    {
       m_sommets[i]->setCvp(m_sommets[i]->getC()/L);
    }

   }

}
void Graphe::afficher_Cvp()
{
    Cvp();
    std::cout<<std::endl;
    std::cout<<"Indice de centralit\202 de vecteur propre par sommet :"<<std::endl;
    std::cout<<std::endl;
    for(size_t i=0;i<m_sommets.size();i++)
    {
        std::cout<<"Sommet "<<i<<": "<<m_sommets[i]->getCvp()<<std::endl;

    }


}


void Graphe::afficherGraphe()
{
    Svgfile svgout;
        ///placer les sommets

        for(size_t i=0; i<m_sommets.size();i++)
        {
            svgout.addDisk(m_sommets[i]->getX()*100 , m_sommets[i]->getY()*100, 5, "blue");
            ///afficher les lettres
            svgout.addText(m_sommets[i]->getX()*100 , m_sommets[i]->getY()*100-5, m_sommets[i]->getNom(),"black" );


        }

        ///placer les arretes
        int s1, s2;

        for(size_t i=0; i<m_arretes.size();i++)
        {
            s1 = m_arretes[i]->getID1();
            s2 = m_arretes[i]->getID2();
            svgout.addLine(m_sommets[s1]->getX()*100, m_sommets[s1]->getY()*100, m_sommets[s2]->getX()*100, m_sommets[s2]->getY()*100, "black");
            svgout.addText((m_sommets[s1]->getX()*100+ m_sommets[s2]->getX()*100)/2, (m_sommets[s1]->getY()*100+ m_sommets[s2]->getY()*100)/2, m_arretes[i]->getNumArrete(),"green" );
        }



}
/*
void Graphe::Cp()
{
    int SomDepart;
    int SomFin;
    int indice = 0;
    int DegMax = 0;
    int compteur = 0;
    int Somme = 0;


    for(int i=0 ; i<getOrdre() ; i++)
    {
        Somme = Somme + AlgoDijkstra(SomDepart,SomFin);
    }

    DegMax = getOrdre()-1;

    for(int i=0 ; i<getOrdre() ; i++)
    {
        indice = (DegMax)/(Somme);
        m_sommets[i]->setCp(indice);
    }
}
*/
std::vector<int> Graphe:: BFS(int num_s0)const
{

    std::cout<<"parcours BFS :";
    /// déclaration de la file
    std::queue<int> file;
    /// pour le marquage
    std::vector<int> couleurs((int)m_sommets.size(),0);
    ///pour noter les prédécesseurs : on note les numéros des prédécesseurs (on pourrait stocker des pointeurs sur ...)
    std::vector<int> preds((int)m_sommets.size(),-1);

    ///étape initiale : on enfile et on marque le sommet initial
    file.push(num_s0);
    couleurs[num_s0]=1;

    int s;

    ///tant que la file n'est pas vide
    while(!file.empty())
    {
        ///on défile le prochain sommet
        s = file.front();
        std::cout<<" "<<s;
        file.pop();

        ///pour chaque successeur du sommet défilé
        for(auto succ:m_sommets[s]->getAdjListe())
        {
            if (couleurs[succ] == 0)
            {
                couleurs[succ]=1;
                preds[succ]=s;
                file.push(succ);
            }                           ///s'il n'est pas marqué
                                        ///on le marque
                                        ///on note son prédecesseur (=le sommet défilé)
                                        ///on le met dans la file
        }
    }
    return preds;
}


/*recherche et affichage des composantes connexes*/
void Graphe :: rechercher_afficher_CC()
{
    size_t num=0;
    bool test;
    int ncc=0;
    ///pour noter les numéros de CC
    std::vector<int> cc(m_sommets.size(),-1);
    do{
        cc[num]=num;
        std::cout<<std::endl<<"composante connexe "<<ncc<<" : "<<num<<" ";
        ncc++;
        ///lancement d'un BFS sur le sommet num
        std::vector<int> arbre_BFS=BFS(num);
        ///affichage des sommets decouverts lors du parcours (ceux qui ont un predecesseur
        for(size_t i=0;i<arbre_BFS.size();++i){
            if ((i!=num)&&(arbre_BFS[i]!=-1)){
                    cc[i]=num;
                    //std::cout<<i<<" ";
            }
        }
        ///recherche d'un sommet non exploré
        ///pour relancer un BFS au prochain tour
        test=false;
        for(size_t i=0;i<m_sommets.size();++i){
            if (cc[i]==-1){
                num=i;
                test=true;
                break;
            }
        }
    }while(test==true);
    std::cout<<std::endl;
}
void Graphe::vulnerabilite()
{
    int test=0;
    int a1=0;
    std::vector<int> ListeADJ;

    do
    {
        std::cout<<"Rentrez le numero de l'arete que vous voulez supprimer"<<std::endl;
        std::cin>>a1;
        m_arretes.erase (m_arretes.begin()+a1+1);

        for(size_t i=0;i<m_sommets.size();++i)
        {
            m_sommets[i]->Erase_Adjacent();
            ListeADJ = m_sommets[i]->getAdjListe() ;
            for(auto element : ListeADJ )
            {

                std::cout<<"coucou: "<<element<<std::endl;
            }
        }

        DeterminerAdjacance();
        afficherGraphe();
        std::cout<<"Vous avez supprim\202 l'arete "<<a1<<". Pour supprimer une autre arete, tapez 0 sinon tapez 1"<<std::endl;
        std::cin>>test;
    }while(test==0);

    rechercher_afficher_CC();

}

void Graphe::setPPL(int PPL)
{
    m_PPLongueur=PPL;
}

int Graphe::getPPL()
{
    return m_PPLongueur;
}

void Graphe::MemeLong(int Somfinal)
{
    for(size_t i=0 ;i<m_parcours.size();++i)
    {
        if(m_parcours[i][0]==getPPL()&&m_parcours[i][m_parcours[i].size()-1]==Somfinal)
        {
            m_parcours[i][1]=1;
        }
    }
}

std::vector<std::vector<int>> Graphe::DijkstraModif(int SomInit,int Somfinal)
{
     int Som=SomInit;
            int EtapeCompteur =1;
            std::vector<std::vector<int>> PlusCourtChemins;
            m_sommets[Som]->setMarquage(1);/// On marque le sommet de départ
            std::vector<int> stock;
            std::vector<int> stock2;
            stock.push_back(0);///On initialise la case de longueur à 0
            stock.push_back(0);///Bool pour savoir si le parcours à deja ete utilisé
            stock.push_back(Som);///On met le sommet de départ
            m_parcours.push_back(stock);///Le sommet est à une longueur 0 de lui meme
            int NumParcours=0;

            while(m_sommets[rechercheID(Somfinal)]->getMarquage()==0)
            {
               // std::cout<<"Etape N :"<<EtapeCompteur<<std::endl;
                ///Preparation à l'actualisation des sommets
                stock.clear();
                stock=m_parcours[NumParcours];
                stock2=stock;
                m_parcours[NumParcours].clear();
                m_parcours.erase(m_parcours.begin()+NumParcours);



                for (int i =0;i<m_sommets[rechercheID(Som)]->getDegre();++i) ///Parcours de la totalité des sommets adjacents
                {
                    stock.clear();
                    stock=stock2;
                    if(m_sommets[rechercheID(m_sommets[Som]->getAdj(i))]->getMarquage()==0)///On sélectionne les sommets adj uniquement non-marqué
                    {
                        stock.push_back(m_sommets[Som]->getAdj(i));///Rajout des sommets ADJ au chemin
                        stock[0]=stock[0]+PoidsArrete(stock[stock.size()-2],stock[stock.size()-1]);
                        m_parcours.push_back(stock);///Ajout du chemin à la liste des chemins
                    }
                }
                /*for (size_t i=0;i<m_parcours.size();++i)
                {

                    std::cout<<" Num :"<< i <<" longueur :"<<m_parcours[i][0]<<" Parcours :";

                    for(size_t y =2; y<m_parcours[i].size();++y)
                    {
                       std::cout <<"->"<<m_parcours[i][y];
                    }
                    std::cout<<std::endl;
                }*/
                NumParcours=PlusPetiteLongueur(m_parcours);///On recupere le parcours avec la plus petite longueur
               // std::cout<<"Numero du parcours"<<NumParcours<<std::endl;
                Som=m_parcours[NumParcours][m_parcours[NumParcours].size()-1];///On recupere le dernier sommet de ce parcours et on le marque
                m_sommets[Som]->setMarquage(1);
                EtapeCompteur++;

                if(m_sommets[rechercheID(Somfinal)]->getMarquage()==1)
                {
                    setPPL(m_parcours[IDParcours(Somfinal)][0]);
                    MemeLong(rechercheID(Somfinal));
                }




            }
            //////AFFICHAGE//////
           /*std::cout <<"Plus court chemin pour aller du sommet "<<SomInit<<" au sommet "<<Somfinal<<" :";*/

            for (size_t y=0;y<m_parcours.size();y++)
            {
                if(m_parcours[y][1]==1)
                {
                    PlusCourtChemins.push_back(m_parcours[y]);
                        for(size_t i=2;i<m_parcours[y].size();++i)
                        {
                            //std::cout<<" ->"<<m_parcours[y][i];
                        }
                        std::cout<<std::endl;
                }
                }
           // std::cout<<"Longueur : "<<m_parcours[IDParcours(Somfinal)][0]<<std::endl;
            m_parcours.clear();
            for(size_t i=0;i<getOrdre();++i)
            {
                m_sommets[i]->setMarquage(0);
            }

            return PlusCourtChemins;
}
void Graphe::Ci()
{
    double n_pccI=0;
 double n_pccJK=0;
 double Somme=0;
 double C=0;
 int compteur =0;
 std::vector<std::vector<int>> PCChemins;
for(int i=0;i<getOrdre();i++)
{

 std::cout<<"I: " <<i<<std::endl;
   for (int j=0;j<=(getOrdre()-2);++j)///Fonctionne uniquement si l'ID des sommets commence par 0
    {
        for (int k=1+j;k<=getOrdre()-1;++k)
        {
            std::cout<<"j :"<<j<<" k : "<<k<<std::endl;;
            PCChemins=DijkstraModif(j,k);
            for(size_t x=0;x<PCChemins.size();x++)
            {
                for(size_t y=2;y<PCChemins[x].size();y++)
                {
                    if(PCChemins[x][y]==i)
                    {
                        n_pccI++;
                    }
                }
            }
            n_pccJK=PCChemins.size();
            Somme=Somme+(n_pccI/n_pccJK);
            n_pccJK=0;
            n_pccI=0;
            PCChemins.clear();
        }
    }

    C=(2*Somme)/(pow((double)getOrdre(),2.0)-(3*(double)getOrdre())+2);
    Somme=0;
}


}

void Graphe::Cp()
{
    double Somme=0;
    double Dij=0;///Distance entre les sommets I et J
    double C=0;
    std::vector<std::vector<int>> PCChemins;
    for(int i=0;i<getOrdre();i++)///Parcours de la totalité des sommets du graphe
    {
     for(int y =0;y<getOrdre();y++)
     {
         if (y==i)///Y=/=i
         {
             if(y==getOrdre()-1)
             {
                 break;
             }
             else
             {
                 y++;
             }
         }
         PCChemins=DijkstraModif(i,y);///On recupere le trajet du plus court chemin avec la longueur situé en 0
         Dij=PCChemins[0][0];
         std::cout<<"i :"<<i<<" y: "<<y<<"Longueur :"<<PCChemins[0][0]<<std::endl;
         PCChemins.clear();
         Somme=Somme+Dij;
         Dij=0;


     }
     C=((double)getOrdre()-1)/Somme;
     Somme=0;
     m_sommets[i]->setCp(C);

    }


}
