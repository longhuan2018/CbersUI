#ifndef QRIBBONTABWIDGET_H
#define QRIBBONTABWIDGET_H

#include <QObject>
#include <QWidget>
#include <QTabWidget>
#include <QMouseEvent>
#include "cbersui_global.h"

BEGIN_NAMESPACE_CBERSUI
class CBERSUI_EXPORT QRibbonTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit QRibbonTabWidget(QWidget *parent = 0);

    void showRibbonElements(bool show);

protected:
    void mouseDoubleClickEvent(QMouseEvent *event);

signals:
    void toggled(bool);

protected:
    bool mShow;
    QSize mOldSize;
    int mMaxHeight;
    int mMinHeight;
};
END_NAMESPACE_CBERSUI
#endif // QRIBBONTABWIDGET_H
