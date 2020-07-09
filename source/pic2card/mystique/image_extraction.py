"""Module for image extraction inside the card design"""

import base64
from typing import Dict, List, Tuple
import os
import sys
from os import environ
from io import BytesIO
import math

import numpy as np
import requests
import cv2
from PIL import Image

from mystique import config


class ImageExtraction:
    """
    Class to identify the edges in the design image and filtering out the
    faster rcnn objects to obtain the image object boundaries and to add
    the cropped out image obejcts as base64 to the card paylaod json.
    """

    def find_points(self, coord1, coord2, for_image=None):
        """
        Finds the intersecting bounding boxes by finding
           the highest x and y ranges of the 2 coordinates
           and determine the intersection by deciding weather
           the new xmin>xmax or the new ymin>ymax.
           For non image objects, includes finding the intersection
           area to a thersold to determine intersection

        @param coord1: list of coordinates of 1st object
        @param coord2: list of coordinates of 2nd object
        @param for_image: boolean to differentiate non image
                          objects
        @return: True/False
        """
        x5 = max(coord1[0], coord2[0])
        y5 = max(coord1[1], coord2[1])
        x6 = min(coord1[2], coord2[2])
        y6 = min(coord1[3], coord2[3])
        if x5 > x6 or y5 > y6:
            return False

        if for_image:
            return True
        else:

            intersection_area = (x6 - x5) * (y6 - y5)
            point1_area = (coord1[2] - coord1[0]) * (coord1[3] - coord1[1])
            point2_area = (coord2[2] - coord2[0]) * (coord2[3] - coord2[1])
            if intersection_area / point1_area > 0.55 or intersection_area / point2_area > 0.55:
                return True
            else:
                return False

    def check_contains(self, point1: Tuple, point2: Tuple, between_models=False):
        """
        Check if a point[coordinates of an object] is inside another point or not

        @param point1: Tuple of coordinates
        @param point2: Tuple of coordinates
        @param between_models: A Boolean for check within image objects or between
                               the RCNN and image model.[ default - Flase i.e
                               by default it's done within image objects]
        @return: True/False
        """
        x_range = min(point2[0], point2[2]), max(point2[0], point2[2])
        y_range = min(point2[1], point2[3]), max(point2[1], point2[3])
        contains = ((x_range[0] <= point1[0] <= x_range[1]
                     and x_range[0] <= point2[2] <= x_range[1]) and
                    (y_range[0] <= point1[1] <= y_range[1]
                     and y_range[0] <= point2[3] <= y_range[1]))
        if between_models:
            return contains or ((point2[0] <= point1[0] + 5 <= point2[2])
                                and (point2[1] <= point1[1] + 5 <= point2[3]))
        else:
            return contains

    def remove_noise_objects(self, points: List[Tuple]):
        """
        Removes all noisy objects by eliminating all smaller and intersecting
                objects within / with the bigger objects.

        @param points: list of detected object's coordinates.

        @return points: list of filtered objects coordinates
        """
        positions_to_delete = []
        intersection_combination = []
        for i in range(len(points)):
            for j in range(len(points)):
                if j < len(points) and i < len(points) and i != j:
                    box1 = [float(c) for c in points[i]]
                    box2 = [float(c) for c in points[j]]
                    intersection = self.find_points(box1, box2, for_image=True)
                    contain = self.check_contains(box1, box2)
                    if intersection or contain:
                        if (i, j) not in intersection_combination:
                            # remove the smallest box
                            box1_area = (box1[2] - box1[0]) * (box1[3] - box1[1])
                            box2_area = (box2[2] - box2[0]) * (box2[3] - box2[1])
                            if box1_area > box2_area and j not in positions_to_delete:
                                positions_to_delete.append(j)
                                intersection_combination.append((i, j))
                            elif box1_area < box1_area and i not in positions_to_delete :
                                    positions_to_delete.append(i)
                                    intersection_combination.append((i, j))
        points = [p for ctr, p in enumerate(
            points) if ctr not in positions_to_delete]
        return points

    def image_edge_detection(self, image: Image):
        """
        Detecs the image edges from the design.

        @param  image: input open-cv image

        @return image_points: list of image objects coordinates
        """
        image_points = []
        # pre processing
        gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
        dst = cv2.equalizeHist(gray)
        blur = cv2.GaussianBlur(dst, (5, 5), 0)
        ret, im_th = cv2.threshold(blur, 150, 255, cv2.THRESH_BINARY)
        # Set the kernel and perform opening
        # k_size = 6
        kernel = np.ones((5, 5), np.uint8)
        opened = cv2.morphologyEx(im_th, cv2.MORPH_OPEN, kernel)
        # edge detection
        edged = cv2.Canny(opened, 0, 255)
        # countours
        _, contours, hierarchy = cv2.findContours(
            edged, cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)
        # get the coords of the contours
        for c in contours:
            (x, y, w, h) = cv2.boundingRect(c)
            image_points.append((x, y, x + w, y + h))

        return image_points

    def remove_model_intersection(self, points1: List[Tuple], points2: List[Tuple],
                                  included_points_positions: List, image_first: bool):
        """
        Removes all image object's intersecting or containing the rcnn
        detected objects.

        @param points1: list of detected image or rcnn model objects coordinates
        @param points2: list of detected image or rcnn model objects coordinates
        @param included_points_positions: list of binray values for maintaing
                                          the position of the points that
                                          intersects.
        @param image_first: Boolean value to determine the image object points
                            among points1 and points2
        """
        
        for point1_ctr, point1 in enumerate(points1):
            for point2_ctr, point2 in enumerate(points2):
                if not image_first:
                    intersection = self.find_points(
                        point1, point2, for_image=True)
                else:
                    intersection = False
                contains = self.check_contains(
                    point1, point2, between_models=True)
                if contains or intersection:
                    if image_first:
                        included_points_positions[point1_ctr] = 1
                    else:
                        included_points_positions[point2_ctr] = 1

    def get_image_with_boundary_boxes(self, image=None, detected_coords=None,
                                      pil_image=None, faster_rcnn_image=None):
        """
        Returns the Detected image object boundary boxes along with
        faster rcnn detected boxes.

        @param image: input open-cv image
        @param detected_coords: list of detected 
                                   object's coordinates from faster rcnn model
        @param pil_image: Input PIL image
        @param faster_rcnn_image: image with faster rcnn detected object's
        boundary boxes
        """
        image_points = self.image_edge_detection(image)

        included_points_positions = [0] * len(image_points)
        self.remove_model_intersection(
            image_points, detected_coords, included_points_positions, True)
        self.remove_model_intersection(
            detected_coords, image_points, included_points_positions, False)

        # remove the included points in intersection removal
        image_points1 = []
        for ctr, point in enumerate(image_points):
            if included_points_positions[ctr] != 1:
                image_points1.append(point)
        image_points = sorted(set(image_points1), key=image_points1.index)

        # If the design boundary is detected as image object remove it
        width, height = pil_image.size
        widths = [point[2] - point[0] for point in image_points]
        heights = [point[3] - point[1] for point in image_points]
        for ctr, w in enumerate(widths):
            if ((w*heights[ctr])/(width*height))*100 >= 70.0:
                del image_points[ctr]
        image_points = self.remove_noise_objects(image_points)

        for point in image_points:
            cv2.rectangle(faster_rcnn_image,
                          (point[0], point[1]), (point[2], point[3]), (0, 0, 255), 2)

    def detect_image(self, image=None, detected_coords=None, pil_image=None):
        """
        Returns the Detected image coordinates by buidling 
        countours over the design edge detection and on removing
        the faster rcnn model detected obects.

        @param image: input open-cv image
        @param detected_coords: list of detected 
                                object's coordinates from faster 
                                rcnn model
        @param pil_image: Input PIL image

        @return: list of image object coordinates
        """
        image_points = self.image_edge_detection(image)
        
        included_points_positions = [0] * len(image_points)
        self.remove_model_intersection(
            image_points, detected_coords, included_points_positions, True)
        self.remove_model_intersection(
            detected_coords, image_points, included_points_positions, False)

        # remove the included points in intersection removal
        image_points1 = []
        for ctr, point in enumerate(image_points):
            if included_points_positions[ctr] != 1:
                image_points1.append(point)
        image_points = sorted(set(image_points1), key=image_points1.index)

        # If the design boundary is detected as image object remove it
        width, height = pil_image.size
        widths = [point[2] - point[0] for point in image_points]
        heights = [point[3] - point[1] for point in image_points]
        for ctr, w in enumerate(widths):
            if ((w*heights[ctr])/(width*height))*100 >= 70.0:
                del image_points[ctr]
        image_points = self.remove_noise_objects(image_points)

        return image_points

    def image_crop_get_url(self, coords=None, image=None):
        """
        Crops the individual image objects from the input
        design and get the hosted url of the images.

        @param coords: list of image points
        @param image: input PIL image

        @return: list of image urls.
        """
        images_urls = []
        images_sizes = []
        for coords in coords:
            cropped = image.crop((coords[0], coords[1], coords[2], coords[3]))
            images_sizes.append(cropped.size)
            buff = BytesIO()
            cropped.save(buff, format="PNG")
            base64_string = base64.b64encode(buff.getvalue()).decode()
            images_urls.append(f"data:image/png;base64,{base64_string}")

            # Place default image holder if image object size is greater
            # than 1MB
            size = sys.getsizeof(base64_string)
            if size >= config.IMG_MAX_HOSTING_SIZE:
                images_urls.append(config.DEFAULT_IMG_HOSTING)
        if os.path.exists("image_detected.png"):
            os.remove("image_detected.png")
        return images_urls, images_sizes
