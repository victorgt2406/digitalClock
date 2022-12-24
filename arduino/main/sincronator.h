#ifndef SINCRONATOR_H
#define SINCRONATOR_H

class Sincronator
{
private:
    //control half of a second
    unsigned long millis_half_second;
public:
    Sincronator();
    ~Sincronator();

    bool is_half_second();
};

#endif