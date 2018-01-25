#!/usr/bin/env python
#coding=UTF-8
from __future__ import print_function

import tensorflow.contrib.slim as slim
import tensorflow as tf
import cv2
import sys
sys.path.append("game/")
import wrapped_flappy_bird as game
import random
import numpy as np
from collections import deque
import math
import matplotlib.pyplot as plt

GAME = 'bird' # the name of the game being played for log files
ACTIONS = 2 # number of valid actions
GAMMA = 0.99 # decay rate of past observations
OBSERVE = 10000. # timesteps to observe before training
EXPLORE = 200000. # frames over which to anneal epsilon
FINAL_EPSILON = 0 # final value of epsilon
INITIAL_EPSILON = 0.1 # starting value of epsilon
REPLAY_MEMORY = 50000 # number of previous transitions to remember
BATCH = 32 # size of minibatch
growth_rate=32
FRAME_PER_ACTION=1
set_step=800000

# def weight_variable(shape):
    # initial = tf.truncated_normal(shape, stddev = 0.01)
    # return tf.Variable(initial)

# def bias_variable(shape):
    # initial = tf.constant(0.01, shape = shape)
    # return tf.Variable(initial)

# def conv2d(x, W, stride):
    # return tf.nn.conv2d(x, W, strides = [1, stride, stride, 1], padding = "SAME")

#def max_pool_2x2(x):
    #return tf.nn.max_pool(x, ksize = [1, 2, 2, 1], strides = [1, 2, 2, 1], padding = "SAME")

def createNetwork():
    s = tf.placeholder("float", [None, 80, 80, 4])
    #s=s/255
    h_conv=slim.conv2d(inputs=s,num_outputs=64,kernel_size=[7,7],stride=[2,2],padding='VALID', biases_initializer=None)
    h_conv=tf.nn.relu(h_conv)
    h_pool=tf.nn.pool(h_conv,window_shape=[3,3],pooling_type='MAX',padding='VALID',strides=[2,2])
    conv=build_block(h_pool,6,growth_rate)
    conv=add_transition(conv,math.floor(int(conv.shape[3])/2))
    conv=build_block(conv,12,growth_rate)
    conv=add_transition(conv,math.floor(int(conv.shape[3])/2))
    conv=build_block(conv,24,growth_rate)
    #conv=add_transition(conv,math.floor(int(conv.shape[3])/2))
    #conv=build_block(conv,16,growth_rate)
    conv=tf.nn.pool(conv,window_shape=[4,4],pooling_type='AVG',padding='VALID',strides=[1,1])
    conv_flat= slim.flatten(conv)
    h_fc1=tf.layers.dense(conv_flat,units=512)
    h_fc1=tf.nn.relu(h_fc1)
    readout=tf.layers.dense(h_fc1,units=ACTIONS)
    # # network weights
    # W_conv1 = weight_variable([8, 8, 4, 32])
    # b_conv1 = bias_variable([32])

    # W_conv2 = weight_variable([4, 4, 32, 64])
    # b_conv2 = bias_variable([64])

    # W_conv3 = weight_variable([3, 3, 64, 64])
    # b_conv3 = bias_variable([64])

    # W_fc1 = weight_variable([1600, 512])
    # b_fc1 = bias_variable([512])

    # W_fc2 = weight_variable([512, ACTIONS])
    # b_fc2 = bias_variable([ACTIONS])

    # # input layer
    # s = tf.placeholder("float", [None, 80, 80, 4])

    # # hidden layers
    # h_conv1 = tf.nn.relu(conv2d(s, W_conv1, 4) + b_conv1)
    # h_pool1 = max_pool_2x2(h_conv1)

    # h_conv2 = tf.nn.relu(conv2d(h_pool1, W_conv2, 2) + b_conv2)
    # #h_pool2 = max_pool_2x2(h_conv2)

    # h_conv3 = tf.nn.relu(conv2d(h_conv2, W_conv3, 1) + b_conv3)
    # #h_pool3 = max_pool_2x2(h_conv3)

    # #h_pool3_flat = tf.reshape(h_pool3, [-1, 256])
    # h_conv3_flat = tf.reshape(h_conv3, [-1, 1600])

    # h_fc1 = tf.nn.relu(tf.matmul(h_conv3_flat, W_fc1) + b_fc1)

    # # readout layer
    # readout = tf.matmul(h_fc1, W_fc2) + b_fc2

    return s, readout, h_fc1

