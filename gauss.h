#ifndef GAUSS_H
#define GAUSS_H

#include <vector>
#include <string>
//наверное стоит переделать
//использование qtlib?
class gauss
{
public:
    float **matrix;
    std::vector<std::string> variables;
    unsigned int n;

    gauss(int*);
    void set_matrix(float**);
    bool check_variables();
    std::string calculate();

    //проверять на соблюдение условий гаусса
private:
    void set_size(int*);
    void init_matrix();
};

#endif // GAUSS_H
