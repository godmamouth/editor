#include "modification.h"

Modification::Modification():
    my_node(),
    my_tag(ModificationTag::None),
    my_comment("Empty Modification")
{

}

Modification::Modification(Node* node, ModificationTag tag,QString comment):
    my_node(node),
    my_tag(tag),
    my_comment(comment)
{

}



 QString Modification::Print() const
 {
    QString mod;
    QString str_id  =  QString::number(my_node->GetNodeId());
    QString str_tag;
    switch(my_tag)
    {
        case None:
            str_tag = "None";
            break;
    case Modified:
            str_tag = "Modified";
            break;
    case Deleted:
            str_tag = "Deleted";
        break;
    }

    mod = str_id + " | "+ str_tag + " | " + my_comment + "\n";
    return mod;
 }
