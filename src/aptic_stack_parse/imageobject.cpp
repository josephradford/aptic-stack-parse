#include "imageobject.h"

ImageObject::ImageObject(const QString &filename)
{
    m_filename = filename;
    m_pixmap = QPixmap(filename);
}
