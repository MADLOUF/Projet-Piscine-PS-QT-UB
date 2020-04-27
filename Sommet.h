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
        char m_nom;
        int m_x;
        int m_y;
        int m_marquage=0;
        int m_centraDegree=0;
    public:
        Sommet(std::istream& is);
        int getDegre() const;
        int getID() const;
        int getX() const;
        int getY() const;
        int getAdj(int i) const;/// ????
        int getMarquage() const;
        char getNom () const;
        void Adjacent(int ID);
        void setMarquage(int coul);
        void setCd(int Deg);
        void Adjtrie();
        void afficherAdj();

};

#endif // SOMMET_H
