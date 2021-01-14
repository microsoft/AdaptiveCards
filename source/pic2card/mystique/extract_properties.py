"""Module for extracting design element's properties"""

import base64
import math
from io import BytesIO
from typing import Tuple, Dict, List, Any, Union

import numpy as np
from PIL import Image
from pytesseract import pytesseract, Output

from mystique import config
from mystique.utils import load_instance_with_class_path
from mystique.extract_properties_abstract import (AbstractFontColor,
                                                  AbstractBaseExtractProperties)

from mystique.card_layout.ds_helper import (ContainerDetailTemplate,
                                            DsHelper)


class BaseExtractProperties(AbstractBaseExtractProperties):

    """
    Base Class for all design objects's common properties extraction.
    """
    def get_alignment(self, image=None, xmin=None, xmax=None,
                      width=None) -> Union[str, None]:
        """
        Get the horizontal alignment of the elements by defining a
        ratio based on the xmin and xmax center of each object.
        if a element's xmin and xmax avg lies within:
        0 - 45 % [ left range ] of the image width
        45 - 55% [ center rance ] of the image width
        > 55% [ right range ] of the image width
        @param image: input PIL image
        @param xmin: xmin of the object detected
        @param xmax: xmax of the object detected
        @return: position string[Left/Right/Center]
        @param width: width of the design element's parent container
        """
        avg = math.ceil((xmin + xmax) / 2)
        if not width:
            width, height = image.size

        left_range = config.ALIGNMENT_THRESHOLDS.get("left_range")
        center_range = config.ALIGNMENT_THRESHOLDS.get("center_range")
        #  if an object lies within the min and max range of the start or end
        #  of the parent coordinates then the object is considered as [left
        #  / right] by default [ for example :to avoid any lengthy textbox
        #  coming into center when considering the xmin and xmax center]
        min_range = (width *
                     config.ALIGNMENT_THRESHOLDS.get("minimum_range"))
        max_range = (width *
                     config.ALIGNMENT_THRESHOLDS.get("center_range"))

        left_min_condition = math.floor(xmin) <= math.ceil(min_range)

        right_min_condition = math.floor(xmax) >= math.ceil(max_range)

        if image:
            if left_min_condition:
                return "Left"
        if not image:
            if left_min_condition and not right_min_condition:
                return "Left"
            if right_min_condition and not left_min_condition:
                return "Right"
            if left_min_condition and right_min_condition:
                return None
        if 0.0 <= (avg / width) < left_range:
            return "Left"
        elif left_range <= (avg / width) < center_range:
            return "Center"
        else:
            return "Right"

    def get_line_alignment(self, image_data: Dict):
        """
        Extracts the alignment of the paragraph text based on the tesseract
        detected lines and top index values.
        Based on the line number and the left values from the pytesseract o/p
        we can check for the distance in left alignments of each line with
        the help of the threshold values , bins the alignments values.
        @param image_data: tesseract detected text data from image
        @return: alignment value
        """

        lines = image_data.get("line_num", [])
        left_values = image_data.get("left", [])
        line_one_index = lines.index(1)
        line_two_index = lines.index(2)
        difference_ratio = (
            max(left_values[line_one_index], left_values[line_two_index]) -
            min(left_values[line_one_index], left_values[line_two_index]))
        difference_ratio = difference_ratio / max(left_values)
        minimum_range = config.LINE_ALIGNMENT_THRESHOLD.get("minimum")
        maximum_range = config.LINE_ALIGNMENT_THRESHOLD.get("maximum")
        if difference_ratio < minimum_range:
            return "Left"
        elif minimum_range < difference_ratio < maximum_range:
            return "Center"
        else:
            return "Right"

    def get_text(self, image: Image, coords: Tuple) -> Tuple[str, Any]:
        """
        Extract the text from the object coordinates
        in the input deisgn image using pytesseract.
        @param image: input PIL image
        @param coords: tuple of coordinates from which
                       text should be extracted
        @return: ocr text, pytesseract image data
        """
        coords = (coords[0] - 5, coords[1], coords[2] + 5, coords[3])
        cropped_image = image.crop(coords)
        cropped_image = cropped_image.convert("LA")

        img_data = pytesseract.image_to_data(
            cropped_image, lang="eng", config="--psm 6",
            output_type=Output.DICT)
        text_list = filter(None, img_data['text'])
        extracted_text = ' '.join(text_list).lstrip("#-_*~").strip()
        return extracted_text, img_data


