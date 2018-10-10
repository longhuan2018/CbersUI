#include "qtitlewidget.h"
#include <QHBoxLayout>
#include <QIcon>
#include <QAction>
#include <QApplication>
#include <QMenu>
#include <QCursor>

#ifdef Q_OS_WIN
#pragma comment(lib, "user32.lib")
#include <qt_windows.h>
#endif
USING_NAMESPACE_CBERSUI

QTitleWidget::QTitleWidget(QWidget *parent) : QWidget(parent)
{
    setObjectName("QRibbonTitleWidget");
    setFixedHeight(30);
    m_bPressed = false;

    m_pIconLabel = new QPushButton(this);
    m_pIconLabel->setObjectName("sysIconLabel");
    //m_pIconLabel->setStyleSheet("QPushButton {background-color: rgba(229, 229, 229, 0);} QPushButton:hover {background-color: rgba(229, 229, 229, 0);} QPushButton:pressed {background-color: rgba(202, 202, 202, 0);}  QPushButton::menu-indicator{image:none;}");
    m_pTitleLabel = new QLabel(this);
    m_pMinimizeButton = new QPushButton(this);
    m_pMaximizeButton = new QPushButton(this);
    m_pRestoreButton   = new QPushButton(this);
    m_pCloseButton    = new QPushButton(this);

    QWidget *pWindow = this->window();
    if (pWindow!=nullptr && pWindow->isTopLevel())
    {
        m_pTitleLabel->setText(pWindow->windowTitle());
        QIcon icon = pWindow->windowIcon();
        m_pIconLabel->setIcon(icon);//setPixmap(icon.pixmap(m_pIconLabel->size()));
    }

    m_pRestoreButton->hide();
    m_pRestoreButton->setDisabled(true);

    QSize szIcon(20, 20);
    m_pIconLabel->setFixedSize(szIcon);
    //m_pIconLabel->setScaledContents(true);

    m_pTitleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QSize szButton(28, 28);
    m_pMinimizeButton->setFixedSize(szButton);
    m_pMaximizeButton->setFixedSize(szButton);
    m_pRestoreButton->setFixedSize(szButton);
    m_pCloseButton->setFixedSize(szButton);

    m_pTitleLabel->setObjectName("sysTitle");
    m_pMinimizeButton->setObjectName("SysBtn_Minimize");
    m_pMaximizeButton->setObjectName("SysBtn_Maximize");
    m_pRestoreButton->setObjectName("SysBtn_Restore");
    m_pCloseButton->setObjectName("SysBtn_Close");

    m_pMinimizeButton->setToolTip(tr("Minimize"));
    m_pMaximizeButton->setToolTip(tr("Maximize"));
    m_pRestoreButton->setToolTip(tr("Restore"));
    m_pCloseButton->setToolTip(tr("Close"));

    QMenu* mainMenu = new QMenu(this);
    QAction* restoreAction = new QAction(m_pRestoreButton->icon(), tr("Restore"), nullptr);
    connect(restoreAction, SIGNAL(triggered()), m_pRestoreButton, SLOT(click()));
    mainMenu->addAction(restoreAction);

    mMoveAction = new QAction(tr("Move"), nullptr);
    connect(mMoveAction, SIGNAL(triggered()), this, SLOT(onMove()));
    mainMenu->addAction(mMoveAction);

    QAction* minimizeAction = new QAction(m_pRestoreButton->icon(), tr("Minimize"), nullptr);
    connect(minimizeAction, SIGNAL(triggered()), m_pMinimizeButton, SLOT(click()));
    mainMenu->addAction(minimizeAction);

    QAction* maximizeAction = new QAction(m_pMaximizeButton->icon(), tr("Maximize"), nullptr);
    connect(maximizeAction, SIGNAL(triggered()), m_pMaximizeButton, SLOT(click()));
    mainMenu->addAction(maximizeAction);

    mainMenu->addSeparator();

    QAction* closeAction = new QAction(m_pCloseButton->icon(), tr("Close"), nullptr);
    connect(closeAction, SIGNAL(triggered()), m_pCloseButton, SLOT(click()));
    mainMenu->addAction(closeAction);

    m_pIconLabel->setMenu(mainMenu);


    QHBoxLayout *pLayout = new QHBoxLayout(nullptr);
    pLayout->addWidget(m_pIconLabel);
    m_pWidgetLayout = new QHBoxLayout(nullptr);
    pLayout->addLayout(m_pWidgetLayout);
    pLayout->addSpacing(5);
    pLayout->addWidget(m_pTitleLabel);
    m_pExtendedLayout = new QHBoxLayout(nullptr);
    pLayout->addLayout(m_pExtendedLayout);
    pLayout->addWidget(m_pMinimizeButton);
    pLayout->addWidget(m_pMaximizeButton);
    pLayout->addWidget(m_pRestoreButton);
    pLayout->addWidget(m_pCloseButton);
    pLayout->setSpacing(0);
    pLayout->setContentsMargins(5, 0, 5, 0);

    setLayout(pLayout);

    connect(m_pMinimizeButton, SIGNAL(clicked(bool)), this, SLOT(onMinimized()));
    connect(m_pMaximizeButton, SIGNAL(clicked(bool)), this, SLOT(onMaximized()));
    connect(m_pRestoreButton, SIGNAL(clicked(bool)), this, SLOT(onRestore()));
    connect(m_pCloseButton, SIGNAL(clicked(bool)), this, SLOT(onClose()));
}

