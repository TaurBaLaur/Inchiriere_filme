#pragma once
#include <QWidget.h>
#include "watchlist.h"
#include <QListWidget.h>
#include <QLayout.h>
#include <QTableWidget.h>
#include <qpushbutton.h>
#include "observer.h"
#include <qpainter.h>

class Watchlist_GUI : public QWidget, public Observer {
private:
	Watch_List& gwl;
	void initGUIcmps();
	void connectSignalsSlots();
	void reloadList(const vector<Film>& filme);

	QVBoxLayout* main_layout = new QVBoxLayout;
	//QListWidget* filme_widget = new QListWidget;
	QTableWidget* filme_widget = new QTableWidget;

public:
	Watchlist_GUI(Watch_List& wl) : gwl{ wl } {
		initGUIcmps();
		connectSignalsSlots();
		reloadList(gwl.get_filme_watchlist());
	}
	void update() override;

	~Watchlist_GUI();
};

class Watchlist_GUI_CRUD : public QWidget, public Observer {
private:
	Watch_List& gwl;
	void initGUIcmps();
	void connectSignalsSlots();
	void reloadList(const vector<Film>& filme);

	QVBoxLayout* main_layout = new QVBoxLayout;
	//QListWidget* filme_widget = new QListWidget;
	QTableWidget* filme_widget = new QTableWidget;
	QPushButton* buton_goleste_watchlist;

	void goleste_wl();


public:
	Watchlist_GUI_CRUD(Watch_List& wl) : gwl{ wl } {
		initGUIcmps();
		connectSignalsSlots();
		reloadList(gwl.get_filme_watchlist());
	}
	void update() override;

	~Watchlist_GUI_CRUD();
};

//class Watchlist_GUI_RO : public QWidget, public Observer {
//private:
//	Watch_List& gwl;
//	//void initGUIcmps();
//	//void connectSignalsSlots();
//	void reloadList(const vector<Film>& filme);
//
//	//QVBoxLayout* main_layout = new QVBoxLayout;
//	////QListWidget* filme_widget = new QListWidget;
//	//QTableWidget* filme_widget = new QTableWidget;
//
//public:
//	/*Watchlist_GUI_RO(Watch_List& wl) : gwl{ wl } {
//		initGUIcmps();
//		connectSignalsSlots();
//		reloadList(gwl.get_filme_watchlist());
//	}*/
//	Watchlist_GUI_RO(Watch_List& wl) : gwl{ wl } {};
//	void update() override
//	{
//		reloadList(gwl.get_filme_watchlist());
//	}
//
//	//~Watchlist_GUI()_RO;
////public:
////	Watchlist_GUI_RO(Watch_List& wl) : gwl{ wl } {};
////	void paintEvent(QPaintEvent* ev) override;
//};