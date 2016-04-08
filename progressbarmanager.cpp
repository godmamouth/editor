#include "progressbarmanager.h"


ProgressBarManager*   ProgressBarManager::my_only_instance =0;



void ProgressBarManager::Initialize(QWidget *parent)
{
    if(!my_only_instance)
    {
        my_only_instance = new ProgressBarManager(parent);
    }
}



void ProgressBarManager::Close()
{
    if(my_only_instance)
    {
        delete my_only_instance;
    }
}


void ProgressBarManager::Show()
{
    my_only_instance->show();
}


void ProgressBarManager::Hide()
{
    my_only_instance->hide();
}


void ProgressBarManager::SetMinMax(int min,int max)
{
    my_only_instance->setMinimum(min);
    my_only_instance->setMaximum(max);
}


void ProgressBarManager::SetValue(int value)
{
    my_only_instance->setValue(value);
}

void ProgressBarManager::SetText(const QString &str)
{
    my_only_instance->setFormat(str);
}

ProgressBarManager::ProgressBarManager(QWidget*parent):
    QProgressBar(parent)
{
    this->hide();
    this->setGeometry(800,400,200,20);
}
