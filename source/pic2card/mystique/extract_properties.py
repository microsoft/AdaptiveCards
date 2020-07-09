"""Module for extracting design element's properties"""

import math
from io import BytesIO
import base64
from typing import Tuple, Dict

from pytesseract import pytesseract
from PIL import Image
import cv2
import numpy as np

from mystique import default_host_configs

class ExtractProperties:
    """
    Class handles of property extraction from the identified design 
    elements.
    from all the design elements - extracts text
    from textual elements - extracts size, color, weight
    from actionset elements - extracts style based on the background 
                              color
    from image objects - extracts image size 
    """

    def get_actionset_type(self, image=None, coords=None):
        """
        Returns the actionset style by finding the
        closes background color of the obejct

        @param image: input PIL image
        @param coords: object's coordinate

        @return : style string of the actionset
        """
        cropped_image = image.crop(coords)
        # get 2 dominant colors
        quantized = cropped_image.quantize(colors=2, method=2)
        # extract the background color
        background_color = quantized.getpalette()[:3]
        colors = {
            "destructive": [
                (255, 0, 0),
                (180, 8, 0),
                (220, 54, 45),
                (194, 25, 18),
                (143, 7, 0)
            ],
            "positive": [
                (0, 0, 255),
                (7, 47, 95),
                (18, 97, 160),
                (56, 149, 211)
            ]
        }
        style = "default"
        found_colors = []
        distances = []
        # find the dominant background colors based on the RGB difference
        for key, values in colors.items():
            for value in values:
                distance = np.sqrt(
                    np.sum((np.asarray(value) - np.asarray(background_color)) ** 2))
                if distance <= 150:
                    found_colors.append(key)
                    distances.append(distance)
        if found_colors:
            index = distances.index(min(distances))
            style = found_colors[index]
        return style

    def get_text(self, image=None, coords=None):
        """
        Extract the text from the object coordinates 
        in the input deisgn image using pytesseract.

        @param image: input PIL image
        @param coords: tuple of coordinates from which 
                       text should be extracted
        @return: ocr text
        """
        coords = (coords[0] - 5, coords[1], coords[2] + 5, coords[3])
        cropped_image = image.crop(coords)
        cropped_image = cropped_image.convert("LA")
        w, h = cropped_image.size
        cropped_image = cropped_image.resize((w*10, h*10),
                                             Image.ANTIALIAS)

        return pytesseract.image_to_string(
            cropped_image, lang="eng", config="--psm 6")

    def get_size_and_weight(self, image=None, coords=None):
        """
        Extract the size and weight of textual contents from
        the input image by taking an average of each edge 
        countour's of height and width of each character.

        @param image : input PIL image
        @param coords: list of coordinated from which 
                       text and height should be extracted
        @return: size and weight
        """
        cropped_image = image.crop(coords)
        img = np.asarray(cropped_image)
        img = cv2.cvtColor(img, cv2.COLOR_RGB2BGR)
        # preprocess
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        gray = cv2.blur(gray, (5, 5))
        kernel = np.ones((5, 5), np.uint8)
        # edge detection
        edged = cv2.Canny(img, 30, 200)
        # contours bulding
        _, contours, _ = cv2.findContours(
            edged, cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)
        box_width = []
        box_height = []
        # calculate the average width and height of the contour
        # coords of the object
        for c in contours:
            (x, y, w, h) = cv2.boundingRect(c)
            box_width.append(w)
            box_height.append(h)

        weights = sum(box_width) / len(box_width)
        heights = sum(box_height) / len(box_height)
        size = "Default"
        weight = "Default"

        if heights <= 5.5:
            size = "Small"
        elif 5.5 < heights <= 7:
            size = "Default"
        elif 7 < heights <= 15:
            size = "Medium"
        elif 15 < heights <= 20:
            size = "Large"
        else:
            size = "ExtraLarge"

        if (size == "Small" or size == "Default") and weights >= 5:
            weight = "Bolder"
        elif size == "Medium" and weights > 6.5:
            weight = "Bolder"
        elif size == "Large" and weights > 8:
            weight = "Bolder"
        elif size == "ExtraLarge" and weights > 9:
            weight = "Bolder"

        return size, weight

    def get_alignment(self, image=None, xmin=None, xmax=None):
        """
        Get the horizontal alignment of the elements by defining a
        thresold based on the xmin and xmax of each object.

        @param image: input PIL image
        @param xmin: xmin of the object detected
        @param xmax: xmax of the object detected

        @return: position string[ Left/Right/Center]
        """

        avg = math.ceil((xmin + xmax) / 2)
        w, h = image.size
        if 0 <= (avg / w) * 100 < 45:
            return "Left"
        elif 45 <= (avg / w) * 100 < 55:
            return "Center"
        else:
            return "Right"

    def get_colors(self, image=None, coords=None):
        """
        EXtract the text color by quantaizing the image i.e
        [cropped to the coordiantes] into 2 colors mainly
        background and foreground and find the closest matching
        foreground color.

        @param image: input PIL image
        @param coords: coordinates from which color needs to be 
                       extracted

        @return: foreground color name
        """
        cropped_image = image.crop(coords)
        # get 2 dominant colors
        q = cropped_image.quantize(colors=2, method=2)
        dominant_color = q.getpalette()[3:6]

        colors = {
            "Attention": [
                (255, 0, 0),
                (180, 8, 0),
                (220, 54, 45),
                (194, 25, 18),
                (143, 7, 0)
            ],
            "Accent": [
                (0, 0, 255),
                (7, 47, 95),
                (18, 97, 160),
                (56, 149, 211)
            ],
            "Good": [
                (0, 128, 0),
                (145, 255, 0),
                (30, 86, 49),
                (164, 222, 2),
                (118, 186, 27),
                (76, 154, 42),
                (104, 187, 89)
            ],
            "Dark": [
                (0, 0, 0),
                (76, 76, 76),
                (51, 51, 51),
                (102, 102, 102),
                (153, 153, 153)
            ],
            "Light": [
                (255, 255, 255)
            ],
            "Warning": [
                (255, 255, 0),
                (255, 170, 0),
                (184, 134, 11),
                (218, 165, 32),
                (234, 186, 61),
                (234, 162, 33)
            ]
        }
        color = "Default"
        found_colors = []
        distances = []
        # find the dominant text colors based on the RGB difference
        for key, values in colors.items():
            for value in values:
                distance = np.sqrt(np.sum(
                    (np.asarray(value) - np.asarray(dominant_color)) ** 2))
                if distance <= 150:
                    found_colors.append(key)
                    distances.append(distance)
        # If the color is predicted as LIGHT check for false cases
        # where both dominan colors are White
        if found_colors:
            index = distances.index(min(distances))
            color = found_colors[index]
            if found_colors[index] == "Light":
                background = q.getpalette()[:3]
                foreground = q.getpalette()[3:6]
                distance = np.sqrt(
                    np.sum(
                        (np.asarray(background) -
                         np.asarray(foreground)) ** 2))
                if distance < 150:
                    color = "Default"
        return color


