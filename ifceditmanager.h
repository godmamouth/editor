#ifndef IFCEDITMANAGER_H
#define IFCEDITMANAGER_H

#include <QQueue>
#include <QMap>
#include "node.h"

/**
 * @brief The IFCEditManager class used to store the modifications done to a file
 * This class keeps record of the modification done for each node
 * It contains several stage and for each stage a QMap containing the node modified during this stage
 * Call RecordNode to register a node state, this function does not advance the stage state
 * Call SET_StageModifier to tel the system if the node(s) are simply modified or deleted
 * Call AdvanceStage to advance the stage, if stage_number exceed max_stage the oldest stage is deleted
 *
 * You can not use a stage to modify and delete
 */

class IFCEditManager
{
public:

    enum StageType{ModifyStage,DeleteStage};

    /**
     * @brief Initialize the manager, call it only once
     */
    static void Initialize();

    /**
     * @brief Close
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
    static void RecordNode(int ifc_id);

    /**
     * @brief AdvanceStage
     */
    static void AdvanceStage();

    /**
     * @brief SetCurrentStageType
     */
    static void SetCurrentStageType(StageType);







private:
    /**
     * @brief IFCEditManager
     */
    IFCEditManager();

    ~IFCEditManager();

    /**
     * @brief my_only_instance
     */
    IFCEditManager * my_only_instance;



};

#endif // IFCEDITMANAGER_H
