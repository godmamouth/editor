#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QTextBrowser>
#include <QPlainTextEdit>
#include "removenodesbytypewidget.h"
#include "ifcbrowser.h"
#include "node.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
     void on_actionOpen_IFC_file_triggered();

     void on_actionRemove_nodes_triggered();

private:
    Ui::MainWindow *ui;
    QDockWidget* dock_widget;
    IFCBrowser* text_browser;

    //dialogs
    RemoveNodesByTypeWidget* remove_nodes_by_type_widget;

};

#endif // MAINWINDOW_H
