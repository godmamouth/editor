#ifndef MODIFICATION_H
#define MODIFICATION_H

#include <QString>
#include "node.h"

/**
 * @brief The Modification class store the previous state of a node, the type of modification done and a comment
 */
class Modification
{
public:
    enum ModificationTag{None,Modified,Deleted};

    /**
     * @brief Modification
     */
    Modification();

    Modification(Node* node, ModificationTag tag,QString comment);


    /**
     * @brief Print
     * @return
     */
    QString Print() const;



    Node* my_node;
    ModificationTag my_tag;
    QString my_comment;

};

#endif // MODIFICATION_H
