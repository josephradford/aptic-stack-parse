#include "imageobject.h"

using namespace boost::gil;

ImageObject::ImageObject(const std::string &filename)
{
    m_filename = filename;
	rgb8_image_t img;
	read_image(filename, img, bmp_tag());

    //QFileInfo fi(m_filename);
    //m_displayName = fi.baseName();
    //m_pixmap = QPixmap(m_filename);
}
