/********************************************
* Titre: Travail pratique #5 - foncteur.h
* Date: 30 octobre 2019
* Auteur: Allan BEDDOUK & Jeffrey LAVALLEE
*******************************************/
#pragma once

#include <string>
#include <vector>
#include <map>
#include <iterator>

#include "coupon.h"
#include "membrePremium.h"

class AjouterCoupon
{
public: 
	AjouterCoupon(vector<Coupon*>& conteneur) { copy(conteneur.begin(), conteneur.end(),back_inserter(conteneur_)); }
	vector<Coupon*> operator()(Coupon* coupon) {
		if (find(conteneur_.begin(), conteneur_.end(), coupon) == conteneur_.end()) {
			conteneur_.push_back(coupon);
		}
		return conteneur_;
	}

private: 
	vector<Coupon*> conteneur_;
};



class AjouterMembre
{
public:
	AjouterMembre(map<string, Membre*>& conteneur) { conteneur_ = conteneur;}
	map<string, Membre*> operator()(pair<string, Membre*> membre) {
		if (find_if(conteneur_.begin(), conteneur_.end(), [&](pair<string, Membre*> m) {
			return m == membre;
			}) == conteneur_.end()) 
		{
			conteneur_.insert(membre);
		}
		return conteneur_;
	}

private:
	map<string, Membre*> conteneur_; 
};

class IntervallePrixBillet
{
public:
	IntervallePrixBillet(double borneInf, double borneSup) { borneInf_ = borneInf; borneSup_ = borneSup; }
	bool operator()(Billet* billet) {
		if (billet->getPrix() >= borneInf_ && billet->getPrix() <= borneSup_) {
			return true;
		}
		else { return false; }
	}

private:
	double borneInf_;
	double borneSup_;
};