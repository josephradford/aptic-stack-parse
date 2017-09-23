#ifndef IMAGEOBJECT_H
#define IMAGEOBJECT_H

#include <QString>
#include <QPixmap>

/*!
 * \brief The ImageObject class contains metadata about an image in the stack as well as the image data itself
 */
class ImageObject
{
public:
    ImageObject(const QString &filename);

    QString filename() const { return m_filename; }
    QPixmap pixmap()   const { return m_pixmap; }

private:
    QString m_filename; ///< The full filename for this image
    QPixmap m_pixmap;   ///< image data
};

#endif // IMAGEOBJECT_H
