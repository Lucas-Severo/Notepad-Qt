#include "notepad.h"
#include "ui_notepad.h"

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

#include <QtPrintSupport>
#include <QPrintDialog>
#include <QPrinter>

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
    setWindowTitle("Notepad");
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
    setWindowTitle(filename);
    currentFile = filename;

    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
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

    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void Notepad::on_actionsave_as_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "save as");
    currentFile = fileName;

    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "Information", "cannot save the file: " + file.errorString());
        return;
    }

    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;

    file.close();
}


void Notepad::on_actionPrint_triggered()
{
    QPrinter printer;
    QPrintDialog dialog(&printer, this);
    if(dialog.exec() == QDialog::Rejected)
        return;
    ui->textEdit->print(&printer);
}
