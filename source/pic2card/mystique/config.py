"""
Gloabal settings and constants.
"""
import os

# max 2mb
IMG_MAX_UPLOAD_SIZE = 2e+6

# tf-serving url
TF_SERVING_URL = os.environ.get("TF_SERVING_URL",
                                "http://172.17.0.5:8501")
TF_SERVING_MODEL_NAME = "mystique"
ENABLE_TF_SERVING = os.environ.get("ENABLE_TF_SERVING",
                                   False)
TF_FROZEN_MODEL_PATH = os.path.join(os.path.dirname(__file__),
                                    "../model/frozen_inference_graph.pb")
TF_LABEL_PATH = os.path.join(os.path.dirname(__file__),
                             "training/object-detection.pbtxt")

# Pytorch model settings.
PTH_MODEL_PATH = os.path.join(
    os.path.dirname(__file__),
    "../model/pth_models/faster-rcnn-2020-05-31-1590943544-epochs_25.pth")

DETR_MODEL_PATH = os.path.join(
    os.path.dirname(__file__),
    "../model/pth_models/detr_trace.pt")


# image hosting max size and default image url
IMG_MAX_HOSTING_SIZE = 1000000
DEFAULT_IMG_HOSTING = "https://lh3.googleusercontent.com/-snm-WznsB3k/XrAWKVCBC3I/AAAAAAAAB8Y/tR-2f8CzboQCmyTzrAfj9Xtvnbeh9PJ8QCK8BGAsYHg/s0/2020-05-04.png" # noqa


# Class labels
ID_TO_LABEL = {
    0: 'background',
    1: "textbox",
    2: "radiobutton",
    3: "checkbox",
    4: "actionset",
    5: "image",
    6: "rating"
}

# image detection swtiching paramater
# On True [ uses custom image pipeline for image objects]
# On False [ uses RCNN model image obejcts ]
# Default is False
USE_CUSTOM_IMAGE_PIPELINE = False

# RCNN model confidence score cutoff
MODEL_CONFIDENCE = 90.0

# Extra textbox padding - 5px
TEXTBOX_PADDING = 5

MODEL_REGISTRY = {
    "tf_faster_rcnn": "mystique.detect_objects.ObjectDetection",
    "tfs_faster_rcnn": "mystique.detect_objects.TfsObjectDetection",
    "pth_faster_rcnn": "mystique.obj_detect.PtObjectDetection",
    "pth_detr": "mystique.obj_detect.DetrOD"
}

ACTIVE_MODEL_NAME = os.environ.get("ACTIVE_MODEL_NAME", "tf_faster_rcnn")

# Noise objects removal IOU threshold
IOU_THRESHOLD = 0.5
