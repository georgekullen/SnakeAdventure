// Copyright 2020 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.

// This header has all the (extern) declarations of the globals.
// "extern" means "this is instantiated somewhere, but here's what the name
// means.
#include "globals.h"

#include "hardware.h"

// We need to actually instantiate all of the globals (i.e. declare them once
// without the extern keyword). That's what this file does!

// Hardware initialization: Instantiate all the things!
uLCD_4DGL uLCD(p9,p10,p11);             // LCD Screen (tx, rx, reset)
//SDFileSystem sd(p5, p6, p7, p8, "sd");  // SD Card(mosi, miso, sck, cs)
Serial pc(USBTX,USBRX);                 // USB Console (tx, rx)
MMA8452 acc(p28, p27, 100000);        // Accelerometer (sda, sdc, rate)
DigitalIn button1(p21);                 // Pushbuttons (pin)
DigitalIn button2(p22);
DigitalIn button3(p23);
AnalogOut DACout(p18);                  // Speaker (pin)
PwmOut speaker(p26);
wave_player waver(&DACout);


// Some hardware also needs to have functions called before it will set up
// properly. Do that here.
int hardware_init()
{
    // Crank up the speed
    uLCD.baudrate(3000000);
    pc.baud(115200);
        
    //Initialize pushbuttons
    button1.mode(PullUp); 
    button2.mode(PullUp);
    button3.mode(PullUp);
    
    return ERROR_NONE;
}

// Implement this function.
// HINT: lookup your accelerometer under mbed site > Hardware> Components
// and look at demo code
GameInputs read_inputs() 
{
    GameInputs in;

    //Read pushbuttons
    in.b1 = button1.read();
    in.b2 = button2.read();
    in.b3 = button3.read();
    
    //read accelerometer values
    acc.readXGravity(&in.ax);
    acc.readYGravity(&in.ay);
    acc.readZGravity(&in.az);

    return in;
}

void playGameOverSound() {
    speaker.period(1.0/300.0); // 500hz period
    speaker =0.5; //50% duty cycle - max volume
    wait(0.25);
    speaker.period(1.0/250.0); // 500hz period
    speaker =0.5; //50% duty cycle - max volum
    wait(0.25);
    speaker.period(1.0/200.0); // 500hz period
    speaker =0.5; //50% duty cycle - max volume
    wait(0.25);
    speaker = 0;
}
void playGoodieSound() {
    speaker.period(1.0/500.0); // 500hz period
    speaker =0.3; //50% duty cycle - max volume
    wait(0.25);
    speaker = 0;
}