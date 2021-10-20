"""Module for object detection using faster rcnn"""

from distutils.version import StrictVersion
from typing import Tuple

import numpy as np
import tensorflow as tf
from PIL import Image

from mystique import config
from mystique.utils import id_to_label, load_image
from .od_base import AbstractObjectDetection
from .utils import load_frozen_graph

# pylint: disable=no-member
if StrictVersion(tf.__version__) < StrictVersion("2.4.0"):
    raise ImportError("Please upgrade your TensorFlow installation to v2.4.x !")


class Tf2ObjectDetection(AbstractObjectDetection):
    """
    This class helps to load and inference the object detection model trained
    using tf2 object detection framework. The training and model export are
    done using this framework.
    """

    MODEL_PATH = config.TF2_FROZEN_MODEL_PATH
    INPUT_NODES = ["input_tensor:0"]
    OUTPUT_NODES = ["Identity_1:0", "Identity_2:0", "Identity_4:0"]

    def __init__(self):
        """
        Initialize the object detection using model loaded from forzen
        graph
        """
        self.model = load_frozen_graph(
            self.MODEL_PATH, self.INPUT_NODES, self.OUTPUT_NODES
        )

    def get_bboxes(self, image_path: str, img_pipeline=False) -> Tuple:
        """
        Get the bounding boxes with scores and label.
        """
        image, image_np = load_image(image_path)
        # width, height = image.size
        result = self.get_objects(image_np=image_np, image=image)
        classes = [id_to_label(i) for i in result["detection_classes"]]
        scores = result["detection_scores"].tolist()
        boxes = result["detection_boxes"].tolist()

        return classes, boxes, scores

    def get_objects(self, image_np: np.array, image: Image):
        """
        Returns the objects and coordiates detected
        from the faster rcnn detected boxes]

        @param image_np: Image tensor, dimension should be HxWx3
        @param image: PIL Image object

        @return: ouput dict from the faster rcnn inference
        """
        output_dict = self.run_inference_for_single_image(image_np)
        width, height = image.size
        # format: ymin, xmin, ymax, xmax, renormalize the coords.
        bboxes = output_dict["detection_boxes"] * [height, width, height, width]

        # format: xmin, ymin, xmax, ymax
        output_dict["detection_boxes"] = bboxes[:, [1, 0, 3, 2]]

        # renormalize the the box cooridinates
        return output_dict

    def run_inference_for_single_image(self, image: np.array):
        """
        Runs the inference graph for the given image
        @param image: numpy array of input design image
        @return: output dict of objects, classes and coordinates
        """
        # Run inference
        bboxes, labels, scores = self.model(
            tf.expand_dims(tf.constant(image), 0)
        )

        # all outputs are float32 numpy arrays, so convert types as
        # appropriate
        output_dict = {}
        output_dict["detection_classes"] = labels.numpy().squeeze(0)
        output_dict["detection_boxes"] = bboxes.numpy().squeeze(0)
        output_dict["detection_scores"] = scores.numpy().squeeze(0)

        return output_dict
