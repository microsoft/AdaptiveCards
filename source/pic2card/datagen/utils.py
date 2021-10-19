"""Contains utilities for the datagen package"""

import os
import time
import glob
import zipfile
import logging
from typing import Tuple, List
from mystique import config

logger = logging.getLogger("commands.generate_bulk_data")


def get_image_name() -> int:
    """
    Returns an image number for the file name to save
    @return: new_img_name
    """
    generated_images = glob.glob(config.GENERATED_IMG_DIR + "/*")
    if generated_images:
        latest_file = max(generated_images, key=os.path.getctime)
        latest_filename = os.path.basename(latest_file)
        new_img_name = int(latest_filename.split(".")[0]) + 1
    else:
        new_img_name = int(1)
    return new_img_name


def get_outgoing_file_paths(bulk_img: int) -> Tuple[List, List]:
    """
    Returns list of image and annotations file names that will be generated
    @param bulk_img: number of images needed for bulk generation
    @retrun img_files, xml_files
    """
    generating_latest_file = get_image_name()
    generating_last_file = generating_latest_file + bulk_img
    img_files = [
        f"{file}.png"
        for file in range(generating_latest_file, generating_last_file)
    ]
    xml_files = [
        f"{file}.xml"
        for file in range(generating_latest_file, generating_last_file)
    ]
    return img_files, xml_files


def get_zip_paths() -> Tuple[str, str]:
    """
    Function is used to construct the path for the zip files
    to be stored for generating synthetic images
    @return : Tuple of the zip path and annotation file zip path
    """
    if not os.path.exists(config.GENERATED_ZIP_DIR):
        os.makedirs(config.GENERATED_ZIP_DIR)
    creation_time = time.strftime("%Y%m%d_%H%M%S", time.localtime())
    zip_path = f"{config.GENERATED_ZIP_DIR}/generated_{creation_time}.zip"
    annotation_zip_path = (
        f"{config.GENERATED_ZIP_DIR}/annotation_{creation_time}.zip"
    )
    return zip_path, annotation_zip_path


def zip_and_remove_file(folder_path: str, zip_path: str, files: List) -> None:
    """
    Saves a zip file of the generated images and annotations to folder
    @param folder_path: the folder path needed to be zipped
    @param zip_path: path where zipfile needs to be saved
    @param files: list of files that will be generated
    @retrun None
    """
    with zipfile.ZipFile(zip_path, mode="a") as zipf:
        len_dir_path = len(folder_path)
        for root, _, _ in os.walk(folder_path):
            for file in files:
                file_path = os.path.join(root, file)
                zipf.write(file_path, file_path[len_dir_path:])
                os.remove(file_path)
        logger.debug(
            "Saved %s and removed duplicate files", os.path.basename(zip_path)
        )
