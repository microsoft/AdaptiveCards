"""Module for object detection using faster rcnn"""

import os
from distutils.version import StrictVersion

import cv2
import numpy as np
import tensorflow as tf


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

    def get_objects(self, image=None):
        """
        Returns the objects and coordiates detected
        from the faster rcnn detected boxes]

        @param image: input image path

        @return: ouput dict from the faster rcnn inference
        """
        output_dict = self.run_inference_for_single_image(image)
        return output_dict, self.category_index

    def run_inference_for_single_image(self, image):
        """
        Runs the inference graph for the given image
        @param image: numpy array of input design image
        @return: output dict of objects, classes and coordinates
        """

        # Run inference
        detection_graph = self.detection_graph
        with detection_graph.as_default():
            image_tensor = detection_graph.get_tensor_by_name("image_tensor:0")
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
