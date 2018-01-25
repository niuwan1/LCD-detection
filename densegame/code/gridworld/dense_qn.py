from __future__ import division

import gym
import numpy as np
import random
import tensorflow as tf
import tensorflow.contrib.slim as slim
import matplotlib.pyplot as plt
import pylab
import scipy.misc
import os
import math

from gridworld import gameEnv

env = gameEnv(partial=False,size=5)

class Qnetwork():
	def __init__(self):
		self.growth_rate=32
		self.keep_prob=0
		self.scalarInput=tf.placeholder(shape=[None,21168],dtype=tf.float32)
		self.imageIn = tf.reshape(self.scalarInput,shape=[-1,84,84,3])
		self.network = slim.conv2d(inputs=self.imageIn,num_outputs=64,kernel_size=[7,7],stride=[3,3],padding='VALID', biases_initializer=None)
		self.network=tf.nn.relu(self.network)
		if self.keep_prob>0:
			self.network=tf.nn.dropout(self.network,self.keep_prob)
		self.network=tf.nn.pool(self.network,window_shape=[3,3],pooling_type='MAX',padding='VALID',strides=[2,2])
		
		self.network=build_block(self.network,6,self.growth_rate,self.keep_prob)
		self.network=add_transition(self.network,math.floor(int(self.network.shape[3])/2),self.keep_prob)
		self.network=build_block(self.network,12,self.growth_rate,self.keep_prob)
		self.network=add_transition(self.network,math.floor(int(self.network.shape[3])/2),self.keep_prob)
		self.network=build_block(self.network,24,self.growth_rate,self.keep_prob)
		self.network=tf.nn.pool(self.network,window_shape=[3,3],pooling_type='AVG',padding='VALID',strides=[1,1])
		
		self.streamAC,self.streamVC = tf.split(self.network,2,3)
		self.streamA = slim.flatten(self.streamAC)
		self.streamV = slim.flatten(self.streamVC)
		self.Advantage = tf.layers.dense(self.streamA,units=env.actions)
		self.Value = tf.layers.dense(self.streamV,units=env.actions)
		
		
		self.Qout = self.Value + tf.subtract(self.Advantage,tf.reduce_mean(self.Advantage,axis=1,keep_dims=True))
		self.predict = tf.argmax(self.Qout,1)
		
		self.targetQ = tf.placeholder(shape=[None],dtype=tf.float32)
		self.actions = tf.placeholder(shape=[None],dtype=tf.int32)
		self.actions_onehot = tf.one_hot(self.actions,env.actions,dtype=tf.float32)
		self.Q = tf.reduce_sum(tf.multiply(self.Qout, self.actions_onehot), axis=1)
		self.td_error = tf.square(self.targetQ - self.Q)
		self.loss = tf.reduce_mean(self.td_error)
		self.trainer = tf.train.AdamOptimizer(learning_rate=0.0001)
		self.updateModel = self.trainer.minimize(self.loss)
		

def build_block(incoming,num_layers,num_channels,keep_prob):
	layer = incoming
	for _ in range(num_layers):
		layer=add_layer(layer,num_channels,keep_prob)
	return layer
		
def add_layer(incoming,num_channels,keep_prob):
	layer=incoming
	layer = slim.conv2d(inputs=layer,num_outputs=num_channels,kernel_size=[1,1],stride=[1,1],padding='SAME', biases_initializer=None)
	layer=tf.nn.relu(layer)
	if keep_prob>0:
		layer=tf.nn.dropout(layer,keep_prob)
	layer = slim.conv2d(inputs=layer,num_outputs=num_channels,kernel_size=[3,3],stride=[1,1],padding='SAME', biases_initializer=None)
	layer=tf.nn.relu(layer)
	if keep_prob>0:
		layer=tf.nn.dropout(layer,keep_prob)
	layer=tf.concat([incoming,layer],3)
	return layer
		
def add_transition(incoming,num_filters,keep_prob):
	layer=incoming
	layer = slim.conv2d(inputs=layer,num_outputs=num_filters,kernel_size=[1,1],stride=[1,1],padding='SAME', biases_initializer=None)
	layer=tf.nn.relu(layer)
	if keep_prob>0:
		layer=tf.nn.dropout(layer,keep_prob)
	layer=tf.nn.pool(layer,window_shape=[2,2],pooling_type='AVG',padding='SAME',strides=[2,2])
	return layer



class experience_buffer():
	def __init__(self, buffer_size = 50000):
		self.buffer = []
		self.buffer_size = buffer_size
		
	def add(self,experience):
		if len(self.buffer) + len(experience) >= self.buffer_size:
			self.buffer[0:(len(experience)+len(self.buffer))-self.buffer_size] = []
		self.buffer.extend(experience)
		
	def sample(self,size):
		return np.reshape(np.array(random.sample(self.buffer,size)),[size,5])
		
