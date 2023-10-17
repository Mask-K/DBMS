#include <QtTest>

#include "../column_int.h"
#include "../column_real.h"
#include "../cartesian_product.h"

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


    QTableWidget leftTable;
    leftTable.setRowCount(2);
    leftTable.setColumnCount(2);
    leftTable.setItem(0, 0, new QTableWidgetItem("A"));
    leftTable.setItem(0, 1, new QTableWidgetItem("B"));
    leftTable.setItem(1, 0, new QTableWidgetItem("C"));
    leftTable.setItem(1, 1, new QTableWidgetItem("D"));


    QTableWidget rightTable;
    rightTable.setRowCount(2);
    rightTable.setColumnCount(1);
    rightTable.setItem(0, 0, new QTableWidgetItem("1"));
    rightTable.setItem(1, 0, new QTableWidgetItem("2"));


    QTableWidget resultTable;
    cartesian_product(&leftTable, &rightTable, &resultTable);


    QCOMPARE(resultTable.rowCount(), 4);
    QCOMPARE(resultTable.columnCount(), 3);
    QCOMPARE(resultTable.item(0, 0)->text(), QString("A"));
    QCOMPARE(resultTable.item(0, 1)->text(), QString("B"));
    QCOMPARE(resultTable.item(0, 2)->text(), QString("1"));



    for (int i = 0; i < resultTable.rowCount(); ++i) {
        for (int j = 0; j < resultTable.columnCount(); ++j) {
            delete resultTable.item(i, j);
        }
    }
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    DBMS dbms;

    int result = QTest::qExec(&dbms, argc, argv);

    return result;
}

#include "tst_dbms.moc"
