"""
Inference APIs for the trained models.
"""

from typing import Callable
import torch
import torchvision.transforms as T
from PIL import Image


# Image Transform before inference.
transform = T.Compose(
    [
        T.Resize(800),
        T.ToTensor(),
        T.Normalize([0.485, 0.456, 0.406], [0.229, 0.224, 0.225]),
    ]
)


def box_cxcywh_to_xyxy(x_a):  # pylint: disable=no-member
    """for output bounding box post-processing"""

    x_c, y_c, w_d, h_e = x_a.unbind(1)
    bbb = [
        (x_c - 0.5 * w_d),
        (y_c - 0.5 * h_e),
        (x_c + 0.5 * w_d),
        (y_c + 0.5 * h_e),
    ]
    return torch.stack(bbb, dim=1)  # pylint: disable=no-member


def rescale_bboxes(out_bbox, size):
    """For Rescaling the bboxes"""
    img_w, img_h = size
    bbb = box_cxcywh_to_xyxy(out_bbox)
    # pylint: disable=not-callable, disable=no-member
    bbb = bbb * torch.tensor(
        [img_w, img_h, img_w, img_h],
        dtype=torch.float32,
    )  # pylint: disable=no-member, not-callable
    return bbb


def detect(
    image: Image, model: Callable, transform: Callable, threshold=0.8
):  # pylint: disable=redefined-outer-name
    """
    @param img: PIL Image
    @param model: A Serialized callable, exported using torchscript.
    @param transform: Data transformer function.
    @param threshold: Confidence of bbox prediction.
    """
    # mean-std normalize the input image (batch-size: 1)
    image_tnsr = transform(image).unsqueeze(0)

    # propagate through the model
    outputs = model(image_tnsr)

    # keep only predictions with 0.7+ confidence
    # Skip the default background class added at train time.
    probas = outputs["pred_logits"].softmax(-1)[0, :, :-1]
    keep = probas.max(-1).values > threshold

    # convert boxes from [0; 1] to image scales
    bboxes_scaled = rescale_bboxes(outputs["pred_boxes"][0, keep], image.size)
    # bboxes = box_cxcywh_to_xyxy(outputs['pred_boxes'][0, keep])

    return probas[keep], bboxes_scaled
