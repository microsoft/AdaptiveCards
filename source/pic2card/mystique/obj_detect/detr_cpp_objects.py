"""
Doing Detr inference using c++ binding, quick checks shows >3x improvements
with the inference time.
"""
from typing import Dict, Tuple
import numpy as np
from PIL import Image
from mystique import config
from .od_base import AbstractObjectDetection


# for output bounding box post-processing
# TODO: Move these tensor works too into c++ side, as this comes in
# inference path.
def box_cxcywh_to_xyxy(
    x_a: np.ndarray,
):  # pylint: disable=missing-function-docstring
    x_c, y_c, w_a, h_a = [i[:, 0] for i in np.split(x_a, [1, 2, 3], axis=1)]
    boundary_box = [
        (x_c - 0.5 * w_a),
        (y_c - 0.5 * h_a),
        (x_c + 0.5 * w_a),
        (y_c + 0.5 * h_a),
    ]
    return np.stack(boundary_box, axis=1)


def rescale_bboxes(
    out_bbox: np.ndarray, size: Tuple[int, int]
):  # pylint: disable=missing-function-docstring
    img_w, img_h = size
    boundary_box = box_cxcywh_to_xyxy(out_bbox)
    boundary_box = boundary_box * [img_w, img_h, img_w, img_h]
    return boundary_box


class DetrCppOD(AbstractObjectDetection):
    """
    Do the inference in c++ code and return the result. This class wraps uses
    detr cpp python extension to do the inference.
    """

    def __init__(
        self, pt_path="./detr_trace.pt", threshold=0.8
    ):  # pylint: disable=unused-argument

        # pylint: disable=import-outside-toplevel, import-error
        import detr

        self.model = detr.Detr(self.model_path)  # pylint: disable=no-member
        self.threshold = threshold

    @property
    def model_path(self):  # pylint: disable=missing-function-docstring
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
            "detection_boxes": boxes,
        }

    def get_bboxes(self):  # pylint: disable=arguments-differ
        pass
