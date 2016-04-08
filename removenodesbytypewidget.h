#ifndef REMOVENODESBYTYPEWIDGET_H
#define REMOVENODESBYTYPEWIDGET_H

#include <QWidget>
#include "ui_removenodesbytypewidget.h"
class RemoveNodesByTypeWidget : public QDialog
{
    Q_OBJECT
public:
    RemoveNodesByTypeWidget(QWidget* parent=0);


private slots:
    void on_buttonBox_accepted();

private:
    Ui::RemoveBytypeDialog * ui;
};

#endif // REMOVENODESBYTYPEWIDGET_H