def processState(states):
	#states=states/255
	return np.reshape(states,[21168])
	
def updateTargetGraph(tfVars,tau):
	total_vars = len(tfVars)
	op_holder = []
	for idx,var in enumerate(tfVars[0:total_vars//2]):
		op_holder.append(tfVars[idx+total_vars//2].assign((var.value()*tau) + ((1-tau)*tfVars[idx+total_vars//2].value())))
	return op_holder
	
def updateTarget(op_holder,sess):
	for op in op_holder:
		sess.run(op)
		
batch_size = 32 #How many experiences to use for each training step.
update_freq = 4 #How often to perform a training step.
y = .99 #Discount factor on the target Q-values
startE = 1 #Starting chance of random action
endE = 0.1 #Final chance of random action
anneling_steps = 10000. #How many steps of training to reduce startE to endE.
num_episodes = 7000 #How many episodes of game environment to train network with.
pre_train_steps = 10000 #How many steps of random actions before training begins.
max_epLength = 50 #The max allowed length of our episode.
load_model = False #Whether to load a saved model.
path = "./dqn" #The path to save our model to.
#h_size = 512 #The size of the final convolutional layer before splitting it into Advantage and Value streams.
tau = 0.001 #Rate to update target network toward primary network

tf.reset_default_graph()
mainQN = Qnetwork()
targetQN = Qnetwork()

init = tf.global_variables_initializer()

saver = tf.train.Saver()

trainables = tf.trainable_variables()

targetOps = updateTargetGraph(trainables,tau)

myBuffer = experience_buffer()

#Set the rate of random action decrease. 
e = startE
stepDrop = (startE - endE)/anneling_steps

#create lists to contain total rewards and steps per episode
jList = []
rList = []
total_steps = 0

if not os.path.exists(path):
	os.makedirs(path)
	
with tf.Session() as sess:
	sess.run(init)
	if load_model == True:
		print('Loading Model...')
		ckpt = tf.train.get_checkpoint_state(path)
		saver.restore(sess,ckpt.model_checkpoint_path)
	updateTarget(targetOps,sess)
	for i in range(num_episodes):
		episodeBuffer = experience_buffer()
		s = env.reset()
		s = processState(s)
		d = False
		rAll = 0
		j = 0
		while j < max_epLength:
			j+=1
			if np.random.rand(1) < e or total_steps < pre_train_steps:
				a = np.random.randint(0,4)
			else:
				a = sess.run(mainQN.predict,feed_dict={mainQN.scalarInput:[s]})[0]
			
			s1,r,d = env.step(a)
			s1 = processState(s1)
			total_steps += 1
			episodeBuffer.add(np.reshape(np.array([s,a,r,s1,d]),[1,5]))
			
			if total_steps > pre_train_steps:
				if e > endE:
					e -= stepDrop
				if total_steps % (update_freq) == 0:
					trainBatch = myBuffer.sample(batch_size)
					Q1 = sess.run(mainQN.predict,feed_dict={mainQN.scalarInput:np.vstack(trainBatch[:,3])})
					Q2 = sess.run(targetQN.Qout,feed_dict={targetQN.scalarInput:np.vstack(trainBatch[:,3])})
					end_multiplier = -(trainBatch[:,4] - 1)
					doubleQ = Q2[range(batch_size),Q1]
					targetQ = trainBatch[:,2] + (y*doubleQ * end_multiplier)
					_ = sess.run(mainQN.updateModel,feed_dict={mainQN.scalarInput:np.vstack(trainBatch[:,0]),mainQN.targetQ:targetQ, mainQN.actions:trainBatch[:,1]})
					
					updateTarget(targetOps,sess)
			rAll += r
			s = s1
			env.renderEnv()
			if d == True:
				break
			
		myBuffer.add(episodeBuffer.buffer)
		jList.append(j)
		rList.append(rAll)
		if i % 1000 == 0:
			saver.save(sess,path+'/model-'+str(i)+'.cptk')
			print("Saved Model")
		if len(rList) % 10 == 0:
			print(total_steps,np.mean(rList[-10:]), e)
	saver.save(sess,path+'/model-'+str(i)+'.cptk')
print("Percent of succesful episodes: " + str(sum(rList)/num_episodes) + "%")

rMat = np.resize(np.array(rList),[len(rList)//100,100])
rMean = np.average(rMat,1)
plt.plot(rMean) 
plt.show()
