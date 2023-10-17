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



private slots:
    void on_createDb_triggered();

    void on_deleteDb_triggered();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();


    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_saveDb_triggered();

    void on_openDb_triggered();

private:
    Ui::MainWindow *ui;
    database_manager* manager__;

    bool saveDb(QString filePath);
};
#endif // MAINWINDOW_H