def build_block(incoming,num_layers,num_channels):
    layer = incoming
    for _ in range(num_layers):
        layer=add_layer(layer,num_channels)
    return layer
        
def add_layer(incoming,num_channels):
    layer=incoming
    layer = slim.conv2d(inputs=layer,num_outputs=num_channels,kernel_size=[1,1],stride=[1,1],padding='SAME', biases_initializer=None)
    layer=tf.nn.relu(layer)
    
    layer = slim.conv2d(inputs=layer,num_outputs=num_channels,kernel_size=[3,3],stride=[1,1],padding='SAME', biases_initializer=None)
    layer=tf.nn.relu(layer)
    
    layer=tf.concat([incoming,layer],3)
    return layer
        
def add_transition(incoming,num_filters):
    layer=incoming
    layer = slim.conv2d(inputs=layer,num_outputs=num_filters,kernel_size=[1,1],stride=[1,1],padding='SAME', biases_initializer=None)
    layer=tf.nn.relu(layer)
    layer=tf.nn.pool(layer,window_shape=[2,2],pooling_type='AVG',padding='SAME',strides=[2,2])
    return layer

def trainNetwork(s, readout, h_fc1, sess):
    # define the cost function
    a = tf.placeholder("float", [None, ACTIONS])
    y = tf.placeholder("float", [None])
    readout_action = tf.reduce_sum(tf.multiply(readout, a), reduction_indices=1)
    cost = tf.reduce_mean(tf.square(y - readout_action))
    train_step = tf.train.AdamOptimizer(1e-6).minimize(cost)

    # open up a game state to communicate with emulator
    game_state = game.GameState()

    # store the previous observations in replay memory
    D = deque()

    # printing
    a_file = open("logs_" + GAME + "/readout.txt", 'w')
    h_file = open("logs_" + GAME + "/hidden.txt", 'w')

    # get the first state by doing nothing and preprocess the image to 80x80x4
    do_nothing = np.zeros(ACTIONS)
    do_nothing[0] = 1
    x_t, r_0, terminal = game_state.frame_step(do_nothing)
    x_t = cv2.cvtColor(cv2.resize(x_t, (80, 80)), cv2.COLOR_BGR2GRAY)
    ret, x_t = cv2.threshold(x_t,1,255,cv2.THRESH_BINARY)
    s_t = np.stack((x_t, x_t, x_t, x_t), axis=2)

    # saving and loading networks
    saver = tf.train.Saver()
    sess.run(tf.initialize_all_variables())
    checkpoint = tf.train.get_checkpoint_state("saved_networks")
    if checkpoint and checkpoint.model_checkpoint_path:
        saver.restore(sess, checkpoint.model_checkpoint_path)
        print("Successfully loaded:", checkpoint.model_checkpoint_path)
    else:
        print("Could not find old network weights")

    # start training
    epsilon = INITIAL_EPSILON
    t = 0
    r=0
    r_list=[]
    t_list=[]
    c_list=[]
    total_t=[]

    while t<set_step:
        # choose an action epsilon greedily
        readout_t = readout.eval(feed_dict={s : [s_t]})[0]
        a_t = np.zeros([ACTIONS])
        action_index = 0
        
        if t % FRAME_PER_ACTION == 0:
            if random.random() <= epsilon:
                print("----------Random Action----------")
                action_index = random.randrange(ACTIONS)
                a_t[random.randrange(ACTIONS)] = 1
            else:
                action_index = np.argmax(readout_t)
                a_t[action_index] = 1
        else:
            a_t[0] = 1 # do nothing

        #if 10000<t<20000:
          #  FRAME_PER_ACTION=7

        if t>10000:
            FRAME_PER_ACTION==1

        # scale down epsilon
        if epsilon > FINAL_EPSILON and t > OBSERVE:
            epsilon -= (INITIAL_EPSILON - FINAL_EPSILON) / EXPLORE

        # run the selected action and observe next state and reward
        x_t1_colored, r_t, terminal = game_state.frame_step(a_t)
        x_t1 = cv2.cvtColor(cv2.resize(x_t1_colored, (80, 80)), cv2.COLOR_BGR2GRAY)
        ret, x_t1 = cv2.threshold(x_t1, 1, 255, cv2.THRESH_BINARY)
        x_t1 = np.reshape(x_t1, (80, 80, 1))
        #s_t1 = np.append(x_t1, s_t[:,:,1:], axis = 2)
        s_t1 = np.append(x_t1, s_t[:, :, :3], axis=2)


        if r_t>0.1:
            r=r+r_t
        if r_t==-1:
            r_list.append(r)
            t_list.append(t)
            r=0


        # store the transition in D
        D.append((s_t, a_t, r_t, s_t1, terminal))
        if len(D) > REPLAY_MEMORY:
            D.popleft()

        # only train if done observing
        if t > OBSERVE:
            # sample a minibatch to train on
            minibatch = random.sample(D, BATCH)

            # get the batch variables
            s_j_batch = [d[0] for d in minibatch]
            a_batch = [d[1] for d in minibatch]
            r_batch = [d[2] for d in minibatch]
            s_j1_batch = [d[3] for d in minibatch]

            y_batch = []
            readout_j1_batch = readout.eval(feed_dict = {s : s_j1_batch})
            for i in range(0, len(minibatch)):
                terminal = minibatch[i][4]
                # if terminal, only equals reward
                if terminal:
                    y_batch.append(r_batch[i])
                else:
                    y_batch.append(r_batch[i] + GAMMA * np.max(readout_j1_batch[i]))

            # perform gradient step
            train_step.run(feed_dict = {
                y : y_batch,
                a : a_batch,
                s : s_j_batch}
            )
            cc=sess.run(cost,feed_dict = {
                y : y_batch,
                a : a_batch,
                s : s_j_batch}
            )
            c_list.append(cc)
            total_t.append(t)

        # update the old values
        s_t = s_t1
        t += 1

        # save progress every 10000 iterations
        if t % 10000 == 0:
            saver.save(sess, 'saved_networks/' + GAME + '-dqn', global_step = t)

        # print info
        state = ""
        if t <= OBSERVE:
            state = "observe"
        elif t > OBSERVE and t <= OBSERVE + EXPLORE:
            state = "explore"
        else:
            state = "train"

        print("TIMESTEP", t, "/ STATE", state, \
            "/ EPSILON", epsilon, "/ ACTION", action_index, "/ REWARD", r)
        # write info to files
        '''
        if t % 10000 <= 100:
            a_file.write(",".join([str(x) for x in readout_t]) + '\n')
            h_file.write(",".join([str(x) for x in h_fc1.eval(feed_dict={s:[s_t]})[0]]) + '\n')
            cv2.imwrite("logs_tetris/frame" + str(t) + ".png", x_t1)
        '''
    fig1 = plt.figure()
    ax1 = fig1.add_subplot(1,1,1)
    ax1.plot(t_list,r_list,'ro')
    #ax1.set_title('reward value')
    foo=plt.gcf()
    foo.savefig('11.eps')

    fig2 = plt.figure()
    ax2 = fig2.add_subplot(1,1,1)
    ax2.plot(total_t,c_list,'b')
    #ax2.set_title('cost value')
    foo=plt.gcf()
    foo.savefig('22.eps')
    plt.show()

def playGame():
    sess = tf.InteractiveSession()
    s, readout, h_fc1 = createNetwork()
    trainNetwork(s, readout, h_fc1, sess)
    
   

def main():
    playGame()

if __name__ == "__main__":
    main()
