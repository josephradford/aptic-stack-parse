#include "imageobject.h"

#include <QFileInfo>

ImageObject::ImageObject(const QString &filename)
{
    m_filename = filename;
    QFileInfo fi(m_filename);
    m_displayName = fi.baseName();
    m_pixmap = QPixmap(m_filename);
}
