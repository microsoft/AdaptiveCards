"""
Inference APIs for the trained models.
"""

from typing import Callable
import torch
import torchvision.transforms as T
from PIL import Image


# Image Transform before inference.
transform = T.Compose([
        T.Resize(800),
        T.ToTensor(),
        T.Normalize([0.485, 0.456, 0.406], [0.229, 0.224, 0.225])
])


# for output bounding box post-processing
def box_cxcywh_to_xyxy(x):
    x_c, y_c, w, h = x.unbind(1)
    b = [(x_c - 0.5 * w), (y_c - 0.5 * h),
         (x_c + 0.5 * w), (y_c + 0.5 * h)]
    return torch.stack(b, dim=1)


def rescale_bboxes(out_bbox, size):
    img_w, img_h = size
    b = box_cxcywh_to_xyxy(out_bbox)
    b = b * torch.tensor([img_w, img_h, img_w, img_h], dtype=torch.float32)
    return b


def detect(image: Image, model: Callable,
           transform: Callable, threshold=0.8):
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
    probas = outputs['pred_logits'].softmax(-1)[0, :, :-1]
    keep = probas.max(-1).values > threshold

    # convert boxes from [0; 1] to image scales
    bboxes_scaled = rescale_bboxes(outputs['pred_boxes'][0, keep], image.size)
    # bboxes = box_cxcywh_to_xyxy(outputs['pred_boxes'][0, keep])

    return probas[keep], bboxes_scaled
