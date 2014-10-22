#include "mbed_synth.h"

AnalogOut synth_pin(p18);
AnalogIn freq_pot_in(p20);
AnalogIn vol_pot_in(p19);
DigitalOut led_red(p21);
DigitalOut led_green(p22);
DigitalOut led_blue(p23);

DigitalOut temp(LED3);
DigitalOut tmp(LED2);
MbedSynth audsynth(&synth_pin,&temp);
Serial pc(USBTX, USBRX); // tx, rx

Ticker synth_tick;

float VOLdata;
float FREQdata;

uint16_t freq_arr[] = {16,32,65,130,261,523,1046,2093,4186,7900};

int main(void) 
{

  tmp = 1;
 
  pc.baud(921600);
  audsynth.init_synth(); // Initialize synth
  int samp_us = 1.0/SAMP_FREQ*1e6; // Determine sample period in microseconds
  audsynth.set_freq(7900); // 16-7902
  
  synth_tick.attach_us( &audsynth, &MbedSynth::send_vals, samp_us); // Call send_vals every samp_us
  
  while(1)
  {
      //audsynth.set_freq(notes[octave][C_NOTE]);
      FREQdata=freq_pot_in*10.0;
      //audsynth.newFreq=freq_arr[(int)FREQdata];
      pc.printf("%d\n\r",freq_arr[(int)FREQdata]);
      audsynth.vol=vol_pot_in+0.01;
      //pc.printf("%f\n\r",VOLdata);
      switch(freq_arr[(int)FREQdata])
      {
        case 16:
            led_red=1;
            led_green=0;
            led_blue=0;
            break;
        case 32:
            led_red=1;
            led_green=0;
            led_blue=0;
            break;
        case 65:
            led_red=1;
            led_green=1;
            led_blue=0;
            break;
        case 130:
            led_red=1;
            led_green=0;
            led_blue=1;
            break;
        case 261:
            led_red=1;
            led_green=0;
            led_blue=1;
            break;
        case 523:
            led_red=1;
            led_green=1;
            led_blue=0;
            break;
        case 1046:
            led_red=1;
            led_green=1;
            led_blue=0;
            break;
        case 2093:
            led_red=0;
            led_green=1;
            led_blue=1;
            break;
        case 4186:
            led_red=0;
            led_green=1;
            led_blue=1;
            break;
        case 7900:
            led_red=1;
            led_green=1;
            led_blue=1;
            break;   
        default:
            led_red=1;
            led_green=0;
            led_blue=0;
            break;    
      }
      audsynth.set_freq(freq_arr[(int)FREQdata]);
  }
  
    
}
