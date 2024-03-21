#include "gui_watchlist.h"
#include <qtimer.h>

//-----WL INITIAL-----
void Watchlist_GUI::initGUIcmps() {
	setLayout(main_layout);


	main_layout->addWidget(filme_widget);
}
void Watchlist_GUI::connectSignalsSlots() {
	QTimer* refreshTimer = new QTimer;
	QObject::connect(refreshTimer, &QTimer::timeout, [this]() {
		reloadList(gwl.get_filme_watchlist());
		});
	refreshTimer->start(1000);


}
void Watchlist_GUI::reloadList(const vector<Film>& filme) {
	/*filme_widget->clear();
	for (const auto& f : filme) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(f.get_titlu()));
		item->setData(Qt::UserRole, QString::fromStdString(f.get_gen()));
		item->setData(Qt::UserRole + 1, QString::number(f.get_an()));
		item->setData(Qt::UserRole + 2, QString::fromStdString(f.get_actor_principal()));
		filme_widget->addItem(item);

	}*/
	filme_widget->clear();
	filme_widget->setRowCount(filme.size());
	filme_widget->setColumnCount(4);
	int i = 0;
	/*filme_widget->setItem(i, 0, new QTableWidgetItem("Titlu"));
	filme_widget->setItem(i, 1, new QTableWidgetItem("Gen"));
	filme_widget->setItem(i, 2, new QTableWidgetItem("An"));
	filme_widget->setItem(i, 3, new QTableWidgetItem("Actor prinipal"));
	i++;*/
	filme_widget->setHorizontalHeaderItem(0, new QTableWidgetItem("Titlu"));
	filme_widget->setHorizontalHeaderItem(1, new QTableWidgetItem("Gen"));
	filme_widget->setHorizontalHeaderItem(2, new QTableWidgetItem("An"));
	filme_widget->setHorizontalHeaderItem(3, new QTableWidgetItem("Actor principal"));
	
	for (const auto& f : filme) {
		filme_widget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(f.get_titlu())));
		filme_widget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(f.get_gen())));
		filme_widget->setItem(i, 2, new QTableWidgetItem(QString::number(f.get_an())));
		filme_widget->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(f.get_actor_principal())));
		i++;

	}
}

void Watchlist_GUI::update(){
	reloadList(gwl.get_filme_watchlist());
}

Watchlist_GUI::~Watchlist_GUI() {
	gwl.removeObserver(this);
}

//-----WL CRUD-----
void Watchlist_GUI_CRUD::initGUIcmps() {
	setLayout(main_layout);


	main_layout->addWidget(filme_widget);
	buton_goleste_watchlist = new QPushButton("Goleste watchlist");
	main_layout->addWidget(buton_goleste_watchlist);
}
void Watchlist_GUI_CRUD::connectSignalsSlots() {
	QTimer* refreshTimer = new QTimer;
	QObject::connect(refreshTimer, &QTimer::timeout, [this]() {
		reloadList(gwl.get_filme_watchlist());
		});
	QObject::connect(buton_goleste_watchlist, &QPushButton::clicked, this, &Watchlist_GUI_CRUD::goleste_wl);
	refreshTimer->start(1000);


}
void Watchlist_GUI_CRUD::goleste_wl()
{
	gwl.goleste_watchlist();
}
void Watchlist_GUI_CRUD::reloadList(const vector<Film>& filme) {
	/*filme_widget->clear();
	for (const auto& f : filme) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(f.get_titlu()));
		item->setData(Qt::UserRole, QString::fromStdString(f.get_gen()));
		item->setData(Qt::UserRole + 1, QString::number(f.get_an()));
		item->setData(Qt::UserRole + 2, QString::fromStdString(f.get_actor_principal()));
		filme_widget->addItem(item);

	}*/
	filme_widget->clear();
	filme_widget->setRowCount(filme.size());
	filme_widget->setColumnCount(4);
	int i = 0;
	/*filme_widget->setItem(i, 0, new QTableWidgetItem("Titlu"));
	filme_widget->setItem(i, 1, new QTableWidgetItem("Gen"));
	filme_widget->setItem(i, 2, new QTableWidgetItem("An"));
	filme_widget->setItem(i, 3, new QTableWidgetItem("Actor prinipal"));
	i++;*/
	filme_widget->setHorizontalHeaderItem(0, new QTableWidgetItem("Titlu"));
	filme_widget->setHorizontalHeaderItem(1, new QTableWidgetItem("Gen"));
	filme_widget->setHorizontalHeaderItem(2, new QTableWidgetItem("An"));
	filme_widget->setHorizontalHeaderItem(3, new QTableWidgetItem("Actor principal"));

	for (const auto& f : filme) {
		filme_widget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(f.get_titlu())));
		filme_widget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(f.get_gen())));
		filme_widget->setItem(i, 2, new QTableWidgetItem(QString::number(f.get_an())));
		filme_widget->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(f.get_actor_principal())));
		i++;

	}
}

void Watchlist_GUI_CRUD::update() {
	reloadList(gwl.get_filme_watchlist());
}

Watchlist_GUI_CRUD::~Watchlist_GUI_CRUD() {
	gwl.removeObserver(this);
}

////-----WL RO-----
//void Watchlist_GUI_RO::reloadList(const vector<Film>& filme);
//{
//	filme_widget->clear();
//	filme_widget->setRowCount(filme.size());
//	filme_widget->setColumnCount(4);
//	int i = 0;
//	/*filme_widget->setItem(i, 0, new QTableWidgetItem("Titlu"));
//	filme_widget->setItem(i, 1, new QTableWidgetItem("Gen"));
//	filme_widget->setItem(i, 2, new QTableWidgetItem("An"));
//	filme_widget->setItem(i, 3, new QTableWidgetItem("Actor prinipal"));
//	i++;*/
//	filme_widget->setHorizontalHeaderItem(0, new QTableWidgetItem("Titlu"));
//	filme_widget->setHorizontalHeaderItem(1, new QTableWidgetItem("Gen"));
//	filme_widget->setHorizontalHeaderItem(2, new QTableWidgetItem("An"));
//	filme_widget->setHorizontalHeaderItem(3, new QTableWidgetItem("Actor principal"));
//
//	for (const auto& f : filme) {
//		filme_widget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(f.get_titlu())));
//		filme_widget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(f.get_gen())));
//		filme_widget->setItem(i, 2, new QTableWidgetItem(QString::number(f.get_an())));
//		filme_widget->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(f.get_actor_principal())));
//		i++;
//
//	}
//}