#ifndef DATA_TYPES_H
#define DATA_TYPES_H

typedef struct time_t{
    int hour;
    int min;
    int sec;
    int mil;
}time_t;
typedef struct date_t{
    int day;
    int month;
    int year;
    int weekday;
}date_t;
//String weekdays[] = {"monday","tuesday","wedneday","thrusday","friday","saturday","sunday"};
typedef struct weather_t
{
    float temp;
    float temp_max;
    float temp_min;
}weather_t;

typedef struct data_t
{
    time_t time;
    date_t date;
    weather_t weather;
}data_t;


#endif
