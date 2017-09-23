#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QtDebug>

#include "imagestack.h"
#include "imagestacklistmodel.h"
#include "imageobject.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(QString("APTIC file parser"));

    m_images = new ImageStack();
    m_imageListView = new ImageStackListModel();
    ui->listViewFiles->setModel(m_imageListView);

    connect(ui->listViewFiles->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this, SLOT(setFileListSelected(QModelIndex,QModelIndex)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    ui->statusBar->showMessage(tr("Selecting files..."), 4000);
    QStringList files = QFileDialog::getOpenFileNames(
                              this,
                              "Select one or more files to open",
                              "/home",
                              "Images (*.png *.xpm *.jpg *.tif)");

    m_images->setFileNames(files);
    m_imageListView->updateStack(m_images);
    ui->statusBar->clearMessage();
}


void MainWindow::setFileListSelected(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous)
    ImageObject *image = m_imageListView->imageData(current);

    if (!image) {
        // not a valid entry in the list
        return;
    }

    // display filename in status bar for confirmation
    ui->statusBar->showMessage(QString("Selected %1").arg(image->filename()), 4000);
}
