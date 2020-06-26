"""This module converts the labelled traning and testing xmls generated
   from the labelImg tool to object:boundary:image mapped csv.
"""
import os

from mystique.utils import xml_to_csv


def main():
    """
    Writes the mapped object boundaries:image csv rows into the
    data folder
    """
    for folder in ["train", "test"]:
        image_path = os.path.join(os.getcwd(), ("../data/" + folder))
        xml_df = xml_to_csv(image_path)
        xml_df.to_csv(("../images/" + folder + "_labels.csv"),
                      index=None)
        print("Successfully converted xml to csv.")


main()
