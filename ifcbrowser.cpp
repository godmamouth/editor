#include <iostream>
#include <QRegExp>
#include "nodesmanager.h"
#include "ifcbrowser.h"

IFCBrowser::IFCBrowser(QWidget* parent):
    QPlainTextEdit(parent),
    my_current_mode(normal),
    my_full_text(),
    last_line(0),
    read_end(true),
    my_timer()



{
    connect(this,SIGNAL(selectionChanged()),this,SLOT(on_selection_changed()));
    connect(&my_timer,SIGNAL(timeout()),this,SLOT(on_time_out()));
}




void IFCBrowser::SetText()
{
    my_full_text = NodesManager::GetText();
    this->clear();
    read_end = false;
    last_line = 0;
    my_timer.start(1);
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

void IFCBrowser::on_time_out()
{
    //add more line
    int i;
    for(i=last_line+1;i<my_full_text.size() && i<last_line+200;i++)
    {
        this->appendPlainText(my_full_text[i]);
    }

    //test si il reste des lignes à lire
    if(i<my_full_text.size())
    {
         my_timer.start(1);
         last_line= i;

    }
    else
    {
        my_timer.stop();
    }
}

void IFCBrowser::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Tab)
    {
        SetText();
    }
}




