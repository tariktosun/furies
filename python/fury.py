# fury class
from pyo import *
import time

class Fury:
	value = None
	oscillator = None
	neighbors = None
	alpha = 0.01

	def __init__(self,value):
		''' Initializes a fury with specified value. '''
		self.value = value
		self.oscillator = Sine(value, 0, 0.1).out()
		self.neighbors = []
	def setValue(self,value):
		''' Sets fury value as specified '''
		self.value = value
		self.oscillator.setFreq(value)
	def update(self):
		''' Updates the fury based on the values of its neighbors '''
		update = 0
		for neighbor in self.neighbors:
			update += self.alpha*(neighbor.value-self.value)
		self.setValue(self.value + update)
	def addNeighbor(self, neighbor):
		''' Adds a fury object as the neighbor of this fury object. '''
		if not neighbor in self.neighbors:
			self.neighbors.append(neighbor)
		if not self in neighbor.neighbors:
			neighbor.neighbors.append(self)

		

if __name__=="__main__":
	s = Server().boot()
	f1 = Fury(440)
	f2 = Fury(500)
	f3 = Fury(720)
	f4 = Fury(250)
	s.start()
 	time.sleep(1)
	f1.addNeighbor(f2)
	f2.addNeighbor(f3)
	f1.addNeighbor(f4)
	furies = [f1, f2, f3, f4]
	while(True):
		for fury in furies:
			time.sleep(0.01)
			fury.update()
