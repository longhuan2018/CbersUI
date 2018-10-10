#ifndef QRIBBONCATEGORY_H
#define QRIBBONCATEGORY_H

#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QList>
#include "cbersui_global.h"
#include "qribbonpanel.h"

BEGIN_NAMESPACE_CBERSUI
class CBERSUI_EXPORT QRibbonCategory : public QWidget
{
    Q_OBJECT
public:
    explicit QRibbonCategory(QWidget *parent = 0);

public:
    QRibbonPanel* addPanel(const QString& name, int nInsertAt = -1);
    bool removePanel(int index, bool bDelete = true);
    int  GetPanelIndex(QRibbonPanel* panel);

    int GetPanelCount() const;
    QRibbonPanel* GetPanel(int index);

signals:

public slots:

protected:
    QHBoxLayout* mHBoxLayout;
    QList<QRibbonPanel*> mPanels;
};
END_NAMESPACE_CBERSUI
#endif // QRIBBONCATEGORY_H
