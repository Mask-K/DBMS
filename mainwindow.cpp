#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "column_int.h"
#include "column_real.h"
#include "column_char.h"
#include "column_html.h"
#include "column_string.h"
#include "column_string_interval.h"
#include "cartesian_product.h"

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QComboBox>
#include <QFileDialog>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

#include <string>
#include <memory>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,manager__(new database_manager)
{
    ui->setupUi(this);
    ui->tabWidget->removeTab(1);
    ui->tabWidget->removeTab(0);

    ui->pushButton->setVisible(false);
    ui->pushButton_2->setVisible(false);
    ui->pushButton_3->setVisible(false);
    ui->pushButton_4->setVisible(false);
    ui->pushButton_5->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_createDb_triggered()
{
    if (manager__->get_database())
        return;

    QDialog dialog(this);
    dialog.setWindowTitle("Створення бдшки");

    QLineEdit *lineEdit = new QLineEdit(&dialog);
    lineEdit->setPlaceholderText("Введіть назву бд");

    QPushButton *okButton = new QPushButton("OK", &dialog);
    okButton->setEnabled(false);

    connect(okButton, &QPushButton::clicked, [&]() {
        QString enteredText = lineEdit->text();

        database *db = new database(enteredText);
        manager__->set_database(std::move(db));

        this->setWindowTitle(enteredText);
        ui->pushButton->setVisible(true);
        ui->pushButton_2->setVisible(true);


        dialog.accept();
    });

    connect(lineEdit, &QLineEdit::textChanged, [&]() {
        okButton->setEnabled(!lineEdit->text().isEmpty());
    });

    QVBoxLayout layout(&dialog);
    layout.addWidget(lineEdit);
    layout.addWidget(okButton);


    dialog.exec();
}



void MainWindow::on_deleteDb_triggered()
{
    if(!manager__->get_database())
        return;
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Підтвердження", "Ви впевнені, що хочете видалити базу даних?",
                                  QMessageBox::Yes | QMessageBox::Cancel);

    if (reply == QMessageBox::Yes) {
        auto db = manager__->get_database();
        delete db;
        manager__->set_database(nullptr);
        this->setWindowTitle("DBMS");
        ui->pushButton->setVisible(false);
        ui->pushButton_2->setVisible(false);
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    QDialog dialog(this);
    dialog.setWindowTitle("Створення таблиці");

    QLineEdit *lineEdit = new QLineEdit(&dialog);
    lineEdit->setPlaceholderText("Введіть назву таблиці");

    QPushButton *okButton = new QPushButton("OK", &dialog);
    okButton->setEnabled(false);
    connect(okButton, &QPushButton::clicked, [&]() {
        QString enteredText = lineEdit->text();


        table t{enteredText};
        manager__->get_database()->add_table(t);

        QWidget *newTab = new QWidget();
        QTableWidget *tableWidget = new QTableWidget(newTab);
        ui->tabWidget->addTab(newTab, enteredText);
        newTab->setLayout(new QVBoxLayout());
        newTab->layout()->addWidget(tableWidget);

        ui->pushButton_3->setVisible(true);
        ui->pushButton_4->setVisible(true);
        ui->pushButton_5->setVisible(true);

        dialog.accept();
    });


    connect(lineEdit, &QLineEdit::textChanged, [&]() {
        okButton->setEnabled(!lineEdit->text().isEmpty());
    });

    QVBoxLayout layout(&dialog);
    layout.addWidget(lineEdit);
    layout.addWidget(okButton);

    dialog.exec();
}



void MainWindow::on_pushButton_clicked()
{
    int currentIndex = ui->tabWidget->currentIndex();

    if (currentIndex >= 0) {

        QMessageBox::StandardButton confirmDelete = QMessageBox::question(this,
                                                                          "Підтвердження видалення",
                                                                          "Ви впевнені, що хочете видалити таблицю?",
                                                                          QMessageBox::Yes | QMessageBox::No);

        if (confirmDelete == QMessageBox::Yes) {
            QWidget *widgetToRemove = ui->tabWidget->widget(currentIndex);


            ui->tabWidget->removeTab(currentIndex);

            manager__->get_database()->remove_table(currentIndex);

            if(!ui->tabWidget->count()){
                ui->pushButton_3->setVisible(false);
                ui->pushButton_4->setVisible(false);
                ui->pushButton_5->setVisible(false);
            }


            delete widgetToRemove;
        }
    }
}



void MainWindow::on_pushButton_3_clicked()
{
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Додати колонку");


    QComboBox *typeComboBox = new QComboBox(dialog);

    typeComboBox->addItem("INT");
    typeComboBox->addItem("REAL");
    typeComboBox->addItem("CHAR");
    typeComboBox->addItem("STRING");
    typeComboBox->addItem("HTML");
    typeComboBox->addItem("STRINGINVL");


    QLineEdit *nameLineEdit = new QLineEdit(dialog);
    nameLineEdit->setPlaceholderText("Назва колонки");

    QPushButton *okButton = new QPushButton("OK", dialog);
    okButton->setEnabled(false);

    connect(okButton, &QPushButton::clicked, [=]() {
        QString selectedType = typeComboBox->currentText();
        QString columnName = nameLineEdit->text();


        std::shared_ptr<column> colPtr;

        if (selectedType == "INT")
            colPtr = std::make_shared<column_int>(columnName);
        else if (selectedType == "REAL")
            colPtr = std::make_shared<column_real>(columnName);
        else if (selectedType == "CHAR")
            colPtr = std::make_shared<column_char>(columnName);
        else if (selectedType == "STRING")
            colPtr = std::make_shared<column_string>(columnName);
        else if (selectedType == "HTML")
            colPtr = std::make_shared<column_html>(columnName);
        else
            colPtr = std::make_shared<column_string_interval>(columnName);



        int currentTabIndex = ui->tabWidget->currentIndex();


        manager__->get_database()->get_table(currentTabIndex).add_column(colPtr);



        if (currentTabIndex != -1){
            QWidget *currentTabWidget = ui->tabWidget->widget(currentTabIndex);


            QTableWidget *currentTableWidget = currentTabWidget->findChild<QTableWidget *>();

            if (currentTableWidget) {

                int columnIndex = currentTableWidget->columnCount();
                currentTableWidget->setColumnCount(columnIndex + 1);
                currentTableWidget->setHorizontalHeaderItem(columnIndex, new QTableWidgetItem(columnName + " [" + selectedType + "]"));

                if (currentTableWidget->rowCount() == 0) {
                    currentTableWidget->setRowCount(1);
                }



                connect(currentTableWidget, &QTableWidget::itemChanged, [=](QTableWidgetItem *item) {

                    {
                        int row = item->row();
                        int col = item->column();
                        auto val = (item->text()).toStdString();



                        if(val != "" && !manager__->get_database()->get_table(ui->tabWidget->currentIndex()).get_column(col)->validate(val)){
                                item->setText("");}
                        }


                    if (item->row() != currentTableWidget->rowCount() - 1) {

                        int row = item->row();
                        bool rowIsEmpty = true;

                        for (int col = 0; col < currentTableWidget->columnCount(); ++col) {
                            QTableWidgetItem *cell = currentTableWidget->item(row, col);
                            if (cell && !cell->text().isEmpty()) {
                                rowIsEmpty = false;
                                break;
                            }
                        }


                        if (rowIsEmpty && row >= 0) {
                            currentTableWidget->removeRow(row);
                            }
                    } else if (item->row() == currentTableWidget->rowCount() - 1 && !item->text().isEmpty()) {

                        currentTableWidget->setRowCount(currentTableWidget->rowCount() + 1);
                   }
                });
            }

        }
        dialog->accept();
    });

    QVBoxLayout *layout = new QVBoxLayout(dialog);
    layout->addWidget(typeComboBox);
    layout->addWidget(nameLineEdit);
    layout->addWidget(okButton);


    connect(nameLineEdit, &QLineEdit::textChanged, [=](const QString &text) {

        okButton->setEnabled(!text.isEmpty());
    });

    dialog->exec();


    delete dialog;
}




void MainWindow::on_pushButton_4_clicked()
{
    QDialog dialog(this);
    dialog.setWindowTitle("Видалити колонку");

    QLineEdit *indexLineEdit = new QLineEdit(&dialog);
    indexLineEdit->setPlaceholderText("Введіть індекс колонки");

    QPushButton *okButton = new QPushButton("OK", &dialog);
    okButton->setEnabled(false);

    connect(indexLineEdit, &QLineEdit::textChanged, [&]() {
        okButton->setEnabled(!indexLineEdit->text().isEmpty());
    });

    connect(okButton, &QPushButton::clicked, [&]() {
        bool ok;
        int columnIndex = indexLineEdit->text().toInt(&ok);

        if (!ok || columnIndex < 0) {
            QMessageBox::warning(this, "Помилка", "Введіть дійсний позитивний індекс колонки.");
        } else {

            int currentTabIndex = ui->tabWidget->currentIndex();

            if (currentTabIndex != -1) {

                QWidget *currentTabWidget = ui->tabWidget->widget(currentTabIndex);
                QTableWidget *currentTableWidget = currentTabWidget->findChild<QTableWidget *>();

                if (currentTableWidget) {

                    if (columnIndex < currentTableWidget->columnCount()) {

                        currentTableWidget->removeColumn(columnIndex);

                        manager__->get_database()->get_table(currentTabIndex).remove_column(columnIndex);

                        // Adjusting the row count to remove empty rows
                        int rowCount = currentTableWidget->rowCount();
                        for (int row = rowCount - 2; row >= 1; --row) {
                            bool hasData = false;
                            for (int col = 0; col < currentTableWidget->columnCount(); ++col) {
                                QTableWidgetItem *item = currentTableWidget->item(row, col);
                                if (item && !item->text().isEmpty()) {
                                    hasData = true;
                                    break;
                                }
                            }
                            if (!hasData) {
                                currentTableWidget->removeRow(row);
                            } else {
                                break;
                            }
                        }

                    } else {
                        QMessageBox::warning(this, "Помилка", "Недійсний індекс колонки.");
                    }
                }
            }

            dialog.accept();
        }
    });

    QVBoxLayout layout(&dialog);
    layout.addWidget(indexLineEdit);
    layout.addWidget(okButton);

    dialog.exec();
}



void MainWindow::on_pushButton_5_clicked()
{

    QDialog dialog(this);
    dialog.setWindowTitle("Cartesian Product");

    QLineEdit *index1LineEdit = new QLineEdit(&dialog);
    index1LineEdit->setPlaceholderText("Enter Index of Table 1");

    QLineEdit *index2LineEdit = new QLineEdit(&dialog);
    index2LineEdit->setPlaceholderText("Enter Index of Table 2");

    QPushButton *okButton = new QPushButton("OK", &dialog);
    okButton->setEnabled(false);

    connect(index1LineEdit, &QLineEdit::textChanged, [&]() {

        okButton->setEnabled(!index1LineEdit->text().isEmpty() && !index2LineEdit->text().isEmpty());
    });

    connect(index2LineEdit, &QLineEdit::textChanged, [&]() {

        okButton->setEnabled(!index1LineEdit->text().isEmpty() && !index2LineEdit->text().isEmpty());
    });

    connect(okButton, &QPushButton::clicked, [&]() {
        bool ok1, ok2;
        int index1 = index1LineEdit->text().toInt(&ok1);
        int index2 = index2LineEdit->text().toInt(&ok2);

        if (!ok1 || !ok2 || index1 < 0 || index2 < 0) {
            QMessageBox::warning(this, "Error", "Enter valid positive integers for table indexes.");
        } else {

            if (index1 < ui->tabWidget->count() && index2 < ui->tabWidget->count()) {
                dialog.close();

                QWidget *tabWidget1 = ui->tabWidget->widget(index1);
                QWidget *tabWidget2 = ui->tabWidget->widget(index2);

                QTableWidget* table1 = tabWidget1->findChild<QTableWidget *>();
                QTableWidget* table2 = tabWidget2->findChild<QTableWidget *>();

                QDialog resultDialog(this);
                resultDialog.setWindowTitle("Cartesian Product Result");

                QTableWidget *resultTableWidget = new QTableWidget(&resultDialog);

                cartesian_product(table1, table2, resultTableWidget);

                QVBoxLayout layout(&resultDialog);
                layout.addWidget(resultTableWidget);


                resultDialog.showMaximized();
                resultDialog.exec();
            } else {
                QMessageBox::warning(this, "Error", "Table indexes are out of range.");
            }
        }
    });

    QVBoxLayout layout(&dialog);
    layout.addWidget(index1LineEdit);
    layout.addWidget(index2LineEdit);
    layout.addWidget(okButton);

    dialog.exec();
}





void MainWindow::on_saveDb_triggered()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save Database as JSON", "", "JSON Files (*.json)");

    if (!filePath.isEmpty()) {
        // Check if the user provided a .json extension, and add it if missing
        if (!filePath.endsWith(".json", Qt::CaseInsensitive)) {
            filePath += ".json";
        }

        // Save the database to the selected JSON file
        bool success = saveDb(filePath);

        if (success) {
            QMessageBox::information(this, "Success", "Database saved to JSON file.");
        } else {
            QMessageBox::warning(this, "Error", "Failed to save the database to JSON file.");
        }
    }
}

