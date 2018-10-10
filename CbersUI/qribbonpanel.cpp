#include "qribbonpanel.h"
#include <QHBoxLayout>
#include <QGroupBox>
#include <QFrame>
#include "qseparator.h"
USING_NAMESPACE_CBERSUI

QRibbonPanel::QRibbonPanel(const QString& name, QWidget *parent) : QGroupBox(parent)
{
    setWindowTitle(name);
    setObjectName("QRibbonPanelGroupBox");
    QVBoxLayout* groupBoxLayout = new QVBoxLayout();
    m_pWidgetLayout = new QHBoxLayout();
    m_pWidgetLayout->setSpacing(2);
    m_pWidgetLayout->setContentsMargins(0,0,0,0);
    groupBoxLayout->addLayout(m_pWidgetLayout);

    {
        QWidget* footerWidget = new QWidget();
        footerWidget->setObjectName("QRibbonPanelFooter");
        QHBoxLayout *footerLayout = new QHBoxLayout();
        mTitle = new QLabel(name);
        mTitle->setObjectName("QRibbonPanelFooterLabel");
        mTitle->setAlignment(Qt::AlignCenter);
        footerLayout->addWidget(mTitle, 0, Qt::AlignCenter);
        footerLayout->setContentsMargins(0,0,0,0);
        footerWidget->setLayout(footerLayout);
        groupBoxLayout->addWidget(footerWidget, 0, Qt::AlignBottom);
    }
    groupBoxLayout->setContentsMargins(2,0,2,0);
    groupBoxLayout->setSpacing(2);
    setLayout(groupBoxLayout);
    //setMinimumWidth(32);
}

void QRibbonPanel::Add(QWidget* pElem)
{
    if( pElem==nullptr )
        return;

    m_pWidgetLayout->addWidget(pElem);
}

void QRibbonPanel::AddSeparator()
{
    QSeparator* pSeparator = new QSeparator(false);
    m_pWidgetLayout->addWidget(pSeparator);
}

bool QRibbonPanel::Insert(QWidget* pElem, int nIndex)
{
    if( pElem==nullptr )
        return false;

    if( nIndex<0 )
        nIndex = 0;
    else if( nIndex>mElements.size() )
        nIndex = mElements.size();
    m_pWidgetLayout->insertWidget(nIndex, pElem);
    return false;
}

bool QRibbonPanel::InsertSeparator(int nIndex)
{
    if( nIndex<0 )
        nIndex = 0;
    else if( nIndex>mElements.size() )
        nIndex = mElements.size();

    QSeparator* pSeparator = new QSeparator(false);
    m_pWidgetLayout->insertWidget(nIndex, pSeparator);
    return true;
}

int QRibbonPanel::GetCount() const
{
    return mElements.size();
}

bool QRibbonPanel::Remove(int nIndex)
{
    if( nIndex<0 || nIndex>mElements.size() )
        return  false;

    m_pWidgetLayout->removeWidget(mElements[nIndex]);
    mElements.removeAt(nIndex);
    return true;
}

void QRibbonPanel::RemoveAll()
{
    for(int i=0; i<mElements.size(); i++)
        m_pWidgetLayout->removeWidget(mElements[i]);
    mElements.clear();
}
