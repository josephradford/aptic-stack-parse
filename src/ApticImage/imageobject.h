#ifndef IMAGEOBJECT_H
#define IMAGEOBJECT_H

#include <string>
#include <boost/gil.hpp>
#include <boost/gil/gil_all.hpp>
#include <boost/gil/extension/io/bmp.hpp>

/*!
 * \brief The ImageObject class contains metadata about an image in the stack as well as the image data itself
 */
class ImageObject
{
public:
    ImageObject(const std::string &filename);

    std::string  filename()    const { return m_filename; }
	std::string  displayName() const { return m_displayName; }
	boost::gil::rgb8_image_t image()       const { return m_image; }

private:
	std::string m_filename; ///< The full filename for this image
	std::string m_displayName;
	boost::gil::rgb8_image_t m_image;
};

#endif // IMAGEOBJECT_H
