#ifndef IFCBROWSER_H
#define IFCBROWSER_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QString>

/**
 * @brief The IFCBrowser class
 */
class IFCBrowser : public QPlainTextEdit
{
    Q_OBJECT
public:
    enum BrowserMode{normal,relation};

    /**
     * @brief IFCBrowser Constructor
     * @param parent
     */
    IFCBrowser(QWidget* parent=0);


    void ResetText();
private slots:
    /**
     * @brief s_selection_changed
     */
    void on_selection_changed();
protected:
    void keyPressEvent(QKeyEvent *);

private:
    //private data
    BrowserMode my_current_mode;
    QString my_backup_text;

};

#endif // IFCBROWSER_H
