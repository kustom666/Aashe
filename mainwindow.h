#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QTextStream>

#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexercpp.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void openFile();
    void closeTab(int index);
    void newFile();

private:
    Ui::MainWindow *ui;

private:
    void readFile(const QString fileName);
};

#endif // MAINWINDOW_H
