#pragma once
#include <qwidget.h>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qboxlayout.h>
#include <qdebug.h>
#include "service.h"
#include "domain.h"
#include <vector>
#include <qlabel.h>
#include <QTableWidget.h>

class Filme_GUI : public QWidget {
private:
	Service_Filme& srv;
	QHBoxLayout* ly_main = new QHBoxLayout;
	QListWidget* lista_filme;

	QTableWidget* tabel_nou;

	QLineEdit* txt_titlu;
	QLineEdit* txt_gen;
	QLineEdit* txt_an;
	QLineEdit* txt_actor;
	QLineEdit* txt_gen_nou;
	QLineEdit* txt_an_nou;
	QLineEdit* txt_filtrare_titlu;
	QLineEdit* txt_filtrare_an;
	QLineEdit* txt_adauga_random_watchlist;
	QLineEdit* txt_exporta_watchlist;

	QPushButton* buton_adauga;
	QPushButton* buton_sterge;
	QPushButton* buton_modifica;
	QPushButton* buton_cauta;
	QPushButton* buton_filtrare_titlu;
	QPushButton* buton_filtrare_an;
	QPushButton* buton_sorteaza_dupa_titlu;
	QPushButton* buton_sorteaza_dupa_actor;
	QPushButton* buton_sorteaza_dupa_an_gen;
	QPushButton* buton_adauga_in_watchlist;
	QPushButton* buton_adauga_random_in_watchlist;
	QPushButton* buton_goleste_watchlist;
	QPushButton* buton_export_watchlist;
	QPushButton* buton_rapoarte;
	QPushButton* buton_undo;
	QPushButton* buton_exit;
	QVBoxLayout* ly_butoane_dinamice = new QVBoxLayout;
	QWidget* butoane_dinamice = new QWidget;

	QPushButton* new_win;


	void initGUICmps();
	void connectSignalsSlots();
	void reloadList(const std::vector<Film>& filme);
	void clearLayout(QLayout* layout);
	void adauga_film();
	void sterge_film();
	void cauta_film();
	void modifica_film();
	void adauga_butoane(const std::vector<Film>& filme);
	void adauga_gen(const std::vector<Film>& filme);
	void filtrare_titlu();
	void filtrare_an();
	void add_wl();
	void add_rand_wl();
	void goleste_wl();
	void exporta_wl();
	void rapoarte();
	void undo();


public:
	Filme_GUI(Service_Filme& srv) :srv{ srv } {
		initGUICmps();
		connectSignalsSlots();
		reloadList(srv.get_toate_filmele());
		adauga_butoane(srv.get_toate_filmele());
	}

	const QPushButton* get_exit();

};