QTitleWidget::~QTitleWidget()
{

}

void QTitleWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    //emit m_pMaximizeButton->clicked();
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
    {
        if( pWindow->isMaximized() )
            pWindow->showNormal();
        else
            pWindow->showMaximized();
    }
}

void QTitleWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_bPressed = true;
        m_point = event->pos();
    }
    /*
#ifdef Q_OS_WIN
    if (ReleaseCapture())
    {
        QWidget *pWindow = this->window();
        if (pWindow->isTopLevel())
        {
            //pWindow->setCursor(QCursor(Qt::ArrowCursor));
            //if( pWindow->isMaximized() )
            //    pWindow->overrideWindowState(Qt::WindowNoState);
            SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
        }
    }
    event->ignore();
#else
#endif
    */
}

void QTitleWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_bPressed = false;
}

void QTitleWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_bPressed && event->pos()!=m_point)
    {
        QWidget *pWindow = this->window();
        if (pWindow->isTopLevel())
        {
            if( pWindow->isMaximized() )
            {
                QPoint oldTopLeft = this->mapToGlobal(this->geometry().topLeft());
                QPoint oldBottomRight = this->mapToGlobal(this->geometry().bottomRight());
                if( m_pWidgetLayout!=nullptr )
                    oldTopLeft.setX(this->mapToGlobal(m_pWidgetLayout->contentsRect().bottomRight()).x());
                if( m_pExtendedLayout!=nullptr )
                    oldBottomRight.setX(this->mapToGlobal(m_pExtendedLayout->contentsRect().topLeft()).x());
                bool inTitleLabel = false;
                if( m_pTitleLabel!=nullptr && event->pos().x()<=(m_pTitleLabel->mapToGlobal(m_pTitleLabel->geometry().topLeft()).x() + m_pTitleLabel->sizeHint().width()))
                    inTitleLabel = true;
                bool inExtendedLayout = false;
                if( m_pExtendedLayout!=nullptr && event->pos().x()>=(this->mapToGlobal(m_pExtendedLayout->contentsRect().topLeft()).x()))
                    inExtendedLayout = true;
                pWindow->showNormal();
                if(m_normalGeometry.isEmpty())
                {
                    QRect rect = pWindow->geometry();
                    rect.setWidth(rect.width()/2);
                    rect.setHeight(rect.height()/2);
                    pWindow->setGeometry(rect);
                }
                else
                    pWindow->restoreGeometry(m_normalGeometry);
                QPoint newTopLeft = this->mapToGlobal(this->geometry().topLeft());
                QPoint newBottomRight = this->mapToGlobal(this->geometry().bottomRight());
                if( m_pWidgetLayout!=nullptr )
                    newTopLeft.setX(this->mapToGlobal(m_pWidgetLayout->contentsRect().bottomRight()).x());
                if( m_pExtendedLayout!=nullptr )
                    newBottomRight.setX(this->mapToGlobal(m_pExtendedLayout->contentsRect().topLeft()).x());

                QPoint newPoint(newTopLeft.x() + (event->pos().x() - oldTopLeft.x()) * (newBottomRight.x() - newTopLeft.x()) / (oldBottomRight.x() - oldTopLeft.x()),
                                newTopLeft.y() + (event->pos().y() - oldTopLeft.y()) * (newBottomRight.y() - newTopLeft.y()) / (oldBottomRight.y() - oldTopLeft.y()));
                if( inTitleLabel && (newBottomRight.x() - newTopLeft.x() > event->pos().x() - oldTopLeft.x()) )
                    newPoint.setX(newTopLeft.x() + (event->pos().x() - oldTopLeft.x()));
                else if( inExtendedLayout && (newBottomRight.x() - newTopLeft.x() > oldBottomRight.x() - event->pos().x()) )
                    newPoint.setX(newBottomRight.x() - (oldBottomRight.x() - event->pos().x()));

                if( m_pExtendedLayout!=nullptr )
                {
                    newPoint.setX(qMin(newPoint.x(), this->mapToGlobal(m_pExtendedLayout->contentsRect().topLeft()).x()));
                }

                if( m_pWidgetLayout!=nullptr )
                    newPoint.setX(qMax(newPoint.x(), this->mapToGlobal(m_pWidgetLayout->contentsRect().bottomRight()).x()));

                m_point = newPoint;
                pWindow->move(event->pos() - newPoint + pWindow->pos());
            }
            else
                pWindow->move(event->pos() - m_point + pWindow->pos());
        }
    }
}