class FontColor(AbstractFontColor):
    """
    Class handles extraction of font color of respective design element.
    """

    def get_colors(self, image: Image, coords: Tuple) -> str:
        """
        Extract the text color by quantaizing the image i.e
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


class ChoiceSetProperty(BaseExtractProperties):

    """
    Class handles extraction of ocr text and alignment property of respective
    choice set elements like radio button and checkboxes.
    """

    def checkbox(self, image: Image, coords: Tuple) -> Dict:
        """
        Returns the checkbox properties of the extracted design object
        @return: property object
        """
        text_data = self.get_text(image, coords)
        return {
            "horizontal_alignment": self.get_alignment(
                image=image,
                xmin=coords[0],
                xmax=coords[2]
            ),
            "data": text_data[0],
            "image_data": text_data[1],
        }

    def radiobutton(self, image: Image, coords: Tuple) -> Dict:
        """
        Returns the radio button properties of the extracted design object
        @return: property object
        """
        return self.checkbox(image, coords)


class TextBoxProperty(BaseExtractProperties, FontColor):
    """
    Class handles extraction of text properties from all the design elements
    like size, weight, colour and ocr text
    """

    def textbox(self, image: Image, coords: Tuple) -> Dict:
        """
        Returns the textbox properties of the extracted design object
        @return: property object
        """
        data, image_data = self.get_text(image, coords)
        # Adding uuid to image_data dict
        image_data.update(uuid=self.uuid)
        font_spec = load_instance_with_class_path(
            config.FONT_SPEC_REGISTRY[config.ACTIVE_FONTSPEC_NAME])
        return {
            "horizontal_alignment": self.get_alignment(
                image=image,
                xmin=coords[0],
                xmax=coords[2]
            ),
            "data": data,
            "image_data": image_data,
            "size": font_spec.get_size(image, coords, img_data=image_data),
            "weight": font_spec.get_weight(image, coords, img_data=image_data),
            "color": self.get_colors(image, coords)

        }


class ActionSetProperty(BaseExtractProperties):
    """
    Class handles extraction of actionset object properties of its
    respective design object
    """

    def get_actionset_type(self, image: Image, coords: Tuple) -> str:
        """
        Returns the actionset style by finding the
        closes background color of the obejct
        @param image: input PIL image
        @param coords: object's coordinate
        @return: style string of the actionset
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
                    np.sum(
                        (np.asarray(value) - np.asarray(
                            background_color)) ** 2
                    )
                )
                if distance <= 150:
                    found_colors.append(key)
                    distances.append(distance)
        if found_colors:
            index = distances.index(min(distances))
            style = found_colors[index]
        return style

    def actionset(self, image: Image, coords: Tuple) -> Dict:
        """
        Returns the actionset properties of the extracted design object
        @return: property object
        """
        text_data = self.get_text(image, coords)
        return {
            "horizontal_alignment": self.get_alignment(
                image=image,
                xmin=coords[0],
                xmax=coords[2]
            ),
            "data": text_data[0],
            "image_data": text_data[1],
            "style": self.get_actionset_type(image, coords)
        }


