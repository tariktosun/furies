#include "mbed.h"
#define PI 3.1415
#define RES 256

Ticker timer; //interrupt to generate sine wave

AnalogOut sine_wave(p18);
PwmOut outp(p22);
Serial pc(USBTX, USBRX); // tx, rx
AnalogIn inp(p19);

DigitalOut led_red(p24);
DigitalOut led_green(p25);
DigitalOut led_blue(p23);

volatile float ain;
float wt;
float sine_freq;
float new_freq;
float volt_freq;
float sine_period;
float sine_amp;
float sine_vals[256], *sp, *last; //setup array for sine values, a pointer to access the array and one for the end of the array
float volt;

float init_vin =0.0;

void sine();
void sine_table();


int main() 
{
   
    sine_freq = 440;
    //new_freq = 220;
    pc.baud( 9600 );
    sine_amp=3.3/20; // peak to peak sine amplitude in V

    wt = 0.01;
    
    outp.period(0.00001f);  // freq
    outp.write(1.00f);  // 50% duty cycle
    
    sine_table(); 
 
    sine_period=(1000000/sine_freq)/RES; // period between calling sine routine
    timer.attach_us(&sine,sine_period); // start interrupt   
    
    while(1) 
    {  
        volt = inp.read();
        pc.printf("\n\r v_in= %f",volt);
        if(init_vin==volt)
        {
            led_red=1;
            led_green=0;
            led_blue=0;
            new_freq=sine_freq;
        }
        else if(volt>0.2)
        {
            led_red=0;
            led_green=0;
            led_blue=1;
            new_freq=220;
        }
        if(sine_freq!=new_freq)
        {
            sine_freq = sine_freq*(1-wt)+new_freq*wt;
            sine_period=(1000000/sine_freq)/RES; // period between calling sine routine
            timer.attach_us(&sine,sine_period); // start interrupt   
            
        }
        else
        {
            sine_freq=440;
            pc.printf("\n\r sine_freq= %f",sine_freq);
            sine_period=(1000000/sine_freq)/RES; // period between calling sine routine
            timer.attach_us(&sine,sine_period); // start interrupt  
        }
        //pc.printf("\n\r sine_freq= %f",sine_freq);
             
    } //while loop
 }



void sine_table() 
{ // function to load sine values into array and start interrupt
    float *p, i;
    
    sine_amp=sine_amp/3.3; //convert from p/p voltage to percentage
    p=sine_vals; //point to beginning of array
    sp=p; //set sp
    for (i=0; i<RES; i++)
    {
        *p=sine_amp*sin(i*2*PI/RES);
        p++;
    }

    last=p-1; //last element in array

}
    
void sine() 
{ //interrupt fn
    
    if (sp>last) sp=sine_vals; //reset sp back to beginning
    sine_wave.write((*sp)+0.5);
    sp++;
} 
