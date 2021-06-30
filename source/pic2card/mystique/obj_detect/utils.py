"""
Model specific utils, Tensorflow / Pytorch helpers
"""
from typing import List
import tensorflow as tf


def load_frozen_graph(
    frozen_model_path: str, input_nodes: List[str], output_nodes: List[str]
):
    """
    Load the frozen graph for inference.

    The input and output nodes are the tensorflow graph node names in the
    exported saved model or frozen graph
    """
    with tf.io.gfile.GFile(frozen_model_path, "rb") as raw_f:
        graph_def = tf.compat.v1.GraphDef()
        _ = graph_def.ParseFromString(raw_f.read())

    frozen_func = wrap_frozen_graph(
        graph_def=graph_def,
        inputs=input_nodes,
        outputs=output_nodes,
    )
    return frozen_func


def wrap_frozen_graph(graph_def, inputs, outputs):
    """
    Make the frozen graph ready for inference with required input and
    output graph nodes.
    """

    def _imports_graph_def():
        tf.compat.v1.import_graph_def(graph_def, name="")

    wrapped_import = tf.compat.v1.wrap_function(_imports_graph_def, [])
    import_graph = wrapped_import.graph
    return wrapped_import.prune(
        tf.nest.map_structure(import_graph.as_graph_element, inputs),
        tf.nest.map_structure(import_graph.as_graph_element, outputs),
    )
