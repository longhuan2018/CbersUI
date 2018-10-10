#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QProgressBar>
#include <QValidator>
#include <QToolButton>
#include <QMdiSubWindow>
#include "qribbonbar.h"
USING_NAMESPACE_CBERSUI

#include "UIPluginsEvents.h"
USING_NAMESPACE_CBERSPLUGINS

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public IAnythingEventObserver
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    // IAnythingEventObserver
    virtual bool OnAnything(x3::IObject* sender, const std::string& eventKey, const QVariant& wParam, const QVariant& lParam);

protected slots:
    void subWindowActivated(QMdiSubWindow *);

private:
    Ui::MainWindow *ui;
    QRibbonBar* mRibbonBar;
    QMdiArea* mMdiArea;
};

#endif // MAINWINDOW_H
