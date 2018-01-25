f = open('/home/xm/桌面/cloud2/all_data.txt','rb')
train_features,train_labels,test_features,test_labels = pickle.load(f)
train_x = train_features[:,:,:,0]
test_x = test_features[:,:,;,0]
# 归一化
mean_train = np.mean(train_x,axis = 0)
mean_test = np.mean(test_x,axis = 0)
train_x = train_x - mean_train
test_x = test_x - mean_test
train_x /= 128
test_x /= 128

# 将一张图片拉成一个向量
train_x = np.reshape(train_x,[-1,128 * 128])
test_x = test_x.reshape([-1,128 * 128])

# 进入训练阶段

from sys import path
path.append('/home/xm/桌面/遥感数据集')
import GCForest
from GCForest import *
gcf = gcForest(shape_1X = [128,128],window = 32,stride = 16)
gcf.fit(train_x,train_labels)

from sklearn.metrics import accuracy_score
preds = gcf.predict(test_x)
acc = accuracy_score(preds,test_labels)
print('this is test_acc:',acc)
