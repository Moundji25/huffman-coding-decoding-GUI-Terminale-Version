#ifndef ARBREB_HH
#define ARBREB_HH
#include "Sommet.hh"
#include <vector>

class ArbreB : public Sommet
{
	private:
		Sommet *racine; //Attribut racine de type pointeur vers un Sommet

		struct elem // structure necessaire à la fusion
		{
			double etiq; // pourcentage 
			char etiq2;  // caractere 
		};		
	
	public:
		ArbreB(); //Constructeur arbre vide
		
		ArbreB(ArbreB &ACopier); //Constructeur par recopie
		
		~ArbreB(); //destructeur 
		
		int taille(); // renvoie la taille d'un arbre (nbre de sommets)

		Sommet *getRacine(); //retourne un pointeur vers la racine
		
		void setRacine(Sommet *r); //placer une nouvelle racine
		
		void inserer(Sommet *s); //insere dans l'arbre le sommet s en cherchant la premiere place libre (du niveau le plus petit et la priorité de la gauche )
		
		Sommet *rechercher(double etiq); // retourne un pointeur vers le sommet dont on a indiquer l'etiquette en parametre  (si deux sommet ont la meme etiquette il retourne le plus profond
																														//et si ils ont le meme niveau elle retourne celui qui se trouve a droite 
		void supprimerProfondDroit(Sommet *profondD); //supprime le sommet le plus profond a droite ( utile dans la méthode supprimer en dessous)
		
		void supprimer(double etiq); //supprime le sommet le plus profond , la priorité a la droite 
		
		void fusion(ArbreB *b,ArbreB* c); // fusionne le sommet appellant et celui passé en paramétre et stocke le résultat dans le deuxième paramétre 
							
		void decomposition(ArbreB *ArbreUn,ArbreB *ArbreDeux); //décompose l'arbre en deux sous arbres et remplie les deux arbres passés en paramétre 
																	// le sous arbre gauche est retourner avec le premier parametre 'ArbreUn' 
																	//	le sous arbre gauche est retourner avec le premier parametre 'ArbreDeux'	
		void affiche(); //affiche un arbre en appelant la fonction affiche_sommet 

		void affiche_sommet(Sommet *s, int current_level); //fonction récursive qui permet l'affichage d'un arbre		
};																					



#endif