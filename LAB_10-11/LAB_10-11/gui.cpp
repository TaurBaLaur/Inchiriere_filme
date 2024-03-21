#include "gui.h"
#include "domain.h"
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <qpalette.h>
#include <qbrush.h>
#include <qdebug.h>
#include <string>
#include <algorithm>

#include "gui_watchlist.h"

void Filme_GUI::initGUICmps() {
	setLayout(ly_main);

	//lista filme si butoane de sortare
	QWidget* wid_stanga = new QWidget;
	QVBoxLayout* vl = new QVBoxLayout;
	wid_stanga->setLayout(vl);

	lista_filme = new QListWidget;
	vl->addWidget(lista_filme);

	tabel_nou = new QTableWidget;
	vl->addWidget(tabel_nou);

	QWidget* wid_butoane_sub_lista = new QWidget;
	QHBoxLayout* ly_butoane_sl = new QHBoxLayout;
	wid_butoane_sub_lista->setLayout(ly_butoane_sl);

	buton_sorteaza_dupa_titlu = new QPushButton("Sortare dupa titlu");
	ly_butoane_sl->addWidget(buton_sorteaza_dupa_titlu);

	/*btnAddToCos = new QPushButton("Adauga in cos");
	lyBtnsDr->addWidget(btnAddToCos);
	btnAddToCos->setDisabled(true);*/

	buton_sorteaza_dupa_actor = new QPushButton("Sortare dupa actor");
	ly_butoane_sl->addWidget(buton_sorteaza_dupa_actor);

	buton_sorteaza_dupa_an_gen = new QPushButton("Sortare dupa an+gen");
	ly_butoane_sl->addWidget(buton_sorteaza_dupa_an_gen);

	vl->addWidget(wid_butoane_sub_lista);
	ly_main->addWidget(wid_stanga);

	//form pt detalii si alte actiuni
	QWidget* wid_detalii = new QWidget;
	QFormLayout* form_ly_detalii = new QFormLayout;
	wid_detalii->setLayout(form_ly_detalii);

	txt_titlu = new QLineEdit;
	form_ly_detalii->addRow("Titlu", txt_titlu);
	txt_gen = new QLineEdit;
	form_ly_detalii->addRow("Gen", txt_gen);
	txt_an = new QLineEdit;
	form_ly_detalii->addRow("An", txt_an);
	txt_actor = new QLineEdit;
	form_ly_detalii->addRow("Actor principal", txt_actor);
	txt_gen_nou = new QLineEdit;
	form_ly_detalii->addRow("Gen nou", txt_gen_nou);
	txt_an_nou = new QLineEdit;
	form_ly_detalii->addRow("An nou", txt_an_nou);
	txt_filtrare_titlu = new QLineEdit;
	form_ly_detalii->addRow("Filtrare titlu", txt_filtrare_titlu);
	txt_filtrare_an = new QLineEdit;
	form_ly_detalii->addRow("Filtrare an", txt_filtrare_an);
	txt_adauga_random_watchlist = new QLineEdit;
	form_ly_detalii->addRow("Adauga random in watchlist n filme", txt_adauga_random_watchlist);
	txt_exporta_watchlist = new QLineEdit;
	form_ly_detalii->addRow("Exporta watchlist in fisier html", txt_exporta_watchlist);

	buton_adauga = new QPushButton("Adauga film");
	buton_sterge = new QPushButton("Sterge film");
	buton_modifica = new QPushButton("Modifica film");
	buton_cauta = new QPushButton("Cauta film");
	buton_filtrare_titlu = new QPushButton("Filtrare dupa titlu");
	buton_filtrare_an = new QPushButton("Filtrare dupa an");
	buton_adauga_in_watchlist = new QPushButton("Adauga film in watchlist");
	buton_adauga_random_in_watchlist = new QPushButton("Adauga random filme in watchlist");
	buton_goleste_watchlist = new QPushButton("Goleste watchlist");
	buton_export_watchlist = new QPushButton("Exporta watchlist");
	buton_rapoarte = new QPushButton("Rapoarte filme pe ani");
	buton_undo = new QPushButton("Undo");
	buton_exit = new QPushButton("Exit");

	new_win = new QPushButton("fereastra noua");


	form_ly_detalii->addWidget(buton_adauga);
	form_ly_detalii->addWidget(buton_sterge);
	form_ly_detalii->addWidget(buton_modifica);
	form_ly_detalii->addWidget(buton_cauta);
	form_ly_detalii->addWidget(buton_filtrare_titlu);
	form_ly_detalii->addWidget(buton_filtrare_an);
	form_ly_detalii->addWidget(buton_adauga_in_watchlist);
	form_ly_detalii->addWidget(buton_adauga_random_in_watchlist);
	form_ly_detalii->addWidget(buton_goleste_watchlist);
	form_ly_detalii->addWidget(buton_export_watchlist);
	form_ly_detalii->addWidget(buton_rapoarte);
	form_ly_detalii->addWidget(buton_undo);
	form_ly_detalii->addWidget(buton_exit);

	form_ly_detalii->addWidget(new_win);

	ly_main->addWidget(wid_detalii);

	butoane_dinamice->setLayout(ly_butoane_dinamice);
	ly_main->addWidget(butoane_dinamice);

}

