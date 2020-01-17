#include "notepad.h"
#include "ui_notepad.h"

Notepad::Notepad(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Notepad)
{
    ui->setupUi(this);

    this->setCentralWidget(ui->plainTextEdit);
}

Notepad::~Notepad()
{
    delete ui;
}

