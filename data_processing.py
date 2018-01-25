import numpy as np
import pandas as pd
from PIL import Image
import os
import pickle
import glob # glob是用来遍历文件夹下的所有bmp文件
cwd = os.getcwd() # 获取电脑的主文件夹路径:/home/xm
arr = [[]]
classes = ['4'] #将所有的文件夹按照预先知道的顺序排列
#存在列表中，实际图片文件夹的顺序要和dmos文件中的标签的顺序要一一对应，
for index,name in enumerate(classes):
    class_path = cwd + '/' + name + '/' #获取图像文件夹的路径
    for infile in glob.glob(class_path + '*.TIF'): #遍历classes列表元素的文件夹中的
    #所有bmp格式的文件
        file,ext = os.path.splitext(infile)
        img = Image.open(infile) # 打开每一张图片
##        img = img.resize([32,32]) # 将图片压缩
        image_arr = np.array(img)
        image_arr = image_arr.reshape([image_arr.shape[0],image_arr.shape[1],1])
        #将三色通道的信息进行横向拼接，这样一张图片的所有信息就全部包含在一个行向量中了
        if arr == [[]]: #将第一张图片的信息放到arr列表中
            arr = [image_arr]
            continue
        arr = np.concatenate((arr,[image_arr]),axis = 0)
        #从第二张开始的图片信息都按照np.concatenate的方式一张一张往下拼接，这样
        #得到的arr.shape = [982,32 * 32 * 3],982张32x32的三色通道图片

f = open('/home/xm/桌面/sbc/xue/4.txt','wb')
pickle.dump(arr,f)
f.close()
