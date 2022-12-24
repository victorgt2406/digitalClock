#include "sincronator.h"

#define HALF_SECOND 500

Sincronator::Sincronator()
{
    this->millis_half_second = 0;
}

Sincronator::~Sincronator()
{

}

bool Sincronator::is_half_second()
{
    unsigned long time = millis();
    bool half_second = false;
    if((unsigned long)(time - this->millis_half_second) >= HALF_SECOND){
        half_second = true;
        this->millis_half_second = time;
    }
    return half_second;
}