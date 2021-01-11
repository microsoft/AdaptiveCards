import os
import unittest
import time
import json
from typing import Dict, List
import numpy as np
import cv2
from PIL import Image

from tests.utils import (
    img_to_base64,
    headers,
    payload_empty_dict_data,
    payload_data_some_string,
    generate_base64,
    get_response,
    api_dict
)

from app.api import app
from mystique.predict_card import PredictCard
from mystique.extract_properties import CollectProperties
from mystique.card_layout.arrange_card import CardArrange
from mystique.utils import load_od_instance

curr_dir = os.path.dirname(__file__)


class BaseAPITest(unittest.TestCase):
    """Base test class """

    @classmethod
    def setUpClass(cls):
        """Define test variables and initialize app."""
        cls.client = app.test_client()
        cls.data = img_to_base64(os.environ["test_img_path"])
        cls.gt_2mb_data = generate_base64()
        cls.empty_data = payload_empty_dict_data
        cls.wrong_data = payload_data_some_string
        cls.headers = headers
        cls._started_at = time.time()
        # api - add test class name in api_dict for new classes
        cls.api = api_dict[cls.__name__]
        # response
        if cls.__name__ != "GetCardTemplatesTestAPI":
            cls.response = get_response(cls.client, cls.api, cls.headers,
                                        cls.data)
        else:
            cls.response = cls.client.get(cls.api)
        # output
        cls.output = json.loads(cls.response.data)

    def tearDown(self):
        """ To get the elapsed time for each test """
        elapsed = time.time() - self._started_at
        print('{} ({}s)'.format(self.id(), round(elapsed, 2)))


class TestUtil:

    def collect_json_objects(self, image: Image,
                             model_instance: PredictCard) -> Dict:
        """
        Returns the dict of design objects collected from the prediction
        @param image: input PIL image
        @param model_instance: model instance object
        @return: dict of design objects
        """
        image = image.convert("RGB")
        image_np = np.asarray(image)
        image_np = cv2.cvtColor(image_np, cv2.COLOR_RGB2BGR)
        output_dict = model_instance.od_model.get_objects(
            image_np=image_np, image=image
        )
        return model_instance.collect_objects(output_dict=output_dict,
                                              pil_image=image)

    def collect_image_sizes(self, json_objects: Dict, image: Image) -> List:
        """
        Returns the list of extracted image object sizes of the input image
        @param json_objects: dict of design objects
        @param image: input PIL image
        @return: list of image object sizes
        """
        collect_properties = CollectProperties(image)
        image_objects = [image_object for image_object in
                         json_objects["objects"]
                         if image_object["object"] == "image"]
        for design_object in image_objects:
            property_object = getattr(collect_properties,
                                      design_object.get("object"))
            property_element = property_object(image,
                                               design_object.get("coords"))
            design_object.update(property_element)
        return [design_object.get("size", "") for design_object in
                image_objects]


class BaseSetUpClass(unittest.TestCase):
    """
    Base setup class for the tests, contains json objects collected
    for a test image
    """

    def setUp(self):
        self.image_path = os.path.join(
            curr_dir, "../tests/test_images/test01.png")
        self.test_util = TestUtil()
        self.model_instance = load_od_instance()
        self.model_instance = PredictCard(self.model_instance)

        self.image = Image.open(self.image_path)
        self.json_objects, _ = self.test_util.collect_json_objects(
            self.image, self.model_instance)
        self.test_coord1 = self.json_objects['objects'][0].get("coords", [])
        self.test_coord2 = self.json_objects['objects'][1].get("coords", [])
        self.card_arrange = CardArrange()
        self._started_at = time.time()

    def tearDown(self):
        """ To get the elapsed time for each test """
        elapsed = time.time() - self._started_at
        print('{} ({}s)'.format(self.id(), round(elapsed, 2)))
