from osgeo import gdal, gdalnumeric,gdal_array
import os
import sys
import numpy as np
from PIL import Image
gdal.UseExceptions()
from PIL import Image
from functools import reduce
dirfile = '/home/xm/桌面/sbc/1' # 挑选出来的图片所在的文件夹，这个文件夹不用动，应该这里面的数据是挑出来的
second_folder = '/home/xm/桌面/sbc/HJ1A-CCD1-23-78-20090205-L20000063628-4' #第二个切割出来的数据集所在的文件夹的位置
#second_folder 最后一个数字要改成对应的文件夹
folder_2 = '/home/xm/桌面/sbc/4'#复制从第2个切割文件夹 2 对应文件夹的号数要改

for file in os.listdir(dirfile):
        singlefileName = dirfile + '/' + file
        singlefileindex = os.path.splitext(singlefileName)[0]
        for file in os.listdir(second_folder):
                filename = second_folder + '/' + file
                fileindex = os.path.splitext(filename)[0]
##                print('this is singlefileindex:\n',singlefileindex[65:])
##                print('this is fileindex:\n',fileindex[65:])
                if singlefileindex[58:] == fileindex[96:]:
                        image_to_copy = Image.open(filename)
                        image_copy_array = np.array(image_to_copy)
                        print('begin to write........')
                        savefile = folder_2 + '//' + 'HJ1A-CCD1-23-78-20090205-L20000063628-4' + '_' + \
                                   fileindex[96:] + '.TIF'
                        gtiffDriver = gdal.GetDriverByName( 'GTiff' )
                        gtiffDriver.CreateCopy(savefile,gdal_array.OpenArray(image_copy_array, prototype_ds=singlefileName))
                        print('finish writing .......')
