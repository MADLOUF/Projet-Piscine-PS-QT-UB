#include "Arrete.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <cmath>
Arrete::Arrete (std::istream& is)///Lecture du fichier
        {

            is >> m_NumArrete;
            std::cout <<"  ID :"<< m_NumArrete<<" ";
            is >> m_ID1;
            std::cout << "Extremites : "<<m_ID1<<" ";
            is >>m_ID2;
            std::cout << m_ID2<<" ";
            /*is >> m_poids;
            std::cout << m_poids;*/
            std::cout<<std::endl;
            if ( is.fail() )
                throw std::runtime_error("Probleme lecture id,x,y d'une Sommet");
        }
int Arrete::getID1() const
{
    return m_ID1;
}

int Arrete::getID2() const
{
    return m_ID2;
}

int Arrete::getPoids() const
{
    return m_poids;
}

int Arrete::getNumArrete() const
{
    return m_NumArrete;
}

void Arrete::setPoids(int poids)
{
    m_poids=poids;
}
void Graphe::setCiar(double C)
{
        m_Ciar=C;
}
double Graphe::getCiar()
{
        return m_Ciar;
}
