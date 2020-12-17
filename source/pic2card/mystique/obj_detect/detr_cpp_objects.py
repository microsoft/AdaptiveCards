"""
Doing Detr inference using c++ binding, quick checks shows >3x improvements
with the inference time.
"""
import detr
import numpy as np
from typing import Dict, Tuple
from PIL import Image

from .od_base import AbstractObjectDetection
from mystique import config


# for output bounding box post-processing
# TODO: Move these tensor works too into c++ side, as this comes in
# inference path.
def box_cxcywh_to_xyxy(x: np.ndarray):
    x_c, y_c, w, h = [i[:, 0] for i in np.split(x, [1, 2, 3], axis=1)]
    b = [(x_c - 0.5 * w), (y_c - 0.5 * h),
         (x_c + 0.5 * w), (y_c + 0.5 * h)]
    return np.stack(b, axis=1)


def rescale_bboxes(out_bbox: np.ndarray, size: Tuple[int, int]):
    img_w, img_h = size
    b = box_cxcywh_to_xyxy(out_bbox)
    b = b * [img_w, img_h, img_w, img_h]
    return b


class DetrCppOD(AbstractObjectDetection):
    """
    Do the inference in c++ code and return the result. This class wraps uses
    detr cpp python extension to do the inference.
    """
    def __init__(self, pt_path="./detr_trace.pt", threshold=0.8):
        self.model = detr.Detr(self.model_path)
        self.threshold = threshold

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
        pred_logits, pred_boxes = self.model.predict(image_np)
        pred_logits = pred_logits[:, :-1]
        # TODO: Use the threshold from config
        mask = pred_logits.max(-1) > 0.8

        scores = pred_logits[mask]
        boxes = rescale_bboxes(pred_boxes[mask], image.size)
        return {
            "detection_classes": scores.argmax(-1),
            "detection_scores": scores.max(-1),
            "detection_boxes": boxes
        }

    def get_bboxes(self):
        pass
