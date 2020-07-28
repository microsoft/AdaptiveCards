# Copyright (c) Microsoft Corporation. All rights reserved. 
# Licensed under the MIT License. 
import unittest
import json
from app import app
from copy import deepcopy


POST_ROUTE = '/'

class TestFlaskApi(unittest.TestCase):
    def setUp(self):
        self.app = app.test_client()
        self.app.testing = True

    def testEmptyData(self):
        jsonFile = open('../../../../samples/v1.0/Scenarios/ActivityUpdate.json')
        template = json.load(jsonFile)
        data = ""
        jsonFile.close()
        response = self.app.post(POST_ROUTE,
                                 data=dict(template=json.dumps(template),
                                           data=data
                                          )
                                )
        self.assertEqual(response.status_code, 200)
        res_json_str = (response.data).decode('utf-8')
        res_json = json.loads(res_json_str)
        img = res_json["imageData"]
        errorList = res_json["errors"]
        warningList = res_json["warnings"]
        self.assertTrue(len(errorList) == 0)
        self.assertTrue(len(warningList) == 0)
        self.assertTrue(len(img) > 0)

    def testEmptyTemplate(self):
        jsonFile = open('../../../../samples/v1.0/Scenarios/ActivityUpdate.json')
        template = json.load(jsonFile)
        data = ""
        jsonFile.close()
        response = self.app.post(POST_ROUTE,
                                 data=dict(data=json.dumps(template),
                                           template=data
                                          )
                                )
        self.assertEqual(response.status_code, 200)
        res_json_str = (response.data).decode('utf-8')
        res_json = json.loads(res_json_str)
        errorList = res_json["errors"]
        self.assertTrue(len(errorList) > 0)
        

    def testEmptyPayLoad(self):
        response = self.app.post(POST_ROUTE, 
                                 data=dict(template="", 
                                           data=""
                                          )
                                )
        self.assertEqual(response.status_code, 200)
        res_json_str = (response.data).decode('utf-8')
        res_json = json.loads(res_json_str)
        errorList = res_json["errors"]
        self.assertTrue(len(errorList) > 0)


    def testSendingInvalidJson(self):
        data = '{"title" : "invalid card data" '
        template = '{"title" : "invalid card template" '
        response = self.app.post(POST_ROUTE, 
                                 data=dict(template=template,
                                           data=data
                                          )
                                )
        self.assertEqual(response.status_code, 200)
        res_json_str = (response.data).decode('utf-8')
        res_json = json.loads(res_json_str)
        errorList = res_json["errors"]
        self.assertTrue(len(errorList) > 0)


    def testSendingCompleteCardPayload(self):
        template = {
                       "type": "AdaptiveCard",
                        "version": "1.0",
                        "body": [
                                    {
                                        "type": "TextBlock",
                                        "text": "Hello ${name}!"
                                    }
                                ]
                    }
        data = {
                   "name": "Matt Hidinger"
               }
        
        response = self.app.post(POST_ROUTE, 
                                 data=dict(template=json.dumps(template),
                                           data=json.dumps(data)
                                          )
                                )
        self.assertEqual(response.status_code, 200)
        res_json_str = (response.data).decode('utf-8')
        res_json = json.loads(res_json_str)
        img = res_json["imageData"]
        errorList = res_json["errors"]
        warningList = res_json["warnings"]
        self.assertTrue(len(errorList) == 0)
        self.assertTrue(len(warningList) == 0)
        self.assertTrue(len(img) > 0)

    def tearDown(self):
        self.app = None

if __name__ == "__main__":
    unittest.main()
