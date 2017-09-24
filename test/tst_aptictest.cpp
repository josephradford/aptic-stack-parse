#include <QString>
#include <QtTest>

#include <QStringList>

#include "imagestack.h"
#include "imageobject.h"

class ApticTest : public QObject
{
    Q_OBJECT

public:
    ApticTest();

private Q_SLOTS:
    void testCase1();

private:
    ImageStack m_stack;
};

ApticTest::ApticTest()
{
}

void ApticTest::testCase1()
{
    // populate the list of files we want to load
    QStringList listOfFiles;
    listOfFiles << "../doc/image/stack1/t0001.tif";
    listOfFiles << "../doc/image/stack1/t0002.tif";
    listOfFiles << "../doc/image/stack1/t0000.tif";

    // load the files
    m_stack.setFileNames(listOfFiles);

    // check they are being converted to pixmap OK
    for (int i = 0; i < m_stack.count(); i++) {
        if (m_stack.imageAt(i)->pixmap().isNull()) {
            // it failed
            QFAIL(qPrintable(QString("%1 did not load a valid QPixmap").arg(m_stack.imageAt(i)->displayName())));
        }
    }

    // check the size of the raw data
    // check they can be reconstructed
}

QTEST_MAIN(ApticTest)

#include "tst_aptictest.moc"
