#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //QMessageBox message;
    tr1.set_data(ui->textEdit->toPlainText());
    tr1.parse();
//    message.setText(tr1.output);
//    message.show();
//    QMessageBox::information(this, tr("Информация"), tr1.output);
    set_matrix();
}

bool MainWindow::set_matrix()
{
    //мап, чтобы не считать сколько уникальных переменных
    QMap<QString, int> temp_map; //нормально бы сделать
    for (int i = 0; i < tr1.variables.size(); i ++)
    {
        temp_map.insert(tr1.variables[i], 0);
    }

    int n = temp_map.size();
    matrix = new float*[n];
    for (int i = 0; i < n; i++)
    {
        matrix[i] = new float[n];
    }

    int k = 0;
    for (int i = 0; i < n; i ++) //n???
    {
        for (int j = 0; j < n; j ++)
        {
            matrix[i][j] = tr1.coefs[k++];
        }
    }

    g = new gauss(&n);
    g->set_matrix(matrix);
    /* как вообще задавать эту матрицу?
     * может быть нарушен порядок
     * может отсутствовать какая-то переменная (коэф == 0)
     * как-то надо упорядочить переменные с коэффициентами
     * перед тем как создавать матрицу коэффициетов
     */
    g->calculate();
    return true;
}
