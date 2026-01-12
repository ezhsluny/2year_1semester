import cv2
import numpy as np
import os
import matplotlib.pyplot as plt


#1-2
path = '/home/ezhsluny/Documents/python/l6/archive/'
tree = os.walk('/home/ezhsluny/Documents/python/l6/archive/images')
for f in tree:
    if f[-1]:
        nails_files = f[-1]
        break

tree = os.walk('/home/ezhsluny/Documents/python/l6/archive/labels')
for f in tree:
    if f[-1]:
        masks_files = f[-1]
        break

for filename in nails_files:
    img1 = cv2.imread(path + 'images/' + filename)
    img2 = cv2.imread(path + 'labels/' + filename)
    vis = np.concatenate((img1, img2), axis=1)
    cv2.imwrite('/home/ezhsluny/Documents/python/l6/archive/res/' + filename, vis)


tree = os.walk('/home/ezhsluny/Documents/python/l6/archive/res')
for f in tree:
    if f[-1]:
        res_files = f[-1]
        break

i = 40
while True:
    if i == len(res_files):
        break

    filename = res_files[i]
    img_path = path + 'res/' + filename
    img = cv2.imread(img_path)
    label_path = path + 'labels/' + masks_files[i]
    label = cv2.imread(label_path)
    label = cv2.cvtColor(label, cv2.COLOR_BGR2GRAY)
    contours, hierarchy = cv2.findContours(label, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    cv2.drawContours(img, contours, -1, (255, 100, 100), 4)

    plt.imshow(img)
    plt.show(block=False)

    key = plt.waitforbuttonpress(100)
    if key:
        i += 1
        
    plt.close()


#3


cap = cv2.VideoCapture('l6/video.mp4')
print("aaaaaaaaaaaaaa")
while True:
    ret, frame = cap.read()
    if not ret:
        break
    
    frame = cv2.cvtColor(frame, cv2.COLOR_RGB2GRAY)
    cv2.imshow('frame', frame)
    
    if cv2.waitKey(20) & 0xFF == 27:
        break
print("aaaaaaaaaaaaaa")
# cv2.destroyWindow('frame')
cv2.destroyAllWindows()
cap.release()
