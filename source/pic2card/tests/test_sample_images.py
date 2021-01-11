import json
from tests.utils import get_response
from tests.test_predict_json import BaseAPITest


class TestSampleImages(BaseAPITest):
    """ Basic Tests that run for a list of sample images
        for predict_json api.
    """

    def setUp(self):
        self.templates_api = "/get_card_templates"
        self.templates_response = self.client.get(self.templates_api)
        self.templates_output = json.loads(self.templates_response.data)

    def test_response(self):
        """
        Basic checks done for the templates images
        checks if return json has no error and
        response status is 200 for predict_json api
        """
        for data in self.templates_output['templates']:
            # update self.data with the template api output
            self.data = f'{{"image": "{data}"}}'
            self.response = get_response(self.client, self.api,
                                         self.headers, self.data)
            self.output = json.loads(self.response.data)
            self.assertEqual(self.response.status_code, 200)
            self.assertEqual(bool(self.output), True)
            self.assertIsNone(self.output["error"])
