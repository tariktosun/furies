#include "mbed_synth.h"

AnalogOut synth_pin(p18);

PwmOut outp(p22);

DigitalOut led_red(p24);
DigitalOut led_green(p25);
DigitalOut led_blue(p23);

DigitalOut temp(LED3);
DigitalOut tmp(LED2);
MbedSynth audsynth(&synth_pin,&temp);

Ticker synth_tick;

float VOLdata;
float FREQdata;
float sine_freq;
float new_freq;
float alpha;

int main(void) 
{
 
  audsynth.init_synth(); // Initialize synth
  int samp_us = 1.0/SAMP_FREQ*1e6; // Determine sample period in microseconds
  
  sine_freq=440;
  new_freq=220;
  alpha=0.01;
  
  audsynth.set_freq(sine_freq); // 16-7902
  
  synth_tick.attach_us( &audsynth, &MbedSynth::send_vals, samp_us); // Call send_vals every samp_us
  
  while(1)
  {
    /*
    wait(2.0);
    audsynth.freqChange=TRUE;
    audsynth.set_freq(440);
    audsynth.freqChange=FALSE;
    wait(2.0);
    audsynth.freqChange=TRUE;
    audsynth.set_freq(880);
    audsynth.freqChange=FALSE;
    wait(2.0);
    */
    
    wait(0.5);        
    sine_freq = sine_freq + alpha*(new_freq - sine_freq);
    audsynth.freqChange=TRUE;
    audsynth.set_freq(sine_freq);
    audsynth.freqChange=FALSE;
  }
  
    
}