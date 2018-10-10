#ifndef QTITLEWIDGET_H
#define QTITLEWIDGET_H

#include <QObject>
#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QAction>
#include "cbersui_global.h"

BEGIN_NAMESPACE_CBERSUI
class CBERSUI_EXPORT QTitleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QTitleWidget(QWidget *parent = 0);
    ~QTitleWidget();

public:
    bool addWidget(QWidget* widget, int index = -1);
    bool addExtendedWidget(QWidget* widget, int index = -1);

protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual bool eventFilter(QObject *obj, QEvent *event);

public slots:
    void onMinimized();
    void onMaximized();
    void onRestore();
    void onClose();
    void onMove();

private:
    void updateMaximize();

protected:
    QPushButton *m_pIconLabel;
    QLabel *m_pTitleLabel;
    QPushButton *m_pMinimizeButton;
    QPushButton *m_pMaximizeButton;
    QPushButton *m_pRestoreButton;
    QPushButton *m_pCloseButton;
    QAction* mMoveAction;

    QHBoxLayout* m_pWidgetLayout;
    QHBoxLayout* m_pExtendedLayout;

private:
    bool m_bPressed;
    QPoint m_point;
    QByteArray m_normalGeometry;
};
END_NAMESPACE_CBERSUI
#endif // QTITLEWIDGET_H
