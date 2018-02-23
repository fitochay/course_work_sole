#include "gauss.h"

gauss::gauss(int *n)
{
    set_size(n);
    init_matrix();
}

void gauss::set_size(int *n)
{
    this->n = *n;
}

void gauss::set_matrix(float **array)
{
    for (unsigned int i = 0; i < n; i ++)
    {
        for (unsigned int j = 0; j < n; j ++)
        {
            matrix[i][j] = array[i][j];
        }
    }
}

bool gauss::check_variables()
{
    if (variables.size() != n)
    {
        return false;
    }
    else
    {
        return true;
    }
}

std::string gauss::calculate()
{

}

void gauss::init_matrix()
{
    matrix = new float*[n];
    for (unsigned int i = 0; i < n; i++)
    {
        matrix[i] = new float[n];
    }
}
