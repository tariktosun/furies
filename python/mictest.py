import alsaaudio as alsa
import numpy as np   
from matplotlib import pyplot as plt
from matplotlib import animation
import time

#Configuration

card = 'default'
audio = alsa.PCM(alsa.PCM_CAPTURE,alsa.PCM_NONBLOCK, card)

def configure():
    #plt.ion()
    audio.setchannels(1)
    audio.setrate(44100)
    audio.setformat(alsa.PCM_FORMAT_S16_LE)
    audio.setperiodsize(1000)

configure()
captured = np.ndarray(0)
for i in xrange(1,100000):
    length, data = audio.read()
    npdata = np.fromstring(data, dtype='<i2')
    captured = np.concatenate((captured, npdata))
plt.plot(captured)
plt.show()
# if you say something, you will see the waveform =)