class ImageProperty(BaseExtractProperties):
    """
    Class handles extraction of image properties from image design object
    like image size, image text and its alignment property
    """

    def get_data(self, base64_string) -> str:
        """
        Returns the base64 string for the detected image property object
        @param base64_string: input base64 encoded value for the buff object
        @return: base64_string appended to filepath
        """
        data = f'data:image/png;base64,{base64_string}'
        return data

    def extract_image_size(self, cropped_image: Image,
                           pil_image: Image) -> str:
        """
        Returns the image size value based on the width and height ratios
        of the image objects to the actual design image.
        @param cropped_image: image object
        @param pil_image: input design image
        @return: image width value
        """
        img_width, img_height = cropped_image.size
        width, height = pil_image.size
        width_ratio = (img_width / width) * 100
        height_ratio = (img_height / height) * 100
        # if the width and height ratio differs more the 25% return the size as
        # Auto
        if abs(width_ratio - height_ratio) > 20:
            return "Auto"
        else:
            # select the image size based on the minimum distance with
            # the default host config values for image size
            keys = list(config.IMAGE_SIZE_RATIOS.keys())
            ratio = (width_ratio, height_ratio)
            distances = [np.sqrt(np.sum(((np.asarray(ratio) -
                                          np.asarray(tuple(point))) ** 2)))
                         for point in keys]
            key = keys[distances.index(min(distances))]
            return config.IMAGE_SIZE_RATIOS[key]

    def image(self, image: Image, coords: Tuple) -> Dict:
        """
        Returns the image properties of the extracted design object
        @return: property object
        """
        cropped = image.crop(coords)
        buff = BytesIO()
        cropped.save(buff, format="PNG")
        base64_string = base64.b64encode(
            buff.getvalue()).decode()

        size = self.extract_image_size(cropped, image)
        return {
            "horizontal_alignment": self.get_alignment(
                image=image,
                xmin=coords[0],
                xmax=coords[2]
            ),
            "data": self.get_data(base64_string),
            "size": size
        }


class CollectProperties(TextBoxProperty, ChoiceSetProperty,
                        ActionSetProperty, ImageProperty):
    """
    Class handles of property extraction from the identified design
    elements.
    from all the design elements - extracts text, alignment
    from textual elements - extracts size, color, weight
    from actionset elements - extracts style based on the background
                              color
    from image objects - extracts image size and image text
    """
    def __init__(self, image=None):
        self.pil_image = image


