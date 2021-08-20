"""Module to Calculate Cosine similarity between the testing and
   generated card json
"""
import os
import re
import argparse
import json


from sklearn.feature_extraction.text import CountVectorizer
from sklearn.metrics.pairwise import cosine_similarity

from mystique.predict_card import PredictCard


model_path = os.path.join(
    os.path.dirname(__file__), "../model/frozen_inference_graph.pb"
)
label_path = os.path.join(
    os.path.dirname(__file__), "../mystique/training/object-detection.pbtxt"
)


def build_generated_card_json(images, path, testing_file_path):
    """
    Build the generated card json file from the list of testing images
    by hiting the api and parsing the card body from the response

    @param images: list of imae filenames
    @param path: folder path of the images
    @param testing_file_path: testing jl file path
    """
    parent = os.path.dirname(testing_file_path)
    generated_images = []
    # pylint: disable=bad-option-value,consider-using-with
    generated_jsonlines_file = open(parent + "/generated_card_json.jl", "w")
    for image in images:
        print(path + image)
        if image not in generated_images:
            # with open(path+image, "rb") as image_file:
            #    base64_string = base64.b64encode(image_file.read()).decode()
            # pylint: disable=unexpected-keyword-arg
            response = PredictCard().main(
                image_path=path + image,
                frozen_graph_path=model_path,
                labels_path=label_path,
            )
            content = {
                "filename": str(image),
                "card_json": response.json().get("card_json"),
            }
            generated_jsonlines_file.write(json.dumps(content))
            generated_jsonlines_file.write("\n")


def get_cosine_sim(*strs):
    """
    Returns the cosine similarity score of the
    given 2 strings

    @param *strs: variable agrument parameter for
                  list of strings
    @return: similarity score

    """
    vectors = [
        t
        for t in get_vectors(*strs)  # pylint: disable=unnecessary-comprehension
    ]
    return cosine_similarity(vectors)[0][1]


def get_vectors(*strs):
    """
    Returns the vectorized values of the text

    @param *strs: variable agrument parameter for
                  list of strings
    @return: the vectorized text ndarray
    """
    text = [t for t in strs]  # pylint: disable=unnecessary-comprehension
    vectorizer = CountVectorizer(text)  # pylint: disable=too-many-function-args
    vectorizer.fit(text)
    return vectorizer.transform(text).toarray()


def get_jaccard_sim(str1, str2):
    """
    Returns the jaccard similarity between the test and generated card
    json

    @param str1: string one
    @param str2: string two

    @return: jaccard score
    """
    str1_set = set(str1.split())
    str2_set = set(str2.split())
    intersection = str1_set.intersection(str2_set)
    return float(len(intersection)) / (
        len(str1_set) + len(str2_set) - len(intersection)
    )


def main(testing_file_path, testing_images_path):
    """.Generating Cosine Similarity, Avg "Cosine Similarity,
    Jaggard Similarity, Average Jaccard Similarity"""

    # Input testing json lines file consists of lines of json with 2 keys
    # filename and card_json for each design image
    testing_jsonlines = open(testing_file_path, "r").readlines()
    images = []
    for josnline in testing_jsonlines:
        json_obj = json.loads(josnline)
        filename = json_obj.get("filename", "")
        images.append(filename)

    # Build the json lines of generated card jsons  of the input images
    build_generated_card_json(images, testing_images_path, testing_file_path)

    if os.path.exists(
        os.path.dirname(testing_file_path) + "/generated_card_json.jl"
    ):
        generated_jsonlines = open("generated_card_json.jl", "r").readlines()
        cosine_similarities = {}.fromkeys(images, "")
        jaccard_similarities = {}.fromkeys(images, "")

        pattern = re.compile(r"\"\s*url\s*\"\s*\:\s*\"[^\"]*\"", re.IGNORECASE)
        for line in testing_jsonlines:
            json_obj = json.loads(line)
            test_card_json = json_obj.get("card_json", "")
            filename = json_obj.get("filename", "")
            generated_card_json = ""
            for gen_jsonline in generated_jsonlines:
                if json.loads(gen_jsonline).get("filename", "") == filename:
                    generated_card_json = json.loads(gen_jsonline).get(
                        "card_json", ""
                    )
                    break
            test_card_json = re.sub(
                pattern, 'url": ""', json.dumps(test_card_json)
            )
            generated_card_json = re.sub(
                pattern, 'url": ""', json.dumps(generated_card_json)
            )
            cosine_similarities[filename] = str(
                get_cosine_sim(test_card_json, generated_card_json)
            )
            jaccard_similarities[filename] = str(
                get_jaccard_sim(test_card_json, generated_card_json)
            )

            print(
                "Cosine Similarities:\n",
                json.dumps(cosine_similarities, indent=2),
            )
            print(
                "Average Cosine Similarity:",
                (
                    sum(
                        [float(ll) for ll in list(cosine_similarities.values())]
                    )
                    / len(list(cosine_similarities.values()))
                )
                * 100,
            )
            print(
                "Jaccard Similarities:\n",
                json.dumps(jaccard_similarities, indent=2),
            )
            print(
                "Average Jaccard Similarity:",
                (
                    sum(
                        [
                            float(ll)
                            for ll in list(jaccard_similarities.values())
                        ]
                    )
                    / len(list(jaccard_similarities.values()))
                )
                * 100,
            )

    else:
        print("Generated card json files not found")


if __name__ == "__main__":

    parser = argparse.ArgumentParser(description="Cosine Similarity")
    parser.add_argument(
        "--testing_file_path", required=True, help="Enter Test File Path"
    )
    parser.add_argument(
        "--testing_images_path",
        required=True,
        help="Enter Test Images Folder Path",
    )
    args = parser.parse_args()
    main(args.testing_file_path, args.testing_images_path)
