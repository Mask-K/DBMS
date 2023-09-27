#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,manager__(new database_manager)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_createDb_triggered()
{
    if(manager__->get_database())
        return;
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Створення бдшки");

    QLineEdit *lineEdit = new QLineEdit(dialog);
    lineEdit->setPlaceholderText("Введіть назву бд");



    QPushButton *okButton = new QPushButton("OK", dialog);

    connect(okButton, &QPushButton::clicked, [=]() {
        QString enteredText = lineEdit->text();
        database* db = new database(enteredText);
        manager__->set_database(std::move(db));

        dialog->accept();
    });

    QVBoxLayout *layout = new QVBoxLayout(dialog);
    layout->addWidget(lineEdit);
    layout->addWidget(okButton);

    dialog->exec();

    delete dialog;
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
    }
}

