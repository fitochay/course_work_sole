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

int translate::parse()
{
    temp_vector.clear();
    vector.clear();
    all_variables.clear();
    results.clear();

    QString temp_str;
    int i = 0;
    while ( i < data.size() ) //set temp_vector
    {
        while ( data[i] != ' ' && data[i] != '\n' && data[i] != '{' && data[i] != '}' &&
                data[i] != ';' && data[i] != '+' && data[i] != '-' && data[i] != '=' &&
                data[i] != '*' && data[i] != '/' && data[i] != '\\' && i < data.size() )
        {
            temp_str += data[i++];
        }

        if ( data[i] == ';' || data[i] == '{' || data[i] == '}' || data[i] == '+' ||
             data[i] == '-' || data[i] == '=' || data[i] == '/' || data[i] == '*' ||
             data[i] == '\\' )
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

    error_pos[0] = 1;
    error_pos[1] = temp_vector.size();
    error_text.clear();

    if ( temp_vector.size() < 4 )
    {
        if ( temp_vector.size() == 0 )
        {
            error_pos[0] = 0;
            error_pos[1] = 0;
            error_text = "[Error] Не задана система!";
        }
        else if ( temp_vector[0] != "begin" )
        {
            error_pos[0] = 0;
            error_pos[1] = 0;
            error_text = "[Error] Конструкция должна начинаться со слова 'begin'!";
        }
        else if ( temp_vector[1] != "{" )
        {
            error_pos[0] = 1;
            error_pos[1] = 1;
            error_text = "[Error] После 'begin' должна идти '{'!";
        }
        else if ( temp_vector[temp_vector.size() - 2] != "}" )
        {
            error_pos[0] = temp_vector.size() - 2;
            error_pos[1] = temp_vector.size() - 2;
            error_text = "[Error] СЛАУ должна заканчиваться '}'!";
        }
        else if ( temp_vector[temp_vector.size() - 1] != "end")
        {
            error_pos[0] = temp_vector.size() - 1;
            error_pos[1] = temp_vector.size() - 1;
            error_text = "[Error] Конструкция должна заканчиваться словом 'end'!";
        }

        return 1;
    }
    else
    {
        if ( temp_vector[0] != "begin" )
        {
            error_pos[0] = 0;
            error_pos[1] = 0;
            error_text = "[Error] Конструкция должна начинаться со слова 'begin'!";
            return 1;
        }
        else
        {
            if ( temp_vector[1] != "{" )
            {
                error_pos[0] = 1;
                error_pos[1] = 1;
                error_text = "[Error] После 'begin' должна идти '{'!";
                return 1;
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
                            temp_vector[i] != "=" && temp_vector[i] != "*" && temp_vector[i] != "/" &&
                            temp_vector[i] != "{" && temp_vector[i] != "}" )
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
                                if ( temp_vector[i][j] == "." )
                                    dot = true;
                            }
                            else
                            {
                                error_pos[0] = i;
                                error_pos[1] = j;
                                error_text = "[Error] В вещественном числе встречено больше одной точки!";
                                return -1;
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

                        if ( j >= temp_vector[i].size())
                        {
                            if ( temp_vector[i+1][0] >= 'a' && temp_vector[i+1] <= 'z' )
                            {
                                error_pos[0] = i;
                                error_pos[1] = i + 1;
                                error_text = "[Error] Между коэффициентом и переменной не может быть пробела!";
                                return 1;
                            }
                            else if ( temp_vector[i+1][0] >= '0' && temp_vector[i+1][0] <= '9' )
                            {
                                error_pos[0] = i;
                                error_pos[1] = i + 1;
                                error_text = "[Error] В коэффициенте не может быть пробела!";
                                return 1;
                            }
                            else
                            {
                                error_pos[0] = i;
                                error_pos[1] = i + 1;
                                error_text = "[Error] В коэффициенте не может быть '" + temp_vector[i+1] + "'!";
                                return 1;
                            }
                        }

                        while( ( temp_vector[i][j].toLower() >= 'a' &&
                                 temp_vector[i][j].toLower() <= 'z' ) ||
                               ( temp_vector[i][j] >= '0' && temp_vector[i][j] <= '9' ) ) //переменная
                        {
                            temp_var += temp_vector[i][j];
                            j++;
                        }

                        if ( j < temp_vector[i].size() -1 )
                        {
                            error_pos[0] = i;
                            error_pos[1] = j;
                            error_text = "[Error] В названии переменной допускаются только латинский алфавит и цифры!";
                            return -1;
                        }
                        else if ( temp_vector[i] != "+" && temp_vector[i] != "-" && temp_vector[i] != "=" )
                        {
                            if ( temp_vector[i+1] == "+" || temp_vector[i+1] == "-" || temp_vector[i+1] == "=" )
                            {
                                if ( temp_vector[i+2] == "+" || temp_vector[i+2] == "-" || temp_vector[i+2] == "=" )
                                {
                                    error_pos[0] = i + 2;
                                    error_pos[1] = i + 2;
                                    error_text = "[Error] После '+', '-', '=' может идти только переменная или коэффициент!";
                                    return 1;
                                }

                            }
                            else if ( temp_vector[i+1] != "+" && temp_vector[i+1] != "-" && temp_vector[i+1] != "=" )
                            {
                                QString asd = temp_vector[i+1];
                                error_pos[0] = i + 1;
                                error_pos[1] = i + 1;
                                error_text = "[Error] После переменной могут идти только '+', '-' или '='!";
                                return 1;
                            }
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

                            if ( !all_variables.count( temp_var ) )
                            {
                                all_variables.insert( temp_var , 0 );
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
                        i ++; int j;
                        for ( j = 0; j < temp_vector[i].size(); j ++)
                        {
                            if ( !( temp_vector[i][j] >= '0' && temp_vector[i][j] <= '9' ) )
                            {
                                error_pos[0] = i;
                                error_pos[1] = j;
                                error_text = "[Error] В правой части допускается только число!";
                                return -1;
                            }
                        }

                        vector[k].insert("=", temp_vector[i].toFloat());

                        if ( temp_vector[++ i] == ";" )
                        {
                            i ++;
                            k ++;
                            continue;
                        }
                        else
                        {
                            if ( temp_vector[i][0] >= '0' && temp_vector[i][0] <= '9' )
                            {
                                error_pos[0] = i - 1;
                                error_pos[1] = i;
                                error_text = "[Error] В коэффициенте не может быть пробела!";
                                return 1;
                            }
                            else if ( temp_vector[i] == "}" )
                            {
                                error_pos[0] = i;
                                error_pos[1] = i;
                                error_text = "[Error] Уравнение должно заканчиваться ';'!";
                                return 1;
                            }
                            else
                            {
                                error_pos[0] = i-1;
                                error_pos[1] = i-1;
                                error_text = "[Error] В правой части может быть только коэффициент!";
                                return 1;
                            }
                        }
                    }
                    else if ( temp_vector[i] == "*" || temp_vector[i] == "/")
                    {
                        error_pos[0] = i;
                        error_pos[1] = i;
                        error_text = "[Error] В СЛАУ не может быть '*' или '/'!";
                        return 1;
                    }
                    else if ( temp_vector[i] == "{" )
                    {
                        error_pos[0] = i;
                        error_pos[1] = i;
                        error_text = "[Error] В контсрукции не может быть несколько '{'!";
                        return 1;
                    }
                    else if ( temp_vector[i] == "}" && i < temp_vector.size() -2)
                    {
                        if ( temp_vector.count("}") > 1 )
                        {
                            error_pos[0] = temp_vector.size()-2;
                            error_pos[1] = temp_vector.size()-2;
                            error_text = "[Error] В конструкции не может быть несколько '}'!";
                            return 1;
                        }
                        if ( temp_vector[i-2] != "}" || temp_vector[i-1] != "end")
                        {
                            error_pos[0] = temp_vector.size() -2;
                            error_pos[1] = temp_vector.size() -1;
                            error_text = "[Error] Конструкция должна заканчиваться на '} end'!";
                            return 1;
                        }
                    }
                    else if ( temp_vector[i] == ";" && temp_vector[i-1] == ";" )
                    {
                        error_pos[0] = i-1;
                        error_pos[1] = i;
                        error_text = "[Error] Не может идти несколько ';' подряд!";
                        return 1;
                    }
                }

                if ( temp_vector[temp_vector.size() -2] != "}" )
                {
                    error_pos[0] = temp_vector.size() - 2;
                    error_pos[1] = temp_vector.size() - 2;
                    error_text = "[Error] СЛАУ должна заканчиваться '}'!";
                    return 1;
                }
                else if ( temp_vector[temp_vector.size() -1] != "end" )
                {
                    error_pos[0] = temp_vector.size() - 1;
                    error_pos[1] = temp_vector.size() - 1;
                    error_text = "[Error] Конструкция должна заканчиваться словом 'end'!";
                    return 1;
                }
            }
        }
    }

    for ( int i = 0; i < vector.size(); i ++)
    {
        for ( QMap< QString, int >::iterator it = all_variables.begin(); it != all_variables.end(); it ++)
        {
            if ( !vector[i].count( it.key() ) )
            {
                vector[i].insert(it.key(), 0);
            }
        }
    }

    gauss();
    return 0;
}

