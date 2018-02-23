#include "translate.h"

translate::translate()
{
    text_error = "";
    pos_begin = 0;
    pos_end = 0;
}

void translate::set_data(QString str)
{
    data = str;
}

bool translate::parse()
{
    variables.clear();
    coefs.clear();
    int i = 0;
    QVector<QString> temp_vector;
    QString temp_str = "";
    if (data.size() < 10)
    {
        text_error = "Ошибка 1"; //недостаточно символов в формуле
        return false;
    }
    else
    {
        //проверить чтобы первое слово было begin
        while ( i < data.size())
        {
            while (data[i] != ' ' && data[i] != '\n' && data[i] != '{' && data[i] != '}' &&
                   data[i] != ';' && i < data.size())
            {
                temp_str += data[i++];
            }
            if (temp_str != "")
            {
                temp_vector.append(temp_str);
            }

            if (data[i] == ';' || data[i] == '{' || data[i] == '}')
            {
                temp_vector.append(QString(data[i]));
            }

            temp_str.clear();
            i++;
        }
        //temp_vector.size должен быть >= 2
        for (int i = 2; i < temp_vector.size(),
             temp_vector[i] != "}"; i ++)
        {
            int j = 0;
            float temp_number = 0;
            //между буквами не может идти цифра
            //проверить на количество точек
            //перед должно быть число
            //после точки должно быть число
            //проверить наличие нескольких одинаковый переменных в строке
            bool dot = false; //встретил ли точку
            bool number = false; //встретил ли число
            QString str_temp_number;
            QString temp_var;
            while ((temp_vector[i][j] >= '0' && temp_vector[i][j] <= '9') || temp_vector[i][j] == '.')
            {
                if ((!dot && temp_vector[i][j] == '.') || temp_vector[i][j] != '.')
                {
                    str_temp_number += temp_vector[i][j];
                }
                else
                {
                    //вывести ошибку. несколько точек
                    return false;
                }
                number = true;
                j++;
            }
            if (!number)
            {
                temp_number = 1;
            }
            else
            {
                temp_number = str_temp_number.toFloat();
            }
            while(temp_vector[i][j] >= 'a' && temp_vector[i][j] <= 'z')
            {
                //между буквами не может идти цифра?
                temp_var += temp_vector[i][j];
                j++;
            }
            if (temp_var != "")
            {
                if (temp_vector[i-1] == "-")
                {
                    temp_number = 0 - temp_number;
                }
                coefs.append(temp_number);
                variables.append(temp_var);
            }
        }

    }
    return true;
}
