#include "gui.h"
#include <QtWidgets/QApplication>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qboxlayout.h>
#include <qlineedit.h>
#include <qformlayout.h>
#include <qlistwidget.h>
#include "gui_watchlist.h"

#include<vector>
#include<string>
using std::vector;
using std::string;

void toate_testele()
{
	teste_domain();
	test_validator();
	teste_repo();
	teste_service();
}

void start(int argc, char* argv[])
{
	QApplication a(argc, argv);

	FilmValidator val;
	//Repo_Filme rep;
	RepoFisier_Filme rep{ "filme.txt" };
	Service_Filme srv{ rep,val };
	Filme_GUI gui{ srv };

	gui.show();

	Watchlist_GUI* wl = new Watchlist_GUI{ srv.get_watchlist_obj() };
	wl->show();

	Watchlist_GUI_CRUD* wlcrud = new Watchlist_GUI_CRUD{ srv.get_watchlist_obj() };
	wlcrud->show();

	/*Watchlist_GUI_RO wlro{ srv.get_watchlist_obj() };
	wlro.show();*/

	QObject::connect(gui.get_exit(), &QPushButton::clicked, &a, QApplication::quit);

	a.exec();

	
}

int main(int argc, char *argv[])
{
	toate_testele();
	start(argc, argv);
	return 0;
}
