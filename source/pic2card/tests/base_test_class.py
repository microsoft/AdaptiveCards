import os
import unittest
import time
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

    @classmethod
    def setUpClass(cls):
        """Define test variables and initialize app."""
        cls.client = app.test_client()
        cls.data = img_to_base64(os.environ["test_img_path"])
        cls.gt_2mb_data = generate_base64()
        cls.empty_data = payload_empty_dict_data
        cls.wrong_data = payload_data_some_string
        cls.headers = headers

    def setUp(self):
        """ To know the time taken for each unittest """
        self._started_at = time.time()

    def tearDown(self):
        """ To get the elapsed time for each test """
        elapsed = time.time() - self._started_at
        print('{} ({}s)'.format(self.id(), round(elapsed, 2)))

