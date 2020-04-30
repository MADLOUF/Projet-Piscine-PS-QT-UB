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
        std::string m_couleur;
        int m_x;
        int m_y;
        int m_marquage=0;
        double m_Cd=0;
        double m_Cd2=0;
        double m_Cdnn=0;
        double m_C=0;
        double m_Cvp=1;
        double m_Cvp2=1;
        double m_Ci=0;
        double m_Ci2=0;
        double m_Cinn=0;
        double m_Cp=0;
        double m_Cp2=0;
        double m_Cpnn=0;
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
        double getCvp2()const;
        double getCd()const;
        double getCd2()const;
        double getCdnn()const;
        double getCi()const;
        double getCi2()const;
        double getCinn()const;
        double getCp()const;
        double getCp2()const;
        double getCpnn()const;
        std::string getNom() const;
        std::string getCouleur() const;
        void setCouleur(std::string C);
        void Adjacent(int ID);
        void Erase_Adjacent();
        void setMarquage(int coul);
        void setCd(double C);
        void setCd2(double C);
        void setCdnn(double C);
        void setCvp(double C);
        void setCvp2(double C);
        void setC(double C);
        void setCi(double C);
        void setCi2(double C);
        void setCinn(double C);
        void setCp(double C);
        void setCp2(double C);
        void setCpnn(double C);
        void Adjtrie();
        void afficherAdj();

};

#endif // SOMMET_H
