import time
import io
from typing import Optional, Dict
import glob
import xml.etree.ElementTree as Et
from contextlib import contextmanager
from importlib import import_module

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from PIL import Image

from mystique import config

# Colro map used for the plotting.
COLORS = [
    [0.000, 0.447, 0.888],
    [0.000, 0.447, 0.741], [0.850, 0.325, 0.098], [0.929, 0.694, 0.125],
    [0.494, 0.184, 0.556], [0.466, 0.674, 0.188], [0.301, 0.745, 0.933]
 ]


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
    return config.ID_TO_LABEL.get(label_id)


def plot_results(pil_img: Image,
                 classes: np.array,
                 scores: np.array,
                 boxes: np.array,
                 label_map: Dict = None,
                 score_threshold=0.8) -> io.BytesIO:
    """
    Generic bounding box plotting, inspired from detr implementation.

    Returns binary representation of the image with bounding box drawn, Use
    `Image.open` to render the image.
    """
    label_map = label_map or config.ID_TO_LABEL
    plt.figure(figsize=(16, 10))
    plt.imshow(pil_img)
    plt.axis('off')
    ax = plt.gca()

    keep = scores >= score_threshold
    scores = scores[keep]
    boxes = boxes[keep]
    classes = classes[keep]

    for cl_id, score, (xmin, ymin, xmax, ymax), c in zip(classes,
                                                         scores,
                                                         boxes.tolist(),
                                                         COLORS * 100):

        ax.add_patch(plt.Rectangle((xmin, ymin), xmax - xmin, ymax - ymin,
                                   fill=False, color=c, linewidth=3))
        text = f'{label_map[cl_id]}: {score:0.2f}'
        ax.text(xmin, ymin, text, fontsize=15,
                bbox=dict(facecolor='yellow', alpha=0.5))

    img_buf = io.BytesIO()
    plt.savefig(img_buf, format="png")
    img_buf.seek(0)
    return img_buf


def load_od_instance():
    """
    Load the object detection instance from class_path
    """
    class_path = config.MODEL_REGISTRY[config.ACTIVE_MODEL_NAME]
    p_split = class_path.split(".")
    module_path, class_name = ".".join(p_split[:-1]), p_split[-1]
    module = import_module(module_path)
    od_obj = getattr(module, class_name)()
    return od_obj
