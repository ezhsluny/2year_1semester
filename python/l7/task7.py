import cv2
import numpy as np
import os
import matplotlib.pyplot as plt


path = '/home/ezhsluny/Documents/python/l7/archive/'
tree = os.walk('/home/ezhsluny/Documents/python/l7/archive/images')
for f in tree:
    if f[-1]:
        images_files = f[-1]
        break

tree = os.walk('/home/ezhsluny/Documents/python/l7/archive/labels')
for f in tree:
    if f[-1]:
        masks_files = f[-1]
        break


def generator(images_files, list_len):
    i = 0
    new_list_images = []
    new_list_images = np.random.choice(images_files, list_len)
    images = []
    masks = []

    while i < list_len:
        image = cv2.imread(path + 'images/' + new_list_images[i])
        mask = cv2.imread(path + 'labels/' + new_list_images[i])
        images.append(image)
        masks.append(mask)

        i += 1
        
    yield images, masks


def turn_on_random_angle(image, mask):
    angle = int(np.random.random_integers(-360, 360, 1))
    heigh, width = image.shape[:2]
    heigh_center = round(heigh/2)
    width_center = round(width/2)

    rot_mat = cv2.getRotationMatrix2D((width_center, heigh_center), angle, 1.0)
    r_image =  cv2.warpAffine(image, rot_mat, (width, heigh), flags=cv2.INTER_LINEAR)
    r_mask = cv2.warpAffine(mask, rot_mat, (width, heigh), flags=cv2.INTER_LINEAR)

    return r_image, r_mask


def flip(image, mask):
    axis = int(np.random.random_integers(-1, 1, 1))

    result_i = cv2.flip(image, axis)
    result_m = cv2.flip(mask, axis)

    return result_i, result_m


def crop_part(image, mask):
    np.random.seed(43)
    heigh, width = image.shape[:2]
    bbox = np.random.randint(0, min(heigh, width), size=4)

    result_i = image[bbox[1]:bbox[1]+bbox[3], bbox[0]:bbox[0]+bbox[2]]
    result_m = mask[bbox[1]:bbox[1]+bbox[3], bbox[0]:bbox[0]+bbox[2]]

    return result_i, result_m



def blur(image, mask):
    blur_kernel = (int(np.random.random_integers(1, 5, 1)*2 + 1), \
                   int(np.random.random_integers(1, 5, 1)*2 + 1))
    blured_i = cv2.GaussianBlur(image, blur_kernel, 3)
    blured_m = cv2.GaussianBlur(mask, blur_kernel, 3)

    return blured_i, blured_m


n = 10
generator = generator(images_files, n)

cv2.namedWindow('image')
cv2.namedWindow('mask')

for images, masks in generator:
    for i in range(n):
        op_idx = np.random.random_integers(0, 3, 1)
        if op_idx == 0:
            image, mask = turn_on_random_angle(images[i], masks[i])
            cv2.putText(image, "rotation", (10, 40), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
        elif op_idx == 1:
            image, mask = flip(images[i], masks[i])
            cv2.putText(image, "flip", (10, 40), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
        elif op_idx == 2:
            image, mask = crop_part(images[i], masks[i])
            cv2.putText(image, "crop", (10, 40), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
        elif op_idx == 3:
            image, mask = blur(images[i], masks[i])
            cv2.putText(image, "blur", (10, 40), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)

        cv2.imshow('image', image)
        cv2.imshow('mask', mask)

        key = cv2.waitKey(0)
        if key == 27:
            cv2.destroyAllWindows()
            break

    if key == 27:
        break


cv2.destroyAllWindows();