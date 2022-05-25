#include "UI.h"
#include <iostream>
#include <string>
#include <map>
using std::cin;
using std::cout;
using std::string;
using std::map;

//UI pentru adauga locatar
void UI::UIadaugaLocatar()
{
	string nume;
	string tipApartament;
	string apartament;
	string suprafata;
	cout << "apartament=";
	getline(cin, apartament, '\n');
	cout << "nume=";
	getline(cin, nume, '\n');
	cout << "suprafata=";
	getline(cin, suprafata, '\n');
	cout << "tipApartament=";
	getline(cin, tipApartament, '\n');
	int apartament1{ 0 };
	double suprafata1{ 0 };
	try {
		apartament1 = stoi(apartament);
	}
	catch (const std::invalid_argument) {
		cout << "Valoare invalida\n";
		return;
	}

	try {
		suprafata1 = stoi(suprafata);
	}
	catch (const std::invalid_argument) {
		cout << "Valoare invalida\n";
		return;
	}

	try {
		srv.adaugaLocatarService(apartament1, nume, suprafata1, tipApartament);
	}
	catch (const RepoException& msg) {
		cout << msg.getMesaj();
	}
	catch (const ValidException& msg) {
		cout << msg.getMesaj();
	}
}

//UI pentru afisare locatari
void UI::UIafisareLocatar()
{
	try {
		const vector < Locatar >& locatari = srv.getAllService();
		if (locatari.size() == 0)
		{
			cout << "lista vida";
			return;
		}
		for (const auto& l : locatari)
			cout << " Apartament:" << l.getApartament() << " Nume:" << l.getNume() << " Suprafata:" << l.getSuprafata() << " mp Tip Apartament:" << l.getTipApartament() << "\n";
	}
	catch (const RepoException& msg) {
		cout << msg.getMesaj();
	}

}

//UI pentru stergere locatari
void UI::UIstergereLocatar()
{
	string apartament;
	int apartament1;
	cout << "apartament=";
	getline(cin, apartament, '\n');

	try {
		apartament1 = stoi(apartament);
	}
	catch (const std::invalid_argument) {
		cout << "Valoare invalida\n";
		return;
	}

	try {
		srv.stergereLocatarService(apartament1);
	}
	catch (const RepoException& msg) {
		cout << msg.getMesaj();
	}

}

//UI pntru modifica locatari
void UI::UImodificaLocatar()
{
	string nume;
	string tipApartament;
	string apartament;
	string suprafata;
	int apartament1{ 0 };
	double suprafata1{ 0 };
	cout << "apartament=";
	getline(cin, apartament, '\n');
	cout << "nume=";
	getline(cin, nume, '\n');
	cout << "suprafata=";
	getline(cin, suprafata, '\n');
	cout << "tipApartament=";
	getline(cin, tipApartament, '\n');
	try {
		apartament1 = stoi(apartament);
	}
	catch (const std::invalid_argument) {
		cout << "Valoare invalida\n";
		return;
	}

	try {
		suprafata1 = stoi(suprafata);
	}
	catch (const std::invalid_argument) {
		cout << "Valoare invalida\n";
		return;
	}

	try {
		srv.modificaLocatarService(apartament1, nume, suprafata1, tipApartament);
	}
	catch (const RepoException& msg) {
		cout << msg.getMesaj();
	}
	catch (const ValidException& msg) {
		cout << msg.getMesaj();
	}
}

//UI pentru cauta apartament
void UI::UIcautaApartament()
{
	string apartament;
	int apartament1;
	cout << "apartament=";
	getline(cin, apartament, '\n');
	try {
		apartament1 = stoi(apartament);
	}
	catch (const std::invalid_argument) {
		cout << "Valoare invalida\n";
		return;
	}
	try {
		const Locatar& l = srv.cautareApartamentService(apartament1);
		cout << "Apartament:" << l.getApartament() << " locatari:" << l.getNume() << " Suprafata:" << l.getSuprafata() << " tip apartament:" << l.getTipApartament() << "\n";
	}
	catch (const RepoException& e)
	{
		cout << e.getMesaj();
	}

}
