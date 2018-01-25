import skimage
import time
import numpy as np
from skimage.feature import greycomatrix,greycoprops
from sklearn.metrics import  accuracy_score
import pickle
from sklearn.svm import SVC
with open('/home/xm/桌面/extra/train_test.txt','rb') as f:
	train_features,train_labels,test_features,test_labels = pickle.load(f)
matrix = []
train_x = train_features[:,:,:,0]
test_x = test_features[:,:,:,0]
train_y = train_labels.reshape([-1,])
test_y = test_labels.reshape([-1,])
size = train_x.shape[0]
fa1 = np.zeros([size])
fb1 = np.zeros([size])
fc1 = np.zeros([size])
fd1 = np.zeros([size])
tr_1 = time.time()
for i in range(train_x.shape[0]):
	glcm = greycomatrix(train_x[i], [5], [0], 256, symmetric=True, normed=True)
	fa1[i] = skimage.feature.greycoprops(glcm, 'contrast')
	fb1[i] = skimage.feature.greycoprops(glcm, 'energy')
	fc1[i] = skimage.feature.greycoprops(glcm, 'homogeneity')
	fd1[i] = skimage.feature.greycoprops(glcm, 'correlation')
fa1 = fa1[:,np.newaxis]
fb1 = fb1[:,np.newaxis]
fc1 = fc1[:,np.newaxis]
fd1 = fd1[:,np.newaxis]
f1 = np.concatenate([fa1,fb1,fc1,fd1],axis = 1)
model = SVC(kernel = 'rbf',C = 32)
model.fit(f1,train_y)
tr_2 = time.time()
print('training time:',tr_2 - tr_1)
test_size = test_x.shape[0]
te1 = np.zeros([test_size])
te2 = np.zeros([test_size])
te3 = np.zeros([test_size])
te4 = np.zeros([test_size])
te_1 = time.time()
for i in range(test_x.shape[0]):
	glcm = greycomatrix(test_x[i], [5], [0], 256, symmetric=True, normed=True)
	te1[i] = skimage.feature.greycoprops(glcm, 'contrast')
	te2[i] = skimage.feature.greycoprops(glcm, 'energy')
	te3[i] = skimage.feature.greycoprops(glcm, 'homogeneity')
	te4[i] = skimage.feature.greycoprops(glcm, 'correlation')
te1 = te1[:,np.newaxis]
te2 = te2[:,np.newaxis]
te3 = te3[:,np.newaxis]
te4 = te4[:,np.newaxis]
te = np.concatenate([te1,te2,te3,te4],axis = 1)
pred = model.predict(te)
te_2 = time.time()
print('predict time:',te_2 - te_1)
acc = accuracy_score(pred,test_y)
print('acc:',acc)
with open('/home/xm/桌面/useful/test_image/3/fenge_502_556.pickle','rb') as f:
	test = pickle.load(f)
test = test[:,:,:,0]
test_1 = np.zeros([test.shape[0]])
test_2 = np.zeros([test.shape[0]])
test_3 = np.zeros([test.shape[0]])
test_4 = np.zeros([test.shape[0]])
for i in range(test.shape[0]):
	glcm = greycomatrix(test[i], [5], [0], 256, symmetric=True, normed=True)
	test_1[i] = skimage.feature.greycoprops(glcm, 'contrast')
	test_2[i] = skimage.feature.greycoprops(glcm,'energy')
	test_3[i] = skimage.feature.greycoprops(glcm, 'homogeneity')
	test_4[i] = skimage.feature.greycoprops(glcm, 'correlation')
test_1 = test_1[:,np.newaxis]
test_2 = test_2[:,np.newaxis]
test_3 = test_3[:,np.newaxis]
test_4 = test_4[:,np.newaxis]

test_11 = np.concatenate([test_1,test_2,test_3,test_4],axis = 1)
prediction = model.predict(test_11)
pred_image = prediction.reshape([502,556])
import cv2
img = np.zeros([502,556,3])
for i in range(pred_image.shape[0]):
        for j in range(pred_image.shape[1]):
                if pred_image[i][j] == 0:
                        img[i][j][0] = 255
                        img[i][j][1] = 0
                        img[i][j][2] = 0
                elif pred_image[i][j] == 1:
                        img[i][j][0] = 0
                        img[i][j][1] = 0
                        img[i][j][2] = 255
                elif pred_image[i][j] == 2:
                        img[i][j][0] = 255
                        img[i][j][1] = 255
                        img[i][j][2] = 255
                else:
                        img[i][j][0] = 0
                        img[i][j][1] = 0
                        img[i][j][2] = 0
cv2.imwrite('/home/xm/桌面/sv1.png',img)
