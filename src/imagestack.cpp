#include "imagestack.h"

#include <QtDebug>
#include "imageobject.h"


ImageStack::ImageStack()
{
}

void ImageStack::setFileNames(const QStringList &filenames)
{
    qDeleteAll(m_images);
    m_images.clear();

    // populate the list of images using the filename
    for (int i = 0; i < filenames.count(); i++) {
        m_images.append(new ImageObject(filenames.at(i)));
    }

    qDebug() << filenames;
    qDebug() << "added to list: " << m_images.count();

    // convert stack into a 3D greyscale array
    m_stackArray.setStackArray(m_images);
}

