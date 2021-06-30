""" Abstract Object Detection, Each model implementation has to follow this
    apis
"""
import abc
from typing import Tuple, Dict
import numpy as np
from PIL import Image


class AbstractObjectDetection(
    metaclass=abc.ABCMeta
):  # pylint: disable=missing-class-docstring
    @abc.abstractmethod
    def get_objects(
        self, image_np: np.array, image: Image
    ) -> Tuple[Dict, object]:
        """
        Return the object detection data from model inference pipeline.

        Ensure the bbox coordinates are xmin, ymin, xmax, ymax format, and
        renormalized to get actual bounding box coordinates.

        Return:
            {
              "detection_classes": [int, int],
              "detection_boxes": Nx4 Tensor. The coordinates are renormalized.,
              "detection_scores": [float, float]
             }
        """
        pass  # pylint: disable=unnecessary-pass

    @abc.abstractmethod
    def get_bboxes(self, image_path: str, img_pipeline=None):
        """
        Deprecated method, soon be removed, added for backward compatibility
        """
        raise NotImplementedError("get_bboxes method isn't defined")
