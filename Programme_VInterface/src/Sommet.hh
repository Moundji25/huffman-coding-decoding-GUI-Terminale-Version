#ifndef SOMMET_HH
#define SOMMET_HH


class Sommet
{
	private:
		double etiquette; // etiquette d'un sommet 
		char etiquette2; // deuxieme etiquette d'un sommet  
		Sommet *Gauche; // pointeur vers un un Sommet (fils gauche)
		Sommet *Droit; // pointeur vers un un Sommet (fils droit) 
	public:
		Sommet(); //Constructeur construit un sommet avec une etiquette = 0
		Sommet(double etiq,char etiq2); //Constructeur construit un sommet avec une etiquette = etiq;
		~Sommet(); //destructeur d'un sommet
		char getEtiquette2(); // retourne l'etiquette2
		double getEtiquette(); //retourne l'etiquette d'un sommet
		void setEtiquette(double eti); //change l'etiquette d'un sommet avec etiq
		void setEtiquette2(char eti2); // change l'etiquette d'un sommet avec etiq2
		Sommet *getGauche(); // retourne un pointeur vers le fils gauche du sommet
		void setGauche(Sommet *g); // insere un sommet fils gauche passé en parm
		Sommet *getDroit(); // retourne un pointeur vers le fils droit du sommet
		void setDroit(Sommet *d); // insere un sommet fils droit passé en param
};


#endif