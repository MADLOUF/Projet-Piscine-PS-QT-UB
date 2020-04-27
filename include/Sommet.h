#ifndef SOMMET_H
#define SOMMET_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <cmath>

class Sommet
{

 private:
        std::vector<int> m_adjacents;
        int m_id;
        std::string m_nom;
        int m_x;
        int m_y;
        int m_marquage=0;
        int m_Cd=0;
        int m_C=0;
        int m_Cvp=1;
    public:
        Sommet(std::istream& is);
        int getDegre() const;
        int getID() const;
        int getX() const;
        int getY() const;
        int getAdj(int i) const;
         std::vector<int> getAdjListe() const;
        int getMarquage() const;
        int getC()const;
        int getCvp()const;
        int getCd()const;
        std::string getNom () const;
        void Adjacent(int ID);
        void setMarquage(int coul);
        void setCd(int C);
        void setCvp(int C);
        void setC(int C);
        void Adjtrie();
        void afficherAdj();

};

#endif // SOMMET_H
