#include "qribbonbar.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QWindowStateChangeEvent>
#include <QTabBar>
#include "qribbonstylesheetmanager.h"
#include "qribbontabwidget.h"
#include "qtitlewidget.h"
USING_NAMESPACE_CBERSUI

QRibbonBar::QRibbonBar(QWidget *parent)
    : QWidget(parent), mParent(parent)
{
    setObjectName("QRibbonBar");
    QRibbonStyleSheetManager::instance()->applyStyleSheet("office2007_black");

    QSize szButton(28, 28);    
    mShowElementsButton = new QPushButton();
    mShowElementsButton->setToolTip(tr("ShowElements"));
    mShowElementsButton->setObjectName("Btn_ShowElements");
    mShowElementsButton->setFixedSize(szButton);
    mShowElementsButton->hide();
    mHideElementsButton = new QPushButton();
    mHideElementsButton->setToolTip(tr("HideElements"));
    mHideElementsButton->setObjectName("Btn_HideElements");
    mHideElementsButton->setFixedSize(szButton);

    mTabWidget = new QRibbonTabWidget();

    //if( parent!=nullptr )
    //    parent->installEventFilter(this);

    connect(mShowElementsButton, SIGNAL(clicked()), this, SLOT(showRibbonElements()));
    connect(mHideElementsButton, SIGNAL(clicked()), this, SLOT(hideRibbonElements()));

    QTitleWidget* pTitleWidget = new QTitleWidget(this);
    mTitleWidget = pTitleWidget;
    installEventFilter(mTitleWidget);
    pTitleWidget->addExtendedWidget(mShowElementsButton);
    pTitleWidget->addExtendedWidget(mHideElementsButton);

    QHBoxLayout* tabLayout = new QHBoxLayout();
    tabLayout->addWidget(mTabWidget);
    tabLayout->setSpacing(0);
    tabLayout->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(mTitleWidget, 0, Qt::AlignTop);
    mainLayout->addLayout(tabLayout);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(1, 1, 1, 1);
    setLayout(mainLayout);

    connect(mTabWidget, SIGNAL(currentChanged(int)) , this, SLOT(showRibbonElements()));
    connect(mTabWidget, SIGNAL(tabBarClicked(int)) , this, SLOT(showRibbonElements()));
    connect(mTabWidget, SIGNAL(toggled(bool)), this, SLOT(toggleRibbonElements(bool)));
}


QRibbonBar::~QRibbonBar()
{

}

void QRibbonBar::toggleRibbonElements(bool show)
{
    if( show )
    {
        mHideElementsButton->show();
        mShowElementsButton->hide();
    }
    else
    {
        mHideElementsButton->hide();
        mShowElementsButton->show();
    }

    QRibbonTabWidget* pRibbonTabWidget = qobject_cast<QRibbonTabWidget*>(mTabWidget);
    if( pRibbonTabWidget!=nullptr )
        pRibbonTabWidget->showRibbonElements(show);
}

void QRibbonBar::showRibbonElements()
{
    toggleRibbonElements(true);
}

void QRibbonBar::hideRibbonElements()
{
    toggleRibbonElements(false);
}

bool QRibbonBar::eventFilter(QObject *target, QEvent *e)
{
    return QWidget::eventFilter(target, e);
}

QRibbonCategory* QRibbonBar::AddCategory(const QString& name, int nInsertAt)
{
    QRibbonCategory* pCategory = new QRibbonCategory(mTabWidget);
    if( pCategory==nullptr )
        return nullptr;

    pCategory->setWindowTitle(name);
    if( nInsertAt==-1 )
    {
        mCategories.append(pCategory);
        mTabWidget->addTab(pCategory, name);
    }
    else
    {
        nInsertAt = qMin(nInsertAt, mCategories.size());
        mCategories.insert(nInsertAt, pCategory);
        mTabWidget->insertTab(nInsertAt, pCategory, name);
    }
    return pCategory;
}

int QRibbonBar::GetCategoryCount() const
{
    return mCategories.size();
}

int QRibbonBar::GetVisibleCategoryCount() const
{
    return mTabWidget->count();
}

QRibbonCategory* QRibbonBar::GetCategory(int nIndex) const
{
    if( nIndex<0 || nIndex>=mCategories.size() )
        return nullptr;

    return mCategories.at(nIndex);
}

int QRibbonBar::GetCategoryIndex(QRibbonCategory* pCategory) const
{
    return mCategories.indexOf(pCategory);
}

void QRibbonBar::ShowCategory(int nIndex, bool bShow)
{
    if( nIndex<0 || nIndex>=mCategories.size() )
        return;

    QRibbonCategory* pCategory = mCategories.at(nIndex);
    if( pCategory==nullptr )
        return;

    int nTabIndex = mTabWidget->indexOf(pCategory);
    if( bShow && nTabIndex==-1 )
    {
        bool bInsert = false;
        for( int i=0; i<mTabWidget->count(); i++ )
        {
            int index = mCategories.indexOf(qobject_cast<QRibbonCategory*>(mTabWidget->widget(i)));
            if( index>nIndex )
            {
                mTabWidget->insertTab(i-1, pCategory, pCategory->windowTitle());
                bInsert = true;
                break;
            }
        }

        if( !bInsert )
            mTabWidget->addTab(pCategory, pCategory->windowTitle());
    }
    else if( !bShow && nTabIndex!=-1 )
    {
        mTabWidget->removeTab(nTabIndex);
    }
}

bool QRibbonBar::RemoveCategory(int nIndex)
{
    if( nIndex<0 || nIndex>=mCategories.size() )
        return false;

    QRibbonCategory* pCategory = mCategories.at(nIndex);
    int nTabIndex = mTabWidget->indexOf(pCategory);
    if( nTabIndex>=0 )
        mTabWidget->removeTab(nTabIndex);
    mCategories.removeAt(nIndex);

    pCategory->deleteLater();
    pCategory = nullptr;
    return true;
}

void QRibbonBar::RemoveAllCategories()
{
    for( int i=mTabWidget->count()-1; i>=0; i--)
        mTabWidget->removeTab(i);

    for( int i=0; i<mCategories.size(); i++ )
    {
        QRibbonCategory* pCategory = mCategories.at(i);
        if( pCategory!=nullptr )
            pCategory->deleteLater();
    }
    mCategories.clear();
}

bool QRibbonBar::SetActiveCategory(QRibbonCategory* pCategory)
{
    if( pCategory==nullptr )
        return false;

    int nIndex = mTabWidget->indexOf(pCategory);
    if( nIndex<0 )
        return false;

    mTabWidget->setCurrentIndex(nIndex);
    return true;
}

QRibbonCategory* QRibbonBar::GetActiveCategory() const
{
    QRibbonCategory* pCategory = qobject_cast<QRibbonCategory*>(mTabWidget->currentWidget());
    return pCategory;
}

QList<QRibbonCategory*> QRibbonBar::FindCategoryByName(const QString& name)
{
    QList<QRibbonCategory*> result;
    for(int i=0; i<mCategories.size(); i++)
    {
        if( mCategories[i]->windowTitle().compare(name, Qt::CaseInsensitive)==0 )
            result.push_back(mCategories[i]);
    }

    return result;
}
