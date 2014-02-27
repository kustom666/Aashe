#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QTextStream>
#include <QPlainTextEdit>
#include <QFont>
#include <QDir>
#include <QTreeWidget>
#include <QTreeWidgetItem>

#include "highlighters/cpphighlighter.h"

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
    void openFolder();
    void openFromTree(QTreeWidgetItem *item, int column);
    void save();

private:
    Ui::MainWindow *ui;
    QFont textFont;
    QString baseDir;
    bool dirOpened;

private:
    void readFile(const QString fileName);
    void saveFile(QString path);
    QPlainTextEdit* currentEditor();

};

#endif // MAINWINDOW_H
