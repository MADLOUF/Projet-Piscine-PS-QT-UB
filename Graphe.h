#ifndef GRAPHE_H
#define GRAPHE_H
#include <Sommet.h>
#include <Arrete.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <cmath>


class Graphe
{
    private:

        int m_oriente;
        std::vector<Sommet*> m_sommets;
        std::vector<Arrete*> m_arretes;
        std::vector<std::vector<int>> m_parcours;
        std::vector<int> m_longueur;

    public:

        Graphe(std::string nomFichier);
        ~Graphe();
        int getOrdre() const;
        int getTaille() const;
        void DeterminerAdjacance();
        int rechercheID(int ID);///Inutile ??? Car les ID représente la position du sommet dans le vecteur.
        int PoidsArrete(int ID1,int ID2);
        int TotalCouleur();
        void afficherAdjacance();
        int PlusPetiteLongueur(std::vector<std::vector<int>> parcours);
        int IDParcours(int somFinal);
        int NmbrAdjNonmarque(int ID);
        void AlgoDijkstra(int SomInit,int Somfinal);
        void test();
        void Cd();
        void Cvp();

};

#endif // GRAPHE_H