void Filme_GUI::connectSignalsSlots() {
	//cand se emite semnalul clicked de pe buton reincarc lista
	QObject::connect(buton_sorteaza_dupa_titlu, &QPushButton::clicked, [&]() {
		reloadList(srv.sortare_titlu());
		});
	//cand se emite semnalul clicked de pe buton reincarc lista
	QObject::connect(buton_sorteaza_dupa_actor, &QPushButton::clicked, [&]() {
		reloadList(srv.sortare_actor_principal());
		});
	//cand se emite semnalul clicked de pe buton reincarc lista
	QObject::connect(buton_sorteaza_dupa_an_gen, &QPushButton::clicked, [&]() {
		reloadList(srv.sortare_an_gen());
		});
	QObject::connect(buton_adauga, &QPushButton::clicked, this, &Filme_GUI::adauga_film);
	QObject::connect(buton_sterge, &QPushButton::clicked, this, &Filme_GUI::sterge_film);
	QObject::connect(buton_modifica, &QPushButton::clicked, this, &Filme_GUI::modifica_film);
	QObject::connect(buton_cauta, &QPushButton::clicked, this, &Filme_GUI::cauta_film);
	QObject::connect(buton_filtrare_titlu, &QPushButton::clicked, this, &Filme_GUI::filtrare_titlu);
	QObject::connect(buton_filtrare_an, &QPushButton::clicked, this, &Filme_GUI::filtrare_an);
	QObject::connect(buton_adauga_in_watchlist, &QPushButton::clicked, this, &Filme_GUI::add_wl);
	QObject::connect(buton_adauga_random_in_watchlist, &QPushButton::clicked, this, &Filme_GUI::add_rand_wl);
	QObject::connect(buton_goleste_watchlist, &QPushButton::clicked, this, &Filme_GUI::goleste_wl);
	QObject::connect(buton_export_watchlist, &QPushButton::clicked, this, &Filme_GUI::exporta_wl);
	QObject::connect(buton_rapoarte, &QPushButton::clicked, this, &Filme_GUI::rapoarte);
	QObject::connect(buton_undo, &QPushButton::clicked, this, &Filme_GUI::undo);


	QObject::connect(new_win, &QPushButton::clicked, [&]() {
		/*auto nw = new Filme_GUI{ this->srv };
		nw->show();*/
		auto nwl = new Watchlist_GUI_CRUD{ this->srv.get_watchlist_obj() };
		nwl->show();
		});


	QObject::connect(lista_filme, &QListWidget::itemSelectionChanged, [&]() {
		auto sel = lista_filme->selectedItems();
		if (sel.isEmpty()) {
			txt_titlu->setText("");
			txt_gen->setText("");
			txt_an->setText("");
			txt_actor->setText("");
			txt_gen_nou->setText("");
			txt_an_nou->setText("");
			txt_filtrare_titlu->setText("");
			txt_filtrare_an->setText("");
			txt_adauga_random_watchlist->setText("");
			txt_exporta_watchlist->setText("");

			//btnAddToCos->setDisabled(true);
		}
		else {
			auto selItem = sel.at(0);
			auto titlu = selItem->text();
			txt_titlu->setText(titlu);
			auto gen = selItem->data(Qt::UserRole).toString();
			txt_gen->setText(gen);
			auto an = selItem->data(Qt::UserRole + 1).toString();
			txt_an->setText(an);
			auto actor = selItem->data(Qt::UserRole + 2).toString();
			txt_actor->setText(actor);
			txt_filtrare_titlu->setText("");
			txt_filtrare_an->setText("");
			txt_adauga_random_watchlist->setText("");
			txt_exporta_watchlist->setText("");
			//btnAddToCos->setEnabled(true);
		}
		});
	/*QObject::connect(btnAddToCos, &QPushButton::clicked, this, [&]() {
		auto sel = lst->selectedItems();
		try {
			if (!sel.isEmpty()) {
				auto selItem = sel.at(0);
				auto species = selItem->text();
				auto type = selItem->data(Qt::UserRole).toString();
				ctr.addToCos(type.toStdString(), species.toStdString());
			}
		}
		catch (const PetException& ex) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
		}
		});*/
}

