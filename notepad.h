#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Notepad; }
QT_END_NAMESPACE

class Notepad : public QMainWindow
{
    Q_OBJECT

public:
    Notepad(QWidget *parent = nullptr);
    ~Notepad();

private slots:
    void on_actionnew_triggered();

    void on_actionopen_triggered();

    void on_actionsave_triggered();

    void on_actionsave_as_triggered();

    void on_actionPrint_triggered();

    void on_actionExit_triggered();

    void on_actionCopy_triggered();

    void on_actionCut_triggered();

    void on_actionPaste_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionSelect_Font_triggered();

    void on_actionAbout_triggered();

private:
    Ui::Notepad *ui;
    QString currentFile;
};
#endif // NOTEPAD_H
