#!/usr/bin/python

# pip install lxml
"""
Module contains functions needed for generating synthetic image dataset.
"""
import random
import os
import glob
import logging
from typing import List, Sequence, Any
import cv2
import numpy as np
from mystique import config


logger = logging.getLogger("commands.generate_bulk_data")
LOGFORMAT = "%(asctime)s - [%(filename)s:%(lineno)s - %(funcName)20s()] - \
    %(levelname)s - %(message)s"
logging.basicConfig(level=logging.DEBUG, format=LOGFORMAT)


class CardElements:
    """
    This class is responsible for the card elements properties
    and its related functionalities
    The card_elements directory default path is defined in the init
    function and can also be passed as argument during runtime
    which is not compulsory
    """

    def __init__(self, number_of_elements: int, elements_dir: str) -> None:
        self.number_of_elements = number_of_elements
        self.elements_dir = elements_dir
        self.elements_with_path = self.get_elements_path()
        self.element_dimensions = self.get_elements_dimensions(
            self.elements_with_path
        )

    def get_elements_path(self) -> List[str]:
        """
        Returns a list of complete path of card_elements selected at random
        @param self: CardElements object
        @return: elements_with_path
        """
        elements = glob.glob(self.elements_dir + "/**/*.*", recursive=True)
        elements_exist = [os.path.isfile(filepath) for filepath in elements]
        if elements_exist:
            elements_with_path = random.choices(
                elements, k=self.number_of_elements
            )
        else:
            error_msg = "No image elements found under card_elements directory"
            logger.error(error_msg)
            raise Exception(error_msg)
        return elements_with_path

    @staticmethod
    def get_elements_dimensions(elements_with_path: List[str]) -> List[tuple]:
        """
        Returns a list of dimensions for the selected elements
        @param elements_with_path : list of selected element paths
        @return : elements_dimensions
        """
        elements_dimensions = []
        for element in elements_with_path:
            element_img = cv2.imread(element)
            dimension = element_img.shape
            elements_dimensions.append(dimension)
        return elements_dimensions


def add_padding_to_img_elements(
    elements_with_path: List[str],
) -> List[Sequence]:
    """
    Returns a list of elements in image format padded
    along width of the image
    @param elements_with_path: list of elements path from elements directory
    @return: reshaped_image_elements
    """

    image_elements = [cv2.imread(element) for element in elements_with_path]
    reference_canvas_width = max(
        [element.shape[1] for element in image_elements]
    )
    reshaped_image_elements = []
    for image_element in image_elements:
        image_element_width = image_element.shape[1]
        pixel_diff = reference_canvas_width - image_element_width
        padded_image_element = cv2.copyMakeBorder(
            image_element,
            top=10,
            bottom=10,
            left=10,
            right=pixel_diff + 10,
            borderType=cv2.BORDER_CONSTANT,
            value=config.CANVAS_COLOR["WHITE"],
        )
        reshaped_image_elements.append(padded_image_element)
    return reshaped_image_elements


def generate_image(reshaped_image_elements: List[Sequence]) -> List[Sequence]:
    """
    Stacks the image elements along an axis and return a list of them
    @param reshaped_image_elements: list of image elements after padding
    @return: stacked image elements in one or two columns respectively
    """
    number_of_elements = len(reshaped_image_elements)
    # to stack elements vertically set number_of_elements less than threshold
    if number_of_elements <= config.ELEMENT_COUNT_THRESHOLD:
        stacked_image_elements = np.vstack(reshaped_image_elements)
    else:
        # stacks to form another column of elements in the generated image
        left_elements = np.vstack(
            reshaped_image_elements[: number_of_elements // 2]
        )
        right_elements = np.vstack(
            reshaped_image_elements[number_of_elements // 2 :]
        )
        pixel_diff = abs(left_elements.shape[0] - right_elements.shape[0])

        if left_elements.shape[0] < right_elements.shape[0]:
            padded_image_element = cv2.copyMakeBorder(
                left_elements,
                top=0,
                bottom=pixel_diff,
                left=0,
                right=0,
                borderType=cv2.BORDER_CONSTANT,
                value=config.CANVAS_COLOR["WHITE"],
            )
            stacked_image_elements = np.hstack(
                [padded_image_element, right_elements]
            )
        else:
            padded_image_element = cv2.copyMakeBorder(
                right_elements,
                top=0,
                bottom=pixel_diff,
                left=0,
                right=0,
                borderType=cv2.BORDER_CONSTANT,
                value=config.CANVAS_COLOR["WHITE"],
            )
            stacked_image_elements = np.hstack(
                [left_elements, padded_image_element]
            )

    return stacked_image_elements


def add_background_colour_to_generated_image(
    generated_image: Any, background_colour: str
) -> List[Sequence]:
    """
    Returns an image with desired color added to background of the image
    generated

    @ param generated_image: the image generated
    @ param background_colour: the default or selected colour
    @ return: overlayed_img
    """
    height, width, channels = generated_image.shape
    # creating a canvas with white background
    canvas = np.ones((height, width, channels), np.uint8) * 255
    canvas[:] = config.CANVAS_COLOR[background_colour]
    foreground_gray_image = cv2.cvtColor(generated_image, cv2.COLOR_RGB2GRAY)
    mask = cv2.adaptiveThreshold(
        src=foreground_gray_image,
        maxValue=255,
        adaptiveMethod=cv2.ADAPTIVE_THRESH_GAUSSIAN_C,
        thresholdType=cv2.THRESH_BINARY,
        blockSize=199,
        C=5,
    )
    mask_inv = cv2.bitwise_not(mask)
    background = cv2.bitwise_and(canvas, canvas, mask=mask)
    foreground = cv2.bitwise_and(
        generated_image, generated_image, mask=mask_inv
    )
    overlayed_img = cv2.add(foreground, background)
    return overlayed_img
