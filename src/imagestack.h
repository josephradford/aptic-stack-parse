#ifndef IMAGESTACK_H
#define IMAGESTACK_H

#include <QList>

class QImage;

class ImageObject; ///< each instance is image name and data

class ImageStackRaw
{
public:
    ImageStackRaw();

    unsigned char data(int row, int column, int sample) const;

    int samples() const { return m_samples; }
    int rows()    const { return m_rows; }
    int columns() const { return m_columns; }

    void setStackArray(const QList<ImageObject*> &images);
private:
    std::vector<unsigned char> m_data;
    int m_rows;
    int m_columns;
    int m_samples;

    void convertToGreyscale(QImage *image);
};

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

    ImageStackRaw m_stackArray;
};

#endif // IMAGESTACK_H
