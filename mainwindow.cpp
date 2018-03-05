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
            ui->textEdit->setTextColor(QColor(201,201,201));
            ui->textEdit->setPlainText(tr1.data);
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
        ui->textEdit->clear();
        int i = 0;
        while ( i < tr1.temp_vector.size() )
        {

            if ( i >= tr1.error_pos[0] && i <= tr1.error_pos[1] )
            {
                ui->textEdit->setTextColor(QColor(255,0,0));
                ui->textEdit->insertPlainText(tr1.temp_vector[i]);
            }
            else
            {
                ui->textEdit->setTextColor(QColor(201,201,201));
                ui->textEdit->insertPlainText(tr1.temp_vector[i]);
            }
            ui->textEdit->insertPlainText(" ");
            if ( tr1.temp_vector[i] == "begin" || tr1.temp_vector[i] == "{" ||
                  tr1.temp_vector[i] == ";" || tr1.temp_vector[i] == "}" || tr1.temp_vector[i] == "end" )
            {
                ui->textEdit->insertPlainText("\n");
            }
            i ++;
            ui->textEdit->setTextColor(QColor(201,201,201));
        }
    }
    else if ( parse == -1 )
    {
        //подсвечивать букву в слове
        ui->label->setText(tr1.error_text);

        QString temp_letter;
        ui->textEdit->clear();
        int i = 0, j = 0;
        while ( i < tr1.temp_vector.size() )
        {
            while ( j < tr1.temp_vector[i].size() )
            {
                if ( i == tr1.error_pos[0] && j == tr1.error_pos[1] )
                {
                    temp_letter = tr1.temp_vector[i][j];
                    ui->textEdit->setTextColor(QColor(255,0,0));
                    ui->textEdit->insertPlainText(temp_letter);
                }
                else
                {
                    temp_letter = tr1.temp_vector[i][j];
                    ui->textEdit->setTextColor(QColor(201,201,201));
                    ui->textEdit->insertPlainText(temp_letter);
                }
                j ++;
            }
            j = 0;
            ui->textEdit->insertPlainText(" ");
            if ( tr1.temp_vector[i] == "begin" || tr1.temp_vector[i] == "{" ||
                  tr1.temp_vector[i] == ";" || tr1.temp_vector[i] == "}" || tr1.temp_vector[i] == "end" )
            {
                ui->textEdit->insertPlainText("\n");
            }
            i ++;
            ui->textEdit->setTextColor(QColor(201,201,201));
        }

    }
//    message.setText(tr1.output);
//    message.show();
//    QMessageBox::information(this, tr("Информация"), tr1.output);
}
