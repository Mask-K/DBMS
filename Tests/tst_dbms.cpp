#include <QtTest>

#include "../column_int.h"
#include "../column_real.h"
#include "../mainwindow.h"

// add necessary includes here

class DBMS : public QObject
{
    Q_OBJECT

public:


private slots:
    void test_int_column();
    void test_real_column();
    void test_table_product();

};



void DBMS::test_int_column()
{
    column_int test("");

    bool test1 = test.validate("12");
    bool test2 = test.validate("12.5");
    bool test3 = test.validate("123a");

    QCOMPARE(test1, true);
    QCOMPARE(test2, false);
    QCOMPARE(test3, false);
}

void DBMS::test_real_column(){
    column_real test("");

    bool test1 = test.validate("12");
    bool test2 = test.validate("12.5");
    bool test3 = test.validate("123a.5");
    bool test4 = test.validate("12,5");

    QCOMPARE(test1, true);
    QCOMPARE(test2, true);
    QCOMPARE(test3, false);
    QCOMPARE(test4, false);

}

void DBMS::test_table_product(){

}

QTEST_APPLESS_MAIN(DBMS)

#include "tst_dbms.moc"
