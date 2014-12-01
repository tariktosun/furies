import alsaaudio as alsa  # For accessing the mic
import numpy as np   
from matplotlib import pyplot as plt
from matplotlib import animation
import time
from pyo import *	# for making sounds

#Configuration

card = 'default'
audio = alsa.PCM(alsa.PCM_CAPTURE,alsa.PCM_NONBLOCK, card)

def configure(Fs):
	#plt.ion()
	audio.setchannels(1)
	audio.setrate(Fs)
	audio.setformat(alsa.PCM_FORMAT_S16_LE)
	audio.setperiodsize(1000)

def capture(numCaptures):
	''' Captures the specified number of times.  '''
	captured = np.ndarray(0)
	for i in xrange(1,numCaptures):
	    length, data = audio.read()
	    npdata = np.fromstring(data, dtype='<i2')
	    captured = np.concatenate((captured, npdata))
	return captured

def plotSpectrum(signal):
	''' Returns the frequency spectrum of the audio. '''
	L = len(signal)
	NFFT = 2**np.ceil(np.log2(L))
	Y = np.fft.fft(signal)/L #Y is complex.
	f = Fs/2 * np.linspace(0,1,NFFT/2+1)
	plt.plot(f, 2*np.abs(Y[0:NFFT/2+1]))
	plt.xlabel('frequency')
	plt.ylabel('amplitude')
	plt.show()

Fs = 44100
configure(Fs)
#play a sine wave:
s = Server().boot()
s.start()
a = Sine(mul=0.01).out()
# Capture the audio:
captured = capture(100000)
# Plot spectrum
plotSpectrum(captured)

