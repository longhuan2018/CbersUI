#ifndef QSEPARATOR_H
#define QSEPARATOR_H

#include <QFrame>
#include "cbersui_global.h"
BEGIN_NAMESPACE_CBERSUI

class CBERSUI_EXPORT QSeparator : public QFrame
{
    Q_OBJECT
public:
    explicit QSeparator(bool bVLine = false, QWidget *parent = 0);

signals:

public slots:
};

END_NAMESPACE_CBERSUI
#endif // QSEPARATOR_H
