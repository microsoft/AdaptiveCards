import unittest
import json
import sys
from mystique import config
from tests.base_test_class import BaseAPITest


class PredictJsonTestAPI(BaseAPITest):
    """ tests for predict_json api """

    def test_status_code(self):
        """ checks if the response has a success status code 200 """
        response = self.client.post(
            "/predict_json", headers=self.headers, data=self.data
        )
        self.assertEqual(response.status_code, 200)

    def test_response(self):
        """ checks if the response is not empty or None """
        response = self.client.post(
            "/predict_json", headers=self.headers, data=self.data
        )
        output = json.loads(response.data)
        self.assertEqual(bool(output), True)
        self.assertEqual(len(output), 2)
        self.assertEqual(len(output["card_json"]["body"]), 13)

    def test_response_for_query_params(self):
        """ checks if the response works for query params """
        response = self.client.post(
            "/predict_json?format=template", headers=self.headers, data=self.data
        )
        output = json.loads(response.data)
        self.assertEqual(bool(output), True)
        self.assertEqual(len(output), 3)
        self.assertEqual(len(output["card_v2_json"]), 2)

    def test_response_for_key_error(self):
        """ checks if the error key in response is null """
        response = self.client.post(
            "/predict_json", headers=self.headers, data=self.data
        )
        output = json.loads(response.data)
        self.assertIsNone(output["error"], msg="Key 'Error' is not 'null'")

    def test_exception_raised(self):
        """ checks if Exception is raised properly """
        response = self.client.post(
            "/predict_json", headers=self.headers, data=self.data
        )
        output = json.loads(response.data)
        if output["error"] is not None:
            key = bool(output.get("error"))
            self.assertTrue(key, msg="Key 'error' is found")
            self.assertIsNone(output["card_json"])

    def test_image_max_size(self):
        """ checks if exception raised if the image uploaded has size more than
            in the config variable IMG_MAX_UPLOAD_SIZE """
        response = self.client.post(
            "/predict_json", headers=self.headers, data=self.gt_3mb_data
        )
        output = json.loads(response.data)
        bs64_img = json.loads(self.gt_3mb_data).get("image")
        if sys.getsizeof(bs64_img) > config.IMG_MAX_UPLOAD_SIZE:
            self.assertEqual(output["error"]["code"], 1002)

    def test_empty_payload_data(self):
        """ checks if Exception is raised if empty data sent in payload """
        response = self.client.post(
            "/predict_json", headers=self.headers, data=self.empty_data
        )
        output = json.loads(response.data)
        key = bool(output.get("error"))
        self.assertTrue(key, msg="Key 'error' is found")
        self.assertIsNone(output["card_json"])
        self.assertEqual(output["error"]["code"], 1001)

    def test_wrong_payload_data(self):
        """ checks if Exception is raised if some string sent in payload """
        response = self.client.post(
            "/predict_json", headers=self.headers, data=self.wrong_data
        )
        output = json.loads(response.data)
        key = bool(output.get("error"))
        self.assertTrue(key, msg="Key 'error' is found")
        self.assertIsNone(output["card_json"])
        self.assertEqual(output["error"]["code"], 1001)


if __name__ == "__main__":
    unittest.main()
