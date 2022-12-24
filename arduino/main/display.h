#ifndef DISPLAY_H
#define DISPLAY_H

//Display
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#include "data_types.h"

class Display{
    public:
        Display();

        Display(Adafruit_NeoMatrix* m);

        ~Display();

        /*It updates all the data*/
        void update_all_data(data_t data);

        /*It should be called every half second*/
        void update_half_second();

        
    private:
        // Collects all the data {time, date, weather}
        data_t data;
        // Controls the time dots of the display
        bool dots_on;
        // The controler of the matrix of leds.
        Adafruit_NeoMatrix* matrix;

        //Updates the data showed in the display
        void update_display();

        /*The function set the value in the display*/
        void set_month(int value);
        
        /*The function set the value in the display*/
        void set_day(int value);

        /*The function set the value in the display*/
        void set_weekday(int value);
        
        /*The function set the value in the display*/
        void set_hour(int value);
        
        /*The function set the value in the display*/
        void set_min(int value);
        
        /*The function set the value in the display*/
        void set_temp(int value);
        
        /*The function prints a number from 0 to 9
        x and y, SHOULD target the TOP LEFT corner
        - The x means row
        - The y means column
        */
        void print_digit(int row, int col, int value, uint16_t color);
        
        /*The function prints a number from 0 to 99
        x and y, SHOULD target the TOP LEFT corner
        - The x means row
        - The y means column
        */
        void print_2digit(int row, int col, int value, uint16_t color);
        
        /*this dots represents half of a second*/
        void print_dots();
        
};
#endif