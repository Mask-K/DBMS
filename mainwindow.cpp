#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "column_int.h"
#include "column_real.h"
#include "column_char.h"
#include "column_html.h"
#include "column_string.h"
#include "column_string_interval.h"

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QComboBox>

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
    okButton->setEnabled(false); // Початково вимкнути кнопку OK

    connect(okButton, &QPushButton::clicked, [&]() {
        QString enteredText = lineEdit->text();

        database *db = new database(enteredText);
        manager__->set_database(std::move(db));

        this->setWindowTitle(enteredText);
        ui->pushButton->setVisible(true);
        ui->pushButton_2->setVisible(true);

        dialog.accept();
    });

    // Підключення слоту до сигналу textChanged
    connect(lineEdit, &QLineEdit::textChanged, [&]() {
        // Активувати/деактивувати кнопку OK залежно від наявності тексту у полі для введення
        okButton->setEnabled(!lineEdit->text().isEmpty());
    });

    QVBoxLayout layout(&dialog);
    layout.addWidget(lineEdit);
    layout.addWidget(okButton);

    if (dialog.exec() == QDialog::Rejected) {
        // Обробити випадок, коли користувач скасував діалог
    }
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
        ui->pushButton->setVisible(true);
        ui->pushButton_2->setVisible(true);
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    QDialog dialog(this);
    dialog.setWindowTitle("Створення таблиці");

    QLineEdit *lineEdit = new QLineEdit(&dialog);
    lineEdit->setPlaceholderText("Введіть назву таблиці");

    QPushButton *okButton = new QPushButton("OK", &dialog);
    okButton->setEnabled(false); // Початково вимкнути кнопку OK

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

        dialog.accept();
    });

    // Підключення слоту до сигналу textChanged
    connect(lineEdit, &QLineEdit::textChanged, [&]() {
        // Активувати/деактивувати кнопку OK залежно від наявності тексту у полі для введення
        okButton->setEnabled(!lineEdit->text().isEmpty());
    });

    QVBoxLayout layout(&dialog);
    layout.addWidget(lineEdit);
    layout.addWidget(okButton);

    if (dialog.exec() == QDialog::Rejected) {
        // Обробити випадок, коли користувач скасував діалог
    }
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
            }

            //
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

        if(manager__->get_database()->get_table(currentTabIndex).get_columns().size()){
            for(auto& r : manager__->get_database()->get_table(currentTabIndex).get_rows()){
                r.add_cell();
            }
        }

        manager__->get_database()->get_table(currentTabIndex).add_column(colPtr);



        if(!currentTabIndex){
            manager__->get_database()->get_table(currentTabIndex).add_row(row(1));
        }


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

                        if(val != ""){
                            if(manager__->get_database()->get_table(ui->tabWidget->currentIndex()).get_column(col)->validate(val)){
                                manager__->get_database()->get_table(ui->tabWidget->currentIndex())[col][row] = val;
                            }
                            else{
                                item->setText("");
                            }
                        }
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
                            manager__->get_database()->get_table(currentTabIndex).remove_row(row);
                        }
                    } else if (item->row() == currentTableWidget->rowCount() - 1 && !item->text().isEmpty()) {

                        currentTableWidget->setRowCount(currentTableWidget->rowCount() + 1);
                        manager__->get_database()->get_table(ui->tabWidget->currentIndex()).add_row(row(currentTableWidget->columnCount()));
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



