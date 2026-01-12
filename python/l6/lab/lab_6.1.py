import cv2
import numpy as np
import matplotlib.pyplot as plt
import os


# def process_video(video_path):
#     cap = cv2.VideoCapture(video_path)

#     if not cap.isOpened():
#         print("Ошибка при открытии видеофайла")
#         return

#     frame_count = 0

#     while True:
#         ret, frame = cap.read()
#         if not ret:
#             break
        
#         cv2.imwrite(f'frames/frame_{frame_count:04d}.png', frame)
#         # image_cont = make_contours(frame)
#         # cv2.imwrite(f'contours/contour_{frame_count:04d}.png', image_cont)

#         frame_count += 1

#     cap.release()
#     cv2.destroyAllWindows()


# def make_contours(frame):
#     frame_gray = cv2.cvtColor(frame, cv2.COLOR_RGB2GRAY)
#     _, thresh = cv2.threshold(frame_gray, 200, 255, cv2.THRESH_BINARY)
#     contours, hierarchy = cv2.findContours(thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
#     image_out = np.zeros_like(frame)
#     image_out = cv2.drawContours(image_out, contours, -1, (0, 255, 0), 2)
#     return image_out


def detect_movement(video_path):
    cap = cv2.VideoCapture(video_path)

    if not cap.isOpened():
        print("Ошибка при открытии видеофайла")
        return

    ret, prev_frame = cap.read()
    if not ret:
        print("Ошибка при чтении первого кадра")
        return

    prev_frame_gray = cv2.cvtColor(prev_frame, cv2.COLOR_RGB2GRAY)
    while True:
        ret, frame = cap.read()
        if not ret:
            break
        
        frame_gray = cv2.cvtColor(frame, cv2.COLOR_RGB2GRAY)
        frame_diff = cv2.absdiff(prev_frame_gray, frame_gray)
        _, thresh = cv2.threshold(frame_diff, 40, 255, cv2.THRESH_BINARY)
        contours, _ = cv2.findContours(thresh, cv2.RETR_EXTERNAL, 
                                               cv2.CHAIN_APPROX_SIMPLE)
        
        movement_flag = False
        for contour in contours:
            if cv2.contourArea(contour) > 500:
                movement_flag = True
                break
        
        card = np.zeros((100, 100, 3), dtype=np.uint8)
        if movement_flag == True:
            card[:, :] = (0, 0, 255)
            cv2.drawContours(frame, contours, -1, (0, 0, 255), 4)
        else:
            card[:, :] = (0, 255, 0)
        
        
        cv2.imshow('frame', frame)
        cv2.imshow('card', card)
        prev_frame_gray = frame_gray

        if cv2.waitKey(20) & 0xFF == 27:
            break

    cap.release()
    cv2.destroyAllWindows()


video_path = 'l6/lab/video.mp4'
# process_video(video_path)
frame_path = '/home/ezhsluny/Documents/python/l6/lab/frames'

detect_movement(video_path)
