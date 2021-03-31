"""Flask service to predict the adaptive card json from the card design"""
import os
import logging
from logging.handlers import RotatingFileHandler
from flask import Flask
from flask_cors import CORS
from flask_restplus import Api

from mystique.utils import load_od_instance
from . import resources as res
from mystique import config

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
    api.add_resource(res.PredictJson, '/predict_json', methods=['POST'])

# Load the models and cache it for request handling.
app.od_model = load_od_instance()

# Include more debug points along with /predict_json api.
api.add_resource(res.DebugEndpoint, "/predict_json_debug", methods=["POST"])
