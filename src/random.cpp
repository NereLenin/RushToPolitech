#include "random.h"

random::random()
{

}

int random::randomNumber(int min, int max)
{
    return (QRandomGenerator::global())->bounded(min,max);
}
