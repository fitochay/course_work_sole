#ifndef TRANSLATE_H
#define TRANSLATE_H

#include <QObject>
#include <QVector>
#include <QMessageBox>
#include <QMap>

class translate
{
public:
    QString data;
    QString text_error;
    int pos_begin;
    int pos_end;
    QString output;
    QVector<QString> temp_vector;
    QVector< QMap<QString , float> > vector;
    QMap<QString,int> all_variables;
    QMap< QString, float > results;

    int error_pos[2];
    QString error_text;

    translate();

    void set_data(QString);
    int parse();

    int gauss();
};

#endif // TRANSLATE_H
