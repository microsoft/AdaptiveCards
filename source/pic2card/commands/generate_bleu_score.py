"""
Thins to pre-process manually while collecting the ground truth adaptive
card json:

1. Filter out the elements not supported by pic2card except factset elements
    The supported elements are: TextBlock, ChoiceSet, ImageSet, CheckBox,
    ColumnSet, Image, ActionSet. This filtering is needed because the R-CNN
    model doesn't detect the unsupported elements and won't be part of the
    predicted JSON, This results in lowering the layout score while comparing
    the predicted SON with ground truth.
2. Update the actions element as separate set of ActionSets with the
   relevant action.
        Right now each actions element is represented as a separate ActionSet
        element having an action.
3. Need to update the un-supported Column Width attribute values.
    Un-supported property values for the property Width for the element
    Column are:
        - Weighted
        - Pixels
    update it to supported values: Stretch / Automatic.

4.Template data binding is not supported in metric collection.
    Since we are comparing the layout structure and each element's
    property values, comparing a custom expression binding variables on
    one side and expression binding done by pic2card / non-template binding
    card JSON values, will be meaningless and lowers our layout metric score.

Command to collect the bleu score metric for the layout generation

USAGE :

If not in debug mode:
python -m commands.generate_bleu_score.py --images_path=/image_path \
    --ground_truths_path=/ground_truth_json_path \
    --api_url=url_of_the_service

If in debug mode:
python -m commands.generate_bleu_score.py --images_path=/image_path \
    --ground_truths_path=/ground_truth_json_path \
    --api_url=url_of_the_service --debug

"""
# pylint: disable=too-many-locals
# pylint: disable=too-many-statements
# pylint: disable=consider-using-with

import argparse
import base64
import copy
import json
import os
import re
from datetime import datetime
from typing import List, Dict

import pandas as pd
import requests
from nltk import translate
from nltk.translate.bleu_score import corpus_bleu


