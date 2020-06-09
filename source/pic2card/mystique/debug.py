"""Module to handle the  returning of debugging images"""

import json
import os
import sys
from typing import Dict, List
import base64
import io

import cv2
from PIL import Image
import numpy as np
import requests
from object_detection.utils import visualization_utils as vis_util

from mystique.predict_card import PredictCard
from mystique.image_extraction import ImageExtraction


class Debug:
    """
    Class to handle debugging the pic2card conversion returing set of
       images from diffrent modules.
    """

    def __init__(self, od_model=None):
        """
        Find the card components using Object detection model
        """
        self.od_model = od_model

    def main(self, image=None, card_format=None):
        """
        Handles the different components calling and returns the
        predicted card json to the API

        @param labels_path: faster rcnn model's label path
        @param forzen_graph_path: faster rcnn model path
        @param image: input image path

        @return: predicted card json
        """
        image = image.convert("RGB")
        image_np = np.asarray(image)
        image_np = cv2.cvtColor(image_np, cv2.COLOR_RGB2BGR)
        image_copy = image_np.copy()

        # Extract the design objects from faster rcnn model
        predict_card = PredictCard(self.od_model)
        output_dict, category_index = self.od_model.get_objects(
            image=image_np
        )

        # If the debug endpoint is hit returns te faster rcnn model
        # detected boundary boxes in a image
        vis_util.visualize_boxes_and_labels_on_image_array(
            image_np,
            output_dict["detection_boxes"],
            output_dict["detection_classes"],
            output_dict["detection_scores"],
            category_index,
            instance_masks=output_dict.get("detection_masks"),
            use_normalized_coordinates=True,
            line_thickness=2,
            skip_scores=True,
            skip_labels=True,
            min_score_thresh=0.9
        )

        debug_output = {}
        json_objects, detected_coords = predict_card.collect_objects(
            output_dict=output_dict, pil_image=image)

        # Detect image coordinates inside the card design
        image_extraction = ImageExtraction()
        image_model_base64_string = image_extraction.get_image_with_boundary_boxes(
            image=image_copy, detected_coords=detected_coords, pil_image=image,
            faster_rcnn_image=image_np)
        debug_output["image"] = image_model_base64_string

        # generate card from existing workflow
        predict_json = predict_card.main(image=image, card_format=card_format)
        debug_output.update(predict_json)
        return debug_output
