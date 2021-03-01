#include "ArbreB.hh"
#include <iostream>
#include <queue>
#include <cmath>
//#include <sstream>

using namespace std;

ArbreB::ArbreB()
{
    this->racine=NULL;
}

ArbreB::ArbreB(ArbreB &ACopier)
{ 
    if(ACopier.getRacine()==NULL)
    {
        this->racine=NULL;
    }
    else
    {
        Sommet * temp = NULL;

        queue<Sommet *> q; 
        q.push(ACopier.getRacine());

        Sommet *r = new Sommet(ACopier.getRacine()->getEtiquette(),ACopier.getRacine()->getEtiquette2());
        this->setRacine(r);

        queue<Sommet *> q1; 
        q1.push(this->getRacine());

        temp = NULL;
        Sommet *temp1;
        Sommet *s1;
        Sommet *s2;

        while (!q.empty())
        {
            temp = q.front();
            temp1 = q1.front();

            q.pop();
            q1.pop();

            if(temp->getGauche() != NULL)
            {
                s1 = new Sommet();
                s1->setEtiquette(temp->getGauche()->getEtiquette());
                s1->setEtiquette2(temp->getGauche()->getEtiquette2());
                temp1->setGauche(s1);

                q1.push(temp1->getGauche());
                q.push(temp->getGauche());
            }

            if(temp->getDroit()  != NULL)
            {
                s2 = new Sommet();
                s2->setEtiquette(temp->getDroit()->getEtiquette());
                s2->setEtiquette2(temp->getDroit()->getEtiquette2());
                temp1->setDroit(s2);

                q1.push(temp1->getDroit());
                q.push(temp->getDroit());
            }
        }
    }
}

ArbreB::~ArbreB()
{
    if (this->racine)
    {   
        if (this->racine->getGauche() != NULL)
        {
            this->racine->getGauche();
        }

        if (this->racine->getDroit() != NULL)
        {
            delete this->racine->getDroit();
        }
        
        delete this->racine;
    }
}

int ArbreB::taille()
{

    queue<Sommet *> Q;
    Q.push(this->racine);
    Sommet * tmp;
    int co=0;
    
    while(! Q.empty())
    {
        tmp = Q.front();
        Q.pop();

        if (tmp->getGauche())
        {
            Q.push(tmp->getGauche());
        }
        if (tmp->getDroit())
        {   
            Q.push(tmp->getDroit());
        }
        
        co++;
    }

    return co;
}

Sommet *ArbreB::getRacine()
{
    return this->racine;
}

void ArbreB::setRacine(Sommet *r)
{
    this->racine=r;
}

void ArbreB::inserer(Sommet *s)
{
    if ( this->getRacine() == NULL)
    {
        this->setRacine(s);
        return;
    }
    
    queue<Sommet *> q;
    q.push(this->racine);
    Sommet *temp;
    
    while(! q.empty())
    {
        temp = q.front();
        q.pop();
        
        if (temp->getGauche() == NULL)
        {
            temp->setGauche(s);
            return;
        }
        else
        {
            q.push(temp->getGauche());
        }

        if (temp->getDroit() == NULL)
        {
            temp->setDroit(s);
            return;
        }
        else
        {
            q.push(temp->getDroit());
        }
    }
}

Sommet *ArbreB::rechercher(double etiq)
{
    if(this->racine==NULL)
        return NULL;

    queue<Sommet *> q;
    q.push(this->racine);

    Sommet *sortie = NULL;
    Sommet *temp;
    while (!q.empty())
    {
        temp = q.front();
        q.pop();

        if(temp->getEtiquette() == etiq) sortie = temp;
        if(temp->getGauche() != NULL) q.push(temp->getGauche());
        if(temp->getDroit()  != NULL) q.push(temp->getDroit());
    }
    
    return sortie;
}

void ArbreB::supprimerProfondDroit(Sommet *profondD)
{
    queue<Sommet *> q;
    q.push(this->racine);
    Sommet *temp;

    while(!q.empty())
    {
        temp = q.front();
        q.pop();

        if (temp->getGauche() != NULL)
        {
            if (temp->getGauche() == profondD)
            {
                temp->setGauche(NULL);
                return;
            }
            else
            {
                q.push(temp->getGauche());
            }
            
            
        }

        if (temp->getDroit() != NULL)
        {
            if (temp->getDroit() == profondD)
            {
                temp->setDroit(NULL);
                return;
            }
            else
            {
                q.push(temp->getDroit());
            }
            
            
        }
        
    }
}

void ArbreB::supprimer(double etiq)
{
    Sommet *sommetASuprimer = this->rechercher(etiq);

    if (sommetASuprimer != NULL)
    {
        queue<Sommet *> q;
        q.push(this->racine);
        Sommet *temp = NULL;

        while (!q.empty())
        {
            temp = q.front();
            q.pop();

            if(temp->getGauche() != NULL)
                q.push(temp->getGauche());
            if(temp->getDroit() != NULL)
                q.push(temp->getDroit());
        }

        double etiAProfondD = temp->getEtiquette();

        supprimerProfondDroit(temp);

        sommetASuprimer->setEtiquette(etiAProfondD);
    }
}

