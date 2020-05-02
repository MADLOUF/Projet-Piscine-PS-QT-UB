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

Graphe::Graphe()
{

}

void Graphe::CreerGraphe(std::string nomFichier)
{
    system("cls");
    setPondere(0); ///ne pas mettre la ponderation au debut du graphe
    setIndice(0); ///ne pas mettre les indices des le debut
    setChoixcoul('1'); /// met l'affichage des sommets par degres par default
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

void Graphe::EffacerGraphe()
{


    for(int i=0;i<getOrdre();++i)   ///suppression des sommet et adjacents
    {
        delete m_sommets[i];
    }
    for(int i=0;i<getTaille();++i)   ///suppression des arretes
    {
        delete m_arretes[i];
    }
    while(!m_sommets.empty())
    {
        m_sommets.erase(m_sommets.begin());
    }
    while(!m_arretes.empty())
    {
        m_arretes.erase(m_arretes.begin());
    }

}

void Graphe::Load_ponderation(std::string nomFichier)
{
    std::ifstream ifs{nomFichier};
            if (!ifs)
                throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
            int taille;
            ifs >> taille;
            std::cout<<std::endl;
            ///rien faire avec la taille?
            int ID;
            int poids;
            for (int i=0; i<taille; ++i)
            {
                ifs>>ID;
                ifs>>poids;
                m_arretes[ID]->setPoids(poids);
                if (!ifs)
                throw std::runtime_error( "Probleme lecture poid arrete" );

            }


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
int Graphe::getPondere() const
{
    return m_pondere;
}

void Graphe::setPondere(bool test)
{
    m_pondere=test;
}

int Graphe::getIndice() const
{
    return m_indice;
}

void Graphe::setIndice(bool test)
{
    m_indice=test;
}

char Graphe::getChoixcoul() const
{
    return m_choixcoul;
}

void Graphe::setChoixcoul(char choix)
{
    m_choixcoul=choix;
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

    double C = 0;
    double Cnn=0;
    for (int i=0; i<getOrdre() ; i++)
    {

        C = double(m_sommets[i]->getDegre())/(getOrdre()-1);
        Cnn= C*(getOrdre()-1);
        m_sommets[i]->setCd(C);
        m_sommets[i]->setCdnn(Cnn);


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
{   double L=0;///Lambda
    double L2=0;
    double L3=1;///DeltaLambda
    double C=0;
    double Cvp=0;
    double Somme=0;
    std::vector<int> ListeADJ;
    for(int i=0;i<getOrdre();++i)///Rénitialisation de Cvp
    {
        m_sommets[i]->setCvp(1);
    }
    while(L3>=0.01)
	{

	  for(int i=0;i<getOrdre();++i)///Determination de  C
	  {
	      Somme=0;
	      //std::cout<<"Sommet N: "<<i<<"  Cvp = "<<m_sommets[i]->getCvp();
	       ListeADJ=m_sommets[i]->getAdjListe();
		   for(int y=0;y<m_sommets[i]->getDegre();y++)
		   {
		     Somme=Somme+m_sommets[ListeADJ[y]]->getCvp();
		   }
		 C=Somme;
		 m_sommets[i]->setC(C);
		 //std::cout<<"  C ="<<m_sommets[i]->getC()<<std::endl;
		 ListeADJ.clear();
	  }


	  Somme=0;
	  for(int i=0;i<getOrdre();++i)
	  {
	    Somme=Somme+pow(m_sommets[i]->getC(),2.0);
	  }

	  L2=L;
	  L=pow(Somme,0.5);
	  //std::cout<<"Lambda = "<<L<<std::endl<<std::endl;
	  if(L2>=L)///Calcul de delta L
      {L3=L2-L;}
      else
      {L3=L-L2;}
	  for(int i=0;i<getOrdre();++i)
	  {
       C=m_sommets[i]->getC();
	   Cvp=(C/L);
	   m_sommets[i]->setCvp(Cvp);
	   //std::cout<<"Sommet N: "<<i<<"  Cvp = "<<m_sommets[i]->getCvp()<<"  C ="<<m_sommets[i]->getC()<<std::endl;
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



void Graphe::Cp()
{
    double Somme=0;
    double Dij=0;///Distance entre les sommets I et J
    double C=0;
    double Cnn=0;
    std::vector<std::vector<int>> PCChemins;

    for(int i=0;i<getOrdre();i++)///Parcours de la totalité des sommets du graphe
    {
        if(m_sommets[i]->getDegre()!=0)
        {
            for(int y =0;y<getOrdre();y++)
            {
                if(y!=i&&m_sommets[y]->getDegre()!=0)
                {
                            PCChemins=DijkstraModif(i,y);///On recupere le trajet du plus court chemin avec la longueur situé en 0
                            Dij=PCChemins[0][0];
                            //std::cout<<"i :"<<i<<" y: "<<y<<"Longueur :"<<PCChemins[0][0]<<std::endl;
                            PCChemins.clear();
                            Somme=Somme+Dij;
                            Dij=0;

                }
            }
            Cnn=(1/Somme);
            C=((double)getOrdre()-1)/Somme;
            Somme=0;
            m_sommets[i]->setCp(C);
            m_sommets[i]->setCpnn(Cnn);
        }
        else
        {
            m_sommets[i]->setCp(0);
            m_sommets[i]->setCpnn(0);
        }


    }
}

void Graphe::afficher_Cp()
{
    Cp();
    std::cout<<std::endl;
    std::cout<<"Indice de centralit\202 de proximit\202 par sommet :"<<std::endl;
    std::cout<<std::endl;
    for(size_t i=0;i<m_sommets.size();i++)
    {
        std::cout<<"Sommet "<<i<<": "<<m_sommets[i]->getCp()<<std::endl;

    }


}

void Graphe::Ci()
{
    double n_pccI=0;
    double n_pccJK=0;
    double Somme=0;
    double C=0;
    double Cnn=0;
    std::vector<std::vector<int>> PCChemins;
    for(int i=0;i<getOrdre();i++)
    {
        if(m_sommets[i]->getDegre()!=0)
        {
            for (int j=0;j<=(getOrdre()-2);++j)///Fonctionne uniquement si l'ID des sommets commence par 0
    {


        if(m_sommets[j]->getDegre()!=0)
        {
            for (int k=1+j;k<=getOrdre()-1;++k)
            {
                if(m_sommets[k]->getDegre()!=0)
                {
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
                n_pccJK=0;
                n_pccI=0;
                PCChemins.clear();


            }

        }

    }
    Cnn=(2*Somme);
    C=(2*Somme)/(pow((double)getOrdre(),2.0)-(3*(double)getOrdre())+2);
    m_sommets[i]->setCinn(Cnn);
    m_sommets[i]->setCi(C);
    Somme=0;

        }
        else
        {
             m_sommets[i]->setCinn(0);
             m_sommets[i]->setCi(0);
        }


    }


}

void Graphe::afficher_Ci()
{
    Ci();
    std::cout<<std::endl;
    std::cout<<"Indice de centralit\202 d'interm\202diarit\202  par sommet :"<<std::endl;
    std::cout<<std::endl;
    for(size_t i=0;i<m_sommets.size();i++)
    {
        std::cout<<"Sommet "<<i<<": "<<m_sommets[i]->getCi()<<std::endl;

    }
}

void Graphe::afficherGraphe()
{

    Svgfile svgout;
    afficherColoration(svgout);
    svgout.addGrid();
    ///placer les sommets

        for(size_t i=0; i<m_sommets.size();i++)
        {
            svgout.addDisk(m_sommets[i]->getX()*100 , m_sommets[i]->getY()*100, 5, m_sommets[i]->getCouleur());
            ///afficher les lettres
            svgout.addText(m_sommets[i]->getX()*100+5 , m_sommets[i]->getY()*100-5, m_sommets[i]->getNom(),"black" );
        }

        ///placer les arretes
        int s1, s2;

        for(size_t i=0; i<m_arretes.size();i++)
        {
            s1 = m_arretes[i]->getID1();
            s2 = m_arretes[i]->getID2();
            svgout.addLine(m_sommets[s1]->getX()*100, m_sommets[s1]->getY()*100, m_sommets[s2]->getX()*100, m_sommets[s2]->getY()*100, "black");
            svgout.addText((m_sommets[s1]->getX()*100+ m_sommets[s2]->getX()*100)/2+18, (m_sommets[s1]->getY()*100+ m_sommets[s2]->getY()*100)/2, i,"green" );

            ///placer les fleches si orienté
            if(m_oriente==1)
            {
                if(m_sommets[s1]->getX()== m_sommets[s2]->getX())
                {
                    if(m_sommets[s1]->getY() < m_sommets[s2]->getY())///vers le bas
                    {
                        svgout.addTriangle(m_sommets[s2]->getX()*100,m_sommets[s2]->getY()*100,m_sommets[s2]->getX()*100+5,m_sommets[s2]->getY()*100-7,m_sommets[s2]->getX()*100-5,m_sommets[s2]->getY()*100-7, "black");
                    }
                    if(m_sommets[s1]->getY() > m_sommets[s2]->getY()) ///vers le haut
                    {
                        svgout.addTriangle(m_sommets[s2]->getX()*100,m_sommets[s2]->getY()*100,m_sommets[s2]->getX()*100+5,m_sommets[s2]->getY()*100+7,m_sommets[s2]->getX()*100-5,m_sommets[s2]->getY()*100+7, "black");
                    }
                }
                if(m_sommets[s1]->getY()== m_sommets[s2]->getY())
                {
                    if(m_sommets[s1]->getX() < m_sommets[s2]->getX()) ///vers la droite
                    {
                        svgout.addTriangle(m_sommets[s2]->getX()*100,m_sommets[s2]->getY()*100,m_sommets[s2]->getX()*100-7,m_sommets[s2]->getY()*100+5,m_sommets[s2]->getX()*100-7,m_sommets[s2]->getY()*100-5, "black");
                    }
                    if(m_sommets[s1]->getX() > m_sommets[s2]->getX()) ///vers la gauche
                    {
                        svgout.addTriangle(m_sommets[s2]->getX()*100,m_sommets[s2]->getY()*100,m_sommets[s2]->getX()*100+7,m_sommets[s2]->getY()*100-5,m_sommets[s2]->getX()*100+7,m_sommets[s2]->getY()*100-5, "black");
                    }

                }
                if(m_sommets[s1]->getX()> m_sommets[s2]->getX())  ///vecteur orienté vers la gauche
                {
                    if(m_sommets[s1]->getY() > m_sommets[s2]->getY()) ///diagonale haut gauche
                    {
                        svgout.addTriangle(m_sommets[s2]->getX()*100,m_sommets[s2]->getY()*100,m_sommets[s2]->getX()*100+9,m_sommets[s2]->getY()*100,m_sommets[s2]->getX()*100,m_sommets[s2]->getY()*100+9, "black");
                    }
                    if(m_sommets[s1]->getY() < m_sommets[s2]->getY()) ///diagonale bas gauche
                    {
                        svgout.addTriangle(m_sommets[s2]->getX()*100,m_sommets[s2]->getY()*100,m_sommets[s2]->getX()*100+9,m_sommets[s2]->getY()*100,m_sommets[s2]->getX()*100,m_sommets[s2]->getY()*100-9, "black");
                    }

                }
                if(m_sommets[s1]->getX()< m_sommets[s2]->getX())  ///vecteur orienté vers la gauche
                {
                    if(m_sommets[s1]->getY() > m_sommets[s2]->getY()) ///diagonale haut droite
                    {
                        svgout.addTriangle(m_sommets[s2]->getX()*100,m_sommets[s2]->getY()*100,m_sommets[s2]->getX()*100-9,m_sommets[s2]->getY()*100,m_sommets[s2]->getX()*100,m_sommets[s2]->getY()*100+9, "black");
                    }
                    if(m_sommets[s1]->getY() < m_sommets[s2]->getY()) ///diagonale bas droite
                    {
                        svgout.addTriangle(m_sommets[s2]->getX()*100,m_sommets[s2]->getY()*100,m_sommets[s2]->getX()*100-9,m_sommets[s2]->getY()*100,m_sommets[s2]->getX()*100,m_sommets[s2]->getY()*100-9, "black");
                    }

                }

            }
        }



        ///LEGENDE
        svgout.addDisk(700,500, 7,"cyan" );  ///disque
        svgout.addDisk(700,524, 7,"blue" );
        svgout.addDisk(700,548, 7,"green" );
        svgout.addDisk(700,572, 7,"yellow" );
        svgout.addDisk(700,596, 7,"orange" );
        svgout.addDisk(700,620, 7,"red" );
        svgout.addRect(693,637,15,15,"green","black"); ///legende carré vert
        svgout.addText(720,651,"ID de l'arete","black");

        ///affiche ponderation si activé
        if(getPondere()==1)
        {
            afficherPonderation(svgout);
        }
        else
            std::cout<<"Vous n'avez pas charg\202 la ponderation"<<std::endl;

        ///affiche indice si activé
        if(getIndice()==1)
        {
            afficherIndices(svgout);
        }
        else
            std::cout<<"Vous n'avez pas charg\202 les indices"<<std::endl;




}

void Graphe::afficherPonderation(Svgfile &svgout)
{


        ///placer les ponderations
        int s1, s2;

        for(size_t i=0; i<m_arretes.size();i++)
        {
            s1 = m_arretes[i]->getID1();
            s2 = m_arretes[i]->getID2();
            svgout.addText((m_sommets[s1]->getX()*100+ m_sommets[s2]->getX()*100)/2-30, (m_sommets[s1]->getY()*100+ m_sommets[s2]->getY()*100)/2, m_arretes[i]->getPoids(),"red" );
        }
        svgout.addRect(693,662,15,15,"red","black");
        svgout.addText(720,676,"Poids de l'arete","black");

}

void Graphe::afficherIndices(Svgfile &svgout)
{


        for(size_t i=0; i<m_sommets.size();i++)
        {

            ///afficher les indices par sommet
            svgout.addText(m_sommets[i]->getX()*100-30, m_sommets[i]->getY()*100+10, m_sommets[i]->getCd(),"purple" );
            svgout.addText(m_sommets[i]->getX()*100-30, m_sommets[i]->getY()*100+27, m_sommets[i]->getCvp(),"purple" );

            if(getPondere()==1)
            {
                svgout.addText(m_sommets[i]->getX()*100-30, m_sommets[i]->getY()*100+44, m_sommets[i]->getCp(),"purple" );
                svgout.addText(m_sommets[i]->getX()*100-30, m_sommets[i]->getY()*100+61, m_sommets[i]->getCi(),"purple" );
            }
        }

}

void Graphe::afficherColoration(Svgfile &svgout)
{
    double maxi=0;
    double inter=0;
        if(getChoixcoul()=='1') /// coloration par degres
        {
            for(int i=0; i<getOrdre();i++)
            {
                if(m_sommets[i]->getDegre()==0)
                {
                    m_sommets[i]->setCouleur("cyan");
                }
                if(m_sommets[i]->getDegre()==1)
                {
                    m_sommets[i]->setCouleur("blue");
                }
                if(m_sommets[i]->getDegre()==2)
                {
                    m_sommets[i]->setCouleur("green");
                }
                if(m_sommets[i]->getDegre()==3)
                {
                    m_sommets[i]->setCouleur("yellow");
                }
                if(m_sommets[i]->getDegre()==4)
                {
                    m_sommets[i]->setCouleur("orange");
                }
                if(m_sommets[i]->getDegre()==5)
                {
                    m_sommets[i]->setCouleur("red");
                }
                if(m_sommets[i]->getDegre()>5)
                {
                    m_sommets[i]->setCouleur("purple");
                }

            }
            svgout.addText(720,506,"0 voisin","black");
            svgout.addText(720,530,"1 voisin","black");
            svgout.addText(720,554,"2 voisins","black");
            svgout.addText(720,578,"3 voisins","black");
            svgout.addText(720,602,"4 voisins","black");
            svgout.addText(720,626,"5 voisins","black");

        }

        if(getChoixcoul()=='2') /// coloration par Cd
        {
            Cd();
            for(int i=0; i<getOrdre();i++)
            {

                if(maxi<m_sommets[i]->getCd())   ///trouver la valeur max
                {
                    maxi=m_sommets[i]->getCd();
                }

            }

            inter=maxi/6;    ///car 6 couleurs

            for(int i=0; i<getOrdre();i++)
            {
                if(0<=m_sommets[i]->getCd() && m_sommets[i]->getCd()<inter)
                {
                    m_sommets[i]->setCouleur("cyan");
                }
                if(inter<=m_sommets[i]->getCd() && m_sommets[i]->getCd()<inter*2)
                {
                    m_sommets[i]->setCouleur("blue");
                }
                if(inter*2<=m_sommets[i]->getCd() && m_sommets[i]->getCd()<inter*3)
                {
                    m_sommets[i]->setCouleur("green");
                }
                if(inter*3<=m_sommets[i]->getCd() && m_sommets[i]->getCd()<inter*4)
                {
                    m_sommets[i]->setCouleur("yellow");
                }
                if(inter*4<=m_sommets[i]->getCd() && m_sommets[i]->getCd()<inter*5)
                {
                    m_sommets[i]->setCouleur("orange");
                }
                if(inter*5<=m_sommets[i]->getCd() && m_sommets[i]->getCd()<=maxi)
                {
                    m_sommets[i]->setCouleur("red");
                }

            }
            svgout.addText(720,506,0,"black");
            svgout.addText(820,506,inter,"black");
            svgout.addText(720,530,inter,"black");
            svgout.addText(820,530,inter*2,"black");
            svgout.addText(720,554,inter*2,"black");
            svgout.addText(820,554,inter*3,"black");
            svgout.addText(720,578,inter*3,"black");
            svgout.addText(820,578,inter*4,"black");
            svgout.addText(720,602,inter*4,"black");
            svgout.addText(820,602,inter*5,"black");
            svgout.addText(720,626,inter*5,"black");
            svgout.addText(820,626,maxi,"black");
        }

        if(getChoixcoul()=='3') /// coloration par Cvp
        {
            Cvp();
            for(int i=0; i<getOrdre();i++)
            {

                if(maxi<m_sommets[i]->getCvp())   ///trouver la valeur max
                {
                    maxi=m_sommets[i]->getCvp();
                }

            }

            inter=maxi/6;    ///car 6 couleurs

            for(int i=0; i<getOrdre();i++)
            {
                if(0<=m_sommets[i]->getCvp() && m_sommets[i]->getCvp()<inter)
                {
                    m_sommets[i]->setCouleur("cyan");
                }
                if(inter<=m_sommets[i]->getCvp() && m_sommets[i]->getCvp()<inter*2)
                {
                    m_sommets[i]->setCouleur("blue");
                }
                if(inter*2<=m_sommets[i]->getCvp() && m_sommets[i]->getCvp()<inter*3)
                {
                    m_sommets[i]->setCouleur("green");
                }
                if(inter*3<=m_sommets[i]->getCvp() && m_sommets[i]->getCvp()<inter*4)
                {
                    m_sommets[i]->setCouleur("yellow");
                }
                if(inter*4<=m_sommets[i]->getCvp() && m_sommets[i]->getCvp()<inter*5)
                {
                    m_sommets[i]->setCouleur("orange");
                }
                if(inter*5<=m_sommets[i]->getCvp() && m_sommets[i]->getCvp()<=maxi)
                {
                    m_sommets[i]->setCouleur("red");
                }

            }
            svgout.addText(720,506,0,"black");
            svgout.addText(820,506,inter,"black");
            svgout.addText(720,530,inter,"black");
            svgout.addText(820,530,inter*2,"black");
            svgout.addText(720,554,inter*2,"black");
            svgout.addText(820,554,inter*3,"black");
            svgout.addText(720,578,inter*3,"black");
            svgout.addText(820,578,inter*4,"black");
            svgout.addText(720,602,inter*4,"black");
            svgout.addText(820,602,inter*5,"black");
            svgout.addText(720,626,inter*5,"black");
            svgout.addText(820,626,maxi,"black");
        }

        if(getPondere()==1)
        {
            if(getChoixcoul()=='4') /// coloration par Cp
            {
                Cp();  ///l'appeler car sinon il s'effectue pas tant qu'on l'affiche pas
                for(int i=0; i<getOrdre();i++)
                {

                    if(maxi < m_sommets[i]->getCp())   ///trouver la valeur max
                    {
                        maxi=m_sommets[i]->getCp();
                        std::cout<<"Maxi : "<<maxi<<std::endl;
                    }

                }
                std::cout<<"Maxi : "<<maxi<<std::endl;

                inter=maxi/6;    ///car 6 couleurs

                for(int i=0; i<getOrdre();i++)
                {
                    if(0<=m_sommets[i]->getCp() && m_sommets[i]->getCp()<inter)
                    {
                        m_sommets[i]->setCouleur("cyan");
                    }
                    if(inter<=m_sommets[i]->getCp() && m_sommets[i]->getCp()<inter*2)
                    {
                        m_sommets[i]->setCouleur("blue");
                    }
                    if(inter*2<=m_sommets[i]->getCp() && m_sommets[i]->getCp()<inter*3)
                    {
                        m_sommets[i]->setCouleur("green");
                    }
                    if(inter*3<=m_sommets[i]->getCp() && m_sommets[i]->getCp()<inter*4)
                    {
                        m_sommets[i]->setCouleur("yellow");
                    }
                    if(inter*4<=m_sommets[i]->getCp() && m_sommets[i]->getCp()<inter*5)
                    {
                        m_sommets[i]->setCouleur("orange");
                    }
                    if(inter*5<=m_sommets[i]->getCp() && m_sommets[i]->getCp()<=maxi)
                    {
                        m_sommets[i]->setCouleur("red");
                    }

                }
                svgout.addText(720,506,0,"black");
                svgout.addText(820,506,inter,"black");
                svgout.addText(720,530,inter,"black");
                svgout.addText(820,530,inter*2,"black");
                svgout.addText(720,554,inter*2,"black");
                svgout.addText(820,554,inter*3,"black");
                svgout.addText(720,578,inter*3,"black");
                svgout.addText(820,578,inter*4,"black");
                svgout.addText(720,602,inter*4,"black");
                svgout.addText(820,602,inter*5,"black");
                svgout.addText(720,626,inter*5,"black");
                svgout.addText(820,626,maxi,"black");

            }

            if(getChoixcoul()=='5') /// coloration par Ci
            {
                Ci();
                for(int i=0; i<getOrdre();i++)
                {

                    if(maxi<m_sommets[i]->getCi())   ///trouver la valeur max
                    {
                        maxi=m_sommets[i]->getCi();
                    }

                }

                inter=maxi/6;    ///car 6 couleurs

                for(int i=0; i<getOrdre();i++)
                {
                    if(0<=m_sommets[i]->getCi() && m_sommets[i]->getCi()<inter)
                    {
                        m_sommets[i]->setCouleur("cyan");
                    }
                    if(inter<=m_sommets[i]->getCi() && m_sommets[i]->getCi()<inter*2)
                    {
                        m_sommets[i]->setCouleur("blue");
                    }
                    if(inter*2<=m_sommets[i]->getCi() && m_sommets[i]->getCi()<inter*3)
                    {
                        m_sommets[i]->setCouleur("green");
                    }
                    if(inter*3<=m_sommets[i]->getCi() && m_sommets[i]->getCi()<inter*4)
                    {
                        m_sommets[i]->setCouleur("yellow");
                    }
                    if(inter*4<=m_sommets[i]->getCi() && m_sommets[i]->getCi()<inter*5)
                    {
                        m_sommets[i]->setCouleur("orange");
                    }
                    if(inter*5<=m_sommets[i]->getCi() && m_sommets[i]->getCi()<=maxi)
                    {
                        m_sommets[i]->setCouleur("red");
                    }

                }
                svgout.addText(720,506,0,"black");
                svgout.addText(820,506,inter,"black");
                svgout.addText(720,530,inter,"black");
                svgout.addText(820,530,inter*2,"black");
                svgout.addText(720,554,inter*2,"black");
                svgout.addText(820,554,inter*3,"black");
                svgout.addText(720,578,inter*3,"black");
                svgout.addText(820,578,inter*4,"black");
                svgout.addText(720,602,inter*4,"black");
                svgout.addText(820,602,inter*5,"black");
                svgout.addText(720,626,inter*5,"black");
                svgout.addText(820,626,maxi,"black");


            }
        }




        ///placer les sommets


}


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
        Cvp();
        Cd();
        if(getPondere()==1)
        {
        Cp();
        Ci();
        }

        std::cout<<"Rentrez le numero de l'arete que vous voulez supprimer"<<std::endl;
        std::cin>>a1;
        m_arretes.erase (m_arretes.begin()+a1);


        for(size_t i=0;i<m_sommets.size();++i)
        {
            m_sommets[i]->Erase_Adjacent();
            ListeADJ = m_sommets[i]->getAdjListe() ;

        }
        DeterminerAdjacance();
        for(int i =0;i<getOrdre();++i)
        {
            m_sommets[i]->setCd2(m_sommets[i]->getCd());
            m_sommets[i]->setCvp2(m_sommets[i]->getCvp());
            m_sommets[i]->setCi2(m_sommets[i]->getCi());
            m_sommets[i]->setCp2(m_sommets[i]->getCp());
        }
        Cvp();
        Cd();
        if(getPondere()==1)
        {
        Cp();
        Ci();
        }
        afficherGraphe();
        std::cout<<"Vous avez supprim\202 l'arete "<<a1<<". Pour supprimer une autre arete, tapez 0 sinon tapez 1"<<std::endl;
        std::cin>>test;
    }while(test==0);




    comparaison();

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

            NumParcours=PlusPetiteLongueur(m_parcours);///On recupere le parcours avec la plus petite longueur

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

            }
            }
       // std::cout<<"Longueur : "<<m_parcours[IDParcours(Somfinal)][0]<<std::endl;
        m_parcours.clear();
        for(int i=0;i<getOrdre();++i)
        {
            m_sommets[i]->setMarquage(0);
        }

        return PlusCourtChemins;
}


void Graphe::Save()
{
    int test=0;
    std::string const save("D:/ECE 19-20/Informatique/C++/Projet-Piscine-PS-QT-UB/Sauvegarde.txt");
    std::ofstream monFlux(save.c_str());

    if(monFlux)
    {
        monFlux << "ID    Cd         Cvp          Cp         Ci"<<std::endl;
        for(int i=0;i<getOrdre();i++)
        {

            monFlux << m_sommets[i]->getID()<<"     "<<  m_sommets[i]->getCd() <<"     "<< m_sommets[i]->getCvp();
            if(getPondere()==1)
            {
                monFlux <<"     "<< m_sommets[i]->getCp() <<"     "<< m_sommets[i]->getCi() <<std::endl;
            }
            else
            {
                monFlux<<std::endl;
                test=1;

            }


        }
        if(test==1)
        {
                std::cout<<std::endl;
                std::cout<<"La ponderation n'est pas charg\202e ! Vous ne pouvez pas sauvegarder Cp et Ci"<<std::endl;
                std::cout<<std::endl;
        }

        std::cout<<std::endl;
        std::cout<<"Vous avez sauvegard\202 vos indices avec succes"<<std::endl;
        std::cout<<std::endl;
    }
    else
    {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
    }
}

void Graphe::comparaison()
{
    std::cout<<" Comparaison des indices de centralite avant et apres la suppression d'aretes :"<<std::endl;
    for(int i=0;i<getOrdre();++i)
    {
        std::cout<<"Sommet N"<<i<<std::endl;
        double Cd3=m_sommets[i]->getCd()-m_sommets[i]->getCd2();
        double Cvp3=m_sommets[i]->getCvp()-m_sommets[i]->getCvp2();
        double Ci3=m_sommets[i]->getCi()-m_sommets[i]->getCi2();
        double Cp3=m_sommets[i]->getCp()-m_sommets[i]->getCp2();
        std::cout<<"Cd Avant: "<<m_sommets[i]->getCd()<<" Cd Apres: "<<m_sommets[i]->getCd2()<<" Difference :"<<Cd3<< std::endl;
        std::cout<<"Cvp Avant: "<<m_sommets[i]->getCvp()<<"Cvp Apres: "<<m_sommets[i]->getCvp2()<<" Difference :"<<Cvp3<< std::endl;
        std::cout<<"Ci Avant: "<<m_sommets[i]->getCi()<<" Ci Apres: "<<m_sommets[i]->getCi2()<<" Difference :"<<Ci3<< std::endl;
        std::cout<<"Cp Avant: "<<m_sommets[i]->getCp()<<" Cp Apres: "<<m_sommets[i]->getCp2()<<" Difference :"<<Cp3<< std::endl<<std::endl;

    }
}

int Graphe::AreteID(int i,std::vector<std::vector<int>> PCC)
{
 int compteur=0;
    for(size_t x=0;x<PCC.size();x++)
            {
                for(size_t y=2;y<PCC[x].size()-1;y++)
                {
                    if(m_arretes[i]->getID1()==PCC[x][y]&&m_arretes[i]->getID2()==PCC[x][y+1])///Check La présence de l'arrete sur le chemin
                    {
                        compteur++;
                    }
                    else if(m_arretes[i]->getID2()==PCC[x][y]&&m_arretes[i]->getID1()==PCC[x][y+1])
                        {
                            compteur++;
                        }
                }
            }
            return compteur;

}
void Graphe::AreteCi()
{

    double n_pccI=0;
    double n_pccJK=0;
    double Somme=0;
    double C=0;
    std::vector<std::vector<int>> PCChemins;
    for(int i=0;i<getTaille();i++)
    {
        std::cout<<"Arete etudiee :"<<m_arretes[i]->getID1()<<" "<<m_arretes[i]->getID2()<<std::endl;
    for (int j=0;j<=(getOrdre()-2);++j)///Fonctionne uniquement si l'ID des sommets commence par 0
    {

        for (int k=1+j;k<=getOrdre()-1;++k)
        {
            std::cout<<"Sommets : "<<j<<" " <<k<<std::endl;
            PCChemins=DijkstraModif(j,k);
            n_pccI= AreteID(i,PCChemins);
            std::cout<<"pccI: "<<n_pccI;
            n_pccJK=PCChemins.size();
            std::cout<<" pccJK :"<<n_pccJK<<std::endl<<std::endl;
            Somme=Somme+(n_pccI/n_pccJK);
            n_pccJK=0;
            n_pccI=0;
            PCChemins.clear();
        }
    }
    C=(2*Somme)/(pow((double)getOrdre(),2.0)-(3*(double)getOrdre())+2);
    std::cout << " C :"<<C<<std::endl;
    m_arretes[i]->setCiar(C);
    Somme=0;
}
}
