#ifndef QRIBBONSTYLESHEETMANAGER_H
#define QRIBBONSTYLESHEETMANAGER_H

#include <QObject>
#include <QMap>
#include "cbersui_global.h"

BEGIN_NAMESPACE_CBERSUI
class CBERSUI_EXPORT QRibbonStyleSheetManager : public QObject
{
    Q_OBJECT

public:    
    static QRibbonStyleSheetManager* instance();
    int count();
    QString styleSheet(const QString& name);
    bool addStyleSheet(const QString& name, const QString& styleSheet);
    bool removeStyleSheet(const QString& name);
    void clear();
    bool applyStyleSheet(const QString& name);

protected:
    explicit QRibbonStyleSheetManager(QObject *parent = 0);
    QString loadStyleSheet(const QString& url);

signals:

public slots:

private:
    static QRibbonStyleSheetManager* sManager;
    QMap<QString, QString> mStyleSheets;
    QString mOldStyleSheet;
};
END_NAMESPACE_CBERSUI
#endif // QRIBBONSTYLESHEETMANAGER_H
