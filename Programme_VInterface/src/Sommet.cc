#include "Sommet.hh"
#include <iostream>

Sommet::Sommet()
{
	this->etiquette = 0;
	this->Gauche=NULL;
	this->Droit=NULL;
}

Sommet::Sommet(double etiq,char etiq2)
{
	this->etiquette = etiq;
	this->etiquette2= etiq2;
	this->Gauche=NULL;
	this->Droit=NULL;
}

Sommet::~Sommet()
{
	/*if(this)
	{	
		if (this->Gauche)
		{
			this->Gauche->~Sommet();
		}

		if (this->Droit)
		{
			this->Droit->~Sommet();
		}

		delete this;
	}*/
	/*if(Droit)
		delete Droit;

	if(Gauche)
		delete Gauche;*/
}

double Sommet::getEtiquette()
{
	return this->etiquette;
}

char Sommet::getEtiquette2()
{
	return this->etiquette2;
}

void Sommet::setEtiquette(double eti)
{
	this->etiquette = eti;
}

void Sommet::setEtiquette2(char eti2)
{
	this->etiquette2 = eti2;
}

Sommet *Sommet::getGauche()
{
	return this->Gauche;
}

void Sommet::setGauche(Sommet *g)
{
	this->Gauche = g;
}

Sommet *Sommet::getDroit()
{
	return this->Droit;
}

void Sommet::setDroit(Sommet *d)
{
	this->Droit = d;
}
