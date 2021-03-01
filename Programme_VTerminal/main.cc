#include "ArbreB.hh"
#include "huffman.hh"
#include <string.h>
#include <iostream>

using namespace std;

int main()
{
   
    huffman H;

    H.start();


   /* 
   // TESTES DES FONCTIONS DE LA CLASSE ArbreB (PARTIE 1 DU PROJET)



   cout << "           arbre a :" << endl << endl; 
    */
    /*

          11
         / \
        1   2  
       /
      5
    */

    /*ArbreB *a = new ArbreB();
    
    Sommet *s = new Sommet(11,(char) 0);
    Sommet *s1 = new Sommet(1,(char) 0);
    Sommet *s2 = new Sommet(2,(char) 0);
    Sommet *s3 = new Sommet(5,(char) 0);
    Sommet *s4 = new Sommet(6,(char) 0);

    a->inserer(s);
    a->inserer(s1);
    a->inserer(s2);
    
    a->affiche();

    cout << "           insrer deux sommet dans a :"  << endl << endl;
    a->inserer(s3);
    a->inserer(s4);
    a->affiche();

    cout << "           supprimer le sommet dont l'etiqutte = 1 dans l'arbre a:" << endl << endl;
    a->supprimer(1);
    a->affiche();



    cout << "           arbre b :" << endl << endl;*/
    /*

           7
         /  \
        3    4

    */

    /*ArbreB *b = new ArbreB();

    Sommet *su = new Sommet(7,(char) 0);   
    Sommet *su1 = new Sommet(3,(char) 0);
    Sommet *su2 = new Sommet(4,(char) 0);

    b->inserer(su);
    b->inserer(su1);
    b->inserer(su2);
    
    b->affiche();
    
    
    // FUSION DE a ET b
    cout << "           arbre c fusion de l'arbre a et l'arbre b :" << endl << endl;

    ArbreB *c = new ArbreB();
    a->fusion(b,c);

    c->affiche();


    // DECOMPOSITION DE c
    cout << "            decomposition de l'arbre c à partir de la racine (la racine est supprimé) --> ( arbre d sous graphe Gauche ) , ( arbre e sous graphe Droit )" << endl << endl;

    ArbreB *d = new ArbreB();
    ArbreB *e = new ArbreB();
    
    c->decomposition(d,e);

    cout << "            arbre d :" << endl << endl;
    d->affiche();
    
    cout << "            arbre e :" << endl << endl;
    e->affiche();

    cout << "            rechercher dans l'arbre c le sommet dont l'etiquette = 3" << endl;
    

    if (c->rechercher(3) != NULL)
    {
        cout << "             -------> votre arbre contient l'element "<< endl  ;
    }
    else
    {
        cout << "             -------> votre arbre ne contient pas l'element 3" << endl;
    }
    */
}



