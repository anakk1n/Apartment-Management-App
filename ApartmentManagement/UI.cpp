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
//UI pentru filtrare dupa tip apartament
void UI::UIfiltrareTipApartament()
{
	string  apartament;
	cout << "tip apartament=";
	getline(cin, apartament, '\n');
	vector<Locatar>locatari = srv.filtrareTipApartament(apartament);
	if (locatari.size() == 0)
	{
		cout << "lista goala\n";
		return;
	}
	for (const auto& l : locatari)
		cout << " Apartament:" << l.getApartament() << " Nume:" << l.getNume() << " Suprafata:" << l.getSuprafata() << " mp Tip Apartament:" << l.getTipApartament() << "\n";
}
//UI pentru filtrare dupa suprafata
void UI::UIfiltrareSuprafata()
{
	string suprafata;
	int suprafata1;
	cout << "suprafata=";
	getline(cin, suprafata, '\n');
	try {
		suprafata1 = stoi(suprafata);
	}
	catch (const std::invalid_argument) {
		cout << "Valoare invalida\n";
		return;
	}
	vector<Locatar>locatari = srv.filtrareSuprafata(suprafata1);
	if (locatari.size() == 0)
	{
		cout << "lista goala\n";
		return;
	}
	for (const auto& l : locatari)
		cout << " Apartament:" << l.getApartament() << " Nume:" << l.getNume() << " Suprafata:" << l.getSuprafata() << " mp Tip Apartament:" << l.getTipApartament() << "\n";

}
//UI pentru sortare dupa nume
void UI::UIsortareNume()
{
	vector<Locatar> locatari = srv.sortareNume();
	if (locatari.size() == 0)
	{
		cout << "lista goala\n";
		return;
	}
	for (const auto& l : locatari)
		cout << " Apartament:" << l.getApartament() << " Nume:" << l.getNume() << " Suprafata:" << l.getSuprafata() << " mp Tip Apartament:" << l.getTipApartament() << "\n";

}

//UI pentru sortare dupa suprafata
void UI::UIsortareSuprafata()
{
	vector<Locatar> locatari = srv.sortareSuprafata();
	if (locatari.size() == 0)
	{
		cout << "lista goala\n";
		return;
	}
	for (const auto& l : locatari)
		cout << " Apartament:" << l.getApartament() << " Nume:" << l.getNume() << " Suprafata:" << l.getSuprafata() << " mp Tip Apartament:" << l.getTipApartament() << "\n";

}

//UI pentru sortare  dupa tip si suprafata
void UI::UIsortareTipSuprafata()
{
	vector<Locatar> locatari = srv.sortareApartamentSuprafata();
	if (locatari.size() == 0)
	{
		cout << "lista goala\n";
		return;
	}
	for (const auto& l : locatari)
		cout << " Apartament:" << l.getApartament() << " Nume:" << l.getNume() << " Suprafata:" << l.getSuprafata() << " mp Tip Apartament:" << l.getTipApartament() << "\n";

}

void UI::UIadaugaListaNotificari()
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
		srv.adaugaLista(apartament1);
	}
	catch (const listaException& msg) {
		cout << msg.getMesaj();
	}
	catch (const RepoException& msg) {
		cout << msg.getMesaj();
	}
	const int total = srv.nrApartamenteLista();
	cout << "nr aparteamente din lista de notificari:" << total;

}

void UI::UIgolesteLista() {
	srv.golesteLista();
	const int total = srv.nrApartamenteLista();
	cout << "nr aparteamente din lista de notificari:" << total;
}

void UI::UIgenereazaLista()
{
	string numar;
	int numar1;
	cout << "apartamente=";
	getline(cin, numar, '\n');

	try {
		numar1 = stoi(numar);
	}
	catch (const std::invalid_argument) {
		cout << "Valoare invalida\n";
		return;
	}
	try {
		srv.genereazaLista(numar1);
	}
	catch (const listaException& msg) {
		cout << msg.getMesaj();
	}
	const int total = srv.nrApartamenteLista();
	cout << "nr aparteamente din lista de notificari:" << total;
}

