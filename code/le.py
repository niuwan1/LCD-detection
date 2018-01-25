from numpy import *  
from keras.models import Sequential  
from keras.layers import Dense  
import numpy as np
from keras.layers import Conv2D, MaxPooling2D, Flatten,Dropout 
from keras.optimizers import SGD
from keras.optimizers import SGD, Adam, RMSprop
from keras.utils import np_utils  
from keras.utils.vis_utils import plot_model  
import matplotlib.pyplot as plt
from keras.callbacks import ReduceLROnPlateau, CSVLogger, EarlyStopping
lr_reducer = ReduceLROnPlateau(factor=np.sqrt(0.1), cooldown=0, patience=5, min_lr=0.1e-6)
early_stopper = EarlyStopping(min_delta=0.01, patience=100)
import keras
import pickle
import numpy as np
import time
f1 = open('/home/xm/桌面/useful/test_image/3/train_test.pickle','rb')   
trainData, trainLabels,testData, testLabels =  pickle.load(f1)

trainData = trainData
testData = testData
trainLabels = np_utils.to_categorical(trainLabels, 4)  
testLabels = np_utils.to_categorical(testLabels, 4)  
class LossHistory(keras.callbacks.Callback):
    def on_train_begin(self, logs={}):
        self.losses = {'batch':[], 'epoch':[]}
        self.accuracy = {'batch':[], 'epoch':[]}
        self.val_loss = {'batch':[], 'epoch':[]}
        self.val_acc = {'batch':[], 'epoch':[]}

    def on_batch_end(self, batch, logs={}):
        self.losses['batch'].append(logs.get('loss'))
        self.accuracy['batch'].append(logs.get('acc'))
        self.val_loss['batch'].append(logs.get('val_loss'))
        self.val_acc['batch'].append(logs.get('val_acc'))
        
    def on_epoch_end(self, batch, logs={}):
        self.losses['epoch'].append(logs.get('loss'))
        self.accuracy['epoch'].append(logs.get('acc'))
        self.val_loss['epoch'].append(logs.get('val_loss'))
        self.val_acc['epoch'].append(logs.get('val_acc'))
        
    def loss_plot(self, loss_type):
        iters = range(len(self.losses[loss_type]))
        plt.figure()
        # acc
        #plt.plot(iters, self.accuracy[loss_type], 'r', label='train acc')
        # loss
        plt.plot(iters, self.losses[loss_type], 'g', label='train loss')
        if loss_type == 'epoch':
            # val_acc
            #plt.plot(iters, self.val_acc[loss_type], 'b', label='val acc')
            # val_loss
            plt.plot(iters, self.val_loss[loss_type], 'k', label='val loss')
        plt.grid(False)
        plt.xlabel(loss_type)
        plt.ylabel('loss')
        plt.legend(loc="upper right")
        plt.savefig('/home/xm/桌面/lenet_loss.png')
        plt.show()
        plt.figure()
        # acc
        plt.plot(iters, self.accuracy[loss_type], 'r', label='train acc')
        # loss
        #plt.plot(iters, self.losses[loss_type], 'g', label='train loss')
        if loss_type == 'epoch':
            # val_acc
            plt.plot(iters, self.val_acc[loss_type], 'b', label='val acc')
            # val_loss
            #plt.plot(iters, self.val_loss[loss_type], 'k', label='val loss')
        plt.grid(False)
        plt.xlabel(loss_type)
        plt.ylabel('accuracy')
        plt.legend(loc="lower right")
        plt.savefig('/home/xm/桌面/lenet_acc.png')
        plt.show()
        with open('/home/xm/桌面/lenet_show.txt','wb') as f:
            pickle.dump({'self.losses':self.losses['epoch'],'self.acc':self.accuracy['epoch'],
                        'self.val_loss':self.val_loss['epoch'],'self.val_acc':self.val_acc['epoch']},f)
history = LossHistory()
  
  
model = Sequential()  
model.add(Conv2D(filters=32, kernel_size=(5,5), padding='same', input_shape=(28,28,4), activation='relu'))  
model.add(MaxPooling2D(pool_size=(2,2)))  
model.add(Conv2D(filters=64, kernel_size=(3,3), padding='same', activation='relu'))  
#model.add(Conv2D(filters=256, kernel_size=(3,3), padding='same', activation='sigmoid')) 
model.add(MaxPooling2D(pool_size=(2,2)))  
model.add(Flatten())  
model.add(Dense(120, activation='sigmoid')) 
model.add(Dense(20, activation='sigmoid'))  
model.add(Dense(4, activation='softmax'))  
sgd = SGD(lr=0.05, decay=0.5e-6, momentum=0.9, nesterov=True)
model.compile(loss='categorical_crossentropy',optimizer=Adam(),metrics=['accuracy'])
#model.compile(optimizer=sgd, loss='categorical_crossentropy', metrics=['accuracy'])  
time_start = time.time()
model.fit(trainData, trainLabels, batch_size=128, epochs=10, verbose=1, shuffle=True,validation_data=(testData,testLabels),callbacks=[lr_reducer, early_stopper,history])
model.save('/home/xm/桌面/lenet_4.h5')
#history.loss_plot('epoch')
time_end = time.time()
print('cost time............................',time_end-time_start,'s')
