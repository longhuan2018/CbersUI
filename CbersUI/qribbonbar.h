#ifndef QRIBBONBAR_H
#define QRIBBONBAR_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QEvent>
#include <QTabWidget>
#include <QList>
#include "cbersui_global.h"
#include "qribboncategory.h"

BEGIN_NAMESPACE_CBERSUI
class CBERSUI_EXPORT QRibbonBar : public QWidget
{
    Q_OBJECT
public:
    explicit QRibbonBar(QWidget *parent = 0);
    virtual ~QRibbonBar();

public:
    QRibbonCategory* AddCategory(const QString& name, int nInsertAt = -1);
    int GetCategoryCount() const;
    int GetVisibleCategoryCount() const;
    QRibbonCategory* GetCategory(int nIndex) const;
    int GetCategoryIndex(QRibbonCategory* pCategory) const;

    void ShowCategory(int nIndex, bool bShow = true);
    bool RemoveCategory(int nIndex);
    void RemoveAllCategories();

    virtual bool SetActiveCategory(QRibbonCategory* pCategory);
    QRibbonCategory* GetActiveCategory() const;

    QList<QRibbonCategory*> FindCategoryByName(const QString& name);

signals:

public slots:
    void showRibbonElements();
    void hideRibbonElements();
    void toggleRibbonElements(bool show);

protected:
    bool eventFilter(QObject *target, QEvent *e);

protected:
    // TabWidget
    QTabWidget* mTabWidget;
    QList<QRibbonCategory*> mCategories;

    QPushButton *mStylesButton;
    QPushButton *mHelpButton;

    QPushButton *mShowElementsButton;
    QPushButton *mHideElementsButton;

    QWidget*     mParent;
    QWidget*     mTitleWidget;
};
END_NAMESPACE_CBERSUI
#endif // QRIBBONBAR_H
