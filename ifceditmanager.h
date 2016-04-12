#ifndef IFCEDITMANAGER_H
#define IFCEDITMANAGER_H

#include <QString>
#include <QList>
#include <QVector>
#include <QMap>
#include "modification.h"
#include "node.h"

/**
 * @brief The IFCEditManager class used to store the modifications done to a file
 * This class keeps record of the modification done for each node
 * It contains several stage and for each stage a QMap containing the node modified during this stage
 * Call RecordNode to register a node modification
 * Call SET_StageModifier to tel the system if the node(s) are simply modified or deleted
 * Call AdvanceStage to advance the stage, if stage_number exceed max_stage the oldest stage is deleted
 *
 */
class MainWindow;
class IFCEditManager
{
public:


    /**
     * @brief Initialize the manager, call it only once
     */
    static void Initialize(MainWindow* parent);

    /**
     * @brief Close the IFCEditManager, will delete all the node stored
     */
    static void Close();

    /**
     * @brief SetMaximalStageRecord
     * @param n is the number of stage to record (keep it small)
     */
    static void SetMaximalStageRecord(int n);

    /**
     * @brief RecordNode record a node before the modification
     * @param ifc_id
     */
    static void RecordNode(int ifc_id,Modification::ModificationTag tag,const QString &comment);

    /**
     * @brief AdvanceStage
     */
    static void AdvanceStage();


    /**
     * @brief PrintCurrentStageModifications  return a QString which contains all the modification donne during the current stage
     * format is : Node_id  ModificationTag Comment
     *             ....
     * (one node per line)
     * @return
     */
    static QString PrintCurrentStageModifications();


private:
    /**
     * @brief IFCEditManager
     */
    IFCEditManager();

    ~IFCEditManager();


    void RemoveAndCleanLastStage();



    /**
     * @brief my_maximal_stage
     */
    int my_maximal_stage;

    /**
     * @brief my_records
     */
    QList<QMap<int,Modification*>* > my_records;

    MainWindow* main_window_ptr;

    /**
     * @brief my_only_instance
     */
    static IFCEditManager * my_only_instance;


};

#endif // IFCEDITMANAGER_H
