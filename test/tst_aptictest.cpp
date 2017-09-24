#include <QString>
#include <QtTest>

class ApticTest : public QObject
{
    Q_OBJECT

public:
    ApticTest();

private Q_SLOTS:
    void testCase1();
};

ApticTest::ApticTest()
{
}

void ApticTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(ApticTest)

#include "tst_aptictest.moc"
