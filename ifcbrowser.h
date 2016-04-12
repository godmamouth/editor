#ifndef IFCBROWSER_H
#define IFCBROWSER_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QString>
#include <QTimer>
#include <vector>

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

    /**
     * @brief SetText  set the text from the current IFCFile, load
     * @param text
     */
    void SetText();



private slots:
    /**
     * @brief s_selection_changed
     */
    void on_selection_changed();


    void on_time_out();
protected:
    void keyPressEvent(QKeyEvent *);

private:
    //private data
    BrowserMode my_current_mode;




    std::vector<QString> my_full_text;
    int last_line;
    bool read_end;
    QTimer my_timer;

};

#endif // IFCBROWSER_H
