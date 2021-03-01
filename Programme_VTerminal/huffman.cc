#include "huffman.hh"
#include <sstream>
#include <string>
using namespace std;


huffman::huffman()
{
    for (size_t i = 0; i < 94; i++) // INTIALISER LE TABLEAU ALPHABET 
    {
        this->alphabet[i] = 0;
    }
    this->nbreCar = 0;
    this->etat = -1;
}

bool huffman::code_lettre( char car, Sommet* s , std::vector <int> * V )
{    
    if ( (s-> getGauche() == NULL && s->getDroit() == NULL ) || (s->getGauche()->getEtiquette() == -1 && s->getDroit()->getEtiquette() == -1 ) )
        return (s->getEtiquette2() == car) ;
    
    if (s->getGauche()!= NULL && code_lettre( car , s->getGauche() , V))
    {
        V->push_back(1);
        return true;
    }
  
    if(s->getDroit()!= NULL && code_lettre( car , s->getDroit() , V))
    {
        V->push_back(0);
        return true;
    }
    
    return false;          
}

void huffman::lecture_traitements_C()
{
    texte.clear();
    bool B;
     do // LECTURE DU TEXTE                          
    {
        B= true;
       cout<<"Veuillez entrez le texte SVP \n";
       getline(cin,this->texte);   

        for (int i = 0; i < texte.size() ; i++) // vérification de la validité du texte
        {
            if ( 126 < (int)texte.at(i) || (int)texte.at(i) < 32 )
            {
                cerr<<"ERREUR : caractere non valide \n\n";
                B =false;
                break;
            }
        }

    } while (this->texte.size() <= 0 || B == false);

    for (size_t i = 0; i < this->texte.size(); i++) // stocker le code ascii de chaque caractére du texte et incrémenter la case correspondante au caractére de 1
    {
        this->alphabet[this->texte.at(i) - 32]++;
    }
    
    this->nbreCar = 0;

    
    for (size_t i = 0; i < 94; i++) // convertir le nombre d'ocurrence de chaque caractére en un pourcentage d'occurence par rapport au nombre de caractéres dans le texte 
    {
        if (alphabet[i] != 0)
        {
            this->alphabet[i] = (this->alphabet[i] * 100) / this->texte.size();
            //cout<<"   "<<(char)i+32<<" : "<<this->alphabet[i]<<"   ";
            this->nbreCar++;
        }
    }
    //cout<<endl;
}

void huffman::lecture_traitements_DE()
{
    this->affiche_dico();
    bool B;
    texte.clear();
     do // LECTURE DU TEXTE                          
    {
        B = true;
       cout<<"Veuillez entrez un code valide SVP \n\n";
       getline(cin,this->texte);   

        for (size_t i = 0; i < texte.size(); i++)
        {
            if ((int)texte.at(i) != 48 && (int)texte.at(i) != 49)
            {
                cout<<"ERREUR : code invalide \n\n";
                B = false; 
                break;
            }
        }
        
    } while (this->texte.size() <= 0 || B == false);

    std::vector<int> tmp;
    string texte_res;
    B = false;

    cout<<"\nles caractéres identifier :  ";
    for (size_t i = 0; i < texte.size(); i++)
    {   
        if(((int)texte.at(i) == 48))
            tmp.push_back(0);
        else
            tmp.push_back(1);
        
        B = false;

        for (size_t j = 0; j < dico.size(); j++)
        {
            if (dico.at(j).le_code == tmp)
            {
               cout<<" '"<<dico.at(j).le_car<<"'  ";
               texte_res.push_back(dico.at(j).le_car);
               B = true;
               tmp.clear();
               break;
            }
            
        }
    }

    if (B == false)
    {
        cout<<"ERREUR : le code fournie n'est pas reconnue par l'arbre \n";
    }
    else
    {
        cout<<"le texte résultat :  "<<texte_res<<endl<<endl;   
    }
    
    

}

void huffman::initialiser_vecteurs_arbres()
{
    for (size_t i = 0; i < this->nbreCar; i++) // initialiser le vecteur arbres  
    {
        this->arbres.push_back(new ArbreB);
    }
    int i=0,j=0;

    while (j < 94 && i < this->arbres.size()) // assigner à chaque arbre un caractére
    {     
        if (this->alphabet[j] != 0)
        {
            this->arbres.at(i)->inserer(new Sommet(this->alphabet[j],j+32));
            i++;
        }
        j++;

    }

     
    cout<<"\n                        >>ALPHABET<<                        \n";

    for ( ArbreB * elem : this->arbres) // afficher l'alphabet 
    {
        cout<<" "<<elem->getRacine()->getEtiquette2()<<" ";
    }
    cout<<endl<<endl;

}

