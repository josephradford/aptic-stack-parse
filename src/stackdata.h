#ifndef STACKDATA_H
#define STACKDATA_H

#include <QList>

class QImage;
class ImageObject;

class StackData
{
public:
    StackData();

    unsigned char data(int column, int row, int sample) const;

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

#endif // STACKDATA_H
