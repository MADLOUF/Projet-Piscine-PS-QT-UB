#ifndef ARRETE_H
#define ARRETE_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <cmath>

class Arrete
{
private :
    int m_NumArrete;
    int m_ID1;
    int m_ID2;
    int m_poids;
    double m_Ciar=0;
public :
        Arrete(std::istream& is);
        int getID1() const;
        int getID2() const;
        int getPoids() const;
        void setPoids(int poids);
        int getNumArrete() const;
        void setCiar(double C);
        double getCiar();


};

#endif // ARRETE_H
