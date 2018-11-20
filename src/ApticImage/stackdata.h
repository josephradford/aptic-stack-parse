#ifndef STACKDATA_H
#define STACKDATA_H

#include <vector> // vector was very slow until this include, does QList use an old vector library?

class ImageObject;

class StackData
{
public:
    StackData();

    unsigned char data(int column, int row, int sample) const;

    int samples() const { return m_samples; }
    int rows()    const { return m_rows; }
    int columns() const { return m_columns; }

    void setStackArray(const std::vector<ImageObject*> &images);
private:
    std::vector<unsigned char> m_data;
    int m_rows;
    int m_columns;
    int m_samples;
};

#endif // STACKDATA_H