void ArbreB::fusion(ArbreB *b,ArbreB *res)
{ 
    int i=0,k=0;
    int j=0,co=0,limite1=0,limite2=0; 

    std::vector<elem> tab1;
    std::vector<elem> tab2;
    std::vector<elem> tab3;
    elem elem_tmp;

    queue<Sommet *> Q1;
    Sommet * tmp1;

    Q1.push(this->racine); 
    

    while (!Q1.empty()) // RÉCUPERER LES VALEURS DU PREMIERE ARBRE 
    {
        
        tmp1 = Q1.front();
        Q1.pop();

        elem_tmp.etiq = tmp1->getEtiquette();
        elem_tmp.etiq2 = tmp1->getEtiquette2();
        
        tab1.push_back(elem_tmp);

        if (tmp1->getGauche())
            Q1.push(tmp1->getGauche());
        
        if (tmp1->getDroit())
            Q1.push(tmp1->getDroit());

    }

    Q1.push(b->racine);   
    
    while (!Q1.empty()) // RÉCUPERER LES VALEURS DU DEUXIEME ARBRE 
    {
        tmp1 = Q1.front();
        Q1.pop();

        elem_tmp.etiq = tmp1->getEtiquette();
        elem_tmp.etiq2 = tmp1->getEtiquette2();

        tab2.push_back(elem_tmp);
    
        if (tmp1->getGauche())
            Q1.push(tmp1->getGauche());
        
        if (tmp1->getDroit())
            Q1.push(tmp1->getDroit());

    }

    while (k < (int)(tab1.size() + tab2.size())) // REMPLIR LE DERNIER TABLEAU avec TOUTES LES VALEURS DES DEUX ARBRES
    {
        i = 0; j = 0;

        while (limite1 < (int)tab1.size() && i < pow(2,co))
        {
          tab3.push_back( tab1.at(limite1) );
          i++; limite1++;
          k++;
        }
        
        while (i < pow(2,co) && limite1 >= (int)tab1.size())
        {
            elem_tmp.etiq = -1;
            elem_tmp.etiq2 = (char) 0;
            tab3.push_back(elem_tmp);
            i++;
        }
        
        while (limite2 < (int)tab2.size() && j < pow(2,co))
        {
            tab3.push_back(tab2.at(limite2));
            j++; limite2++;
            k++;
        }

        while (j < pow(2,co) && limite2 >= (int)tab2.size())
        {
            elem_tmp.etiq = -1;
            elem_tmp.etiq2 = (char) 0;
            tab3.push_back(elem_tmp);
            j++;
        }

        co++;
        
    }

    res->inserer(new Sommet(tab3.at(0).etiq + tab3.at(1).etiq,(char)0)); // INSERER LA RACINE DE L'ARBRE RESULTAT

    for (size_t i = 0; i < tab3.size() ; i++)  // INSERER LES VALEURS DES DEUX ARBRES 
    {
        res->inserer(new Sommet(tab3.at(i).etiq,tab3.at(i).etiq2));
    }
    

}

void ArbreB::decomposition(ArbreB *ArbreUn,ArbreB *ArbreDeux)
{
    ArbreB *temp = new ArbreB(*this);

    ArbreUn->inserer(temp->getRacine()->getGauche());
    ArbreDeux->inserer(temp->getRacine()->getDroit());
}

void ArbreB::affiche()
{
  //this->affiche_sommet(this->getRacine(),1);
  //cout << endl << endl;
  this->affichage << "                        >>ARBRE DU CODE<<                        \n\n";
  this->affiche_sommet(this->getRacine(),1);
  this->affichage << "\n\n";
  
}

void  ArbreB::affiche_sommet(Sommet *s, int niveau)
{
/*
  int i;
 
  if (s)
  {
    affiche_sommet(s->getDroit(), niveau + 1);
    for (i = 0; i < niveau; i++)
    {
      cout << "........";
    }
    if(s->getEtiquette() != -1)
        cout << s->getEtiquette() <<"."<< s->getEtiquette2()<<endl;  // AFFICHER LE POURCENTAGE DE SOMMET ET LE CARACTERE SI C UNE FEUILLE
    else
        cout <<(char)0<<"."<<(char)0<<endl;

    affiche_sommet(s->getGauche(), niveau + 1);
  }
*/

  int i;
 
  if (s)
  {
    affiche_sommet(s->getDroit(), niveau + 1);
    for (i = 0; i < niveau; i++)
    {
      this->affichage << "        ";
    }
    if(s->getEtiquette() != -1)
    {
        //cout << s->getEtiquette() <<"."<< s->getEtiquette2()<<endl;  // AFFICHER LE POURCENTAGE DE SOMMET ET LE CARACTERE SI C UNE FEUILLE
        this->affichage << s->getEtiquette();
        this->affichage << (char)0;
        this->affichage << "   ";
        this->affichage << (char)0;
        this->affichage << s->getEtiquette2();
        this->affichage << "\n";

    }
    else
    {
        //cout <<(char)0<<"."<<(char)0<<endl;
        this->affichage << (char)0;
        this->affichage << "   ";
        this->affichage << (char)0;
        this->affichage << "\n";

    }

    affiche_sommet(s->getGauche(), niveau + 1);
  }


}