int translate::gauss()
{
    double **a, *y;
    int n = vector.size();

    a = new double*[n];
    y = new double[n];
    for (int i = 0; i < n; i++)
    {
        a[i] = new double[n];

        QMap< QString, float >::iterator it = vector[i].begin();
        it ++;
        int j = 0;

        while (it != vector[i].end())
        {
            a[i][j] = it.value();
            j ++;
            it ++;
        }
    }

    for (int i = 0; i < n; i ++)
    {
        y[i] = vector[i]["="];
    }

    double *x, max;
    int k, index;
    const double eps = 0.00001;  // точность
    x = new double[n];
    k = 0;
    while (k < n)
    {
        // Поиск строки с максимальным a[i][k]
        max = abs(a[k][k]);
        index = k;
        for (int i = k + 1; i < n; i++)
        {
            if (abs(a[i][k]) > max)
            {
                max = abs(a[i][k]);
                index = i;
            }
        }
        // Перестановка строк
        if (max < eps)
        {
            error_pos[0] = 0;
            error_pos[1] = 0;
            error_text = "[Error] Нет ненулевых диагональных элементов!";
            // нет ненулевых диагональных элементов
            //Решение получить невозможно из-за нулевого столбца
            return 1;
        }
        for (int j = 0; j < n; j++)
        {
            double temp = a[k][j];
            a[k][j] = a[index][j];
            a[index][j] = temp;
        }
        double temp = y[k];
        y[k] = y[index];
        y[index] = temp;
        // Нормализация уравнений
        for (int i = k; i < n; i++)
        {
            double temp = a[i][k];
            if (abs(temp) < eps) continue; // для нулевого коэффициента пропустить
            for (int j = 0; j < n; j++)
                a[i][j] = a[i][j] / temp;
            y[i] = y[i] / temp;
            if (i == k)  continue; // уравнение не вычитать само из себя
            for (int j = 0; j < n; j++)
                a[i][j] = a[i][j] - a[k][j];
            y[i] = y[i] - y[k];
        }
        k++;
    }
    // обратная подстановка
    for (k = n - 1; k >= 0; k--)
    {
        x[k] = y[k];
        for (int i = 0; i < k; i++)
            y[i] = y[i] - a[i][k] * x[k];
    }

    int i = 0;
    for ( QMap< QString, int >::iterator it = all_variables.begin(); it != all_variables.end(); it ++, i ++)
    {
        results.insert(it.key(), x[i]);
    }

    return 0;
}
