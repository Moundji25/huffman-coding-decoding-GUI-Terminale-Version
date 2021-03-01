#ifndef HUFFMAN_HH
#define HUFFMAN_HH

#include "ArbreB.hh"
#include <iostream>
#include <vector>

struct elem2
{
    std::vector<int> le_code;
    char le_car;
};
    

class huffman
{    
private:
    int etat; // indique si un cryptage à était deja fait ou pas
    std::vector<elem2>dico;

    std::string texte;  // le texte entrer en entrée standard (texte à crypter/ code à décrypter)

    double alphabet[94]; // tableau représentant le nbre d'occurence des caractéres/pourcentage d'occurence des caractéres qui varient entre code ascii (32 'espace'  ... 126 '~') 
    std::vector<ArbreB *> arbres; // vecteur necessiare à la fusion car il contenir les arbres à fusionner  
    std::vector<ArbreB *> dechets;  // vecteur necessaire à la fusion car il va contenir les arbres à supprimer 
    int nbreCar; // entier necessaire à la fusion

    
public:

    huffman(); // constructeur de la classe 

    void start(); // demande à l'utilisateur de faire un cryptage/decryptage est appelle les fonctions nécessaire à cela puis demande à l'utilisateur si il voudrait continuer à utiliser le programme  

    std::vector<ArbreB *> getArbres(); // retourne le vecteur arbres 
    std::vector<elem2> getDico(); // retourne le vecteur dico

    void lecture_traitements_C(); // recupere le texte à traiter, initialise le vecteur arbres en stockant le code ascii de chaque caractére du texte
                                // convertir le nombre d'ocurrence de chaque caractére en un pourcentage d'occurence par rapport à la taille du texte
    void lecture_traitements_DE(); // fonction qui recupere le code à decrypter vérifie sa validité puis essaie de le décrypter et retourne le résultat dans le cas favorable sinon une erreur 

    void initialiser_vecteurs_arbres(); // initialiser le vecteur arbres, assigner à chaque arbre un caractére et son pourcentage d'occurence et afficher l'alphabet 
    void fusionner_arbres(); // Fusionner les arbres du vecteur arbres jusqu'a avoir un seul arbre dans le vecteur qui sera le résultat de la fusion de tout les arbres et aura
                            // un pourcentage = 100 
    bool code_lettre( char car, Sommet* s , std::vector <int> * ); // fonction récursive qui parcoure l'arbre en profondeur jusqu'à trouver le caractére spécifié comme premier
                                                                   // parametre puis retourne le code de ce dernier dans le troisiéme paramétre, dans le cas où la fonction trouve
                                                                   // le valeur de retour est true sinon c'est false                                            
    void vider(); // fonction qui sert à libérer des zones mémoires nécessaire à la fonction fusionner_arbres()

    void genere_code(); // génere le code correspondant au texte à partir de l'arbre trouvé dans la fonction fusionner_arbres 

    void affiche_dico(); // affiche la correspondance entre un caractére est un code binaire
};

#endif