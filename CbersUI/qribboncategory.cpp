#include "qribboncategory.h"
#include <QGridLayout>
#include <QPushButton>
USING_NAMESPACE_CBERSUI

QRibbonCategory::QRibbonCategory(QWidget *parent) : QWidget(parent)
{
    setObjectName("QRibbonCategory");    
    mHBoxLayout = new QHBoxLayout();
    mHBoxLayout->addStretch(1);
    mHBoxLayout->setContentsMargins(0,0,0,0);
    mHBoxLayout->setSpacing(2);    
    setLayout(mHBoxLayout);
}

QRibbonPanel* QRibbonCategory::addPanel(const QString& name, int nInsertAt)
{
    QRibbonPanel* panel = new QRibbonPanel(name, this);
    if( nInsertAt<0 )
    {
        mHBoxLayout->insertWidget(mPanels.size(), panel);
        mPanels.append(panel);
    }
    else
    {
        nInsertAt = qMin(nInsertAt, mPanels.size());
        mHBoxLayout->insertWidget(nInsertAt, panel);
        mPanels.insert(nInsertAt, panel);
    }

    return panel;
}

bool QRibbonCategory::removePanel(int index, bool bDelete)
{
    if( index<0 || index>=mPanels.size() )
        return false;

    QRibbonPanel* panel = mPanels.at(index);
    mHBoxLayout->removeWidget(panel);
    mPanels.removeAt(index);
    if( bDelete )
        panel->deleteLater();
    panel = nullptr;
    return true;
}

int  QRibbonCategory::GetPanelIndex(QRibbonPanel* panel)
{
    return mPanels.indexOf(panel);
}

int QRibbonCategory::GetPanelCount() const
{
    return mPanels.size();
}

QRibbonPanel* QRibbonCategory::GetPanel(int index)
{
    if( index<0 || index>=mPanels.size() )
        return nullptr;

    return mPanels.at(index);
}
