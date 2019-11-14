/********************************************
* Titre: Travail pratique #5 - gestionnaireMembres.cpp
* Date: 30 octobre 2019
* Auteur: Allan BEDDOUK & Jeffrey LAVALLEE
*******************************************/

#include "GestionnaireMembres.h"
#include <numeric>

void GestionnaireMembres::assignerBillet(Billet* billet, const string& nomMembre, int rabaisCoupon)
{
	Membre* membre = conteneur_[nomMembre];

	if (membre == nullptr) {
		delete billet;
		return;
	}

	double prix = billet->getPrix();

	if (auto solde = dynamic_cast<Solde*>(billet)) {
		prix = solde->getPrixBase();
	}

	
	prix -= rabaisCoupon;
	

	if (auto membrePremium = dynamic_cast<MembrePremium*>(membre)) {
		double rabais = 0.005 * membrePremium->getpointsCumulee() / 1000;
		if (rabais > 0.1)
			rabais = 0.1;

		prix *= (1 - rabais);
	}

	billet->setPrix(prix);
	membre->ajouterBillet(billet);
}



double GestionnaireMembres::calculerRevenu() const
{
	double revenu = 0; 
	for_each(conteneur_.begin(), conteneur_.end(), [&revenu](pair<string, Membre*> m) {
		for_each(m.second->getBillets().begin(), m.second->getBillets().end(), [&revenu](Billet* billet) {
			revenu += billet->getPrix(); });
		});
	return revenu; 
}


int GestionnaireMembres::calculerNombreBilletsEnSolde() const
{
	int nbBilletsSolde = 0; 
	for_each(conteneur_.begin(), conteneur_.end(), [&](pair<string, Membre*> m) {
		for_each(m.second->getBillets().begin(), m.second->getBillets().end(), [&](Billet* billet) {
			if (dynamic_cast<Solde*>(billet)) { 
				++nbBilletsSolde;
			}
			});
		});
	return nbBilletsSolde;
}


Billet* GestionnaireMembres::getBilletMin(string nomMembre) const {

	vector<Billet*> it = conteneur_.at(nomMembre)->getBillets();

	auto min = min_element(it.begin(), it.end(), [&](Billet* billet1, Billet* billet2) {
		return billet1->getPrix() < billet2->getPrix();
	});
	return *min; 
}


Billet* GestionnaireMembres::getBilletMax(string nomMembre) const {

	vector<Billet*> it = conteneur_.at(nomMembre)->getBillets();

	auto max = max_element(it.begin(), it.end(), [&](Billet* billet1, Billet* billet2) {
		return billet1->getPrix() > billet2->getPrix();
		});
	return *max;
}


vector<Billet*> GestionnaireMembres::trouverBilletParIntervallle(Membre* membre, double prixInf, double prixSup) const {
	vector<Billet*> vec;
	copy_if(membre->getBillets().begin(), membre->getBillets().end(), back_inserter(vec), IntervallePrixBillet(prixInf, prixSup));
	return vec; 
}


void GestionnaireMembres::afficher(ostream& o) const
{
	o << "=================== ETAT ACTUEL DU PROGRAMME ==================\n\n";

	for_each(conteneur_.begin(), conteneur_.end(), [&o](pair<string, Membre*> m) {
		m.second->afficher(o);
		});
}