class CollectProperties(ExtractProperties):
    """
    Helps to collect the properties for respective design object.
    """
    def __init__(self, image):
        self.pil_imgae = image

    def actionset(self, coords: Tuple) -> Dict:
        """
        Returns the actionset properties of the extracted design object
        @return: property object
        """
        return {
                "horizontal_alignment": self.get_alignment(image=self.pil_imgae,
                                                           xmin=coords[0],
                                                           xmax=coords[2]),
                "data": self.get_text(image=self.pil_imgae, coords=coords),
                "style": self.get_actionset_type(image=self.pil_imgae,
                                                 coords=coords)
        }

    def textbox(self, coords: Tuple) -> Dict:
        """
        Returns the textbox properties of the extracted design object
        @return: property object
        """
        size, weight = self.get_size_and_weight(image=self.pil_imgae,
                                                coords=coords)
        return {
                "horizontal_alignment": self.get_alignment(image=self.pil_imgae,
                                                           xmin=coords[0],
                                                           xmax=coords[2]),
                "data": self.get_text(image=self.pil_imgae, coords=coords),
                "size": size,
                "weight": weight,
                "color": self.get_colors(image=self.pil_imgae, coords=coords)

        }

    def radiobutton(self, coords: Tuple) -> Dict:
        """
        Returns the radiobutton properties of the extracted design object
        @return: property object
        """
        return {
                "horizontal_alignment": self.get_alignment(image=self.pil_imgae,
                                                           xmin=coords[0],
                                                           xmax=coords[2]),
                "data": self.get_text(image=self.pil_imgae, coords=coords),
        }

    def checkbox(self, coords: Tuple) -> Dict:
        """
        Returns the checkbox properties of the extracted design object
        @return: property object
        """
        return {
                "horizontal_alignment": self.get_alignment(image=self.pil_imgae,
                                                           xmin=coords[0],
                                                           xmax=coords[2]),
                "data": self.get_text(image=self.pil_imgae, coords=coords),
        }

    def image(self, coords: Tuple) -> Dict:
        """
        Returns the image properties of the extracted design object
        @return: property object
        """
        cropped = self.pil_imgae.crop(coords)
        buff = BytesIO()
        cropped.save(buff, format="PNG")
        base64_string = base64.b64encode(
                buff.getvalue()).decode()
        data = f'data:image/png;base64,{base64_string}'

        img_width, img_height = cropped.size
        # set the closest size label for the image object's width and
        # height
        size = "Auto"
        keys = list(default_host_configs.IMAGE_SIZE.keys())
        width_key = min(keys, key=lambda x: abs(x - img_width))
        height_key = min(keys, key=lambda x: abs(x - img_height))
        if width_key == height_key:
            size = default_host_configs.IMAGE_SIZE[width_key]
        size = size
        return {
                "horizontal_alignment": self.get_alignment(image=self.pil_imgae,
                                                           xmin=coords[0],
                                                           xmax=coords[2]),
                "data": data,
                "size": size
        }
