#include "mainwindow.h"
#include "nodesmanager.h"
#include "ifceditmanager.h"

IFCEditManager * IFCEditManager::my_only_instance = 0;



void IFCEditManager::Initialize(MainWindow* parent)
{
    if(!my_only_instance)
    {
        my_only_instance = new IFCEditManager();
        my_only_instance->main_window_ptr = parent;
    }
}


void IFCEditManager::Close()
{
    if(my_only_instance)
        delete my_only_instance;
}


void IFCEditManager::SetMaximalStageRecord(int n)
{
    //verify that n is large enough
    if(n<5)
        n = 5;

    //test if we have more records than n
    if(my_only_instance->my_maximal_stage>n)
    {
        //clear the last stage
        while(my_only_instance->my_records.size()>n)
        {
            //clean the duplicate node
            my_only_instance->RemoveAndCleanLastStage();
        }
    }

    my_only_instance->my_maximal_stage = n;
}


void IFCEditManager::RecordNode(int ifc_id,Modification::ModificationTag tag,const QString &comment)
{
    //get the current QMap

    if(my_only_instance->my_records.empty())
    {
        //if the there is no reccords we push the first stage
        AdvanceStage();
    }

    QMap<int,Modification*> * map = my_only_instance->my_records.front();
    //We duplicate the node
    Node * node = NodesManager::GetNodeByIFCId(ifc_id);

    Node * n2= new Node(*node);

    Modification * mod =  new Modification(n2,tag,comment);

    //insert the modification into the map
    map->insert(ifc_id,mod);
}


void IFCEditManager::AdvanceStage()
{
    QMap<int,Modification*> *map = new QMap<int,Modification*>();
    my_only_instance->my_records.push_front(map);

    //verify that we don't exceed max stage
    if(my_only_instance->my_records.size()>my_only_instance->my_maximal_stage)
        my_only_instance->RemoveAndCleanLastStage();

}

QString IFCEditManager::PrintCurrentStageModifications()
{
    QString mod;
    QMap<int,Modification*>* map = my_only_instance->my_records.front();
    for(QMap<int,Modification*>::Iterator it=map->begin();it !=map->end();++it)
    {
            Modification * modification =  it.value();
            mod += modification->Print();
    }

    my_only_instance->main_window_ptr->UpdateModification(mod);
    return mod;
}



IFCEditManager::IFCEditManager():
    my_maximal_stage(15),
    my_records()
{

}

IFCEditManager::~IFCEditManager()
{
    while(!my_records.empty())
    {
        RemoveAndCleanLastStage();
    }
}


void IFCEditManager::RemoveAndCleanLastStage()
{
    QMap<int,Modification*>* map = my_records.back();
    //clean the map
    for(QMap<int,Modification*>::Iterator it=map->begin();it !=map->end();++it)
    {
        delete  (*it)->my_node;
        Modification * mod = it.value();
        delete  mod;
    }

    delete map;
    my_records.pop_back();
}



