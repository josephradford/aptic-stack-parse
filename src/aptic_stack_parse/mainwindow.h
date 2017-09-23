#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class ImageStack;
class ImageStackListModel;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void setFileListSelected(const QModelIndex &current, const QModelIndex &previous);
private:
    Ui::MainWindow *ui;

    ImageStack *m_images;
    ImageStackListModel *m_imageListView;
};

#endif // MAINWINDOW_H
