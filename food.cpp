#include "food.h"

food::food()
{
    this->score = (rand()%3)+2;
    this->invicible = 0;
}

void food::ReInit()
{
    *this = food();
}
