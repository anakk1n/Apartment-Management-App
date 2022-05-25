#include <qwidget.h>
#include <QtWidgets/QApplication>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <QItemSelectionModel>
#include <qlistwidget.h>
#include <qboxlayout.h>
#include <qformlayout.h>
#include <qlistwidget.h>
#include <qobject.h>
#include <qtablewidget.h>
#include <qmessagebox.h>
#include "LocatarRepository.h"
#include "ValidareLocatar.h"
#include "ListaNotificari.h"
#include "LocatarService.h"
#include "LocatarRepositoryFile.h"
#include "ExceptionRepo.h"
#include <iostream>
#include <string>
#include "Teste.h"
#include "UI.h"
#include "Exceptii.h"
#include <vector>
#include <qpainter.h>
#include "Observer.h"
#include <string>
#include <QPoint>
#include <QPoint>
using std::vector;
using std::string;

//clasa pentru a afisa un tabel
class tabel :public QDialog {
private:
	vector<Locatar>locatari;
	QHBoxLayout* box;

	/*initilizare
	date de intrare:-
	date de iesire:-
	*/
	void init();
public:
	/*constructor
	* date de intrare:-locatar-vector
	* date de iesire:-
	*/
	tabel(vector<Locatar> locatar) :locatari{ locatar } {
		init();
	}
};

class tabelDetalii :public QDialog {
private:
	Locatar locatar;
	QLineEdit* apartament;
	QLineEdit* nume;
	QLineEdit* suprafata;
	QLineEdit* tipApartament;
	/*initilizare
	date de intrare:-
	date de iesire:-
	*/
	void init();
public:
	/*constructor
	* date de intrare:-locatar-vector
	* date de iesire:-
	*/
	tabelDetalii(Locatar locatar) :locatar{ locatar } {
		init();
	}
};

//clasa pentru lista de notificari
class listNotificariGUI : public QWidget {
private:
	LocatarService& srv;
	//box-uri
	QHBoxLayout* principalBox;
	QVBoxLayout* box;
	QHBoxLayout* box1;
	QHBoxLayout* box2;
	QHBoxLayout* box3;
	QListWidget* list;

	//butoane
	QPushButton* adauga;
	QPushButton* sterge;
	QPushButton* genereaza;
	QPushButton* Export;
	QPushButton* afisare;
	QPushButton* exit;

	//QLineEdit
	QLineEdit* apartament;
	QLineEdit* numarApartamente;
	QLineEdit* numeFisier;

	//afiseaza lista de locatari din lista de notificari
	//date de intrare:-locatari:-vector
	//                -numar:-int
	//date de iesire:-
	void loadList(vector<Locatar>, int numar);

	/*initilizare
	date de intrare:-
	date de iesire:-
	*/
	void init();

	/*
* conectam butoanele
* date de intrare:
* date de iesire:
*/
	void connect();

public:
	//constructor
	//date de intrare:-srv-referinta la LocatarService
	//date de iesire:-
	listNotificariGUI(LocatarService& srv) :srv{ srv } {
		init();
		loadList(srv.getAllService(), 0);
		connect();
	}
};
