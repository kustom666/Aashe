#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    textFont()
{
    ui->setupUi(this);
    ui->textTabs->clear();

    textFont.setFamily("Droid Sans Mono");
    textFont.setStyleHint(QFont::Monospace);
    textFont.setFixedPitch(true);
    textFont.setPointSize(8);

    // Connexions
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
    QTextEdit *editor = new QTextEdit;
    editor->setFont(textFont);
    QFontMetrics metrics(textFont);
    editor->setTabStopWidth(4*metrics.width(' '));
    editor->setStyleSheet("background-color: #272822;");
    editor->setTextColor(QColor(248,248,242));
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open a file"), QString(), tr("All files (*.*)"));
    QFile fileBuffer(fileName);
    if(!fileBuffer.open(QFile::ReadOnly))
    {
        QMessageBox::warning(this, tr("Aashe | Error"), tr("Aashe could not read the requested file %1\n%2").arg(fileName).arg(fileBuffer.errorString()));
    }

    QTextStream inStream(&fileBuffer);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    editor->setText(inStream.readAll());
    QApplication::restoreOverrideCursor();

    if(fileName.endsWith(".cpp") || fileName.endsWith(".h") || fileName.endsWith(".hpp") || fileName.endsWith(".cc"))
    {
        CppHighlighter* cppCodeHigh = new CppHighlighter(editor->document());
    }
    ui->textTabs->addTab(editor, fileName);
    ui->textTabs->setCurrentIndex(ui->textTabs->count()-1);
}

void MainWindow::newFile()
{
    QTextEdit *editor = new QTextEdit;
    ui->textTabs->addTab(editor, tr("New file"));
}

void MainWindow::closeTab(int index)
{
    ui->textTabs->removeTab(index);
}