class ContainerProperties:
    """
    Class handling the needed utility functions for extraction and collection
    of different types of container properties

    """

    def __init__(self, pil_image=None):
        self.pil_image = pil_image

    def get_container_properties(self, design_object: Union[Dict, List[Dict]],
                                 pil_image,
                                 container_detail: ContainerDetailTemplate
                                 ) -> List[Dict]:
        """
        Method to extract the design properties of the containers objects.
        @param design_object: the container object
        @param pil_image: input PIL image
        @returns: the property updated design element.
        @param container_detail: object of the ContainerDetailTemplate
        """

        # TODO: remove the choiceset removal part after the container
        #  alignment property is added
        if isinstance(design_object, list):
            for design_obj in design_object:
                self.get_container_properties(design_obj, pil_image,
                                              container_detail)

        elif (isinstance(design_object, dict)
              and design_object.get("object", "") in DsHelper.CONTAINERS[:-1]):

            container_objects = getattr(container_detail,
                                        design_object.get("object", ""))
            # TODO: This check will be removed after row-column optimization
            if design_object.get("object") == "column":
                container_property = None
            else:
                property_object = getattr(self, design_object.get("object", ""))
                container_property = property_object(design_object)

            if container_property:
                design_object.update(container_property)
            self.get_container_properties(container_objects(design_object),
                                          pil_image,
                                          container_detail)
        return design_object

    def get_column_width_keys(self, default_config: Dict, ratio: Tuple,
                              column_set: Dict,
                              column_number: int) -> Union[Dict, None]:
        """
        Extract the column width key from the default config which is minimum
        in distance with the given point / ratio
        @param default_config: the default host config dict for column width
        @param ratio: the point derived from the column coordinates
        @param column_set: dict of columns
        @param column_number: the position of the column
        """
        keys = list(default_config.keys())
        distances = [np.sqrt(np.sum(((np.asarray(ratio) -
                                      np.asarray(tuple(point))) ** 2)))
                     for point in keys]
        key = keys[distances.index(min(distances))]
        column_set["row"][column_number]["width"] = default_config[key]
        return column_set

    def _get_mid_distance(self, point1: List, point2: List) -> float:
        """
        Returns the mid point - end point distance for a given 2 points
        @param point1: coordinates of object one
        @param point2: coordinates of object two
        @return: mid distance
        """
        mid_point1 = np.asarray(((point1[0] + point1[2]) / 2,
                                 (point1[1] + point1[3]) / 2))
        mid_point2 = np.asarray(((point2[0] + point2[2]) / 2,
                                 (point2[1] + point2[3]) / 2))

        end_point1 = np.asarray(
            (min(point1[0], point2[0]), min(point1[1], point2[1])))
        end_point2 = np.asarray(
            (max(point1[2], point2[2]), max(point1[3], point2[3])))
        end_distance = np.sqrt(np.sum(((end_point1 - end_point2) ** 2)))
        mid_distance = np.sqrt(np.sum(((mid_point1 - mid_point2) ** 2)))
        mid_distance = (mid_distance / end_distance)

        return mid_distance

    def change_column_coordinates(self, column: Dict) -> List:
        """
        Change/ return the column coordinates for the new layout generation
        method , if the column has the image-set get the element's
        coordinates to the coordinates of the 1st image in the image-set.
        @param column: column layout structure
        @return: column coordinates
        """
        if "imageset" in [list(item.keys())[0]
                          for item in column.get("column")["items"]]:
            item_coords = [item["imageset"]["items"][0]["coordinates"]
                           if item["object"] == "imageset"
                           else item["coordinates"]
                           for item in column["column"]["items"]]
            column_coords = [min([coord[0] for coord in item_coords]),
                             min([coord[1] for coord in item_coords]),
                             max([coord[2] for coord in item_coords]),
                             max([coord[3] for coord in item_coords])]
            return column_coords
        return column["coordinates"]

    def extract_column_width(self, column_set: Dict,
                             image: Image) -> Union[None, Dict]:
        """
        Extract column width property for the given columnset based on the
        mid point distance between 2 design objects.
        @param column_set: list of column design objects
        @param image: input PIL image
        """
        columns = column_set.get("columns", column_set.get("row", []))
        image_width, _ = image.size
        for ctr, column in enumerate(columns):
            config_file = ''
            ratio = ()
            if ctr + 1 < len(columns):
                # if the column is not a last column then calculate the
                # mid point distance ratio for the 2 element
                first_column = column.get("coordinates", [])
                second_column = column_set.get(
                    "row", [])[ctr + 1].get("coordinates", [])
                config_file = config.COLUMN_WIDTH_DISTANCE
                mid_ratio = self._get_mid_distance(first_column,
                                                   second_column)
                ratio = (1, mid_ratio)
            elif ctr == len(columns) - 1:
                # if the column is the last column then calculate the
                # xmax / parent_width [ image ] ratio
                first_column = self.change_column_coordinates(column)
                config_file = config.LAST_COLUMN_THRESHOLD
                xmax_ratio = first_column[2] / image_width
                ratio = (1, xmax_ratio)
            column_set = self.get_column_width_keys(
                config_file, ratio, column_set, ctr)

        return column_set

    def columnset(self, columnset: Dict) -> Union[None, Dict]:
        """
        Updates the container properties for the column-set
        - horizontal alignment: based on the horizontal alignment of each column
        inside the column-set.
        - updates the width property for the columns inside a column-set
        @param columnset: Column-set dict
        """
        # Columns width extraction for the columns inside the row
        return self.extract_column_width(columnset, self.pil_image)

    def imageset(self, design_object: Dict) -> Dict:
        """
        Returns the image-set container properties
        @param design_object: image-set layout structure with merged
                              image properties
        @return: image-set properties dict
        """
        sizes = []
        for images in design_object.get("imageset").get("items", []):
            sizes.append(images.get("size", ""))
        if len(sizes) == len(list(set(sizes))):
            size = "Auto"
        else:
            size = max(sizes, key=sizes.count)

        design_object.update({"size": size})
        return design_object
