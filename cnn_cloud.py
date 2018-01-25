import pickle
import random
import scipy.io as sio
import numpy as np
from sklearn.preprocessing import scale
from sklearn.model_selection import train_test_split
np.random.seed(1337)  # for reproducibility
from keras.datasets import mnist
from keras.utils import np_utils
from keras.models import Sequential
from keras.layers import Dense, Activation, Convolution2D, MaxPooling2D, Flatten,Dropout,BatchNormalization
from keras.optimizers import Adam

f1 = open('/home/xm/桌面/cloud2/all_data.txt','rb')
train_features,train_labels,test_features,test_labels = pickle.load(f1)
f1.close()
def normalization(image):
    mean_image = np.mean(image,axis = 0)
    image_1 = image - mean_image
    image_1 /= 128
    return image_1
train_x = normalization(train_features)
test_x =  normalization(test_features)
###归一化
##for i in range(1,features.shape[2]):
##    
##    features_1 = np.concatenate([features_1,normalization(features[:,:,i]).reshape([610,340,1])],axis = 2)
##features_1 = features_1.reshape([-1,103])
##labels_1 = labels.reshape([-1,1])
##
###去掉 label为0的
##zero_index = []
##for i in range(labels_1.shape[0]):
##    if labels_1[i] == 0:
##        zero_index.append(i)
##features_1 = np.delete(features_1,zero_index,axis = 0)
##labels_1 = np.delete(labels_1,zero_index,axis = 0)
##
### pad
##features_1 = np.pad(features_1,(0,18),'constant',constant_values = 0)
##features_1 = features_1[:-18,:]
##features_1 = features_1.reshape([-1,11,11,1])
##
##X_train,X_test_,train_labels,train_labels_ = train_test_split(features_1,labels_1,test_size = 0.4)
##X_valid,X_test,valid_labels,test_labels = train_test_split(X_test_,train_labels_,test_size = 0.5)

##index_1,index_2,index_3,index_4,index_5,index_6,index_7,index_8,index_9 = [],[],[],[],[],[],[],[],[]
##for i in range(labels_1.shape[0]):
##    if labels_1[i] == 1:
##        index_1.append(i)
##    elif labels_1[i] == 2:
##        index_2.append(i)
##    elif labels_1[i] == 3:
##        index_3.append(i)
##    elif labels_1[i] == 4:
##        index_4.append(i)
##    elif labels_1[i] == 5:
##        index_5.append(i)
##    elif labels_1[i] == 6:
##        index_6.append(i)
##    elif labels_1[i] == 7:
##        index_7.append(i)
##    elif labels_1[i] == 8:
##        index_8.append(i)
##    else:
##        index_9.append(i)
##
##
##train_index_1 = random.sample(index_1,round(len(index_1) * 0.6))
##train_index_2 = random.sample(index_2,round(len(index_2) * 0.6))
##train_index_3 = random.sample(index_3,round(len(index_3) * 0.6))
##train_index_4 = random.sample(index_4,round(len(index_4) * 0.6))
##train_index_5 = random.sample(index_5,round(len(index_5) * 0.6))
##train_index_6 = random.sample(index_6,round(len(index_6) * 0.6))
##train_index_7 = random.sample(index_7,round(len(index_7) * 0.6))
##train_index_8 = random.sample(index_8,round(len(index_8) * 0.6))
##train_index_9 = random.sample(index_9,round(len(index_9) * 0.6))
##train_index = []
##
##train_index.extend(train_index_1)
##train_index.extend(train_index_2)
##train_index.extend(train_index_3)
##train_index.extend(train_index_4)
##train_index.extend(train_index_5)
##train_index.extend(train_index_6)
##train_index.extend(train_index_7)
##train_index.extend(train_index_8)
##train_index.extend(train_index_9)
##train_index = random.sample(train_index,len(train_index))
##
##X_train = features_1[train_index]
##train_labels = labels_1[train_index]
##
##train_index_ = [i for i in list(range(features_1.shape[0])) if i not in train_index]
##valid_index = random.sample(train_index_,round(len(train_index_) * 0.5))
##test_index = [i for i in train_index_ if i not in valid_index]
##
##X_valid = features_1[valid_index]
##valid_labels = labels_1[valid_index]
##
##X_test = features_1[test_index]
##test_labels = labels_1[test_index]

# data pre-processing
y_train = np_utils.to_categorical(train_labels, num_classes = 2)

y_test = np_utils.to_categorical(test_labels, num_classes = 2)

# Another way to build your CNN
model = Sequential()

# Conv layer 1 output shape (11, 11, 32)
model.add(Convolution2D(
    batch_input_shape=(None, 128, 128, 4),
    filters=32,
    kernel_size=5,
    strides=2,
    padding='same',     # Padding method
    data_format='channels_first',
))
model.add(Activation('relu'))

### Pooling layer 1 (max pooling) output shape (6, 6, 32)

##model.add(MaxPooling2D(
## pool_size=3,
## strides=2,
## padding='same',    # Padding method
## data_format='channels_first',
##))
model.add(BatchNormalization(epsilon=1e-06))

# Conv layer 2 output shape (64, 11, 11)
model.add(Convolution2D(64, 5, strides=1, padding='same', data_format='channels_first'))
##model.add(Convolution2D(64,3,strides = 1,padding = 'same',data_format = 'channels_first'))
model.add(Convolution2D(128,3,strides = 1,padding = 'same',data_format = 'channels_first'))
##model.add(Convolution2D(256,3,strides = 1,padding = 'same',data_format = 'channels_first'))
model.add(Convolution2D(256,3,strides = 1,padding = 'same',data_format = 'channels_first'))
model.add(Convolution2D(512,3,strides = 1,padding = 'same',data_format = 'channels_first'))
model.add(Activation('relu'))

# Pooling layer 2 (max pooling) output shape (64, 3, 3)
##model.add(MaxPooling2D(3, 2, 'same', data_format='channels_first'))
##model.add(BatchNormalization(epsilon=1e-06))
# Fully connected layer 1 input shape (64 * 11 * 11) = (3136), output shape (1024)
model.add(Flatten())
model.add(Dense(500))
model.add(Activation('relu'))
model.add(Dropout(0.1))
model.add(Dense(100))
model.add(Activation('relu'))
model.add(Dropout(0.1))


# Fully connected layer 2 to shape (10) for 10 classes
model.add(Dense(2))
model.add(Activation('softmax'))

# Another way to define your optimizer
adam = Adam(lr=1e-4)

# We add metrics to get more results you want to see
model.compile(optimizer=adam,
              loss='categorical_crossentropy',
              metrics=['accuracy'])

print('Training ------------')
# Another way to train the model
model.fit(train_x, y_train, epochs=5000, batch_size=64,validation_data = (test_x,y_test))

print('\nTesting ------------')
# Evaluate the model with the metrics we defined earlier
loss, accuracy = model.evaluate(X_test, y_test)

print('\ntest loss: ', loss)
print('\ntest accuracy: ', accuracy)
if accuracy > 0.95:
    f = open('/home/xm/桌面/遥感数据集/all_data.txt','wb')
    pickle.dump([X_train,y_train,X_test,y_test,X_valid,y_valid],f)
