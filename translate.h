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
    QVector< QMap<QString , float> > vector;
    QMap<QString,int> all_variables;
    QVector<float> coefs;
    QVector<QString> variables;

    translate();

    void set_data(QString);
    bool parse();
};

#endif // TRANSLATE_H
