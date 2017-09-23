#ifndef IMAGESTACKLISTMODEL_H
#define IMAGESTACKLISTMODEL_H

#include <QAbstractListModel>

class ImageStack;
class ImageObject;

class ImageStackListModel : public QAbstractListModel
{
public:
    ImageStackListModel(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parent) const;

    void updateStack(ImageStack *stack);

    ImageObject * imageData(const QModelIndex &index) const;
private:
    ImageStack *m_stack;
};

#endif // IMAGESTACKLISTMODEL_H
