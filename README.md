# bigan
snow/cloud recognition based on different models

1.train_test data are from HJ-1A/1B satellite,you can use *********.py to sample data from the original data

2.using different models to train and test
1)SVM
get the Gray-level co-occurrence matrix(GLCM) from every image,and according the the GLCM,get COR(self correlation),CON(contrast),ENT(entropy),IDM(inverse different moment) values,and combine this values from a images as a vector,regarging this vector as texture features from a image,using SVM to classify.
2)Random Forest
flatten a image into a vector and use 1000 random forest to classify,each random forest consists of 1000 decision trees
3)GcForest
this is a new method from ZHOU Z H,using multi-Grained Scanning to get many instances from ths original image,every instance was sent into two random forests,one is normal random forest,and another one is complete random forest,the differences between these two random forest is that complete random forest select sqrt(k)(k is the number of features) features to classfy.after multi-Grained Scanning,original data can be re-represent into a vector,which is the class probilities of one instance.then a Cascade Forest strucure will be used to train thses vectors.
4)Convolutional neural network (CNN)
a framework to automatically extrate features from original image
5)Deep Residual Network (ResNet)
a deep neural nework that can solve the gradient vinishing problem,and preformance is better than shallow neural networks

using 80% data for traning and the rest are used for testing
after training and testing,using models above to predict the whole HJ-1A/1B satellite image,blue color stands for snow area,red color stands for cloud area,white color stands for cloud/snow mixed area