bool MainWindow::saveDb(QString filePath)
{
    // Create a JSON object to represent your database
    QJsonObject dbObject;
    QJsonArray tablesArray;

    int tabCount = ui->tabWidget->count();

    for (int tabIndex = 0; tabIndex < tabCount; ++tabIndex) {
        QWidget* tabWidget = ui->tabWidget->widget(tabIndex);
        QTableWidget* tableWidget = tabWidget->findChild<QTableWidget *>();
        QJsonObject tableObject;
        tableObject["table_name"] = ui->tabWidget->tabText(tabIndex);

        QJsonArray columnTypesArray;
        QJsonArray columnNamesArray;

        for(int tablecolInd = 0; tablecolInd < tableWidget->columnCount(); ++tablecolInd){
            //columnNamesArray.append()
            auto type = manager__->get_database()->get_table(tabIndex).get_column(tablecolInd)->get_type();
            switch (type){
            case TYPE::INT:
                columnTypesArray.append("int");
                break;
            case TYPE::CHAR:
                columnTypesArray.append("char");
                break;
            case TYPE::HTML:
                columnTypesArray.append("html");
                break;
            case TYPE::REAL:
                columnTypesArray.append("real");
                break;
            case TYPE::STRING:
                columnTypesArray.append("string");
                break;
            case TYPE::STRINGINVL:
                columnTypesArray.append("stringInvl");
                break;
            }
        }
        tableObject["columns"] = columnTypesArray;

        int colCount = tableWidget->columnCount();
        QJsonArray rowsArray;
        for(int rowInd = 0; rowInd < tableWidget->rowCount() - 1; ++rowInd){
            QJsonArray row;
            for(int colInd = 0; colInd < colCount; ++colInd){
                auto item = tableWidget->item(rowInd, colInd);
                row.append(item->text());
            }

            rowsArray.append(row);
        }
        tableObject["rows"] = rowsArray;

        tablesArray.append(tableObject);
    }
    dbObject[this->windowTitle()] = tablesArray;


    QJsonDocument jsonDocument(dbObject);

    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        // Write the JSON data to the file
        file.write(jsonDocument.toJson());
        file.close();
        return true; // File saved successfully
    }
    else
    {
        return false; // Error in opening or writing to the file
    }
}



