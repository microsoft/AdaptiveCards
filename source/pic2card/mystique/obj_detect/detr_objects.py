"""
Find the objects from card and its attributes using DETR object detection
model.
"""
import numpy as np
from typing import Dict
from PIL import Image
import torch

from .od_base import AbstractObjectDetection
from mystique.models.pth.detr.predict import detect, transform
from mystique import config


class DetrOD(AbstractObjectDetection):
    """
    Load the DETR torchscript model and does the inference on PIL images.
    """
    def __init__(self, pt_path="./detr_trace.pt"):
        self.model = torch.jit.load(self.model_path)

    @property
    def model_path(self):
        return config.DETR_MODEL_PATH

    def get_objects(self, image_np: np.array, image: Image) -> Dict:
        """
        Do model inference using `od_model` and return standard response.

        This function gets both image tensor or PIL image, The implementation
        can pick the one which suits. Helps to avoid further transformations.

        Response:
            {
            "detection_classes": [],
             "detection_scores": [],
             "detection_boxes": []
             },
        """
        # TODO: Use the threshold from config
        scores, boxes = detect(image, self.model, transform, threshold=0.8)
        ss_ = scores.max(-1)
        return {
            "detection_classes": ss_.indices.detach().numpy(),
            "detection_scores": ss_.values.detach().numpy(),
            "detection_boxes": boxes.detach().numpy()
        }

    def get_bboxes(self):
        pass
