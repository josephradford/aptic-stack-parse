#include "stackdata.h"

#include <boost/gil.hpp>

#include <iostream>

#include "imageobject.h"

using namespace boost::gil;

StackData::StackData()
{
    m_samples = 0;
    m_rows = 0;
    m_columns = 0;
}

unsigned char StackData::data(int column, int row, int sample) const
{
    size_t idx = column + (row * m_columns) + (sample * m_columns * m_rows);

    if (idx < m_data.size()) {
        return m_data[idx];
    }

    // otherwise the index was invalid, so return 0
    return 0;
}

void StackData::setStackArray(const std::vector<ImageObject *> &images)
{
    // go through all the images in the stack and create a 3D greyscale array

    // clear all the parsed data

    if (images.size() == 0) {
        // nothing to process
        return;
    }

    // the accepted row and column count is decided by the first image
    // if any subsequent images do not match, they will be ignored
	m_rows = images.front()->image().height();
    m_columns = images.front()->image().width();

    for (size_t i = 0; i < images.size(); i++) {
		rgb8_image_t img = images.at(i)->image();
        if ((img.height() == m_rows) && (img.width() == m_columns)) {

            //if (img.isGrayscale() == false) {
            //    // convert
            //    //convertToGreyscale(&img);

            //}
            //else {
            //    // copy straight in
            //}

            //unsigned char *imgBytes = img.bits();
            //// only need every 4th. RGBA, only need one.
            //for (int j = 0; j < img.byteCount(); j += 4) {
            //    m_data.push_back(imgBytes[j]);
            //}

            // more checking may be needed here if different types of images start getting imported
            // crucially, the output must be greyscale, with one byte representing the intensity of one pixel

            m_samples++;
        }
    }

	std::cout << m_data.size();
	std::cout << m_samples;
}

