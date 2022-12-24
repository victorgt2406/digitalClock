#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include "data_types.h" 

bool look_serial(data_t* data);
void update_data(String str,data_t* data);
date_t str_to_date(String str);
time_t str_to_time(String str);
weather_t str_to_weather(String str);


#endif
