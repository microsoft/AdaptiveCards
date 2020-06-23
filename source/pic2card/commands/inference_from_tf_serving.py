"""
Do inference using the tf-serve service.

We have loaded the saved model into the tf-serve
"""
import os
import io
import click
import base64
import json
import requests
import numpy as np
import cv2
from PIL import Image
import tensorflow as tf

from utils import timeit
from mystique.initial_setups import set_graph_and_tensors
from mystique.predict_card import PredictCard
from mystique.detect_objects import ObjectDetection

# tf.logging.set_verbosity(tf.logging.ERROR)
os.environ["TF_CPP_MIN_LOG_LEVEL"] = '3'


@click.command()
@click.option("-t", "--tf_server", required=True,
              help="TF serving base URL")
@click.option("-i", "--image", required=True, help="Path to the image")
@click.option("-n", "--model_name", required=True,
              help="Model name to be used, as we can host multiple models in"
              " tf-serving")
def inference_graph(tf_server, image, model_name):
    with open(image, "rb") as f:
        bs64_img = base64.b64encode(f.read()).decode("utf8")
    card_ = PredictCard(None)
    with timeit("tf-verving") as t:
        card = card_.tf_serving_main(bs64_img, tf_server, model_name)

    # Frozen graph implementation.
    img = Image.open(open(image, "rb"))
    image_np = cv2.cvtColor(np.asarray(img), cv2.COLOR_RGB2BGR)

    object_detection = ObjectDetection(*set_graph_and_tensors())
    predict_card = PredictCard(object_detection)

    with timeit("frozen-graph") as t:
        card = predict_card.main(image=img)


if __name__ == "__main__":
    inference_graph()
