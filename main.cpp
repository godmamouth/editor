/**
 * @file main.cpp
 * @author  Nicolas Cherin <ncherin@socinformatique.fr>
 * @version 0.1 alpha
 *
 * IFCEdit is a tool to edit ifc text files
*/


#include "mainwindow.h"
#include <QApplication>



/**
 * @brief main  entry point of the application
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{




    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
