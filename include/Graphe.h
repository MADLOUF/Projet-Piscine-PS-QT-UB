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
        int m_PPLongueur=99999;

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
        void afficherGraphe();
        int PlusPetiteLongueur(std::vector<std::vector<int>> parcours);
        int IDParcours(int somFinal);
        int NmbrAdjNonmarque(int ID);
        void setPPL(int PPL);
        int getPPL();
        void MemeLong(int Somfinal);
        void AlgoDijkstra(int SomInit,int Somfinal);
        std::vector<std::vector<int>> DijkstraModif(int SomInit,int Somfinal);
        void Cd();
        void Cvp();
        void Cp();
        void Ci();
        void vulnerabilite();
        void afficher_Cd();
        void rechercher_afficher_CC();
        std::vector<int> BFS(int num_s0)const;

};

#endif // GRAPHE_H
