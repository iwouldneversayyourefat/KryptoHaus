import cv2
import sys
import os
import numpy as np
import re



def FUCKU(filename,info):
    bininfo="".join([bin(i)[2:].zfill(8) for i in info])
    bininfo=[int(i) for i in bininfo]
    print("info ","".join([str(i) for i in bininfo]))
    if(os.path.exists(filename)):
        im=cv2.imread(filename)
    else:
        exit()
    h=im.shape[0]
    w=im.shape[1]
    ch=im.shape[2]
    flt=im.reshape(h*w,ch)
    capacity=len(flt)
    len_needed=len(info)*8
    if(len_needed>capacity):
        exit()
    flt[:,0][:len_needed]=(flt[:,0][:len_needed] | 0x1) & ((np.ones(len_needed)*0xfe).astype(int) | bininfo)
    cv2.imwrite("a%d.png"%len_needed,flt.reshape(h,w,ch))
    a="".join((flt[:,0][:len_needed]&0x1).astype(str))
    print("".join([chr(int(i,2)) for i in re.findall("."*8,a)]))