class Helper:
    """
    This class is holds the needed pre-processing methods which handles:
    1. Filter the non-supported attributes from the element and maintain the
       common supported in both ground-truth and test card JSON.
    2. Maintain the order of the element's attributes in both ground-truth and
       test card JSON.
    3. Converts simple date expression to textual representation
    4. Adapt a factset element as rows:columns of text-boxes
    """

    CONTAINER_SUB_MAPPINGS = {
        "Column": "items",
        "ColumnSet": "columns",
        "ImageSet": "images",
    }
    ELEMENTS_PROPERTIES_MAP = {
        "TextBlock": {
            "attributes": ["type", "text", "size", "color", "weight", "wrap"],
            "method": "text_block",
        },
        "actions": {
            "attributes": ["type", "title", "style"],
            "method": "actions",
        },
        "ActionSet": {
            "attributes": ["type", "actions", "spacing"],
            "method": "action_set",
        },
        "Image": {
            "attributes": ["type", "altText", "size", "url"],
            "method": "image",
        },
        "Input.Toggle": {
            "attributes": ["type", "title"],
            "method": "check_box",
        },
        "choices": {"attributes": ["title", "value"], "method": "choices"},
        "Input.ChoiceSet": {
            "attributes": ["type", "choices", "style"],
            "method": "choice_set",
        },
        "Column": {
            "attributes": ["type", "width", "items"],
            "method": "column",
        },
        "ColumnSet": {
            "attributes": ["type", "columns"],
            "method": "column_set",
        },
        "ImageSet": {
            "attributes": ["type", "imageSize", "images"],
            "method": "image_set",
        },
    }

    # pylint: disable=no-self-use
    def _change_date_expression(self, expression: str) -> str:

        """
        Convert the date expression to date string in words format
        @param expression: date expression
        @return: date string in words format
        """
        date_string = re.findall(
            r"\b\d+\-\d+-\d+T\d+:\d+:\d+\w{1}", expression
        )[0]
        date_time_obj = datetime.strptime(date_string, "%Y-%m-%dT%H:%M:%SZ")
        date_string = date_time_obj.strftime("%a, %d %b %Y")
        return date_string

    # pylint: disable=no-self-use
    def factset_to_textbox(self, element: Dict) -> List:
        """
        Convert the factset element to column-sets of textboxes
        @param element: factset element
        @return: updated list column-sets of textboxes.
        """
        keys_values = element.get("facts")
        updated_element = []
        for ctr, value in enumerate(keys_values):
            print(f"{value} index {ctr}")
            item1 = {
                "type": "TextBlock",
                "text": value.get("title"),
                "size": "Default",
                "horizontalAlignment": "Left",
                "color": "Default",
                "weight": "Bolder",
                "wrap": "true",
            }
            item2 = {
                "type": "TextBlock",
                "text": value.get("value"),
                "size": "Default",
                "horizontalAlignment": "Right",
                "color": "Default",
                "weight": "Default",
                "wrap": "true",
            }
            columns = [
                {
                    "type": "Column",
                    "width": "auto",
                    "items": [item1],
                    "horizontalAlignment": "Left",
                },
                {
                    "type": "Column",
                    "width": "auto",
                    "items": [item2],
                    "horizontalAlignment": "Left",
                },
            ]
            columnset = {
                "type": "ColumnSet",
                "columns": columns,
                "horizontalAlignment": "Left",
            }
            updated_element.append(columnset)
        return updated_element

    # pylint: disable=no-self-use
    def remove_fields_from_element(
        self, element: Dict, reference_list: List
    ) -> Dict:
        """
        Remove the extra fields from the element , i.e keep only the
        supported attributes for the element.
        @param element: adaptive card design element
        @param reference_list: list of supported attributes
        for the passed element's type.
        @return: updated element.
        """
        fields = list(element.keys())
        fields = list(set(fields) & set(reference_list))
        element = {k: element[k] for k in fields}
        return element

    def clean_element(self, element: Dict) -> Dict:
        """
        Method responsible for calling the appropriate pre-process method for
        the passed element.
        :param element: adaptive card design element
        :return: pre-processed adaptive card design element
        """
        type_text = element.get("type", "")
        if "type" not in element:
            type_text = "choices"
        elif re.findall(r"\bAction\b", element.get("type")):
            type_text = "actions"
        element_attributes = self.ELEMENTS_PROPERTIES_MAP.get(
            type_text, {}
        ).get("attributes")
        element = self.remove_fields_from_element(element, element_attributes)
        if element.get("type", "") not in list(
            self.CONTAINER_SUB_MAPPINGS.keys()
        ) + ["Input.Toggle"]:
            if type_text not in ["choices", "actions"]:
                type_text = self.ELEMENTS_PROPERTIES_MAP.get(
                    element.get("type", ""), {}
                ).get("method")
                template_object = getattr(self, type_text)
                element = template_object(element)
        if element.get("type", "") in self.CONTAINER_SUB_MAPPINGS:
            element[self.CONTAINER_SUB_MAPPINGS[element.get("type", "")]] = []

        element = dict(sorted(element.items(), key=lambda s: s[0]))
        return element

    def text_block(self, element: Dict) -> Dict:
        """
        Performs all the pre-process operation related to Textbox
        @param element: adaptive cards design element
        @return: pre-processed textbox element
        """
        fields = list(element.keys())
        # add the extra fileds with default values
        element.update({"wrap": "true"})
        if "size" not in fields:
            element.update({"size": "Default"})
        if "weight" not in fields:
            element.update({"weight": "Default"})
        if "color" not in fields:
            element.update({"color": "Default"})

        if re.findall(r"{{.*}}", element.get("text", "")):
            need_to_update = self._change_date_expression(
                re.findall(r"{{.*}}", element.get("text"))[0]
            )
            text = element.get("text")
            text = re.sub(r"{{.*}}", need_to_update, text)
            element.update({"text": text})
        return element

    def action_set(self, element: Dict) -> Dict:
        """
        Performs all the pre-process operation related to Actionset
        @param element: adaptive cards design element
        @return: pre-processed actionset element
        """
        fields = list(element.keys())
        if "spacing" not in fields:
            element.update({"spacing": "Medium"})
        element["actions"] = [self.clean_element(element["actions"][0])]
        fields = list(element["actions"][0].keys())

        if "style" not in fields:
            element["actions"][0].update({"style": "default"})

        element["actions"] = [
            dict(sorted(element["actions"][0].items(), key=lambda s: s[0]))
        ]
        return element

    def image(self, element: Dict) -> Dict:  # pylint: disable=no-self-use
        """
        Performs all the pre-process operation related to Image
        @param element: adaptive cards design element
        @return: pre-processed image element
        """
        fields = list(element.keys())
        if "altText" not in fields:
            element.update({"altText": "Image"})
        element["url"] = ""
        return element

    def choice_set(self, element: Dict) -> Dict:
        """
        Performs all the pre-process operation related to Choice-Set
        @param element: adaptive cardsgetattr design element
        @return: pre-processed choice-set element
        """
        element.update({"style": "expanded"})
        element["choices"] = [
            self.clean_element(ch) for ch in element["choices"]
        ]
        return element

    def clean_containers_train(
        self,
        body: List,
        element: Dict,
        pre_process_object=None,
        ground_truth=False,
    ) -> None:
        """
        Method for cleaning the container elements.
        based on the ground_truth flag swihces and calls the appropriate
        pre_process methods for both ground truth and predicted card JSON
        :param body: adaptive card JSON body
        :param element: design element to be pre-processed
        :param pre_process_object: Preprocess class object
        :param ground_truth: flag to switch between ground truth
                            and predicted card JSON
        """
        if ground_truth:
            backup = copy.deepcopy(element)
            element = self.clean_element(element)

        element = dict(sorted(element.items(), key=lambda s: s[0]))
        body.append(element)
        if element.get("type", "") != "Input.ChoiceSet":
            container_sub_filed = self.CONTAINER_SUB_MAPPINGS[element["type"]]
            body = body[-1].get(container_sub_filed)
            if ground_truth:
                pre_process_object.pre_process_elements(
                    body, backup[container_sub_filed]
                )
            else:
                pre_process_object.pre_process_elements(
                    body, element[container_sub_filed]
                )


