#include "stackdata.h"

#include <QImage>
#include "imageobject.h"

#include <QDebug>

StackData::StackData()
{
    m_samples = 0;
    m_rows = 0;
    m_columns = 0;
}

void StackData::setStackArray(const QList<ImageObject *> &images)
{
    // go through all the images in the stack and create a 3D greyscale array

    // clear all the parsed data

    if (images.count() == 0) {
        // nothing to process
        return;
    }

    // the accepted row and column count is decided by the first image
    // if any subsequent images do not match, they will be ignored
    m_rows = images.first()->pixmap().height();
    m_columns = images.first()->pixmap().width();


    for (int i = 0; i < images.count(); i++) {
        QImage img = images.at(i)->pixmap().toImage();
        if ((img.height() == m_rows) && (img.width() == m_columns)) {

            if (img.isGrayscale() == false) {
                // convert
                convertToGreyscale(&img);

            }
            else {
                // copy straight in
            }

            unsigned char *imgBytes = img.bits();
            // only need every 4th. RGBA, only need one.
            for (int j = 0; j < img.byteCount(); j += 4) {
                m_data.push_back(imgBytes[j]);
            }

            // more checking may be needed here if different types of images start getting imported
            // crucially, the output must be greyscale, with one byte representing the intensity of one pixel

            m_samples++;
        }
    }

    qDebug () << m_data.size();
    qDebug() << m_samples;
}

// from https://stackoverflow.com/questions/27949569/convert-a-qimage-to-grayscale
void StackData::convertToGreyscale(QImage *image) {
    for (int ii = 0; ii < image->height(); ii++) {
        uchar* scan = image->scanLine(ii);
        int depth =4;
        for (int jj = 0; jj < image->width(); jj++) {

            QRgb* rgbpixel = reinterpret_cast<QRgb*>(scan + jj*depth);
            int gray = qGray(*rgbpixel);
            *rgbpixel = QColor(gray, gray, gray).rgba();
        }
    }
}
