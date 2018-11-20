#include "imagestack.h"

#include "imageobject.h"


ImageStack::ImageStack()
{
}

void ImageStack::setFileNames(const std::vector<std::string> &filenames)
{
	m_images.clear();

    // populate the list of images using the filename
    for (size_t i = 0; i < filenames.size(); i++) {
        m_images.push_back(new ImageObject(filenames.at(i)));
    }

    // convert stack into a 3D greyscale array
    m_stackArray.setStackArray(m_images);
}

