"""Module to handle the  returning of debugging images"""

from typing import Dict, List, Tuple
import base64
import io

import cv2
from PIL import Image
import numpy as np
from object_detection.utils import visualization_utils as vis_util
import matplotlib.pyplot as plt

from mystique.predict_card import PredictCard
from mystique.image_extraction import ImageExtraction
from mystique import config


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

    def visualize_rcnn_model_objects(self, image_np: np.array, boxes: List, classes: List,
                                     scores: List, category_index: List):
        """
        Visualzie the RCNN model detected objects

        @param image_np: opencv input image
        @param boxes: rcnn model's list of object boundary boxes
        @param classes: rcnn model's list of object classes
        @param scores: rcnn model's list of object scores
        @param category_index: a dict that maps integer ids to category dicts
        """
        vis_util.visualize_boxes_and_labels_on_image_array(
            image_np,
            boxes,
            classes,
            scores,
            category_index,
            use_normalized_coordinates=True,
            line_thickness=5,
            skip_scores=True,
            skip_labels=True,
            min_score_thresh=0.9
        )

    def visualize_custom_image_pipeline_objects(self, image_copy: np.array,
                                                detected_coords: List[Tuple],
                                                image: Image, image_np: np.array):
        """
        Visualize the custom image pipeline objects
        @param image_copy: opencv input image
        @param detected_coords: rcnn model's object's coordinates
        @param image: PIL input image
        @param image_np: faster rcnn display image
        """
        image_extraction = ImageExtraction()
        image_extraction.get_image_with_boundary_boxes(
            image=image_copy, detected_coords=detected_coords,
            pil_image=image, faster_rcnn_image=image_np)

    def plot_debug_images(self, faster_rcnn_image: np.array,
                          image_pipeline_image: np.array):
        """
        Plots the debugs images and returns the base64 string of the plot

        @param faster_rcnn_image: rcnn model object visualization
        @param image_pipeline_image: custom image pipeline object visualization

        @return: base64 string of the plot
        """
        plt.figure(figsize=(20, 8))
        plt.subplot(1, 2, 1)
        plt.title("RCNN Model Objects")
        plt.imshow(cv2.cvtColor(faster_rcnn_image, cv2.COLOR_BGR2RGB))
        plt.axis('off')
        plt.subplot(1, 2, 2)
        plt.title("Custom Image Pipeline Objects")
        plt.imshow(cv2.cvtColor(image_pipeline_image, cv2.COLOR_BGR2RGB))
        plt.axis('off')
        pic_iobytes = io.BytesIO()
        plt.savefig(pic_iobytes, format='png')
        pic_iobytes.seek(0)

        return base64.b64encode(pic_iobytes.read()).decode()

    def get_boundary_boxes(self, image_np: np.array):
        """
        Get the predicted objects and classes from the rcnn model.

        @param image_np: input open cv image

        @return: list of boundaries, classes , scores , output dict and category
                         index
        """
        # Extract the design objects from faster rcnn model
        output_dict, category_index = self.od_model.get_objects(
            image=image_np
        )
        boxes = np.squeeze(output_dict["detection_boxes"])
        classes = np.squeeze(
            output_dict["detection_classes"]).astype(np.int32)
        scores = np.squeeze(output_dict["detection_scores"])

        return boxes, classes, scores, output_dict, category_index

    def main(self, pil_image=None, card_format=None):
        """
        Handles the different components calling and returns the
        predicted card json to the API

        @param image: input image path

        @return: predicted card json
        """
        pil_image = pil_image.convert("RGB")
        image_np = np.asarray(pil_image)
        image_np = cv2.cvtColor(image_np, cv2.COLOR_RGB2BGR)
        image_copy = image_np.copy()
        boxes, classes, scores, output_dict, category_index = self.get_boundary_boxes(
            image_np)
        predict_card = PredictCard(self.od_model)
        if config.USE_CUSTOM_IMAGE_PIPELINE:
            indices = np.argwhere(classes != 5)
            boxes = np.squeeze(boxes[indices], axis=1)
            scores = np.squeeze(scores[indices], axis=1)
            classes = np.squeeze(classes[indices], axis=1)
            self.visualize_rcnn_model_objects(
                image_np, boxes, classes, scores, category_index)
            json_objects, detected_coords = predict_card.collect_objects(
                output_dict=output_dict, pil_image=pil_image)
            # delete image from the rcnn model detected coordinates
            positions_to_remove = [ctr for ctr, design_object in enumerate(
                json_objects.get("objects", [])) if design_object.get("object") == "image"]
            detected_coords = [coords for ctr, coords in enumerate(
                detected_coords) if ctr not in positions_to_remove]

            self.visualize_custom_image_pipeline_objects(image_copy,
                                                         detected_coords,
                                                         pil_image, image_np)
        self.visualize_rcnn_model_objects(
            image_np, boxes, classes, scores, category_index)

        retval, image_buffer = cv2.imencode(".png", image_np)
        image_model_base64_string = base64.b64encode(image_buffer).decode()
        # {"image": self.plot_debug_images(image_np, image_copy)}
        debug_output = {"image": image_model_base64_string}
        # generate card from existing workflow
        predict_json = predict_card.main(
            image=pil_image, card_format=card_format)
        debug_output.update(predict_json)
        return debug_output
