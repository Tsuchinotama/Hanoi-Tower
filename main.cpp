#include <iostream>
#include <vector>
#include <array>

using namespace std;

typedef size_t Disques;

constexpr Disques PAS_DE_DISQUES=0;

typedef vector<Disques> Pilier;

typedef array<Pilier, 3> Jeu;

void init(Jeu& jeu, size_t hauteur);

void affiche(Jeu jeu);

void affiche(Disques d);

void affiche(char c, unsigned int n);

void hanoi(size_t n, size_t origine, size_t destination, Jeu& jeu);

void deplace(Pilier& origine, Pilier& destination);

size_t sommet(Pilier p);

int main()
{
    Jeu monjeu;
    size_t n(4);

    init(monjeu, n);
    affiche(monjeu);
    hanoi(n, 0, 2, monjeu);

    return 0;
}

void init(Jeu& jeu, size_t hauteur)
{
    for (auto& pilier : jeu)
    {
        pilier=Pilier(hauteur, PAS_DE_DISQUES);
    }
    for (size_t i=1; i<=hauteur; i++)
    {
        jeu[0][i-1]=Disques(i);
    }
}

void affiche(Jeu jeu)
{
    int hauteur;
    hauteur=jeu[0].size();
    for (int i=0; i<hauteur; i++)
    {
        if (jeu[0][i]==PAS_DE_DISQUES)
        {
            affiche(' ', hauteur-1);
            cout << '|';
            affiche(' ', hauteur-1);
        }
        else
        {
            affiche(' ', hauteur-jeu[0][i]);
            affiche('-', 2*jeu[0][i]-1);
            affiche(' ', hauteur-jeu[0][i]);
        }
        cout << " ";
        if (jeu[1][i]==PAS_DE_DISQUES)
        {
            affiche(' ', hauteur-1);
            cout << '|';
            affiche(' ', hauteur-1);
        }
        else
        {
            affiche(' ', hauteur-jeu[1][i]);
            affiche('-', 2*jeu[1][i]-1);
            affiche(' ', hauteur-jeu[1][i]);
        }
        cout << " ";
        if (jeu[2][i]==PAS_DE_DISQUES)
        {
            affiche(' ', hauteur-1);
            cout << '|';
            affiche(' ', hauteur-1);
        }
        else
        {
            affiche(' ', hauteur-jeu[2][i]);
            affiche('-', 2*jeu[2][i]-1);
            affiche(' ', hauteur-jeu[2][i]);
        }
        cout << endl;
    }
    affiche('#', 6*hauteur-1);
    cout << endl << endl;;
}

void affiche(Disques d)
{
    if (d==PAS_DE_DISQUES)
    {
        cout << "|";
    }
    else
    {
        for (int i=1; i<=d; i++)
        {
            cout << "-";
        }
    }
}

void affiche(char c, unsigned int n)
{
    for (int i=1; i<=n; i++)
        cout << c;
}



void hanoi(size_t n, size_t origine, size_t destination, Jeu& jeu)
{
    if (n==1)
    {
        deplace(jeu[origine], jeu[destination]);
        affiche(jeu);

    }
    else
    {
        hanoi(n-1, origine, 3-destination-origine, jeu);
        deplace(jeu[origine], jeu[destination]);
        affiche(jeu);
        hanoi(n-1, 3-destination-origine, destination, jeu);
    }
}

void deplace(Pilier& origine, Pilier& destination)
{
    size_t top1(sommet(origine));
    size_t top2(sommet(destination));
    if (top1<origine.size())
    {
        if ((top2<destination.size()) && (destination[top2]<origine[top1]))
        {
            cerr << "Erreur : on ne peut pas déplacer un disque de taille " << origine[top1] << " sur un disque de taille " << destination[top2] << endl;
        }
        destination[top2-1]=origine[top1];
        origine[top1]=PAS_DE_DISQUES;

    }
}

size_t sommet(Pilier p)
{
    size_t top;
    for (top=0; (top<p.size() && (p[top]==PAS_DE_DISQUES)); top++);
    return top;
}
