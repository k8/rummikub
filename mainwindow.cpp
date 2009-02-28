#include "server.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTextEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindowClass)
{
    //ui->setupUi(this);
    Server * server = new Server;
    QTextEdit * console = new QTextEdit(this);
    this->setCentralWidget(console);
    connect(server, SIGNAL(error(QString)), console, SLOT(append(QString)));
    server->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::startServer() {}
void MainWindow::stopServer() {}

void MainWindow::print(const QString & message) {}
