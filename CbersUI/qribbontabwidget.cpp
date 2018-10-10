#include "qribbontabwidget.h"
#include <QRect>
#include <QTabBar>
USING_NAMESPACE_CBERSUI

QRibbonTabWidget::QRibbonTabWidget(QWidget *parent) : QTabWidget(parent)
{
    mMinHeight = 32;
#ifdef Q_OS_WIN
    mMaxHeight = 110;
#else
    mMaxHeight = 120;
#endif

    if( tabBar()!=nullptr )
        mMinHeight = tabBar()->geometry().height() + 2;

    setObjectName("QRibbonTabWidget");
    setFixedHeight(mMaxHeight);
    mOldSize = size();
}

void QRibbonTabWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton )
    {
        QRect tabBarRect;
        if( tabBar()!=nullptr )
        {
            tabBarRect.setTopLeft(tabBar()->mapToGlobal(tabBar()->geometry().topLeft()));
            tabBarRect.setBottomRight(tabBar()->mapToGlobal(tabBar()->geometry().bottomRight()));
        }

        QRect widgetRect;
        if( currentWidget()!=nullptr )
        {
            widgetRect.setTopLeft(currentWidget()->mapToGlobal(currentWidget()->geometry().topLeft()));
            widgetRect.setBottomRight(currentWidget()->mapToGlobal(currentWidget()->geometry().bottomRight()));
        }

        if( (!tabBarRect.isValid() || !tabBarRect.contains(event->globalPos()))
                && (!widgetRect.isValid() || !widgetRect.contains(event->globalPos())) )
        {
            showRibbonElements(!mShow);
            emit toggled(mShow);
        }
    }
}

void QRibbonTabWidget::showRibbonElements(bool show)
{
    if( mShow==show )
        return;

    mShow = show;
    if( mShow )
    {
        setFixedHeight(mMaxHeight);
        resize(mOldSize);
    }
    else
    {
        mOldSize = size();
        QSize newSize(size().width(), mMinHeight);
        setFixedHeight(mMinHeight);
        resize(newSize);
    }
}
