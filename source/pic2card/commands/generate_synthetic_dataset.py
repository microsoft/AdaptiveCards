#!/usr/bin/python

# pip install lxml
"""
Command to generate adaptive cards as training image dataset in bulk.

USAGE :

Arguments : card_elements_dir_path , number_of_elements , bg_color, bulk_img \
            save_as_zip

command :  python -m commands.generate_synthetic_dataset \
    --number_of_elements=number of elements desired \
    --card_elements_dir_path=/path/to/input/card_elements \
    --bg_color= any one of the list ["WHITE","GREY","CYAN","ROSE","GOLD"] \
    --bulk_img=number of images needs to be generated \
    --save_as_zip=True if you want to save files to zip

     python -m commands.generate_synthetic_dataset -n <number of images> \
            -z true \
            -c <colour> -e <number of elements needed>

"""
import argparse
from typing import Any, Sequence, List
import cv2
from mystique import config
from datagen import generate_synthetic_image as synthetic
from datagen.generate_annotations import get_annotation_file
from datagen.utils import (
    get_zip_paths,
    zip_and_remove_file,
    get_image_name,
    get_outgoing_file_paths,
)


def save_img_and_annotations(
    image_with_canvas: Any, annotation_xml: Any
) -> None:
    """
    Function is used to save the generated images and annotation files
    in the respective paths defined in config or given in args while using
    command
    """
    image_name = get_image_name()
    # saving image and annotation xml
    cv2.imwrite(
        filename=f"{config.GENERATED_IMG_DIR}/{image_name}.png",
        img=image_with_canvas,
    )

    annotation_xml.write(
        f"{config.GENERATED_ANNOTATION_DIR}/{image_name}.xml", pretty_print=True
    )
    synthetic.logger.debug(
        "Saved image and annotation - %s.png and %s.xml in destination folder",
        image_name,
        image_name,
    )


def get_synthetic_image_properties(
    number_of_elements: int, card_elements_dir_path: List
) -> Sequence:
    """
    To create the synthetic image from the card elements arguments given
    @param number_of_elements
    @param card_elements_dir_path
    return generated_image
    """
    layout = synthetic.CardElements(number_of_elements, card_elements_dir_path)
    padded_image_element = synthetic.add_padding_to_img_elements(
        layout.elements_with_path
    )
    generated_image = synthetic.generate_image(padded_image_element)
    synthetic_image_properties = {
        "layout": layout,
        "padded_image": padded_image_element,
        "generated_image": generated_image,
    }
    return synthetic_image_properties


def main(
    card_elements_dir_path=None,
    number_of_elements=None,
    background_colour=None,
    bulk_img: int = None,
    save_as_zip: bool = None,
) -> None:
    """
    Command generates cards with random elements from the
    card_elements directory at bulk

    @param bulk_img: number of images needs to be generated
    """
    generating_file_paths, generating_xml_paths = get_outgoing_file_paths(
        bulk_img
    )
    for _ in range(bulk_img):
        synthetic_image_property = get_synthetic_image_properties(
            number_of_elements, card_elements_dir_path
        )
        annotation_xml = get_annotation_file(
            synthetic_image_property["layout"],
            synthetic_image_property["generated_image"],
            synthetic_image_property["padded_image"],
        )
        image_with_canvas = synthetic.add_background_colour_to_generated_image(
            synthetic_image_property["generated_image"], background_colour
        )
        save_img_and_annotations(image_with_canvas, annotation_xml)
    if save_as_zip:
        zip_path, annotation_zip_path = get_zip_paths()
        zip_and_remove_file(
            config.GENERATED_IMG_DIR, zip_path, generating_file_paths
        )
        zip_and_remove_file(
            config.GENERATED_ANNOTATION_DIR,
            annotation_zip_path,
            generating_xml_paths,
        )


def set_args() -> Any:
    """
    Returns parser object for the command
    @return: parser
    """
    parser = argparse.ArgumentParser(description="Generate adaptive cards")
    parser.add_argument(
        "-p",
        "--card_elements_dir_path",
        default=config.ELEMENTS_DIR,
        help="Enter Card elements directory path",
    )
    parser.add_argument(
        "-c",
        "--bg_color",
        default=config.BACKGROUND_COLOR,
        help="Enter the background color desired for the generated image",
    )
    parser.add_argument(
        "-e",
        "--number_of_elements",
        type=int,
        default=config.ELEMENT_COUNT_THRESHOLD,
        help="Enter number of Card elements desired in the generated image",
    )

    parser.add_argument(
        "-n",
        "--bulk_img",
        default=config.BULK_IMAGES_NEEDED,
        type=int,
        help="Number of images needed for bulk generation",
    )
    parser.add_argument(
        "-z",
        "--save_as_zip",
        default=False,
        type=bool,
        help="Set True to save generated images in zip format",
    )
    return parser


if __name__ == "__main__":
    parser_object = set_args()
    args = parser_object.parse_args()
    main(
        card_elements_dir_path=args.card_elements_dir_path,
        number_of_elements=args.number_of_elements,
        background_colour=args.bg_color,
        bulk_img=args.bulk_img,
        save_as_zip=args.save_as_zip,
    )
