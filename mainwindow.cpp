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
    int parse = tr1.parse();
    if ( parse == 0 )
    {
        int gauss = tr1.gauss();
        if ( gauss == 0 )
        {
            QString result;
            for ( QMap< QString, float >::iterator it = tr1.results.begin(); it != tr1.results.end(); it ++)
            {
                result += it.key() + ": " + QString::number( it.value() ) + "\n";
            }
            ui->label->setText(result);
        }
        else if ( gauss == 1 )
        {
            ui->label->setText(tr1.error_text);
        }
    }
    else if ( parse == 1 )
    {
        //подсвечивать слов[о,а]
        ui->label->setText(tr1.error_text);
    }
    else if ( parse == -1 )
    {
        //подсвечивать букву в слове
        ui->label->setText(tr1.error_text);
    }
//    message.setText(tr1.output);
//    message.show();
//    QMessageBox::information(this, tr("Информация"), tr1.output);
}
