import alsaaudio as alsa
import numpy as np   
from matplotlib import pyplot as plot
from matplotlib import animation
import time

#Configuration

card = 'default'
audio = alsa.PCM(alsa.PCM_CAPTURE,alsa.PCM_NONBLOCK, card)

def configure():
    plot.ion()
    audio.setchannels(1)
    audio.setrate(44100)
    audio.setformat(alsa.PCM_FORMAT_S16_LE)
    audio.setperiodsize(1000)

def run():
    loops = 100000
    plot.show()
    while loops > 0 :
            loops-=1
            length,data = audio.read()

            if length:
                #converting into a float array
                npdata = np.fromstring(data,dtype='<i2')
                #Obtaining FFT
                freq_list = np.fft.fft(npdata)
                plot.plot(freq_list)
                plot.draw()
                plot.clf()
		plot.xlim(0,1000)
		plot.ylim(-20000, 20000)
		plot.xlabel(np.arange(0.0, length - 1) / length * 44100)
    plot.close()


configure()
run()
