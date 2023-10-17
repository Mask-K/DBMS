#ifndef CARTESIAN_PRODUCT_H
#define CARTESIAN_PRODUCT_H

#include <QTableWidget>


inline void cartesian_product(QTableWidget* left, QTableWidget* right, QTableWidget* result){
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
    for (int leftRowIndex = 0; leftRowIndex < leftRows - (leftRows > 1 ? 1 : 0); ++leftRowIndex) {
        for (int rightRowIndex = 0; rightRowIndex < rightRows - (rightRows > 1 ? 1 : 0); ++rightRowIndex) {
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



#endif // CARTESIAN_PRODUCT_H
