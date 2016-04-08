#ifndef PROGRESSBARMANAGER_H
#define PROGRESSBARMANAGER_H
#include <QProgressBar>
#include <QWidget>
#include <QString>


class ProgressBarManager : public QProgressBar
{
public:
    /**
     * @brief Initialize the progress bar manager
     * @param parent
     */
    static void Initialize(QWidget *parent=0);


    /**
     * @brief Close the progress bar manager
     */
    static void Close();

    /**
     * @brief Show
     */
    static void Show();

    /**
     * @brief Hide
     */
    static void Hide();

    /**
     * @brief SetMinMax
     * @param min
     * @param max
     */
    static void SetMinMax(int min,int max);

    /**
     * @brief SetValue
     * @param value
     */
    static void SetValue(int value);


    static void SetText(const QString &str);

private:

    ProgressBarManager(QWidget * parent=0);


    static ProgressBarManager* my_only_instance;
};

#endif // PROGRESSBARMANAGER_H