void huffman::fusionner_arbres()
{
    int co1,co2;
    double min1,min2;
    char tmp1;

    ArbreB * tmpArbre;
    while (arbres.size()>1)  // Fusionner les arbres du vecteur arbres jusqu'a avoir un seul arbre dans le vecteur qui auront un pourcentage = 100 
    {
       
        if (arbres.at(1)->getRacine()->getEtiquette() < arbres.at(0)->getRacine()->getEtiquette()) // // determiner le minimum en terme de pourcentage d'occurence 
        {
            min1 = arbres.at(1)->getRacine()->getEtiquette(); co1 = 1;
            min2 = arbres.at(0)->getRacine()->getEtiquette(); co2 = 0;
        }
        else
        {
            min1 = arbres.at(0)->getRacine()->getEtiquette(); co1 = 0;
            min2 = arbres.at(1)->getRacine()->getEtiquette(); co2 = 1;
        }


        for (size_t i = 0; i < arbres.size(); i++) // trouver les deux min et sauvgarder leurs positions 
        {
            if (arbres.at(i)->getRacine()->getEtiquette() < min1)
            {
                co1 = i;
                min1 = arbres.at(i)->getRacine()->getEtiquette();
            }
            if (arbres.at(i)->getRacine()->getEtiquette() < min2 && i != co1)
            {
                min2 = arbres.at(i)->getRacine()->getEtiquette();
                co2 = i;
            }
            
            
        }

        this->dechets.push_back(arbres.at(co1)); // stocker arbre qui a était fusionner dans dechets pour etre supprimer
        this->dechets.push_back(arbres.at(co2)); // stocker arbre qui a était fusionner dans dechets pour etre supprimer

        tmpArbre = new ArbreB;
        arbres.at(co1)->fusion(arbres.at(co2),tmpArbre); // faire la fusion de deux arbres et récupérer le résultat dans tmpArbre

        tmp1 = arbres.at(co2)->getRacine()->getEtiquette2(); 
   
        arbres.erase(arbres.begin() + co1); // supprimer le premier arbre fusionné du vecteur arbres


        for (size_t i = 0; i < arbres.size(); i++)  // supprimer le deuxième arbre fusionné du vecteur arbres
        {
            if(tmp1 == arbres.at(i)->getRacine()->getEtiquette2())
            {
                arbres.erase(arbres.begin() + i); 
                break;
            }
        }
        arbres.push_back(tmpArbre); // inserer l'arbre résultat de la fusion

    }
    
}

void huffman::vider()
{
      for (size_t i = 0; i < dechets.size(); i++)
    {
        delete dechets.at(i);
    }
    dechets.clear();
}

std::vector<ArbreB *> huffman::getArbres() // retourne le vecteur arbres
{
    return this->arbres;
}

std::vector<elem2> huffman::getDico ()
{
    return this->dico;
}

void huffman::genere_code()
{
    std::vector<int> tmp_code;
    char tmp1;
    elem2 tmp2;
    
    cout<<"                        >>CODE DES CARACTÉRES DU TEXTE<<                        \n";
    cout<<"( Gauche = 0 et Droite = 1, sens de lecture \nde bas vers le haut <--\nde haut vers le bas --> ) \n";
    for (size_t i = 0; i < 94 ; i++)
    {
        if (this->alphabet[i] != 0)
        {   
            tmp1 = i+32 ;

            code_lettre(i+32,this->arbres.at(0)->getRacine(),&tmp_code);

            cout<<tmp1<<"  =  ";

            tmp2.le_car = tmp1;
            
            for (int i = (int)tmp_code.size()-1; i >= 0; i--)
            {
                cout<<tmp_code.at(i);
                tmp2.le_code.push_back(tmp_code.at(i));
            }
            
            cout<<endl;
            tmp_code.clear();

            dico.push_back(tmp2);
            tmp2.le_code.clear();
        }
    }
    cout<<endl;


    cout<<"\n                        >>CODE TEXTE ( SENS DE LECTURE ----> )<<                        \n";
    for (size_t i = 0; i < texte.size(); i++)
    {
        code_lettre(texte.at(i),arbres.at(0)->getRacine(),&tmp_code);

        for (int i = (int)tmp_code.size()-1; i >= 0; i--)
        {
            cout<<tmp_code.at(i);
        }
        tmp_code.clear();
        
    }
    cout<<endl<<endl;
}

void huffman::affiche_dico()
{
    for ( elem2 element : this->dico)
    {
        cout<<"     - "<<element.le_car<<"   code binaire  :  ";

        for (int element2 : element.le_code)
        {
            cout<<element2;
        }
        cout<<endl<<endl;
    }   

    
}

void huffman::start ()
{
    cout<<"                        >>PROGRAMME DE CRYPTAGE/DECRYPTAGE DE TEXTE/CODE GRAÇE A L'ALGORITHME DE HUFFMAN<<\n\nLes options : \n\n      -Pour crypter un texte en anglais en code huffman tapez 0\n      -Pour decrypter un code a partir d'un arbre tapez 1\n\n";

    string tmp,tmp2;
    do
    {
    
        do // LECTURE DU TEXTE                          
        {
            cout<<"veuillez entrez votre choix \n";
            getline(cin,tmp);



        if ( (int)tmp.at(0) == 48 )
        {
            for (size_t i = 0; i < 94; i++) 
            {
                this->alphabet[i] = 0;
            }
            if (arbres.size() != 0)
                delete this->arbres.at(0);

            this->arbres.clear();
            this->dechets.clear();
            this->dico.clear();
            this->nbreCar = 0;
            this->etat = 0;
            this->lecture_traitements_C();
            this->initialiser_vecteurs_arbres();
            this->fusionner_arbres();
            this->vider();
            cout<<"                        >>ARBRE DU CODE<<                        \n\n";
            this->getArbres().at(0)->affiche();
            this->genere_code();
        }
        else
        {
            if ( (int)tmp.at(0) == 49 )
            {
                if (this->etat == -1)
                    cout<<"ERREUR : il n'existe aucun arbre permettant de décrypter un code huffman\n";
                else
                {
                    this->etat = 1;
                    this->lecture_traitements_DE();
                }

            } 
        }

        } while ( (tmp.size()==0 || tmp.size()>1 ) || tmp.at(0) != '1' && tmp.at(0) != '0' );

        cout<<"\n\nvoulez vous continuer à utiliser le programme O/N ? \n\n";
        getline(cin,tmp2);

    } while ( tmp.size()==0 || tmp2.compare("Non") != 0 && tmp2.compare("N") != 0 && tmp2.compare("non") != 0 && tmp2.compare("n") != 0);
    
    if (arbres.size() != 0)
        delete this->arbres.at(0);    

}