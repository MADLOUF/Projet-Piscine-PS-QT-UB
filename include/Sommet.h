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
        double m_Cd=0;
        double m_C=0;
        double m_Cvp=1;
        double m_Ci=0;
        double m_Cp=0;
    public:
        Sommet(std::istream& is);
        int getDegre() const;
        int getID() const;
        int getX() const;
        int getY() const;
        int getAdj(int i) const;
         std::vector<int> getAdjListe() const;
        int getMarquage() const;
        double getC()const;
        double getCvp()const;
        double getCd()const;
        double getCi()const;
        double getCp()const;
        std::string getNom () const;
        void Adjacent(int ID);
        void Erase_Adjacent();
        void setMarquage(int coul);
        void setCd(double C);
        void setCvp(double C);
        void setC(double C);
        void setCi(double C);
        void setCp(double C);
        void Adjtrie();
        void afficherAdj();

};

#endif // SOMMET_H
