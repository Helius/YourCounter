#include "Theme.h"

Theme::Theme(QObject *parent) : QObject(parent)
{
}

QColor Theme::background() const
{
    return m_background;
}
