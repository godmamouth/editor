#include <QFile>
#include <QTextStream>
#include <QString>
#include <vector>
#include <iostream>
#include "nodesmanager.h"
#include "filemanager.h"




FileManager* FileManager::my_only_instance=0;


void FileManager::Initialize()
{
    if(!my_only_instance)
        my_only_instance = new FileManager();
}

void FileManager::Close()
{
    if(my_only_instance)
        delete my_only_instance;
}



int FileManager::OpenFile(const QString &path)
{
   return my_only_instance->LoadIfcFile(path);
}

int FileManager::SaveFile(const QString &path)
{
    return my_only_instance->SaveIfcFile(path);
}


FileManager::FileManager()
{
}




int  FileManager::LoadIfcFile(const QString &path)
{
    //compteur de lignes
    int cpt =0;
    //open the file
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly))
        return -1;

    //test if file is empty
    if(file.atEnd())
        return -1;

    //load begining of the file
    QString line;
    while(!file.atEnd())
    {
         line = file.readLine();
         cpt++;
         //remove white spaces
         line.replace(" ","");
         if(line.isEmpty())
             continue;

         if(line.at(0)=='#')
             break;
         else
            top_data = top_data +line +"\n";

    }
    if(file.atEnd())
        return -1;


    //load core of the file
    if(!NodesManager::AddNode(line))
        return -3;


    while(!file.atEnd())
    {
        line = file.readLine();

        cpt++;
        //remove white spaces
        line.replace(" ","");
        if(line.at(0)==' ')
            continue;

        if(line.at(0).toLatin1()=='#')
        {
            if(!NodesManager::AddNode(line))
                return -3;
        }
        else
        {
            break;
        }
    }

    if(file.atEnd())
        return -1;

    //Build the nodes relationships
    if(!NodesManager::BuildRelations())
           return -2;

    //Load the end of the file
    while(!file.atEnd())
    {
        line = file.readLine();
        cpt++;
        //remove white spaces
        line.replace(" ","");
        bottom_data+= line;
        bottom_data+= "\n";
    }
    file.close();
    return cpt;
}


//Save the current ifc file
int FileManager::SaveIfcFile(const QString &path)
{
    std::vector<QString> str  = NodesManager::GetText();
    QFile file(path);
    if(!file.open(QIODevice::WriteOnly))
        return -1;
     QTextStream stream( &file );

    stream << top_data;
    for(int i=0;i<str.size();i++)
    {
        stream << str.at(i);
    }
    stream << bottom_data;
    file.close();
    return 1;
}
