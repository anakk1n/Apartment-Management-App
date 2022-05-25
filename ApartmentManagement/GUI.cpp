#include "GUI.h"
#include <string>

/*initilizare
date de intrare:-
date de iesire:-
*/
void GUI::init()
{
	this->setWindowTitle("Administrare bloc");

	principalBox = new QHBoxLayout;
	box = new QVBoxLayout;
	box1 = new QHBoxLayout;
	box2 = new QHBoxLayout;
	box3 = new QHBoxLayout;
	box4 = new QHBoxLayout;
	box5 = new QHBoxLayout;
	mesaj = new QLabel("@ Instrumente lista notificari @");
	buttAndLines = new QVBoxLayout;
	buttons = new QHBoxLayout;

	//butoane
	adauga = new QPushButton("&adauga");
	afisare = new QPushButton("&lista");
	sterge = new QPushButton("&sterge");
	cauta = new QPushButton("&cauta");
	modifica = new QPushButton("&modifica");
	filtrare = new QPushButton("&filtrare");
	filtrareTip = new QPushButton("&filtrare Tip");
	filtrareSuprafata = new QPushButton("&filtrare Suprafata");
	sortare = new QPushButton("&sortare");
	sortareSuprafata = new QPushButton("&sortare suprafata");
	sortareNume = new QPushButton("&sortare nume");
	sortareTipSuprafata = new QPushButton("&sortare tip si suprafata");
	undo = new QPushButton("&undo");
	listaNotificari = new QPushButton("&lista notificari");
	CosCRUD = new QPushButton("&Genereaza Apart.");
	adaugaCos = new QPushButton("&adauga cos");
	Export = new QPushButton("&export");
	//genereaza = new QPushButton("&genereaza");
	exit = new QPushButton("&exit");

	//QLineEdit
	apartament = new QLineEdit;
	nume = new QLineEdit;
	suprafata = new QLineEdit;
	tipApartament = new QLineEdit;
	fisier = new QLineEdit;
	nrApart = new QLineEdit;
	//lista
	list = new QListWidget;
	table = new QTableWidget{ 1, 4 };

	principalBox->addLayout(box);
	box->addWidget(list);
	box->addLayout(box1);
	box1->addWidget(filtrare);
	box1->addStretch();
	box1->addWidget(sortare);
	box1->addStretch();
	box1->addWidget(afisare);


	box2->addWidget(adauga);
	box2->addStretch();
	box2->addWidget(sterge);
	box2->addStretch();
	box2->addWidget(cauta);
	box2->addStretch();


	box3->addWidget(modifica);
	box3->addWidget(undo);

	box4->addWidget(adaugaCos);
	box4->addWidget(Export);



	box5->addWidget(CosCRUD);


	QFormLayout* form = new QFormLayout;
	form->addRow("Apartament", apartament);
	form->addRow("Nume", nume);
	form->addRow("Suprafata", suprafata);
	form->addRow("Tip Apartament", tipApartament);
	form->addRow("Fisier", fisier);


	buttAndLines->addLayout(form);
	buttAndLines->addLayout(box2);
	buttAndLines->addLayout(box3);
	buttAndLines->addWidget(mesaj);
	buttAndLines->addLayout(box4);
	buttAndLines->addLayout(box5);
	buttAndLines->addWidget(exit);
	buttAndLines->addStretch();
	principalBox->addLayout(buttAndLines);

	auto tab = new tabel{ srv.getAllService() };
	tab->setModal(false);
	principalBox->addWidget(table);
	//butoaneFiltrare->addWidget(filtrareTip);
	setLayout(principalBox);
}

/*afisare lista utilizand QListWidget
* date de intrare:-vector de Locatar
* date de iesire:
*/
void GUI::loadList(vector<Locatar> locatari)
{
	list->clear();
	for (const auto& loc : locatari) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(loc.getNume()));
		list->addItem(item);
		item->setData(Qt::UserRole, QString::fromStdString(std::to_string(loc.getApartament())));
	}
}

/*
* conectam butoanele cu functiile
* date de intrare:
* date de iesire:
*/
void GUI::connect()
{

	QWidget::connect(exit, &QPushButton::clicked, [&]() {
		close();
		});

	QWidget::connect(CosCRUD, &QPushButton::clicked, [&]() {
		auto* cos = new CosCRUDGUI(srv);
		cos->show();
		});

	QWidget::connect(listaNotificari, &QPushButton::clicked, [&]() {
		auto listaNot = new listNotificariGUI(srv);
		listaNot->show();
		});

	QWidget::connect(list, &QListWidget::itemSelectionChanged, [&]() {
		if (selectedItem != nullptr)
			selectedItem->setBackground(Qt::transparent);
		if (list->selectedItems().isEmpty())
		{
			apartament->setText("");
			nume->setText("");
			suprafata->setText("");
			tipApartament->setText("");
			return;
		}
		auto item = list->selectedItems().at(0);
		apartament->setText(item->data(Qt::UserRole).toString());
		nume->setText(item->text());
		suprafata->setText(QString::number(srv.cautareApartamentService(item->data(Qt::UserRole).toInt()).getSuprafata()));
		tipApartament->setText(QString::fromStdString(srv.cautareApartamentService(item->data(Qt::UserRole).toInt()).getTipApartament()));
		item->setBackground(Qt::darkGreen);
		auto tab = new tabelDetalii{ srv.cautareApartamentService(item->data(Qt::UserRole).toInt()) };
		tab->show();
		selectedItem = item;
		//item->setBackground(Qt::transparent);
		});

	QWidget::connect(adaugaCos, &QPushButton::clicked, [&]() {
		int apartament1{ 0 };
		try {
			try {
				apartament1 = std::stoi(apartament->text().toStdString());
			}
			catch (const std::invalid_argument) {
				QMessageBox::warning(this, "warning", "valoare invalida");
				return;
			}
			srv.adaugaLista(apartament1);
		}
		catch (const RepoException& msg) {
			QMessageBox::warning(this, "warning", QString::fromStdString(msg.getMesaj()));
		}
		catch (const listaException& msg) {
			QMessageBox::warning(this, "warning", QString::fromStdString(msg.getMesaj()));
		}
		}
	);


	QWidget::connect(Export, &QPushButton::clicked, [&]() {
		try {
			srv.writeToFile(fisier->text().toStdString());
		}
		catch (const listaException& msg) {
			QMessageBox::warning(this, "warning", QString::fromStdString(msg.getMesaj()));
		}
		});

	adaugaLocatar();
	stergeLocatar();
	cautaLocatar();
	modificaLocatar();
	filtrareButton();
	filtrareTipApart();
	filtrareSupra();
	sortareButton();
	sortSuprafata();
	sortNume();
	sortTipSuprafata();
	Undo();
	afisareLocatar();
}
