"""Flask service to predict the adaptive card json from the card design"""
import os
import logging
from logging.handlers import RotatingFileHandler
from flask import Flask
from flask_cors import CORS
from flask_restplus import Api
from . import resources as res

from mystique import config
from mystique.initial_setups import set_graph_and_tensors
from mystique.detect_objects import ObjectDetection

logger = logging.getLogger("mysitque")
logger.setLevel(logging.DEBUG)

# Suppress the tf warnings.
os.environ["TF_CPP_MIN_LOG_LEVEL"] = '3'

file_handler = RotatingFileHandler(
    'mystique_app.log', maxBytes=1024 * 1024 * 100, backupCount=20)
formatter = logging.Formatter(
    "%(asctime)s - [%(filename)s:%(lineno)s - %(funcName)20s() ] - \
    %(levelname)s - %(message)s")
file_handler.setFormatter(formatter)
file_handler.setLevel(logging.DEBUG)
logger.addHandler(file_handler)


app = Flask(__name__)
CORS(app)

api = Api(app, title="Mystique", version="1.0",
          default="Jobs", default_label="",
          description="Mysique App For Adaptive card Json Prediction from \
                       UI Design")
api.add_resource(res.GetCardTemplates, '/get_card_templates',
                 methods=['GET'])

# Conditional loading helps to reduce the bundle size, as we don't need to
# package the tensorflow.
# TODO: Experimental API
if config.ENABLE_TF_SERVING:
    api.add_resource(res.TfPredictJson, '/tf_predict_json',
                     methods=['POST'])
else:
    # Load the model into flask cache
    from mystique.initial_setups import set_graph_and_tensors
    from mystique.detect_objects import ObjectDetection
    app.od_model = ObjectDetection(*set_graph_and_tensors())
    api.add_resource(res.PredictJson, '/predict_json', methods=['POST'])

#Debugging Endpoint which returns the set of images from different models
app.od_model = ObjectDetection(*set_graph_and_tensors(tensors =
                                ["detection_boxes", "detection_scores",
                                "detection_classes", "detection_masks"]))

# Include more debug points along with /predict_json api.
api.add_resource(res.DebugEndpoint, "/predict_json_debug", methods=["POST"])
