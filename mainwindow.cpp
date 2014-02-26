#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textTabs->clear();
    QObject::connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
    QObject::connect(ui->textTabs, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
    QObject::connect(ui->actionNew_file, SIGNAL(triggered()), this, SLOT(newFile()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile()
{
    QsciScintilla* textEdit = new QsciScintilla(ui->textTabs);
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open a file"), QString(), tr("All files (*.*)"));
    QFile fileBuffer(fileName);
    if(!fileBuffer.open(QFile::ReadOnly))
    {
        QMessageBox::warning(this, tr("Aashe | Error"), tr("Aashe could not read the requested file %1\n%2").arg(fileName).arg(fileBuffer.errorString()));
    }

    QTextStream inStream(&fileBuffer);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    textEdit->setText(inStream.readAll());
    QApplication::restoreOverrideCursor();

    if(fileName.endsWith(".cpp") || fileName.endsWith(".h") || fileName.endsWith(".hpp") || fileName.endsWith(".cc"))
    {
        QsciLexerCPP* lexerCpp = new QsciLexerCPP();
        textEdit->setLexer(lexerCpp);
    }
    ui->textTabs->addTab(textEdit, fileName);
    ui->textTabs->setCurrentIndex(ui->textTabs->count()-1);
}

void MainWindow::newFile()
{
    QsciScintilla* textEdit = new QsciScintilla(ui->textTabs);
    ui->textTabs->addTab(textEdit, tr("New file"));
}

void MainWindow::closeTab(int index)
{
    ui->textTabs->removeTab(index);
}

