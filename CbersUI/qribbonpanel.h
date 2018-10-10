#ifndef QRIBBONPANEL_H
#define QRIBBONPANEL_H

#include <QObject>
#include <QWidget>
#include <QGroupBox>
#include <QLabel>
#include <QList>
#include <QHBoxLayout>
#include "cbersui_global.h"

BEGIN_NAMESPACE_CBERSUI
class CBERSUI_EXPORT QRibbonPanel : public QGroupBox
{
    Q_OBJECT
public:
    explicit QRibbonPanel(const QString& name, QWidget *parent = 0);

public:    
    void Add(QWidget* pElem);
    void AddSeparator();
    bool Insert(QWidget* pElem, int nIndex);
    bool InsertSeparator(int nIndex);

    int GetCount() const;
    bool Remove(int nIndex);
    void RemoveAll();

signals:

public slots:

protected:
    QHBoxLayout* m_pWidgetLayout;
    QLabel* mTitle;
    QList<QWidget*> mElements;
};
END_NAMESPACE_CBERSUI
#endif // QRIBBONPANEL_H
