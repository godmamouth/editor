#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QScrollBar>
#include <vector>
#include "nodesmanager.h"
#include "filemanager.h"

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



    dock_widget = new QDockWidget(this);
    this->addDockWidget(Qt::TopDockWidgetArea,dock_widget);
    text_browser = new IFCBrowser(dock_widget);
    text_browser->setGeometry(text_browser->geometry().x(),text_browser->geometry().y()
                              ,960,text_browser->geometry().height());

    dock_widget->setWidget(text_browser);
    text_browser->addScrollBarWidget(new QScrollBar(text_browser),Qt::AlignRight);

    remove_nodes_by_type_widget = new RemoveNodesByTypeWidget();




}

MainWindow::~MainWindow()
{
    delete ui;
    delete dock_widget;
    delete text_browser;

    //Unload the nodes manager
    NodesManager::Close();

    FileManager::Close();
}

void MainWindow::on_actionOpen_IFC_file_triggered()
{
    QString file_name =  QFileDialog::getOpenFileName(this);

    int n_line = FileManager::OpenFile(file_name);
    std::cerr<< "Nombre de lignes :" << n_line;
    if(n_line>0)
    {
        std::vector<QString> text =  NodesManager::GetText();
        for(int i=0;i<text.size();i++)
            text_browser->appendPlainText(text[i]);

    }


}


void MainWindow::on_actionRemove_nodes_triggered()
{
    remove_nodes_by_type_widget->show();
}
