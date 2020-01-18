#include "notepad.h"
#include "ui_notepad.h"

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

Notepad::Notepad(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Notepad)
{
    ui->setupUi(this);

    this->setCentralWidget(ui->textEdit);
}

Notepad::~Notepad()
{
    delete ui;
}


void Notepad::on_actionnew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(currentFile);
}

void Notepad::on_actionopen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::information(this, "Information", "cannot open file: ", file.errorString());
        return;
    }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
}

void Notepad::on_actionsave_triggered()
{
    QString fileName;

    if(currentFile.isEmpty())
    {
        fileName = QFileDialog::getSaveFileName(this, "save");
        currentFile = fileName;
    } else {
        fileName = currentFile;
    }

    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::information(this, "Information", "Cannot save the file: ", file.errorString());
        return;
    }

    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}















