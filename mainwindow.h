#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <gauss.h>
#include <translate.h>
#include <QMessageBox>
#include <QMap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    translate tr1;
    gauss *g;
    float **matrix;
    bool set_matrix();

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H