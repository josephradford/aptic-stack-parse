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
    if (!m_stack) {
        // this not valid, return empty variant
        return QVariant();
    }

    if (index.row() >= this->rowCount(index)) {
        // row is too big.
        return QVariant();
    }

    if (role != Qt::DisplayRole) {
        // not returning anything other than the raw data for now
        return QVariant();
    }

    return QVariant(m_stack->imageAt(index.row())->filename());
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