void Filme_GUI::adauga_film() {
	try {
		srv.adauga_film(txt_titlu->text().toStdString(), txt_gen->text().toStdString(), txt_an->text().toInt(), txt_actor->text().toStdString());
		//adaugaDacaPasare(ctr.find(txtType->text().toStdString(), txtSpecies->text().toStdString()));
		reloadList(srv.get_toate_filmele());
		adauga_gen(srv.get_toate_filmele());
		QMessageBox::information(nullptr, "Info", "Film adaugat cu succes.");
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.get_erori()));
	}
	catch (ValidationException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.get_erori()));
	}
}

void Filme_GUI::sterge_film() {
	try {
		srv.sterge_film(txt_titlu->text().toStdString(), txt_gen->text().toStdString(), txt_an->text().toInt(), txt_actor->text().toStdString());
		//adaugaDacaPasare(ctr.find(txtType->text().toStdString(), txtSpecies->text().toStdString()));
		reloadList(srv.get_toate_filmele());
		adauga_gen(srv.get_toate_filmele());
		QMessageBox::information(nullptr, "Info", "Film sters cu succes.");
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.get_erori()));
	}
}

void Filme_GUI::modifica_film() {
	try {
		srv.modifica_film(txt_titlu->text().toStdString(), txt_gen->text().toStdString(), txt_an->text().toInt(), txt_actor->text().toStdString(), txt_gen_nou->text().toStdString(), txt_an_nou->text().toInt());
		//adaugaDacaPasare(ctr.find(txtType->text().toStdString(), txtSpecies->text().toStdString()));
		reloadList(srv.get_toate_filmele());
		adauga_gen(srv.get_toate_filmele());
		QMessageBox::information(nullptr, "Info", "Film modificat cu succes.");
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.get_erori()));
	}
}

void Filme_GUI::cauta_film()
{
	try {
		Film f = srv.cauta_film(txt_titlu->text().toStdString(), txt_an->text().toInt(), txt_actor->text().toStdString());
		QMessageBox::information(nullptr, "Film cautat", "Titlu: "+ txt_titlu->text() +"\n"+ "Gen: " + QString::fromStdString(f.get_gen()) + "\n" + "An: " + txt_an->text() + "\n" + "Actor principal: " + txt_actor->text());
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.get_erori()));
	}
}

void Filme_GUI::filtrare_titlu()
{
	reloadList(srv.get_toate_filmele());
	vector<Film> filme_filtrate = srv.filtrare_titlu(txt_filtrare_titlu->text().toStdString());
	int j = 0;
	for (int i = 0; i < lista_filme->count(); i++)
	{
		if (j == filme_filtrate.size())
		{
			break;
		}
		else
		{
			QListWidgetItem* item = lista_filme->item(i);
			if (item->text().toStdString() == filme_filtrate[j].get_titlu() && item->data(Qt::UserRole + 1).toInt() == filme_filtrate[j].get_an() && item->data(Qt::UserRole + 2).toString().toStdString() == filme_filtrate[j].get_actor_principal())
			{
				j++;
				item->setData(Qt::BackgroundRole, QBrush{ Qt::yellow, Qt::SolidPattern });
			}
		}
	}
}

void Filme_GUI::filtrare_an()
{
	reloadList(srv.get_toate_filmele());
	vector<Film> filme_filtrate = srv.filtrare_an(txt_filtrare_an->text().toInt());
	int j = 0;
	for (int i = 0; i < lista_filme->count(); i++)
	{
		if (j == filme_filtrate.size())
		{
			break;
		}
		else
		{
			QListWidgetItem* item = lista_filme->item(i);
			if (item->text().toStdString() == filme_filtrate[j].get_titlu() && item->data(Qt::UserRole + 1).toInt() == filme_filtrate[j].get_an() && item->data(Qt::UserRole + 2).toString().toStdString() == filme_filtrate[j].get_actor_principal())
			{
				j++;
				item->setData(Qt::BackgroundRole, QBrush{ Qt::green, Qt::SolidPattern });
			}
		}
	}
}

void Filme_GUI::add_wl()
{
	try
	{
		srv.adauga_in_watchlist(txt_titlu->text().toStdString(), txt_an->text().toInt(), txt_actor->text().toStdString());
		QMessageBox::information(nullptr, "Info", "Filmul a fost adaugat in watchlist.");
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.get_erori()));
	}
}

