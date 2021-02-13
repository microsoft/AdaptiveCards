from typing import Tuple
import numpy as np

import torch
import torchvision.transforms as T
from detecto.core import Model
from detecto.utils import read_image, normalize_transform

from .od_base import AbstractObjectDetection
from mystique import config


class PtObjectDetection(AbstractObjectDetection):
    """
    Pytorch implementation of object detection classes.
    """
    transformer = T.Compose([
            T.ToPILImage(),
            lambda image: image.convert("RGB"),
            T.ToTensor(),
            normalize_transform()
    ])

    classes = ["checkbox",
               "radiobutton",
               "textbox",
               "actionset",
               "image",
               "rating"]
    model = None

    def __init__(self, model_path=None):
        self.model_path = model_path or config.PTH_MODEL_PATH
        if self.model_path:
            self.model = self._load_model()

    def _transform(self, image: np.array) -> torch.Tensor:
        """
        Transform the image and convert to Tensor.
        """
        return self.transformer(image)

    def _load_model(self):
        """ Load the saved model and pass the required classes """
        return Model.load(self.model_path, classes=self.classes)

    def get_bboxes(self, image_path: str,
                   img_pipeline=None) -> Tuple:
        """
        Do inference and return the bounding boxes compatible to caller.
        """
        image_np = read_image(image_path)
        image = self._transform(image_np)
        labels, boxes, scores = self.model.predict([image])[0]

        return labels, boxes.tolist(), scores.tolist()
