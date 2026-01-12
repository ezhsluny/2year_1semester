import cv2 as cv
import numpy as np

def rotate_angle(image, angle):
    heigh, width = image.shape[:2]
    heigh_center = round(heigh/2)
    width_center = round(width/2)

    rot_mat = cv.getRotationMatrix2D((width_center, heigh_center), angle, 1.0)
    r_image =  cv.warpAffine(image, rot_mat, (width, heigh), flags=cv.INTER_LINEAR)

    return r_image


def downscale_image(image, scale_factor):
    height, width = image.shape[:2]

    new_height = int(height / scale_factor)
    new_width = int(width / scale_factor)

    resized_image = cv.resize(image, (new_width, new_height))

    return resized_image


def find_ghost_corners(ghost_image, house_image):
    sift = cv.SIFT_create()
    kp_house, des_house = sift.detectAndCompute(house_image, None)
    kp_ghost, des_ghost = sift.detectAndCompute(ghost_image, None)
    
    #des
    bf = cv.BFMatcher(cv.NORM_L2, crossCheck=False)
    matches = bf.knnMatch(des_ghost,des_house, k=2)
    #knnMatch
    good = []
    for m, n in matches: #m - first closect, n - second closest match
        if m.distance < 0.7*n.distance:
            good.append(m)
    
    
    if len(good) > 0:
        src_pts = np.float32([kp_ghost[m.queryIdx].pt for m in good]).reshape(-1, 1, 2)
        dst_pts = np.float32([kp_house[m.trainIdx].pt for m in good]).reshape(-1, 1, 2)
    
        M, _ = cv.findHomography(src_pts, dst_pts, cv.RANSAC)
        if M is not None:
            h, w = ghost_image.shape
            ghost_corners = np.float32([[0, 0],
                                        [0, h - 1],
                                        [w - 1, h - 1],
                                        [w - 1, 0]]).reshape(-1, 1, 2)
            transformed_corners = cv.perspectiveTransform(ghost_corners, M)
            return transformed_corners
            
    return None


def find_all_ghosts_corners(ghosts_list, house_image):
    corners = []
    for ghost in ghosts_list:
        corner = find_ghost_corners(ghost, house_image)
        house_image = draw_rectangles(corner, house_image)
        corners.append(corner)
    return corners


def draw_rectangles(corners, house_image):
    if corners is not None:
        house_image = cv.fillPoly(house_image,
                                  [np.int32(corners)],
                                  (0, 255, 0))
    return house_image

def draw_polylines(list_corners, house_image):
    for corners in list_corners:
        if corners is not None:
            house_image = cv.polylines(house_image,
                                      [np.int32(corners)],
                                      True,
                                      (0, 255, 0),
                                      3)

house_with_ghosts = cv.imread('l7/halloween/lab7.png')
house = cv.imread('l7/halloween/lab7.png')
# house_with_ghosts = cv.medianBlur(house_with_ghosts, 3)
candy_ghost = cv.imread("l7/halloween/candy_ghost.png")
pampkin_ghost = cv.imread("l7/halloween/pampkin_ghost.png")
scary_ghost = cv.imread("l7/halloween/scary_ghost.png")

candy_ghost_gray = cv.cvtColor(candy_ghost, cv.COLOR_BGR2GRAY)
pampkin_ghost_gray = cv.cvtColor(pampkin_ghost, cv.COLOR_BGR2GRAY)
scary_ghost_gray = cv.cvtColor(scary_ghost, cv.COLOR_BGR2GRAY)

# house_crop = house_with_ghosts[0:370, 0:350]
# house_crop = cv.medianBlur(house_crop, 1)



ghosts = [rotate_angle(candy_ghost_gray, -30), 
          candy_ghost_gray, 
          pampkin_ghost_gray,
          scary_ghost_gray, 
          cv.flip(scary_ghost_gray, 0),
          rotate_angle(downscale_image(candy_ghost_gray, 2), -10)
]


ghosts1 = []
# corners_list1 = find_all_ghosts_corners(ghosts1, house_crop)

corners_list = find_all_ghosts_corners(ghosts, house_with_ghosts)
# corners_list.append(corners_list1[0])
# draw_rectangles(corners_list, house_with_ghosts)
draw_polylines(corners_list, house)
cv.imshow("ghosts", house)
cv.waitKey(0)
cv.destroyAllWindows()