import os
import unittest
from tests.utils import (
    img_to_base64,
    headers,
    payload_empty_dict_data,
    payload_data_some_string,
    generate_base64,
)
from app.api import app


class BaseAPITest(unittest.TestCase):
    """Base test class """

    def setUp(self):
        """Define test variables and initialize app."""
        self.data = img_to_base64(os.environ["test_img_path"])
        self.gt_3mb_data = generate_base64()
        self.empty_data = payload_empty_dict_data
        self.wrong_data = payload_data_some_string
        self.headers = headers
        app.testing = True
        self.client = app.test_client()
