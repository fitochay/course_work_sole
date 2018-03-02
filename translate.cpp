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
    QVector<QString> temp_vector;
    QString temp_str;
    int i = 0;
    while ( i < data.size() ) //set temp_vector
    {
        while ( data[i] != ' ' && data[i] != '\n' && data[i] != '{' && data[i] != '}' &&
                data[i] != ';' && data[i] != '+' && data[i] != '-' && data[i] != '=' &&
                i < data.size() )
        {
            temp_str += data[i++];
        }



        if ( data[i] == ';' || data[i] == '{' || data[i] == '}' || data[i] == '+' ||
             data[i] == '-' || data[i] == '=' )
        {
            if ( temp_str != "" )
            {
                temp_vector.append(temp_str);
            }
            temp_vector.append(QString(data[i]));
        }
        else if ( temp_str != "" )
        {
            temp_vector.append(temp_str);
        }

        temp_str.clear();
        i++;
    }

    if ( temp_vector.size() < 4 )
    {
        //error
        return false;
    }
    else
    {
        if ( temp_vector[0] != "begin" )
        {
            //error
            return false;
        }
        else
        {
            if ( temp_vector[1] != "{" )
            {
                //error
                return false;
            }
            else
            {
                i = 2;
                int k = 0;
                int j;
                bool neg = false; //negative number
                float num = 0; //number
                bool dot = false; //встретил ли точку
                bool number = false; //встретил ли число
                QString str_temp_number;
                QString temp_var;

                while ( i < temp_vector.size() - 2)
                {
                    while ( i < temp_vector.size() - 2 && temp_vector[i] != ";" &&
                            temp_vector[i] != "=" )
                    {
                        j = 0;

                        if ( temp_vector[i] == "-" )
                        {
                            i ++;
                            neg = true;
                            continue;
                        }

                        while ( ( temp_vector[i][j] >= '0' && temp_vector[i][j] <= '9' ) ||
                                temp_vector[i][j] == '.' ) //коэффициент
                        {
                            if ( ( !dot && temp_vector[i][j] == '.' ) || temp_vector[i][j] != '.' )
                            {
                                if ( neg )
                                {
                                    str_temp_number = "-1";
                                }
                                else
                                {
                                    str_temp_number += temp_vector[i][j];
                                }
                            }
                            else
                            {
                                //dot count > 1
                                return false;
                            }

                            number = true;
                            j++;
                        }

                        if ( !number )
                        {
                            if ( neg )
                            {
                                num = -1;
                            }
                            else
                            {
                                num = 1;
                            }
                        }
                        else
                        {
                            num = str_temp_number.toFloat();
                        }

                        while( temp_vector[i][j].toLower() >= 'a' &&
                               temp_vector[i][j].toLower() <= 'z' ) //переменная
                        {
                            //между буквами не может идти цифра?
                            temp_var += temp_vector[i][j];
                            j++;
                        }

                        if (temp_var != "")
                        {
                            if ( vector.size() <= k )
                            {
                                QMap<QString, float> temp_map;
                                temp_map.insert(temp_var, num);
                                vector.append(temp_map);
                            }
                            else if (vector[k].count(temp_var))
                            {
                                vector[k][temp_var] += num;
                            }
                            else
                            {
                                vector[k].insert(temp_var, num);
                            }
                        }

                        str_temp_number.clear();
                        temp_var.clear();
                        number = false;
                        neg = false;
                        num = 0;
                        i ++;
                    }

                    if ( temp_vector[i] == "=")
                    {
                        i ++;
                        if ( temp_vector[i][0] >= "0" && temp_vector[i] <= "9" )
                        {
                            //coefs.append(temp_vector[++i].toFloat());
                            vector[k].insert("=", temp_vector[i].toFloat());
                        }
                        else
                        {
                            //error no matching last coef
                            return false;
                        }

                        if ( temp_vector[++ i] == ";" )
                        {
                            i ++;
                            k ++;
                            continue;
                        }
                        else
                        {
                            //error уравнение должно заканчиваться на ';'
                            return false;
                        }
                    }
                    else if ( temp_vector[i] != "}" )
                    {
                        //error ! '='
                        //это равно можно обработать при проходе vector'а
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

//bool translate::parse()
//{
//    variables.clear();
//    coefs.clear();
//    int i = 0;
//    QVector<QString> temp_vector;
//    QString temp_str = "";
//    if (data.size() < 10)
//    {
//        text_error = "Ошибка 1"; //недостаточно символов в формуле
//        return false;
//    }
//    else
//    {
//        //проверить чтобы первое слово было begin
//        while ( i < data.size())
//        {
//            while (data[i] != ' ' && data[i] != '\n' && data[i] != '{' && data[i] != '}' &&
//                   data[i] != ';' && i < data.size())
//            {
//                temp_str += data[i++];
//            }
//            if (temp_str != "")
//            {
//                temp_vector.append(temp_str);
//            }

//            if (data[i] == ';' || data[i] == '{' || data[i] == '}')
//            {
//                temp_vector.append(QString(data[i]));
//            }

//            temp_str.clear();
//            i++;
//        }
//        QMap<QString, float> temp_map;
//        //temp_vector.size должен быть >= 2
//        for (int i = 2; i < temp_vector.size(),
//             temp_vector[i] != "}"; i ++)
//        {
//            int j = 0;
//            float temp_number = 0;
//            /* между буквами не может идти цифра
//             * проверить на количество точек
//             * перед должно быть число
//             * после точки должно быть число
//             * проверить наличие нескольких одинаковый переменных в строке
//             */
//            bool dot = false; //встретил ли точку
//            bool number = false; //встретил ли число
//            QString str_temp_number;
//            QString temp_var;
//            while ((temp_vector[i][j] >= '0' && temp_vector[i][j] <= '9') || temp_vector[i][j] == '.' || temp_vector[i][j] == '-') //коэффициент
//            {
//                if ((!dot && temp_vector[i][j] == '.') || temp_vector[i][j] != '.')
//                {
//                    if (temp_vector[i][j] == '-')
//                    {
//                        str_temp_number = -1;
//                    }
//                    else
//                    {
//                        str_temp_number += temp_vector[i][j];
//                    }
//                }
//                else
//                {
//                    //вывести ошибку. несколько точек
//                    return false;
//                }
//                number = true;
//                j++;
//            }

//            if (!number)
//            {
//                temp_number = 1;
//            }
//            else
//            {
//                temp_number = str_temp_number.toFloat();
//            }

//            while(temp_vector[i][j] >= 'a' && temp_vector[i][j] <= 'z') //переменная
//            {
//                //между буквами не может идти цифра?
//                temp_var += temp_vector[i][j];
//                j++;
//            }

//            if (temp_var != "")
//            {
//                if (temp_vector[i-1] == "-")
//                {
//                    temp_number = 0 - temp_number;
//                }

//                if (temp_map.count(temp_var))
//                {
//                    temp_map[temp_var] += temp_number;
//                }
//                else
//                {
//                    temp_map.insert(temp_var, temp_number);
//                }
//            }
//            if (temp_vector[i] == ";")
//            {
//                vector.append(temp_map);
//                temp_map.clear();
//            }
//        }
//        for (int i = 0; i < vector.size(); i ++) //получение списка всех переменных
//        {
//            for (QMap<QString,float>::iterator it = vector[i].begin(); it != vector[i].end(); it ++)
//            {
//                all_variables.insert(it.key(), 0);
//            }
//        }
////        float **matrix = new float*[all_variables.size()];
////        for (unsigned int i = 0; i < all_variables.size(); i++)
////        {
////            matrix[i] = new float[all_variables.size()];
////        }
//        float matrix[all_variables.size()][all_variables.size()];

//        int j = 0;
//        for (int i = 0; i < vector.size(); i ++) //заполнение матрицы коэффициентов
//        {
//            for (QMap<QString,int>::iterator it = all_variables.begin(); it != all_variables.end(); it ++)
//            {
//                if (vector[i].count(it.key()))
//                {
//                    matrix[i][j] = vector[i][it.key()];
//                }
//                else
//                {
//                    matrix[i][j] = 0;
//                }
//                j ++;
//            }
//            j = 0;
//        }

//        QString temp;
//        for (int i = 0; i < all_variables.size(); i ++)
//        {
//            for (int j = 0; j < all_variables.size(); j ++)
//            {
//                temp += QString::number(matrix[i][j]);
//            }
//        }

//        //не отлавливает -a

//        /*
//        begin
//        {
//            2a - b = 0;
//            -a + b + 4c = 13;
//            a + 2b + 3c = 14;
//        }
//        end
//        */


////        while(temp_vector[i] != ";" || temp_vector[i] != "end") заменить конструкцию на этот цикл
////        {

////        }
//    }
//    return true;
//}
