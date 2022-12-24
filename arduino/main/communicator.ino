#include "communicator.h"

bool look_serial(data_t *data)
{
  bool update = false;
  String serial_msg;
  if (Serial.available() != 0)
  {
    // Message from serial:
    serial_msg = "";
    serial_msg += Serial.readString();
    Serial.print("recibido: " + serial_msg);
    /*The message reciebed, should be like:
    D:YEAR;MONTH;DAY;DAYWEEK
    T:HOUR;MINUTE;SECOND
    W:TEMP
    !! All of them should be numbers !!
    */
    update_data(serial_msg, data);
    update = true;
  }
  return update;
}

void update_data(String str, data_t *data)
{
  String str_data = getStrData(str);
  if (str.charAt(0) == 'T')
  {
    data->time = str_to_time(str_data);
  }
  if (str.charAt(0) == 'D')
  {
    data->date = str_to_date(str_data);
  }
  if (str.charAt(0) == 'W')
  {
    data->weather = str_to_weather(str_data);
  }
}

String getStrData(String str)
{
  return str.substring(2, str.length());
}

date_t str_to_date(String str)
{
  date_t res;

  int index = str.indexOf(';');
  res.year = str.substring(0, index).toInt();
  str = str.substring(index + 1, str.length());

  index = str.indexOf(';');
  res.month = str.substring(0, index).toInt();
  str = str.substring(index + 1, str.length());

  index = str.indexOf(';');
  res.day = str.substring(0, index).toInt();
  str = str.substring(index + 1, str.length());

  res.weekday = str.toInt();
  return res;
}

time_t str_to_time(String str)
{
  time_t res;

  int index = str.indexOf(';');
  res.hour = str.substring(0, index).toInt();
  str = str.substring(index + 1, str.length());

  index = str.indexOf(';');
  res.min = str.substring(0, index).toInt();
  str = str.substring(index + 1, str.length());

  res.sec = str.toInt();
  return res;
}

weather_t str_to_weather(String str)
{
  weather_t res;

  int index = str.indexOf(';');
  res.temp = str.substring(0, index).toFloat();
  str = str.substring(index + 1, str.length());

  index = str.indexOf(';');
  res.temp_min = str.substring(0, index).toFloat();
  str = str.substring(index + 1, str.length());

  res.temp_max = str.toFloat();
  return res;
}
