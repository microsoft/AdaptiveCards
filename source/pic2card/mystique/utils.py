import time
from typing import Optional
import glob
import xml.etree.ElementTree as Et
from contextlib import contextmanager
import pandas as pd

from mystique.config import ID_TO_LABEL


@contextmanager
def timeit(name="code-block"):
    """
    Execute the codeblock and measure the time.

    >> with timeit('name') as f:
    >>     # Your code block
    """
    try:
        start = time.time()
        yield
    finally:
        # Execution is over.
        end = time.time() - start
        print(f"Execution block: {name} finishes in : {end} sec.")


def xml_to_csv(labelmg_dir: str) -> pd.DataFrame:
    """
    Maps the xml labels of each object
    to the image file

    @param labelmg_dir: Folder with labelmg exported image and tags.

    @return: xml dataframe
    """
    xml_list = []
    for xml_file in glob.glob(labelmg_dir + "/*.xml"):
        tree = Et.parse(xml_file)
        root = tree.getroot()
        for member in root.findall("object"):
            value = (root.find("filename").text,
                     int(root.find("size")[0].text),
                     int(root.find("size")[1].text),
                     member[0].text,
                     int(member[4][0].text),
                     int(member[4][1].text),
                     int(member[4][2].text),
                     int(member[4][3].text)
                     )
            xml_list.append(value)
    column_name = ["filename", "width", "height", "class", "xmin",
                   "ymin", "xmax", "ymax"]
    xml_df = pd.DataFrame(xml_list, columns=column_name)

    return xml_df


def id_to_label(label_id: int) -> Optional[str]:
    return ID_TO_LABEL.get(label_id)
