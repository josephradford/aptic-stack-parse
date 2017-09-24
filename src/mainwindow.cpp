#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QtDebug>
#include <QSettings>

#include "imagestack.h"
#include "imagestacklistmodel.h"
#include "imageobject.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(QString("APTIC file parser"));

    // set up the application and settings
    QCoreApplication::setOrganizationName("JORA");
    QCoreApplication::setOrganizationDomain("jora.io");
    QCoreApplication::setApplicationName("APTIC Image Parser");
    QSettings settings;

    m_lastOpenDir = settings.value("filemanager/openDir", "/home").toString();


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
    // confirm we are opening by updating status
    ui->statusBar->showMessage(tr("Selecting files..."), 4000);

    // clear any photos on display
    ui->lblSelectedFile->clear();

    // open the file dialog
    QStringList files = QFileDialog::getOpenFileNames(
                              this,
                              "Select one or more files to open",
                              m_lastOpenDir,
                              "Images (*.png *.xpm *.jpg *.tif)");

    // renew the stack
    m_images->setFileNames(files);

    // refresh the list view on the left to show the latest filenames
    m_imageListView->updateStack(m_images);

    // clear the status bar
    ui->statusBar->clearMessage();

    // save the directory
    if (files.count()) {
        m_lastOpenDir = files.first();

        QSettings settings;
        settings.setValue("filemanager/openDir", m_lastOpenDir);
    }

    // test - pixmap of stack
    QImage img(512, 512, QImage::Format_Grayscale8);
    for (int i = 0; i < 512; i++) {
        for (int j = 0; j < 512; j++) {
            quint8 temp8 = m_images->stack().data(i, j, 0);
            qDebug() << temp8;
            QRgb rgb = qRgb(temp8,temp8,temp8);
            img.setPixel(i, j, rgb);
        }
    }
    ui->lblSelectedFile->setPixmap(QPixmap::fromImage(img));
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

    // show the image, if it is available
    //ui->lblSelectedFile->setPixmap(image->pixmap());
}
