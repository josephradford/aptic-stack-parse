#include "imagestacklistmodel.h"

#include "imagestack.h"
#include "imageobject.h"

ImageStackListModel::ImageStackListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_stack = 0;
}

QVariant ImageStackListModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole) {
        // not returning anything other than the raw data for now
        return QVariant();
    }

    ImageObject *image = imageData(index);
    if (!image) {
        // not valid object, return
        return QVariant();
    }

    return QVariant(image->displayName());
}

int ImageStackListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    if (!m_stack) {
        // object not set, so no rows
        return 0;
    }

    // else
    return m_stack->count();
}

void ImageStackListModel::updateStack(ImageStack *stack)
{
    emit layoutAboutToBeChanged();
    m_stack = stack;
    emit layoutChanged();
}

ImageObject *ImageStackListModel::imageData(const QModelIndex &index) const
{
    if (!m_stack) {
        // this not valid, return empty variant
        return 0;
    }

    if (index.row() >= this->rowCount(index)) {
        // row is too big.
        return 0;
    }

    return m_stack->imageAt(index.row());
}
