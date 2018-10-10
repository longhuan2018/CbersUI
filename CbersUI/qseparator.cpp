#include "qseparator.h"
USING_NAMESPACE_CBERSUI

QSeparator::QSeparator(bool bVLine, QWidget *parent) : QFrame(parent)
{
    setFrameShape(bVLine ? QFrame::VLine : QFrame::HLine);
    setFrameShadow(QFrame::Sunken);
}
