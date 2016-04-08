#include <algorithm>
#include "nodesmanager.h"
#include "node.h"

Node::Node(int ifc_id,QString node_name,QString text,const std::vector<int>& relations):
    my_id(ifc_id),
    link_to(),
    linked_by(),
    my_node_name(node_name),
    my_text(text),
    my_relations(relations)
{

}

Node::~Node()
{

}


bool Node::BuildRelations()
{
    for(int i=0;i<my_relations.size();i++)
    {
        Node* temp = NodesManager::GetNodeByIFCId(my_relations.at(i));
        if(!temp)
            return false;
        //Set the relation
        link_to.push_back(my_relations.at(i));
        temp->AddLinkedBy(my_id);
    }
    return true;
}



std::vector<int> Node::PrepareDeletion()
{
    std::vector<int> modified = linked_by;
    //delete the reference of this node in the linked by node
    for(int i=0;i<linked_by.size();i++)
    {
        Node * ref_node  = NodesManager::GetNodeByIFCId(linked_by.at(i));
        //erase my id  in the node referencing this node
        ref_node->link_to.erase(std::remove(ref_node->link_to.begin(), ref_node->link_to.end(), my_id), ref_node->link_to.end());

    }

    for(int i=0;i<link_to.size();i++)
    {
        Node * ref_node  = NodesManager::GetNodeByIFCId(link_to.at(i));
        //erase my id  in the node referenced by this node
        ref_node->linked_by.erase(std::remove(ref_node->linked_by.begin(), ref_node->linked_by.end(), my_id), ref_node->linked_by.end());
    }

    return modified;
}
