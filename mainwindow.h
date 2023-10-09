#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>

#include "database_manager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void cartesian_product(QTableWidget* left, QTableWidget* right, QTableWidget* result){
        int leftRows = left->rowCount();
        int leftCols = left->columnCount();


        int rightRows = right->rowCount();
        int rightCols = right->columnCount();

        result->setRowCount(leftRows * rightRows);
        result->setColumnCount(leftCols + rightCols);

        for (int i = 0; i < leftCols; ++i) {
            QTableWidgetItem* headerItem = left->horizontalHeaderItem(i);
            if (headerItem) {
                result->setHorizontalHeaderItem(i, new QTableWidgetItem(headerItem->text()));
            }
        }
        for (int i = 0; i < rightCols; ++i) {
            QTableWidgetItem* headerItem = right->horizontalHeaderItem(i);
            if (headerItem) {
                result->setHorizontalHeaderItem(leftCols + i, new QTableWidgetItem(headerItem->text()));
            }
        }

        int resultRowIndex = 0;
        for (int leftRowIndex = 0; leftRowIndex < leftRows; ++leftRowIndex) {
            for (int rightRowIndex = 0; rightRowIndex < rightRows; ++rightRowIndex) {
                for (int leftColIndex = 0; leftColIndex < leftCols; ++leftColIndex) {
                    QTableWidgetItem* leftItem = left->item(leftRowIndex, leftColIndex);
                    if (leftItem) {
                        result->setItem(resultRowIndex, leftColIndex, new QTableWidgetItem(leftItem->text()));
                    }
                }
                for (int rightColIndex = 0; rightColIndex < rightCols; ++rightColIndex) {
                    QTableWidgetItem* rightItem = right->item(rightRowIndex, rightColIndex);
                    if (rightItem) {
                        result->setItem(resultRowIndex, leftCols + rightColIndex, new QTableWidgetItem(rightItem->text()));
                    }
                }
                ++resultRowIndex;
            }
        }
    }

private slots:
    void on_createDb_triggered();

    void on_deleteDb_triggered();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();


    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    database_manager* manager__;
};
#endif // MAINWINDOW_H