bool QTitleWidget::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type())
    {
    case QEvent::WindowTitleChange:
    {
        QWidget *pWidget = qobject_cast<QWidget *>(obj);
        if (pWidget)
        {
            m_pTitleLabel->setText(pWidget->windowTitle());
            return true;
        }
    }
    case QEvent::WindowIconChange:
    {
        QWidget *pWidget = qobject_cast<QWidget *>(obj);
        if (pWidget)
        {
            QIcon icon = pWidget->windowIcon();
            m_pIconLabel->setIcon(icon);//setPixmap(icon.pixmap(m_pIconLabel->size()));
            return true;
        }
    }
    case QEvent::WindowStateChange:
    case QEvent::Resize:
    {
        updateMaximize();
        return true;
    }
    }
    return QWidget::eventFilter(obj, event);
}

void QTitleWidget::onMove()
{
    QPoint center = this->mapToGlobal(this->geometry().center());
    QCursor::setPos(center);
    m_bPressed = true;
    m_point = center;
    /*
#ifdef Q_OS_WIN
    if (ReleaseCapture())
    {
        QWidget *pWindow = this->window();
        if (pWindow->isTopLevel())
        {
            if( pWindow->isMaximized() )
                pWindow->overrideWindowState(Qt::WindowNoState);

            QPoint center = this->mapToGlobal(this->geometry().center());
            QCursor::setPos(center);
            //pWindow->setCursor(QCursor(Qt::SizeAllCursor));
            //this->cursor().setShape(Qt::SizeAllCursor);
            SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
        }
    }
#else
#endif
    */
}

void QTitleWidget::onMinimized()
{
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
        pWindow->showMinimized();
}

void QTitleWidget::onMaximized()
{
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
    {
        pWindow->showMaximized();
        //m_pRestoreButton->show();
        //m_pMaximizeButton->hide();
    }
}

void QTitleWidget::onRestore()
{
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
    {
        pWindow->showNormal();
        //m_pRestoreButton->hide();
        //m_pMaximizeButton->show();
    }
}

void QTitleWidget::onClose()
{
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
        pWindow->close();
}

void QTitleWidget::updateMaximize()
{
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
    {
        bool bMaximize = pWindow->isMaximized();
        if (bMaximize)
        {
            m_pRestoreButton->show();
            m_pRestoreButton->setDisabled(false);
            m_pMaximizeButton->hide();
            m_pMaximizeButton->setDisabled(true);
            mMoveAction->setEnabled(false);
        }
        else
        {
            m_pRestoreButton->hide();
            m_pRestoreButton->setDisabled(true);
            m_pMaximizeButton->show();
            m_pMaximizeButton->setDisabled(false);
            mMoveAction->setEnabled(true);
            m_normalGeometry = pWindow->saveGeometry();
        }
    }
}

bool QTitleWidget::addWidget(QWidget* widget, int index)
{
    if( m_pWidgetLayout==nullptr || widget==nullptr )
        return false;

    m_pWidgetLayout->addWidget(widget);
    return true;
}

bool QTitleWidget::addExtendedWidget(QWidget* widget, int index)
{
    if( m_pExtendedLayout==nullptr || widget==nullptr )
        return false;

    m_pExtendedLayout->addWidget(widget);
    return true;
}
