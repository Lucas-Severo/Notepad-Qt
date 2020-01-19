#include "notepad.h"
#include "ui_notepad.h"

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

#include <QtPrintSupport>
#include <QPrintDialog>
#include <QPrinter>

#include <QFont>
#include <QFontDialog>
#include <iomanip>

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

void Notepad::on_actionExit_triggered()
{
    if(currentFile.isEmpty())
        QCoreApplication::quit();
    else{
        QFile file(currentFile);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;
        QString text1 = ui->textEdit->toPlainText();
        QString text = file.readAll();
        file.close();

        if(QString::compare(text1, text)){
            QMessageBox::StandardButton resp;
            resp = QMessageBox::question(this, "Exit", "The file has been modified, are you sure you want to exit?",
                                         QMessageBox::Yes | QMessageBox::No);
            if(resp==QMessageBox::Yes)
                QCoreApplication::exit();
        } else {
            QCoreApplication::exit();
        }
    }
}

void Notepad::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void Notepad::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void Notepad::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void Notepad::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void Notepad::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void Notepad::on_actionSelect_Font_triggered()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if(ok)
        ui->textEdit->setFont(font);
}

void Notepad::on_actionAbout_triggered()
{
    QString attributions[] = {"open icon - Icon made by Freepik from www.flaticon.com",
                              "add icon - Icon made by Kiranshastry from www.flaticon.com",
                              "save icon - Icon made by Freepik from www.flaticon.com",
                              "print icon - Icon made by Those Icons from www.flaticon.com",
                              "copy icon - Icon made by monkik from www.flaticon.com",
                              "paste icon - Icon made by Smashicons from www.flaticon.com",
                              "cut icon - Icon made by Those Icons from www.flaticon.com",
                              "undo icon - Icon made by Pixel perfect from www.flaticon.com",
                              "redo icon -  Icon made by Google from www.flaticon.com",
                              "exit icon - Icon made by Pixel perfect from www.flaticon.com",
                              "font icon - Icon made by Those Icons from www.flaticon.com"};

    QString msg = tr("<b>Application made with QT and C++</b><br/><br/>\
                   <b>Icons Attributions:</b><br/>");

    for(auto attribution: attributions)
    {
        msg += "<hr><i>" + attribution + "</i>" + "<br/>";
    }

    QMessageBox::about(this, "About", msg);
}