class Preprocess:
    """
    This class Handles the pre-processing for both ground truth adaptive card
    json and pi2card generated adaptive card json
    """

    helper_object = Helper()
    CONTAINERS = ["ColumnSet", "Imageset", "Column", "Input.ChoiceSet"]
    GROUND_TRUTH_DUMP_PATH = "../../../ground_truth_dump"
    PREDICTED_DUMP_PATH = "../../../predicted_dump"
    CSV_EXPORT_PATH = "../../../layout_metric_scores.csv"

    def pre_process_elements(self, body: List, design_object: Dict) -> None:
        """
        Pre-process the passed adaptive card design element
        @param body: adaptive card json body
        @param design_object: element to be pre-processed
        """

        if (
            isinstance(design_object, dict)
            and design_object.get("type", "") not in self.CONTAINERS
        ):
            if design_object.get("type") == "FactSet":
                design_objects = Helper.factset_to_textbox(
                    self.helper_object, design_object
                )
                body += design_objects
            else:
                design_object = self.helper_object.clean_element(design_object)
                body.append(design_object)
        elif isinstance(design_object, list):
            for design_obj in design_object:
                self.pre_process_elements(body, design_obj)
        else:
            self.helper_object.clean_containers_train(
                body, design_object, self, ground_truth=True
            )

    def process_elements_test(self, body: List, design_object: Dict) -> None:
        """
        Process the pic2card generated adaptive card json for pre-processing
        @param body: adaptive card json body
        @param design_object: element to be processed
        """

        if (
            isinstance(design_object, dict)
            and design_object.get("type", "") not in self.CONTAINERS
        ):
            if design_object.get("type") == "Image":
                design_object["url"] = ""
            del design_object["horizontalAlignment"]
            design_object = dict(
                sorted(design_object.items(), key=lambda s: s[0])
            )
            body.append(design_object)
        elif isinstance(design_object, list):
            for design_obj in design_object:
                self.pre_process_elements(body, design_obj)
        else:
            del design_object["horizontalAlignment"]
            self.helper_object.clean_containers_train(body, design_object, self)

    # pylint: disable=no-self-use
    def _get_card_json(self, image_path: str, api_url: str) -> Dict:
        """
        Fetch the pic2card generated adaptive card json
        @param image_path: image full path
        @param api_url: pic2card api url
        @return: adaptive card json
        """
        base64_string = ""
        with open(image_path, "rb") as image_file:
            base64_string = base64.b64encode(image_file.read()).decode()

        headers = {"Content-Type": "application/json"}
        response = requests.post(
            url=api_url,
            data=json.dumps({"image": base64_string}),
            headers=headers,
        )
        response.raise_for_status()
        return response.json().get("card_json").get("card")

    def main(
        self,
        api_url=None,
        images_path=None,
        ground_truths_path=None,
        debug=False,
    ) -> None:
        """
        Collect and log bleu_score metric for the set of images with their
        ground truths passed.
        @param api_url: pic2card api url
        @param images_path: images path [ directory / image ]
        @param ground_truths_path:  ground truth jsons path
        @param debug: Debug flag to enable the metric collection in
                      debugging mode to dump the train/test and
                      resulting metric scores
        [ directory / single json file ]
        """
        rows = []
        if ".png" in images_path:
            images = [images_path]
            ground_truths = [ground_truths_path]
        else:
            images = list(sorted(os.listdir(images_path)))
            images = [f"{images_path}/{image}" for image in images]
            ground_truths = list(sorted(os.listdir(ground_truths_path)))
            ground_truths = [
                f"{ground_truths_path}/{item}" for item in ground_truths
            ]

        avg_score = 0.0
        for ctr, train_image in enumerate(images):
            print(f"\nMetric collection for image: {train_image}..")
            # preprocess train
            print(f"Ground Truth file: {ground_truths[ctr]} ...")
            train = json.loads(open(ground_truths[ctr], "r").read())
            body = []
            self.pre_process_elements(body, train["body"])
            train["body"] = body
            train = dict(sorted(train.items(), key=lambda s: s[0]))
            train["version"] = "1.3"

            print("Getting pic2card generated adaptive card json....")
            test = self._get_card_json(train_image, api_url)

            # preprocess test
            body = []
            self.process_elements_test(body, test["body"])
            test["body"] = body
            test = dict(sorted(test.items(), key=lambda s: s[0]))
            test["version"] = "1.3"
            train_corpus = json.dumps(train)
            train_corpus = re.sub(r"[^\w\s\{\}]", "", train_corpus)
            test_corpus = json.dumps(test)
            test_corpus = re.sub(r"[^\w\s\{\}]", "", test_corpus)

            # Get metric
            smoothing = translate.bleu_score.SmoothingFunction().method7
            score = corpus_bleu(
                [[train_corpus.lower().split()]],
                [test_corpus.lower().split()],
                smoothing_function=smoothing,
                weights=(0.5, 0.5),
            )
            if score > 1:
                smoothing = translate.bleu_score.SmoothingFunction().method3
                score = corpus_bleu(
                    [[train_corpus.lower().split()]],
                    [test_corpus.lower().split()],
                    smoothing_function=smoothing,
                    weights=(0.5, 0.5),
                )

            print(f"Similarity score for {train_image} is : {score}\n")
            avg_score += score
            if debug:
                rows.append([train_image, score])
                file_name = train_image.split("/")[-1]
                if not os.path.exists(self.GROUND_TRUTH_DUMP_PATH):
                    os.makedirs(self.GROUND_TRUTH_DUMP_PATH)
                if not os.path.exists(self.PREDICTED_DUMP_PATH):
                    os.makedirs(self.PREDICTED_DUMP_PATH)

                print(
                    f"Dumping pre-processed train "
                    f"and test json of: {file_name}"
                )

                open(
                    f"{self.GROUND_TRUTH_DUMP_PATH}/"
                    f"{file_name.split('.')[0]}_pre_processed.json",
                    "w",
                ).write(json.dumps(train))
                open(
                    f"{self.PREDICTED_DUMP_PATH}/"
                    f"{file_name.split('.')[0]}_pre_processed.json",
                    "w",
                ).write(json.dumps(test))
        print(f"average score = {(avg_score / len(images)) * 100}%")
        if debug:
            print("Dumping the per image score collected as a CSV")
            dfr = pd.DataFrame(rows, columns=["image", "score"])
            dfr.to_csv(self.CSV_EXPORT_PATH, index=False)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Collect the blue score metric" "for layout generation"
    )
    parser.add_argument(
        "--images_path",
        required=True,
        help="Enter Image path/ Images directory path",
    )
    parser.add_argument(
        "--ground_truths_path",
        required=True,
        help="Enter ground truth card json path/ ground truth "
        "card json directory path",
    )
    parser.add_argument(
        "--api_url",
        help="Enter the endpoint of pic2card server, this does "
        "not support template binding of data",
        default=None,
    )
    parser.add_argument(
        "--debug",
        help="Debug flag to enable the metric collection in "
        "debugging mode to dump the train/test and "
        "resulting metric scores",
        required=False,
        action="store_true",
    )
    args = parser.parse_args()
    pre_process = Preprocess()
    pre_process.main(
        images_path=args.images_path,
        ground_truths_path=args.ground_truths_path,
        api_url=args.api_url,
        debug=args.debug,
    )
