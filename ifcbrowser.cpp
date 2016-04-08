#include <iostream>
#include <QRegExp>
#include "nodesmanager.h"
#include "ifcbrowser.h"

IFCBrowser::IFCBrowser(QWidget* parent):
    QPlainTextEdit(parent),
    my_current_mode(normal),
    my_backup_text()

{
    connect(this,SIGNAL(selectionChanged()),this,SLOT(on_selection_changed()));
}


void IFCBrowser::ResetText()
{
    std::vector<QString> display_text = NodesManager::GetText();
    this->clear();
    for(int i=0;i<display_text.size();i++)
        this->appendPlainText(display_text[i]);


}




void IFCBrowser::on_selection_changed()
{

    //checking the current selection

    QString text =this->textCursor().selectedText();
    std::cerr << text.toStdString() << std::endl;
    if(!text.isEmpty())
    {
        //on test si la selection contient un nombre ou un string de la forme #id
        //ou id est un nombre
        QRegExp exp("\\#*\\d+");
        if (exp.exactMatch(text))
        {
            text.replace("#","");
            bool conversion;
            int node_id = text.toInt(&conversion);
            if(conversion&& NodesManager::IsIdValid(node_id))
            {
                std::vector<QString> display_text = NodesManager::GetRelationText(node_id);
                this->clear();
                for(int i=0;i<display_text.size();i++)
                    this->appendPlainText(display_text[i]);


            }


        }

    }

}



void IFCBrowser::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Tab)
    {
        ResetText();
    }
}




