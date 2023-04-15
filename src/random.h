#ifndef RANDOM_H
#define RANDOM_H
#include <QRandomGenerator>

class random
{
private:
    random();

public:
    static int randomNumber(int min, int max);
};

#endif // RANDOM_H
