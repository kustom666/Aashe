#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    textFont(),
    dirOpened(false)
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
    QObject::connect(ui->actionOpen_Folder, SIGNAL(triggered()), this, SLOT(openFolder()));
    QObject::connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(save()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile()
{
    QPlainTextEdit *editor = new QPlainTextEdit;
    editor->setFont(textFont);
    QPalette p = editor->palette();
    p.setColor(QPalette::Text, QColor(248,248,242));
    editor->setPalette(p);

    // Setting the tab with to 4 spaces
    QFontMetrics metrics(textFont);
    editor->setTabStopWidth(4*metrics.width(' '));

    editor->setStyleSheet("background-color: #272822;");

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open a file"), QString(), tr("All files (*.*)"));
    QFile fileBuffer(fileName);
    if(!fileBuffer.open(QFile::ReadOnly))
    {
        QMessageBox::warning(this, tr("Aashe | Error"), tr("Aashe could not read the requested file %1\n%2").arg(fileName).arg(fileBuffer.errorString()));
    }

    QTextStream inStream(&fileBuffer);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    editor->setPlainText(inStream.readAll());
    QApplication::restoreOverrideCursor();

    editor->setDocumentTitle(fileName);

    if(fileName.endsWith(".cpp") || fileName.endsWith(".h") || fileName.endsWith(".hpp") || fileName.endsWith(".cc"))
    {
        CppHighlighter* cppCodeHigh = new CppHighlighter(editor->document());
        cppCodeHigh->setParent(editor->document());
    }

    ui->textTabs->addTab(editor, fileName);
    ui->textTabs->setCurrentIndex(ui->textTabs->count()-1);
}

void MainWindow::newFile()
{
    QPlainTextEdit *editor = new QPlainTextEdit;
    ui->textTabs->addTab(editor, tr("New file"));
}

void MainWindow::closeTab(int index)
{
    ui->textTabs->removeTab(index);
}

void MainWindow::openFolder()
{
    // We need to get the folder's path
    QString path = QFileDialog::getExistingDirectory(this, tr("Open a folder"), ".", QFileDialog::ShowDirsOnly);
    baseDir = path;
    QDir selectedDir(path);
    QStringList dirContent = selectedDir.entryList(QDir::Files);

    // We need to clear the previous dir, if any
    if(dirOpened)
    {
        QLayoutItem *child = ui->horizontalLayout->takeAt(0);
        delete child;
    }

    // Then create our folder tree
    QTreeWidget *dirTree = new QTreeWidget(this);
    dirTree->setColumnCount(1);
    QList<QTreeWidgetItem *> items;

    // We populate it with the folder's content
    foreach(const QString &content, dirContent)
    {
        if(content.compare(".") != 0 && content.compare("..") != 0 )
        {
            items.append(new QTreeWidgetItem(dirTree, QStringList(content)));
        }
    }

    dirTree->insertTopLevelItems(0, items);
    dirTree->setMaximumWidth(200);
    dirTree->setHeaderLabel(baseDir);
    dirTree->header()->setStyleSheet("background: #E6E6E6; color: #000000");
    dirTree->setStyleSheet("background-color: #E6E6E6; color: #000000");

    // Connect it to open the file clicked
    QObject::connect(dirTree, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(openFromTree(QTreeWidgetItem*, int)));

    // And insert the new widget in the view
    ui->horizontalLayout->insertWidget(0, dirTree);
    dirOpened = true;
}

void MainWindow::openFromTree(QTreeWidgetItem *item, int column)
{
    QPlainTextEdit *editor = new QPlainTextEdit;
    editor->setFont(textFont);

    // Setting the tab with to 4 spaces
    QFontMetrics metrics(textFont);
    editor->setTabStopWidth(4*metrics.width(' '));

    editor->setStyleSheet("background-color: #272822;");

    QPalette p = editor->palette();
    p.setColor(QPalette::Text, QColor(248,248,242));
    editor->setPalette(p);

    QString fileName = baseDir + "/" + item->text(column);
    QFile fileBuffer(fileName);
    if(!fileBuffer.open(QFile::ReadOnly))
    {
        QMessageBox::warning(this, tr("Aashe | Error"), tr("Aashe could not read the requested file %1\n%2").arg(fileName).arg(fileBuffer.errorString()));
    }

    QTextStream inStream(&fileBuffer);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    editor->setPlainText(inStream.readAll());
    QApplication::restoreOverrideCursor();

    editor->setDocumentTitle(fileName);

    if(fileName.endsWith(".cpp") || fileName.endsWith(".h") || fileName.endsWith(".hpp") || fileName.endsWith(".cc"))
    {
        CppHighlighter* cppCodeHigh = new CppHighlighter(editor->document());
        cppCodeHigh->setParent(editor->document());
    }
    ui->textTabs->addTab(editor, fileName);
    ui->textTabs->setCurrentIndex(ui->textTabs->count()-1);
}

void MainWindow::save()
{
    if(currentEditor()->documentTitle().isEmpty())
    {
        QString path = QFileDialog::getSaveFileName(this, tr("Save File"));
        saveFile(path);
    }
    else
    {
        saveFile(currentEditor()->documentTitle());
    }
}

void MainWindow::saveFile(QString path)
{
    QFile fileBuffer(path);
    if(!fileBuffer.open(QFile::WriteOnly))
    {
        QMessageBox::warning(this, tr("Aashe | Error"), tr("Aashe could not write the requested file %1\n%2").arg(path).arg(fileBuffer.errorString()));
    }
    QTextStream outStream(&fileBuffer);
    outStream << currentEditor()->toPlainText();
    fileBuffer.close();

}

QPlainTextEdit* MainWindow::currentEditor()
{
    return ui->textTabs->currentWidget()->findChild<QPlainTextEdit *>();
}
