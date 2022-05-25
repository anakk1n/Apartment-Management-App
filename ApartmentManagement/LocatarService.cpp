#include "LocatarService.h"
#include "Exceptii.h"
#include <iostream>
#include <algorithm>
#include <random> 
#include <chrono> 


/*adauga locatar
date de intrare: -apart-int
*				 -nume-string
*			     -suprafata-double
*		         -tip-string
* date de iesire:-
*/
void LocatarService::adaugaLocatarService(const int& apartament, const string& nume, const double& suprafata, const string& tipApartament) {
	Locatar loc{ apartament,nume,suprafata,tipApartament };
	val.valideazaLocatar(loc);
	repo.adaugaLocatar(loc);
	notify();
	undoActions.push_back(std::make_unique<UndoAdauga>(repo, loc));
}

/*stergere locatar
* date de intrare:-apartament-int
* date de iesire:-
*/
void LocatarService::stergereLocatarService(const int& apartament)
{
	const Locatar& loc = repo.cautareApartament(apartament);
	undoActions.push_back(std::make_unique<UndoSterge>(repo, loc));
	repo.stergereLocatar(apartament);
	lista.stergereApartament(apartament);
	notify();
}

/*modifica locatar
date de intrare: -apart-int
*				 -nume-string
*			     -suprafata-double
*		         -tip-string
* date de iesire:-
*/
void LocatarService::modificaLocatarService(const int& apartament, const string& nume, const double& suprafata, const string& tipApartament)
{
	Locatar loc{ apartament,nume,suprafata,tipApartament };
	val.valideazaLocatar(loc);
	Locatar loc1 = repo.cautareApartament(apartament);
	undoActions.push_back(std::make_unique<UndoModifica>(repo, loc1));
	repo.modificareLocatar(loc);
	lista.modificaApartament(loc);
	notify();
}

/*cautare apartament
* date de intrare:-apartament-int
* date de iesire:-locatarul dorit-referinta la locatar
*/

const Locatar& LocatarService::cautareApartamentService(const int& apartament)
{
	return repo.cautareApartament(apartament);
}

/*returneaza toti locatarii din repo
* date de intrare:-
* date de iesire:-locatarii-referinta la VectorDinamic
*/
const vector<Locatar>& LocatarService::getAllService() {
	return repo.getAll();
}

/*functie de filtrare
* date de intrare:-functie booleana
* date de iesire:-rez-referinta la VectorDinamic

vector<Locatar> LocatarService::filtrare(function<bool(const Locatar& loc)> fct)
{
	vector<Locatar> rez;
	const vector<Locatar>& locatari = repo.getAll();
	for (int i=0; i<locatari.size();i++)
		if (fct(locatari.at(i)))
			rez.push_back(locatari.at(i));
	return rez;
}
*/
/*filtrare dupa tipul apartamentului
* date de intrare:-tip-string
* date de iesire:-rez-referinta la VectorDinamic
*/
vector<Locatar> LocatarService::filtrareTipApartament(const string& tip)
{
	vector<Locatar> rez;
	const vector<Locatar>& locatari = repo.getAll();
	std::copy_if(locatari.begin(), locatari.end(), std::back_inserter(rez), [&](const Locatar& l) {return l.getTipApartament() == tip; });
	return rez;
}

/*filtrare dupa auprafata apartamentului
* date de intrare:-suprafata-int
* date de iesire:-rez-referinta la VectorDinamic
*/
vector<Locatar> LocatarService::filtrareSuprafata(const double& suprafata)
{
	vector<Locatar> rez;
	const vector<Locatar>& locatari = repo.getAll();
	std::copy_if(locatari.begin(), locatari.end(), std::back_inserter(rez), [&](const Locatar& l) {return l.getSuprafata() <= suprafata; });
	return rez;
}

/*functie de sortare
* date de intrare:-functie booleana
* date de iesire:-rez-referinta la VectorDinamic

vectorDinamic<Locatar> LocatarService::sortare(function<bool(const Locatar& loc1, const Locatar& loc2)> fct)
{
	vectorDinamic<Locatar> rez{ repo.getAll() };
	for(int i{0};i<rez.size();i++)
		for(int j{0};j<rez.size();j++)
			if (fct(rez.at(i), rez.at(j)))
			{
				Locatar aux = rez.at(i);
				rez.set(rez.at(j), i);
				rez.set(aux, j);
			}
	return rez;
}
*/

/*sortare dupa nume
* date de intrare:-
* date de iesire:-rez-referinta la VectorDinamic
*/
vector<Locatar> LocatarService::sortareNume()
{
	vector<Locatar> rez{ repo.getAll() };
	std::sort(rez.begin(), rez.end(), [](const Locatar& loc1, const Locatar& loc2) {return loc1.getNume() <= loc2.getNume(); });
	return rez;
}

/*sortare dupa suprafata
* date de intrare:-
* date de iesire:-rez-referinta la VectorDinamic
*/
