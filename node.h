/**
 * @file node.h
 * @author  Nicolas Cherin <ncherin@socinformatique.fr>
 * @version 1.0
 *
*/


#ifndef NODE_H
#define NODE_H



#include <vector>
#include <string>

#include <QString>

class Node
{
public:
    /**
     * @brief Constructor
     *
     * @param ifc_id IFC id of the element
     * @param node_name is the name of the element (e.g. IfcColumn, IfcWall, etc.)
     * @param text A line of the ifc document (transformed)
     * @param relations
     */
    Node(int ifc_id,QString node_name,QString text,const std::vector<int>& relations);

    ~Node();


    /**
     * @brief AddLinkTo
     * @param node
     */
    inline void AddLinkTo(int node_id){link_to.push_back(node_id);}

    /**
     * @brief AddLinkedBy
     * @param node
     */
    inline void AddLinkedBy(int node_id){linked_by.push_back(node_id);}

    /**
     * @brief GetLinkTo
     * @return
     */
    inline std::vector<int> GetLinkTo() const {return link_to;}

    /**
     * @brief GetLinkedBy
     * @return
     */
    inline std::vector<int> GetLinkedBy() const {return linked_by;}


    /**
     * @brief GetNodeId
     * @return
     */
    inline int GetNodeId() const{return my_id;}

    /**
     * @brief GetNodeName
     * @return
     */
    inline QString GetNodeName() const{return my_node_name;}

    /**
     * @brief SetNodeName
     * @param str
     * @return
     */
    inline QString SetNodeName(const QString & str){my_node_name = str;}


    /**
     * @brief GetText
     * @return
     */
    inline QString GetText()const {return my_text;}


    /**
     * @brief BuildRelations
     * @return
     */
    bool BuildRelations();

    /**
     * @brief PrepareDeletion prepare the node to be safely delete
     */
    std::vector<int> PrepareDeletion();

private:

    /**
     * @brief my_id
     */
    int my_id;
    /**
     * @brief link_to Contains the links to the node linked by this node
     * exemple : #18839= IFCLOCALPLACEMENT(#18804,#18838);
     * this node (18839) contains link to 18804 and 18838
     */
    std::vector<int> link_to;
    /**
     * @brief linked_by Contains the link to node which are linking this node
     * exemple
     * #18839= IFCLOCALPLACEMENT(#18804,#18838);
     * if this node is 18804, this node is linked by 18839
     */
    std::vector<int> linked_by;
    /**
     * @brief my_node_name
     */
    QString my_node_name;
    /**
     * @brief my_text
     */
    QString my_text;

    /**
     * @brief my_relations temporary vector used to build the node's relationships
     */
    std::vector<int> my_relations;


};

#endif // NODE_H
