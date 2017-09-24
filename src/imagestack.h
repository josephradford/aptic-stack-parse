#ifndef IMAGESTACK_H
#define IMAGESTACK_H

#include <QList>
#include "stackdata.h"

class QImage;

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

    StackData stack() const { return m_stackArray; }

private:
    QList<ImageObject*> m_images;

    StackData m_stackArray;
};

#endif // IMAGESTACK_H
