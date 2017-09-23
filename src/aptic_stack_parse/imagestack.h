#ifndef IMAGESTACK_H
#define IMAGESTACK_H

#include <QList>

class ImageObject; ///< each instance is image name and data

/*!
 * \brief The ImageStack class manages a list of \sa ImageObject
 */
class ImageStack
{
public:
    ImageStack();

    void setFileNames(const QStringList &filenames);

    int count() const { return m_images.count(); }

    ImageObject * imageAt(int idx) const { return m_images[idx]; }

private:
    QList<ImageObject*> m_images;
};

#endif // IMAGESTACK_H