void Filme_GUI::add_rand_wl()
{
	int cate_au_fost_adaugate = srv.adauga_random_in_watchlist(txt_adauga_random_watchlist->text().toInt());
	QMessageBox::information(nullptr, "Info", "Au fost adaugate " + QString::number(cate_au_fost_adaugate) + " filme in watchlist.");
}

void Filme_GUI::goleste_wl()
{
	srv.goleste_watchlist();
	QMessageBox::information(nullptr, "Info", "Watchlistul a fost golit.");
}

void Filme_GUI::exporta_wl()
{
	try
	{
		srv.export_watchlist_to_html(txt_exporta_watchlist->text().toStdString());
		QMessageBox::information(nullptr, "Info", "Export realizat cu succes.");
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.get_erori()));
	}
}

void Filme_GUI::rapoarte()
{
	unordered_map<string, DTO> rapoarte_ani = srv.rapoarte_filme();
	if (rapoarte_ani.size() == 0)
	{
		QMessageBox::warning(this, "Rapoarte filme pe ani", "Nu sunt filme.");
	}
	else
	{
		string rap_string;
		for (auto rap : rapoarte_ani)
		{
			rap_string += rap.first + ": " + std::to_string(rap.second.get_contor()) + "\n";
		}
		QMessageBox::information(nullptr, "Rapoarte filme", QString::fromStdString(rap_string));
	}
}

void Filme_GUI::undo()
{
	try
	{
		srv.undo();
		reloadList(srv.get_toate_filmele());
		adauga_gen(srv.get_toate_filmele());
		QMessageBox::information(nullptr, "Info", "Undo realizat cu succes.");
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.get_erori()));
	}
}

void Filme_GUI::clearLayout(QLayout* layout) {
	if (layout == NULL)
		return;
	QLayoutItem* item;
	while ((item = layout->takeAt(0))) {
		if (item->layout()) {
			clearLayout(item->layout());
			delete item->layout();
		}
		if (item->widget()) {
			delete item->widget();
		}
		delete item;
	}
}

void Filme_GUI::adauga_gen(const std::vector<Film>& filme) {

	unordered_map<string, int> gen_nr;
	clearLayout(ly_butoane_dinamice);
	for (const Film& f : filme)
	{
		if (gen_nr.find(f.get_gen()) == gen_nr.end())
		{
			string g = f.get_gen();
			unsigned int contor;
			contor = (unsigned int)std::count_if(srv.get_toate_filmele().begin(), srv.get_toate_filmele().end(), [g](const Film& f) {
				return f.get_gen() == g; });
			gen_nr.insert({ f.get_gen() , contor});
			auto buton = new QPushButton{ QString::fromStdString(f.get_gen()) };
			ly_butoane_dinamice->addWidget(buton);
			QObject::connect(buton, &QPushButton::clicked, [this, buton, f, contor]() {
				QMessageBox::information(nullptr, "Info", QString::number(contor));
				delete buton;
				});
		}
	}
}

void Filme_GUI::adauga_butoane(const std::vector<Film>& filme) {
	/*for (const auto& f : filme) {
		adauga_gen(f);
	}*/
	adauga_gen(filme);

}

void Filme_GUI::reloadList(const std::vector<Film>& filme) {
	lista_filme->clear();
	for (const auto& f : filme) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(f.get_titlu()));
		item->setData(Qt::UserRole, QString::fromStdString(f.get_gen()));
		item->setData(Qt::UserRole + 1, QString::number(f.get_an()));
		item->setData(Qt::UserRole + 2, QString::fromStdString(f.get_actor_principal()));
		lista_filme->addItem(item);

	}

	tabel_nou->clear();
	tabel_nou->setRowCount(filme.size());
	tabel_nou->setColumnCount(4);
	int i = 0;
	tabel_nou->setHorizontalHeaderItem(0, new QTableWidgetItem("Titlu"));
	tabel_nou->setHorizontalHeaderItem(1, new QTableWidgetItem("Gen"));
	tabel_nou->setHorizontalHeaderItem(2, new QTableWidgetItem("An"));
	tabel_nou->setHorizontalHeaderItem(3, new QTableWidgetItem("Actor principal"));

	for (const auto& f : filme) {
		tabel_nou->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(f.get_titlu())));
		tabel_nou->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(f.get_gen())));
		tabel_nou->setItem(i, 2, new QTableWidgetItem(QString::number(f.get_an())));
		tabel_nou->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(f.get_actor_principal())));
		i++;

	}

}

const QPushButton* Filme_GUI::get_exit()
{
	return buton_exit;
}