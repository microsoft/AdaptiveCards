"""Module for object detection using faster rcnn"""

from distutils.version import StrictVersion

import numpy as np
import tensorflow as tf
from typing import Dict, Tuple
from PIL import Image

from mystique.utils import id_to_label
from mystique.image_extraction import ImageExtraction


if StrictVersion(tf.__version__) < StrictVersion("1.9.0"):
    raise ImportError(
        "Please upgrade your TensorFlow installation to v1.9.* or later!")


class ObjectDetection:
    """
    Class handles generating faster rcnn models from the model inference
    graph and returning the ouput dict which consists of classes, scores,
    and object bounding boxes.
    """

    def __init__(self, detection_graph, category_index, tensor_dict):
        """
        Initialize the object detection using model loaded from forzen
        graph
        """
        self.detection_graph = detection_graph
        self.category_index = category_index
        self.tensor_dict = tensor_dict

    def _img_preprocess(self, image_path: str) -> Tuple[Image.Image, np.array]:
        """
        Image preprocessing and convert to tensor.
        """
        image = Image.open(image_path)
        width, height = image.size
        image = image.convert("RGB")
        image_np = np.asarray(image)
        return image, image_np

    def get_image_coordinates(self, image: Image,
                              image_np: np.array, result: Dict):
        """
        Custom pipeline written outside the model to extract
        image coordinates.
        """
        from mystique.predict_card import PredictCard
        predict_card = PredictCard()

        json_objects, detected_coords = predict_card.collect_objects(
            output_dict=result, pil_image=image
        )
        ie = ImageExtraction()
        image_points = ie.detect_image(image=image_np,
                                       detected_coords=detected_coords,
                                       pil_image=image)
        return image_points

    def get_bboxes(self, image_path: str, img_pipeline=False) -> Tuple:
        """
        Get the bounding boxes with scores and label.
        """
        image, image_np = self._img_preprocess(image_path)
        width, height = image.size
        result, _index = self.get_objects(image_np)
        classes = [id_to_label(i) for i in result['detection_classes']]
        scores = result['detection_scores'].tolist()
        boxes = result['detection_boxes'].tolist()

        # Denormalize the bounding box coordinates.
        bbox_dnorm = []
        for bbox in boxes:
            ymin = bbox[0] * height
            xmin = bbox[1] * width
            ymax = bbox[2] * height
            xmax = bbox[3] * width
            bbox_dnorm.append([xmin, ymin, xmax, ymax])

        if img_pipeline:
            image_points = self.get_image_coordinates(image, image_np, result)
            classes = ["image"] * len(image_points) + classes
            scores = [1.0] * len(image_points) + scores
            bbox_dnorm = image_points + bbox_dnorm

        return classes, bbox_dnorm, scores

    def get_objects(self, image: np.array = None):
        """
        Returns the objects and coordiates detected
        from the faster rcnn detected boxes]

        @param image: Image tensor, dimension should be HxWx3

        @return: ouput dict from the faster rcnn inference
        """
        output_dict = self.run_inference_for_single_image(image)
        return output_dict, self.category_index

    def run_inference_for_single_image(self, image: np.array):
        """
        Runs the inference graph for the given image
        @param image: numpy array of input design image
        @return: output dict of objects, classes and coordinates
        """
        # Run inference
        detection_graph = self.detection_graph
        with detection_graph.as_default():
            image_tensor = detection_graph.get_tensor_by_name(
                "image_tensor:0")
            with tf.compat.v1.Session() as sess:
                output_dict = sess.run(
                    self.tensor_dict, feed_dict={
                        image_tensor: np.expand_dims(
                            image, 0)})

        # all outputs are float32 numpy arrays, so convert types as
        # appropriate
        output_dict["detection_classes"] = output_dict[
            "detection_classes"][0].astype(np.uint8)
        output_dict["detection_boxes"] = output_dict[
            "detection_boxes"][0]
        output_dict["detection_scores"] = output_dict[
            "detection_scores"][0]

        return output_dict
