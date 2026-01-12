import cv2
import os
import random

def nails_segmentation_generator(image_dir, mask_dir, batch_size):
    image_files = os.listdir(image_dir)
    mask_files = os.listdir(mask_dir)
    indices = list(range(len(image_files)))
    random.shuffle(indices)

    while True:
        if len(indices) < batch_size:
            random.shuffle(indices)

        batch_indices = indices[:batch_size]
        indices = indices[batch_size:]

        images = []
        masks = []

        for idx in batch_indices:
            image_path = os.path.join(image_dir, image_files[idx])
            mask_path = os.path.join(mask_dir, mask_files[idx])

            image = cv2.imread(image_path)
            mask = cv2.imread(mask_path, cv2.IMREAD_GRAYSCALE)

            images.append(image)
            masks.append(mask)

        yield images, masks

# Пример использования генератора
image_dir = 'path/to/images'
mask_dir = 'path/to/masks'
batch_size = 4

generator = nails_segmentation_generator(image_dir, mask_dir, batch_size)

for images, masks in generator:
    # Обработка пары списков изображений и масок
    print(f"Batch of {len(images)} images and {len(masks)} masks")
    # Ваш код для обработки изображений и масок
