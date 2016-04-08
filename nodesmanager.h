#ifndef NODESMANAGER_H
#define NODESMANAGER_H

#include <QString>
#include <vector>
#include <QHash>
#include <QStack>
#include <QMap>
#include "node.h"
/**
 * @brief The NodesManager class
 */
class NodesManager
{

public:
    /**
     * @brief Initialize
     */
    static void Initialize();

    /**
     * @brief Close
     */
    static void Close();


    /**
     * @brief AddNode Add a node to the node manager with no relationship
     * @param line
     * @return Return false if the line is not well formated
     */
    static bool AddNode(const QString &line);

    /**
     * @brief BuildRelations Build the relationships beetween nodes
     * @return Return false if one node doesn't exist
     */
    static bool BuildRelations();


    /**
     * @brief GetText Get all node text to display in the textbrowser
     * @return a vector of QString which contains all the line to display
     */
    static std::vector<QString> GetText();


    /**
     * @brief GetRelationText
     * @param ifc_id
     * @return
     */
    static std::vector<QString> GetRelationText(int ifc_id);

    /**
     * @brief RemoveNodeByID remove the node id specified, it can lead to removing several other nodes
     * @param node_id the node to remove
     * @return the number of nodes removed
     */
    static int RemoveNodeByID(int node_id);

    /**
     * @brief RemoveNodeByIFCClass Remove all the nodes of a certain type,
     * for exemple RemoveNodeByIFCClass("IFCPROPERTYSET");  will remove all the IFCPROPERTYSET
     * @param node_class node class to remove (in  upper case)
     * @return the number of nodes removed
     */
    static int RemoveNodeByIFCClass(QString node_class);

    /**
     * @brief GetNodeByIFCId
     * @param ifc_id
     * @return
     */
    static Node* GetNodeByIFCId(int ifc_id);

    /**
     * @brief IsIdValid
     * @param ifc_id
     * @return
     */
    static bool IsIdValid(int ifc_id);




private:
    /**
     * @brief NodesManager  private constructor
     */
    NodesManager();
    ~NodesManager();

    /**
     * @brief DeleteStack  Delete all the nodes of the stack
     * @param stack
     * @return
     */
    int DeleteStack(QStack<int>&stack);


    /**
     * @brief DeleteNode
     * @param ifc_id
     * @return
     */
    std::vector<int> DeleteNode(int ifc_id);

    /**
     * @brief Sort the QHash my_nodes containing the nodes
     */
    void Sort();

    /**
     * @brief my_only_instance  ptr to the only instance of the NodesManager
     */
    static NodesManager* my_only_instance;

    /**
     * @brief my_nodes
     */
    QMap<int,Node*> my_nodes;


};

#endif // NODESMANAGER_H
