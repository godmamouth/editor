#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QPlainTextEdit>
#include <QString>
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


    void UpdateModification(const QString&str);


private slots:
     void on_actionOpen_IFC_file_triggered();

     void on_actionRemove_nodes_triggered();

private:
    Ui::MainWindow *ui;
    QDockWidget* dock_widget, *modification_dock;
    IFCBrowser* text_browser;
    QPlainTextEdit * modification_browser;

    //IFC4 documentation browser


    //dialogs
    RemoveNodesByTypeWidget* remove_nodes_by_type_widget;

};

#endif // MAINWINDOW_H
