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
std::string Sommet::getNom ()const
{
    return m_nom;
}
int Sommet::getMarquage ()const
{
    return m_marquage;
}
double Sommet::getC() const
{
    return m_C;
}
double Sommet::getCvp() const
{
    return m_Cvp;
}
double Sommet::getCvp2() const
{
    return m_Cvp2;
}
double Sommet::getCd() const
{
    return m_Cd;
}
double Sommet::getCd2() const
{
    return m_Cd2;
}
void Sommet::Adjacent(int ID)
{
     m_adjacents.push_back(ID);
}
void Sommet::Erase_Adjacent()
{
     m_adjacents.clear();
}
void Sommet::setMarquage(int coul)
{
    m_marquage=coul;
}
void Sommet::setCd(double C)
{
    m_Cd=C;
}
void Sommet::setCd2(double C)
{
    m_Cd2=C;
}
void Sommet::setCdnn(double C)
{
    m_Cdnn=C;
}
void Sommet::setCvp(double C)
{
    m_Cvp=C;
}
void Sommet::setCvp2(double C)
{
    m_Cvp2=C;
}
void Sommet::setC(double C)
{
    m_C=C;
}
double Sommet::getCp() const
{
    return m_Cp;
}
double Sommet::getCp2() const
{
    return m_Cp2;
}
double Sommet::getCpnn() const
{
    return m_Cpnn;
}
void Sommet::setCp(double C)
{
    m_Cp=C;
}
void Sommet::setCp2(double C)
{
    m_Cp2=C;
}
void Sommet::setCpnn(double C)
{
    m_Cpnn=C;
}
double Sommet::getCi() const
{
    return m_Ci;
}
double Sommet::getCi2() const
{
    return m_Ci2;
}
double Sommet::getCinn() const
{
    return m_Cinn;
}
void Sommet::setCi(double C)
{
    m_Ci=C;
}
void Sommet::setCi2(double C)
{
    m_Ci2=C;
}
void Sommet::setCinn(double C)
{
    m_Cinn=C;
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

