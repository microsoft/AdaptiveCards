""" resources for api """
import sys
import os
import io
import base64
import json
import logging
from urllib.parse import parse_qs, urlparse

import numpy as np
import cv2
import requests
from PIL import Image
from flask import request
from flask_restplus import Resource
from flask import current_app

from mystique.predict_card import PredictCard
from mystique.debug import Debug
from mystique import config
from .utils import get_templates


logger = logging.getLogger("mysitque")

cur_dir = os.path.dirname(__file__)
input_image_collection = os.path.join(cur_dir, "input_image_collection")
model_path = os.path.join(os.path.dirname(__file__),
                          "../model/frozen_inference_graph.pb")
label_path = os.path.join(os.path.dirname(__file__),
                          "../mystique/training/object-detection.pbtxt")


class PredictJson(Resource):
    """
    Handling Adaptive Card Predictions
    """

    def _get_card_object(self, bs64_img: str, card_format: str):
        """
        From base64 image generate adaptive card schema.

        Make use of the frozen graph for inferencing.
        """
        imgdata = base64.b64decode(bs64_img)
        image = Image.open(io.BytesIO(imgdata))
        predict_card = PredictCard(current_app.od_model)
        card = predict_card.main(image=image, card_format=card_format)
        return card

    def post(self):
        """
        predicts the adaptive card json for the posted image
        :return: adaptive card json
        """
        try:
            card_format = parse_qs(urlparse(request.url).query).get("format",
                                                                    [None])[0]
            bs64_img = request.json.get("image", "")
            if sys.getsizeof(bs64_img) < config.IMG_MAX_UPLOAD_SIZE:
                response = self._get_card_object(bs64_img, card_format)
            else:
                # Upload smaller image.
                response = {
                    "error": {
                        "msg": f"Upload images of size <="
                        " {config.IMG_MAX_UPLOAD_SIZE/(1024*1024)} MB.",
                        "code": 1002
                    }
                }

        except Exception as ex:
            error_msg = f"Unhandled Error, failed to process the request: {ex}"
            logger.error(error_msg)
            response = {
                "error": {
                    "msg": error_msg,
                    "code": 1001
                },
                "card_json": None
            }

        return response


class TfPredictJson(PredictJson):
    """
    Serve the card prediction using tf-serving service.
    """

    def __init__(self, *args, **kwargs):
        self.model_name = config.TF_SERVING_MODEL_NAME
        self.tf_server = config.TF_SERVING_URL
        super(PredictJson, self).__init__(*args, **kwargs)

    def _get_card_object(self, bs64_img: str, card_format: str):
        """
        From base64 image generate adaptive card schema.

        Using TF serving to do the object detection.
        """
        pic2card = PredictCard(None)
        card = pic2card.tf_serving_main(bs64_img, self.tf_server,
                                        self.model_name, card_format)
        return card


class GetCardTemplates(Resource):
    """
    Handling adaptive card template images
    """

    def get(self):
        """
        returns adaptive card templates images
        :return: adaptive card templates images in str format
        """
        templates = get_templates()
        return templates

class DebugEndpoint(PredictJson):

    """
    Handles the returning the debug images from different adaptive card
    prediction models.
    """

    def __init__(self, *args, **kwargs):
        super(PredictJson, self).__init__(*args, **kwargs)

    def _get_card_object(self, bs64_img: str, card_format: str):
        """
        From base64 image generate debugging images from the adaptive
        card prediction.

        Make use of the frozen graph for inferencing.
        """

        imgdata = base64.b64decode(bs64_img)
        image = Image.open(io.BytesIO(imgdata))
        debug = Debug(current_app.od_model)
        images = debug.main(pil_image=image, card_format=card_format)
        return images


