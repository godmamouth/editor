#include <iostream>
#include "nodesmanager.h"
#include "filemanager.h"
#include "removenodesbytypewidget.h"

RemoveNodesByTypeWidget::RemoveNodesByTypeWidget(QWidget* parent):
    QDialog(parent),
    ui(new Ui::RemoveBytypeDialog)
{
    ui->setupUi(this);
}

void RemoveNodesByTypeWidget::on_buttonBox_accepted()
{

    QString type_to_remove = ui->ifcclass->text();
    int n =NodesManager::RemoveNodeByIFCClass(type_to_remove);
    std::cerr << "Removed " << n << " nodes" << std::endl;
    FileManager::SaveFile("C:/Users/ncherin/Documents/projects/test/saved_temp.ifc");
    this->close();


}
