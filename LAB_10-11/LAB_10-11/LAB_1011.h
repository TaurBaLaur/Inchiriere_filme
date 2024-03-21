#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LAB_1011.h"

class LAB_1011 : public QMainWindow
{
    Q_OBJECT

public:
    LAB_1011(QWidget *parent = nullptr);
    ~LAB_1011();

private:
    Ui::LAB_1011Class ui;
};
