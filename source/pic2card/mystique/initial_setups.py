""" Module for setting up the tensorflow graphs and tensors for faster 
    rcnn object detection
"""
import os

import tensorflow as tf
from object_detection.utils import label_map_util

model_path = os.path.join(os.path.dirname(__file__),
                          "../model/frozen_inference_graph.pb")
label_path = os.path.join(os.path.dirname(__file__),
                          "training/object-detection.pbtxt")


def set_graph_and_tensors(tensors=("detection_boxes", "detection_scores",
                                   "detection_classes")):
    """
    setting up tf graphs and tensors using the trained inference graph

    @param tensors: required tensors from inference graph

    :return: detection_graph, category_index, tensor_dict
    """
    tensor_dict = dict()
    detection_graph = tf.Graph ()
    #setting up default graph with graphs from inference graph
    with detection_graph.as_default() as default_graph:
        od_graph_def = tf.compat.v1.GraphDef()
        with tf.compat.v1.gfile.GFile(model_path, "rb") as fid:
            serialized_graph = fid.read()
            od_graph_def.ParseFromString(serialized_graph)
            tf.import_graph_def(od_graph_def, name="")
        ops = default_graph.get_operations()
        all_tensor_names = {output.name for op in ops for output in op.outputs}
        for tensor in tensors:
            tmp_tensor_name = tensor + ":0"
            if tmp_tensor_name in all_tensor_names:
                tensor_dict[tensor] = default_graph.get_tensor_by_name(
                    tmp_tensor_name
                )

    category_index = label_map_util.create_category_index_from_labelmap(
        label_path, use_display_name=True)

    return detection_graph, category_index, tensor_dict
