#include <iostream>

#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QScrollBar>
#include <vector>
#include "nodesmanager.h"
#include "filemanager.h"
#include "progressbarmanager.h"
#include "ifceditmanager.h"
#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    remove_nodes_by_type_widget()
{
    ui->setupUi(this);


    //Load the file manager
    FileManager::Initialize();
    //Load the node manager
    NodesManager::Initialize();
    //load the modification manager
    IFCEditManager::Initialize(this);

    //Loadn the progress bar
    ProgressBarManager::Initialize(this);



    //IFC text browser
    dock_widget = new QDockWidget(this);
    this->addDockWidget(Qt::TopDockWidgetArea,dock_widget);
    text_browser = new IFCBrowser(dock_widget);
    text_browser->setGeometry(text_browser->geometry().x(),text_browser->geometry().y()
                              ,960,text_browser->geometry().height());

    dock_widget->setWidget(text_browser);
    text_browser->addScrollBarWidget(new QScrollBar(text_browser),Qt::AlignRight);

    //
    remove_nodes_by_type_widget = new RemoveNodesByTypeWidget();


    //modification broser
    modification_dock = new QDockWidget(this);
    this->addDockWidget(Qt::TopDockWidgetArea,modification_dock);
    modification_browser = new QPlainTextEdit();
    modification_dock->setWidget(modification_browser);




}

MainWindow::~MainWindow()
{
    delete ui;
    delete dock_widget;
    delete text_browser;

    //Unload the managers
    NodesManager::Close();
    FileManager::Close();
    IFCEditManager::Close();
    ProgressBarManager::Close();
}


void MainWindow::UpdateModification(const QString&str)
{
    modification_browser->setPlainText(str);
}

void MainWindow::on_actionOpen_IFC_file_triggered()
{
    QString file_name =  QFileDialog::getOpenFileName(this);


    int n_line = FileManager::OpenFile(file_name);
    ProgressBarManager::Hide();
    std::cerr<< "Nombre de lignes :" << n_line;
    if(n_line>0)
    {
            text_browser->SetText();
    }


}


void MainWindow::on_actionRemove_nodes_triggered()
{
    remove_nodes_by_type_widget->show();
}
