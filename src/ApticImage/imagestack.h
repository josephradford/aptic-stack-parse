#ifndef IMAGESTACK_H
#define IMAGESTACK_H

#include <vector>
#include <string>
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

    void setFileNames(const std::vector<std::string> &filenames);

    int count() const { return m_images.size(); }

    ImageObject * imageAt(int idx) const { return m_images[idx]; }

    StackData const & stack() const { return m_stackArray; }

private:
    std::vector<ImageObject*> m_images;

    StackData m_stackArray;
};

#endif // IMAGESTACK_H
