import unittest
import json
import sys
from mystique import config
from tests.base_test_class import BaseAPITest
from tests.utils import get_response


class PredictJsonDebugTestAPI(BaseAPITest):
    """ tests for predict_json_debug api """

    def test_status_code(self):
        """ checks if the response has a success status code 200 """
        self.assertEqual(self.response.status_code, 200)

    def test_response(self):
        """ checks if the response is not empty """
        self.assertEqual(bool(self.output), True)
        self.assertEqual(len(self.output), 3)
        # Not fixing the length, as different models give different size,
        # one thing for sure is it shouldn't be empty.
        self.assertTrue(len(self.output["card_json"]["card"]["body"]) > 0)
        self.assertIsNone(self.output["error"],
                          msg="Key 'Error' is not 'null'")

    def test_response_for_query_params(self):
        """ checks if the response works for query params """
        api = "/predict_json_debug?format=template"
        response = get_response(self.client, api, self.headers, self.data)
        output = json.loads(response.data)
        self.assertEqual(bool(output), True)
        self.assertEqual(len(output), 3)
        self.assertEqual(len(output["card_json"]), 2)
        self.assertTrue(output["card_json"]["data"])

    def test_response_for_key_image(self):
        """ checks if the response has a certain key named 'image' """
        key = bool(self.output.get("image"))
        self.assertTrue(key, msg="Key 'image' not found")

    def test_image_max_size(self):
        """ checks if exception raised if the image uploaded has size more than
            in the config variable IMG_MAX_UPLOAD_SIZE """
        response = get_response(self.client, self.api, self.headers,
                                self.gt_2mb_data)
        output = json.loads(response.data)
        bs64_img = json.loads(self.gt_2mb_data).get("image")
        if sys.getsizeof(bs64_img) > config.IMG_MAX_UPLOAD_SIZE:
            self.assertEqual(output["error"]["code"], 1002)

    def test_exception_raised(self):
        """ checks if Exception for API is raised properly """
        if self.output["error"] is not None:
            key = bool(self.output.get("error"))
            self.assertTrue(key, msg="Key 'error' is found")
            self.assertIsNone(self.output["card_json"])

    def test_empty_payload_data(self):
        """ checks if Exception is raised if empty data sent in payload """
        response = get_response(self.client, self.api, self.headers,
                                self.empty_data)
        output = json.loads(response.data)
        key = bool(output.get("error"))
        self.assertTrue(key, msg="Key 'error' is found")
        self.assertIsNone(output["card_json"])
        self.assertEqual(output["error"]["code"], 1001)

    def test_wrong_payload_data(self):
        """ checks if Exception is raised if some string sent in payload """
        response = get_response(self.client, self.api, self.headers,
                                self.wrong_data)
        output = json.loads(response.data)
        key = bool(output.get("error"))
        self.assertTrue(key, msg="Key 'error' is found")
        self.assertIsNone(output["card_json"])
        self.assertEqual(output["error"]["code"], 1001)


if __name__ == "__main__":
    unittest.main()
