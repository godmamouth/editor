#include <QStringList>
#include <iostream>
#include "ifceditmanager.h"
#include "nodesmanager.h"


NodesManager* NodesManager::my_only_instance=0;

void NodesManager::Initialize()
{
    if(!my_only_instance)
        my_only_instance = new NodesManager();

    else
        std::cerr << "Warning! NodesManager::Initialize()  called several times !" << std::endl;
}


void NodesManager::Close()
{
    if(my_only_instance)
        delete my_only_instance;

}


bool NodesManager::AddNode(const QString &line)
{
    //Break  the line in 3
    // (id)  IFCClass   references

    //1 extract the node id;
    QStringList step_1_list = line.split('=');
    if(step_1_list.size()!=2)
        return false;

    QString left_str = step_1_list.at(0);
    left_str.replace("#","");
    bool conversion;
    int node_id = left_str.toInt(&conversion);
    if(!conversion)
        return false;

    //2 extract the IFCClass
    QString step_2_str = step_1_list.at(1);
    //split along (
    QStringList step_2_list = step_2_str.split('(');
    if(step_2_list.size()<2)
        return false;
    QString ifc_class = step_2_list.at(0);


    //3 extract the link(s) to other node(s)
    //Utiliser QRegularExpression plutot ?

    std::vector<int> links;
    int k;
    bool find_id = false;
    for(int i=0;i<step_2_str.size();i++)
    {
        if(!find_id)
        {
            if(step_2_str.at(i)=='#')
            {
                find_id= true;
                k = i+1;
            }
        }
        else
        {
            if(step_2_str.at(i)==',' || step_2_str.at(i)==')' || step_2_str.at(i)=='(')
            {
                find_id = false;
                QStringRef  sub_str(&step_2_str,k,i-k);
                int node_link_id = sub_str.toInt(&conversion);
                if(!conversion)
                    return false;
                links.push_back(node_link_id);

            }
        }

    }

    //Add the node
    Node * node = new Node(node_id,ifc_class,line,links);
    //Add the node to the hash table
    my_only_instance->my_nodes.insert(node_id,node);

    return true;
}




bool NodesManager::BuildRelations()
{
    std::cerr <<  "Building relations... Nodes size : "<< my_only_instance->my_nodes.size() << std::endl;
    for(QMap<int,Node*>::iterator it = my_only_instance->my_nodes.begin();it!=my_only_instance->my_nodes.end();++it)
    {
        if(!it.value()->BuildRelations())
            return false;
    }
    return true;
}



std::vector<QString> NodesManager::GetText()
{
    std::vector<QString> text;
    for(QMap<int,Node*>::iterator it = my_only_instance->my_nodes.begin();it!=my_only_instance->my_nodes.end();++it)
    {
        text.push_back(it.value()->GetText());
    }

    return text;
}

std::vector<QString> NodesManager::GetRelationText(int ifc_id)
{
    std::vector<QString> text;
    Node * node = my_only_instance->my_nodes[ifc_id];
    if(node)
    {
        std::vector<int> linked_by = node->GetLinkedBy();
        std::vector<int> link_to = node->GetLinkTo();

        for(int i=0;i<linked_by.size();i++)
        {
            text.push_back(my_only_instance->my_nodes[linked_by[i]]->GetText());
        }
        text.push_back(node->GetText());
        for(int i=0;i<link_to.size();i++)
        {
            text.push_back(my_only_instance->my_nodes[link_to[i]]->GetText());
        }
    }
    return text;
}

int NodesManager::RemoveNodeByID(int node_id)
{
    return 0;
}

int NodesManager::RemoveNodeByIFCClass(QString node_class)
{
    //create a new stage in the ifceditmanager
    IFCEditManager::AdvanceStage();


    QStack<int> remove_stack;
    //1. Find the nodes to delete
    for(QMap<int,Node*>::iterator it = my_only_instance->my_nodes.begin();it!=my_only_instance->my_nodes.end();++it)
    {
        if(it.value()->GetNodeName() == node_class)
            remove_stack.push(it.key());
    }

    if(remove_stack.isEmpty())
        return 0;

    //2.
    return my_only_instance->DeleteStack(remove_stack);

}


Node* NodesManager::GetNodeByIFCId(int ifc_id)
{
    return my_only_instance->my_nodes[ifc_id];
}


bool NodesManager::IsIdValid(int ifc_id)
{
    return my_only_instance->my_nodes.contains(ifc_id);
}

Node* NodesManager::Duplicate(int ifc_id)
{
    if(IsIdValid(ifc_id))
    {
        Node * node =GetNodeByIFCId(ifc_id);
        Node * n2 = new Node(*node);
        return n2;
    }
    else
    {
        return nullptr;
    }
}


NodesManager::NodesManager():
    my_nodes()

{

}

NodesManager::~NodesManager()
{
    for(int i=0;i<my_nodes.size();i++)
    {
        delete my_nodes[i];
    }
}


int NodesManager::DeleteStack(QStack<int> &stack)
{
    int n=0;
    while(!stack.empty())
    {
        //get the top element
        int node_id =  stack.pop();
        Node* node = my_nodes[node_id];
        if(node)
        {

            //remove the node from the hash
            std::vector<int> modified_nodes = DeleteNode(node_id);
            n++;
            //for the moment we will delete ALL the modified nodes
            for(int i=0;i<modified_nodes.size();i++)
            {
                stack.push(modified_nodes.at(i));
            }
        }
    }


    IFCEditManager::PrintCurrentStageModifications();
    //return the number of deleted nodes
    return n;
}


std::vector<int> NodesManager::DeleteNode(int ifc_id)
{

    Node *node =  my_nodes[ifc_id];

    //record the node prior delete
    IFCEditManager::RecordNode(ifc_id,Modification::Deleted,node->GetNodeName());

    //prepare the node to be deleted
    std::vector<int> modified = node->PrepareDeletion();

    //erase the node of the hash
    my_nodes.remove(ifc_id);

    //delete the node
    delete node;

    return modified;
}

