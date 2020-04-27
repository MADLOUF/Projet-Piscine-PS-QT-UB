#include "Sommet.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <cmath>

Sommet::Sommet(std::istream& is)
{
    is >> m_id ;
    std::cout<<"  ID :"<<m_id;
    is >> m_nom;
    std::cout<<"  Nom :"<<m_nom;
    is >> m_x;
    std::cout<<"  X :"<<m_x;
    is >> m_y;
    std::cout<<"  Y :"<<m_y<<std::endl;

    if ( is.fail() )
    throw std::runtime_error("Probleme lecture id,x,y d'une Sommet");
}
int Sommet::getDegre() const
{
    return (int)m_adjacents.size();
}
int Sommet::getID() const
{
    return (int) m_id;
}
int Sommet::getAdj( int i) const
{
    return m_adjacents[i];
}
std::vector<int> Sommet::getAdjListe() const
{
    return m_adjacents;
}
int Sommet::getX ()const
{
    return m_x;
}
int Sommet::getY ()const
{
    return m_y;
}
char Sommet::getNom ()const
{
    return m_nom;
}
int Sommet::getMarquage ()const
{
    return m_marquage;
}
int Sommet::getC() const
{
    return m_C;
}
int Sommet::getCvp() const
{
    return m_Cvp;
}
int Sommet::getCd() const
{
    return m_Cd;
}
void Sommet::Adjacent(int ID)
{
     m_adjacents.push_back(ID);
}
void Sommet::setMarquage(int coul)
{
    m_marquage=coul;
}
void Sommet::setCd(int C)
{
    m_Cd=C;
}
void Sommet::setCvp(int C)
{
    m_Cvp=C;
}
void Sommet::setC(int C)
{
    m_C=C;
}
void Sommet::Adjtrie()
{
            struct myclass
            {
           bool operator() (int i,int j) { return (i<j);}
            }myobject;
            std::sort (m_adjacents.begin(), m_adjacents.end(), myobject);
}
void Sommet::afficherAdj()
{
        for ( int y =0 ; y<getDegre();++y)
        {
          std::cout <<m_adjacents[y]<<" ";
        }
}