void MainWindow::on_openDb_triggered()
{
    if(manager__->get_database())
        return;

    QString filePath = QFileDialog::getOpenFileName(this, "Open JSON Database", "", "JSON Files (*.json)");

    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Error", "Failed to open the selected file.");
            return;
        }

        // Read all data from the file
        QTextStream fileStream(&file);
        QString jsonString = fileStream.readAll();
        file.close();

        // Convert the JSON data to a QJsonObject
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
        QJsonObject dbObject = jsonDoc.object();

        {
            auto dbName = dbObject.keys().first();
            this->setWindowTitle(dbName);
            database *db = new database(dbName);
            manager__->set_database(std::move(db));
        }



        QJsonArray tablesArray = dbObject[dbObject.keys().first()].toArray();
        int tableInd = 0;
        for (const QJsonValue &tableValue : tablesArray) {
            QJsonObject tableObject = tableValue.toObject();
            QString tableName = tableObject["table_name"].toString();

            table t{tableName};
            manager__->get_database()->add_table(t);
            // Create a new tab
            QWidget* newTab = new QWidget();
            ui->tabWidget->addTab(newTab, tableName);
            newTab->setLayout(new QVBoxLayout());

            // Create a table inside the tab
            QTableWidget* newTable = new QTableWidget(newTab);
            newTab->layout()->addWidget(newTable);


            QJsonArray columnTypesArray = tableObject["columns"].toArray();
            int colIndex = 0;
            newTable->setColumnCount(columnTypesArray.count());

            for (const auto& columnTypeValue : columnTypesArray) {
                QString columnName = columnTypeValue.toString();

                if (columnName == "int")
                    manager__->get_database()->get_table(tableInd).add_column(std::make_shared<column_int>(columnName));
                else if (columnName == "real")
                    manager__->get_database()->get_table(tableInd).add_column(std::make_shared<column_real>(columnName));
                else if (columnName == "char")
                    manager__->get_database()->get_table(tableInd).add_column(std::make_shared<column_char>(columnName));
                else if (columnName == "string")
                    manager__->get_database()->get_table(tableInd).add_column(std::make_shared<column_string>(columnName));
                else if (columnName == "html")
                    manager__->get_database()->get_table(tableInd).add_column(std::make_shared<column_html>(columnName));
                else
                    manager__->get_database()->get_table(tableInd).add_column(std::make_shared<column_string_interval>(columnName));

                newTable->setHorizontalHeaderItem(colIndex, new QTableWidgetItem(columnName));
                ++colIndex;
            }

            // Add rows to the table based on the JSON data
            QJsonArray rowsArray = tableObject["rows"].toArray();
            int rowIndex = 0;
            for (const QJsonValue& rowValue : rowsArray) {
                QJsonArray rowData = rowValue.toArray();
                newTable->insertRow(rowIndex);
                int colIndex = 0;
                for (const QJsonValue& dataValue : rowData) {
                    QString cellData = dataValue.toString();
                    newTable->setItem(rowIndex, colIndex, new QTableWidgetItem(cellData));
                    ++colIndex;
                }
                ++rowIndex;
            }
            if(colIndex)
                newTable->insertRow(rowIndex);

            connect(newTable, &QTableWidget::itemChanged, [=](QTableWidgetItem *item) {

                {
                    int row = item->row();
                    int col = item->column();
                    auto val = (item->text()).toStdString();



                    if(val != "" && !manager__->get_database()->get_table(tableInd).get_column(col)->validate(val)){
                        item->setText("");}
                }


                if (item->row() != newTable->rowCount() - 1) {

                    int row = item->row();
                    bool rowIsEmpty = true;

                    for (int col = 0; col < newTable->columnCount(); ++col) {
                        QTableWidgetItem *cell = newTable->item(row, col);
                        if (cell && !cell->text().isEmpty()) {
                            rowIsEmpty = false;
                            break;
                        }
                    }


                    if (rowIsEmpty && row >= 0) {
                        newTable->removeRow(row);
                    }
                } else if (item->row() == newTable->rowCount() - 1 && !item->text().isEmpty()) {

                    newTable->setRowCount(newTable->rowCount() + 1);
                }
            });
            ++tableInd;
        }
        ui->pushButton_3->setVisible(true);
        ui->pushButton_4->setVisible(true);
        ui->pushButton_5->setVisible(true);
        QMessageBox::information(this, "Success", "Database loaded from JSON file.");
    }
}


