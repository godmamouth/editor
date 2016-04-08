#ifndef FILEMANAGER_H
#define FILEMANAGER_H


#include <QString>

/**
 * @brief The FileManager class  Load an ifc file
 */
class FileManager
{

public:
    /**
     * @brief Initialize  Initialize the FileManager
     */
    static void Initialize();

    /**
     * @brief Close  Close the FileManager
     */
    static void Close();


    /**
     * @brief OpenFile
     * @param path
     * @return
     */
    static int OpenFile(const QString &path);


    /**
     * @brief SaveFile
     * @param path
     * @return
     */
    static int SaveFile(const QString &path);


private:
    /**
     * @brief FileManager
     */
    FileManager();


    /**
     * @brief LoadIfcFile
     * @param path
     * @return
     */
     int LoadIfcFile(const QString &path);


     /**
     * @brief SaveIfcFile
     * @param path
     * @return
     */
    int SaveIfcFile(const QString &path);


    /**
     * @brief my_only_instance
     */
    static FileManager* my_only_instance;



    //data before the nodes  and after (temp)
    QString top_data;
    QString bottom_data;




};

#endif // FILEMANAGER_H
