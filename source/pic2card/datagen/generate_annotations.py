"""module that consists of functions to create the annotation for datagen"""
# pylint: disable=import-error

import os
from typing import List, Sequence, Any
import numpy as np
from lxml import etree as et
from mystique import config
from .utils import get_image_name


def calculate_annotation(
    elements_with_path: List[str],
    elements_dimensions: List[tuple],
    padded_image_element: List[Sequence],
) -> List[List[tuple]]:
    """
    Calculates the annotations for a given list of elements.

    @param elements_with_path: list of elements path from elements directory
    @param elements_dimensions: list of elements dimensions
    @param padded_image_element: list of image elements after padding
    @return: annotations
    """
    annotations = []
    padded_elements_height = [
        element.shape[0] for element in padded_image_element
    ]
    number_of_elements = len(elements_with_path)
    for index in range(number_of_elements):
        xmin = 10
        if index == 0:
            ymin = 10
        else:
            ymin = (
                sum([padded_elements_height[height] for height in range(index)])
                + 10
            )
        xmax = elements_dimensions[index][1] + 10
        ymax = (
            sum([padded_elements_height[height] for height in range(index + 1)])
            - 10
        )
        annotations.append([(xmin, ymin), (xmax, ymax)])
    return annotations


def generate_annotation_xml(
    annotations: List[List[tuple]],
    img_prop: List[Any],
    element_types: List[str],
) -> Any:
    """
    Returns an xml tree object with annotations for the generated image
    @param annotations: List of coordinates of the image elements
    @return tree
    """
    root = et.Element("annotation")
    et.SubElement(root, "folder").text = os.path.basename(
        os.path.abspath(config.GENERATED_ANNOTATION_DIR)
    )
    et.SubElement(root, "filename").text = f"{img_prop[-1]}.png"
    et.SubElement(root, "path").text = (
        os.path.abspath(config.GENERATED_ANNOTATION_DIR)
        + f"\\{img_prop[-1]}.xml"
    )
    source = et.SubElement(root, "source")
    et.SubElement(source, "database").text = "Unknown"
    size = et.SubElement(root, "size")
    et.SubElement(size, "height").text = str(img_prop[0][0])
    et.SubElement(size, "width").text = str(img_prop[0][1])
    et.SubElement(size, "depth").text = str(img_prop[0][2])
    et.SubElement(root, "segmented").text = "0"
    for index, element_type in enumerate(element_types):
        element = et.SubElement(root, "object")
        et.SubElement(element, "name").text = os.path.basename(element_type)
        et.SubElement(element, "pose").text = "Unspecified"
        et.SubElement(element, "truncated").text = "0"
        et.SubElement(element, "difficult").text = "0"
        bndbox = et.SubElement(element, "bndbox")
        et.SubElement(bndbox, "xmin").text = str(annotations[index][0][0])
        et.SubElement(bndbox, "ymin").text = str(annotations[index][0][1])
        et.SubElement(bndbox, "xmax").text = str(annotations[index][1][0])
        et.SubElement(bndbox, "ymax").text = str(annotations[index][1][1])

    tree = et.ElementTree(root)
    return tree


def run_annotator(
    elements_with_path: List[str],
    elements_dimensions: List[tuple],
    padded_image_element: List[Sequence],
) -> List[List[tuple]]:
    """
    Returns a list of x and y coords of the elements in the generated image
    for both above and below threshold element numbers
    @param elements_with_path: list of elements path from elements directory
    @param elements_dimensions: list of elements dimensions
    @param padded_image_element: list of image elements after padding
    @return: annotations
    """
    number_of_elements = len(elements_with_path)
    if number_of_elements <= config.ELEMENT_COUNT_THRESHOLD:
        annotations = calculate_annotation(
            elements_with_path, elements_dimensions, padded_image_element
        )
    else:
        mid_value = number_of_elements // 2
        left_elements_with_path = elements_with_path[:mid_value]
        left_elements_dimensions = elements_dimensions[:mid_value]
        left_padded_image_element = padded_image_element[:mid_value]

        left_elements_annotations = calculate_annotation(
            left_elements_with_path,
            left_elements_dimensions,
            left_padded_image_element,
        )

        right_elements_with_path = elements_with_path[mid_value:]
        right_elements_dimensions = elements_dimensions[mid_value:]
        right_padded_image_element = padded_image_element[mid_value:]

        right_elements_annotations = calculate_annotation(
            right_elements_with_path,
            right_elements_dimensions,
            right_padded_image_element,
        )

        padded_pixels_for_right_element = (
            max([element[1] for element in elements_dimensions]) + 20
        )
        right_elements_annotations = np.array(right_elements_annotations)
        right_elements_annotations = right_elements_annotations + [
            padded_pixels_for_right_element,
            0,
        ]
        right_elements_annotations = right_elements_annotations.tolist()
        right_elements_annotations = [
            [(*coord,) for coord in element]
            for element in right_elements_annotations
        ]
        annotations = left_elements_annotations + right_elements_annotations
    return annotations


def get_annotation_file(
    layout: Any, generated_image: Any, padded_image_element: List[Sequence]
) -> Any:
    """Returns the annotation file in xml format"""
    # properties of generated image
    image_name = get_image_name()
    element_type = [os.path.dirname(path) for path in layout.elements_with_path]
    generated_image_prop = [np.shape(generated_image), image_name]

    # run annotations
    annotations = run_annotator(
        layout.elements_with_path,
        layout.element_dimensions,
        padded_image_element,
    )
    # get annotation xml
    annotation_xml = generate_annotation_xml(
        annotations, generated_image_prop, element_type
    )
    return annotation_xml
