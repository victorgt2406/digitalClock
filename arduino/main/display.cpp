#include "display.h"

#define MAX_WIDTH 3
#define MAX_LENGTH 5
#define MAX_NUMBERS 10
#define TEMP_APROX 5

bool numbers_5x3[MAX_NUMBERS][MAX_LENGTH][MAX_WIDTH] = {
    //0
    {
        {1,1,1},
        {1,0,1},
        {1,0,1},
        {1,0,1},
        {1,1,1}
    },
    //1
    {
        {0,0,1},
        {0,1,1},
        {0,0,1},
        {0,0,1},
        {0,0,1}
    },
    //2
    {
        {1,1,1},
        {0,0,1},
        {1,1,1},
        {1,0,0},
        {1,1,1}
    },
    //3
    {
        {1,1,1},
        {0,0,1},
        {1,1,1},
        {0,0,1},
        {1,1,1}
    },
    //4
    {
        {1,0,1},
        {1,0,1},
        {1,1,1},
        {0,0,1},
        {0,0,1}
    },
    //5
    {
        {1,1,1},
        {1,0,0},
        {1,1,1},
        {0,0,1},
        {1,1,1}
    },
    //6
    {
        {1,1,1},
        {1,0,0},
        {1,1,1},
        {1,0,1},
        {1,1,1}
    },
    //7
    {
        {1,1,1},
        {0,0,1},
        {0,0,1},
        {0,1,0},
        {1,0,0}
    },
    //8
    {
        {1,1,1},
        {1,0,1},
        {1,1,1},
        {1,0,1},
        {1,1,1}
    },
    //9
    {
        {1,1,1},
        {1,0,1},
        {1,1,1},
        {0,0,1},
        {0,0,1}
    }
};

Display::Display(){
  matrix = NULL;
}

Display::Display(Adafruit_NeoMatrix* m){
  this->matrix = m;
  this->dots_on = false;
}

Display::~Display(){

}

void Display::update_all_data(data_t data){
  this->data = data;
}

void Display::update_half_second(){
  /*If dots are on it will add a second*/
  if(dots_on){
    this->data.time.sec++;
  }
  if(this->data.time.sec>=60){
      this->data.time.min++;
      this->data.time.sec = 0;
  }
  if(this->data.time.min>=60){
      this->data.time.hour++;
      this->data.time.min = 0;
  }
  if(this->data.time.hour>=24){
      this->data.date.day++;
      this->data.date.weekday++;
      this->data.time.hour = 0;
  }
  if(this->data.date.weekday>=7){
    this->data.date.weekday=0;
  }

  this->print_dots();
  if(this->dots_on){
    this->dots_on=false;
  }
  else{
    this->dots_on=true;
  }
  this->update_display();
}

void Display::update_display(){
  this->set_month(this->data.date.month);
  this->set_day(this->data.date.day);
  this->set_weekday(this->data.date.weekday);
  this->set_hour(this->data.time.hour);
  this->set_min(this->data.time.min);
  this->set_temp(this->data.weather.temp);

  this->matrix->show();
}

void Display::set_month(int value){
  //1(row), 9(column)
  if(value < 1 || value > 12){
    value = 1;
  }
  int month_value = value-1;
  int row = month_value / 2;
  int col = month_value % 2;
  for(int i=0; i<6; i++){
    for(int j=0; j<2; j++){
      this->matrix->writePixel(j+9,i+1,0);
    }
  }
  this->matrix->writePixel(9+col,1+row,this->matrix->Color(0,255,0));
}

void Display::set_day(int value){
  this->print_2digit(2,1,value,matrix->Color(0,255,0));
}

void Display::set_weekday(int value){
  for(int i=0; i<7;i++){
    if(value == i){
      this->matrix->writePixel(1+i,0,matrix->Color(0,255,0));
    }
    else{
      this->matrix->writePixel(1+i,0,0);
    }
  }
}

void Display::set_hour(int value){
  this->print_2digit(2,13,value,matrix->Color(0,255,0));
}

void Display::set_min(int value){
  this->print_2digit(2,22,value,matrix->Color(0,255,0));
}

void Display::set_temp(int value){
  //0,13
  int min_temp = -30;
  int max_temp = 50;
  if(value < min_temp){
    value = min_temp;
  }
  if(value > max_temp){
    value = max_temp;
  }
  value+=(min_temp*(-1));
  int positions = (value/TEMP_APROX)+1;
  for(int i=0; i<positions; i++){
    this->matrix->writePixel(13+i,0,matrix->Color(0,255,0));
  }
}

void Display::print_digit(int row, int col, int value, uint16_t color){
  if(value >=0 && value <=9){
    //rows (length)
    for(int i=0; i<MAX_LENGTH; i++){
      //columns (width)
      for(int j=0; j<MAX_WIDTH; j++){
        //it means it has to paint
        if(numbers_5x3[value][i][j]){
          matrix->writePixel(j+col,i+row,color);
        }
        //it means it has to earase
        else{
          matrix->writePixel(j+col,i+row,0);
        }
      }
    }
  }
}

void Display::print_2digit(int row, int col, int value, uint16_t color){
  if(value>=0 && value<=99){
    int digit1=0;
    int digit2=0;
    if(value<=9){
      digit2=value;
    }
    else{
      digit1 = value/10;
      digit2 = value%10;
    }
    print_digit(row,col,digit1,color);
    print_digit(row,col+MAX_WIDTH+1,digit2,color);
  }
}

void Display::print_dots(){
  uint16_t color = 0;
  if(this->dots_on){
    color = this->matrix->Color(0,255,0);
  }
  //20,3
  this->matrix->writePixel(20,3,color);
  this->matrix->writePixel(20,5,color);

  this->matrix->writePixel(21,3,color);
  this->matrix->writePixel(21,5,color);
}