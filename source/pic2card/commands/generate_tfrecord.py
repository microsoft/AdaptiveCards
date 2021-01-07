"""
Generates tensorflow records from the label mapped train and test csv
files.

Usage:
  # From tensorflow/models/
  # Create train data:
  python generate_tfrecord.py --csv_input=data/train_labels.csv \
      --output_path=train.record

  # Create test data:
  python generate_tfrecord.py --csv_input=data/test_labels.csv \
      --output_path=test.record
"""
from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import io
import os
from collections import namedtuple

import pandas as pd
import tensorflow as tf
from PIL import Image
from object_detection.utils import dataset_util

flags = tf.app.flags
flags.DEFINE_string("csv_input", "", "Path to the CSV input")
flags.DEFINE_string("output_path", "", "Path to output TFRecord")
flags.DEFINE_string("image_dir", "", "Path to images")
FLAGS = flags.FLAGS


# TO-DO replace this with label map
def class_text_to_int(row_label):
    """
    Function to define the class lables

    @param row_label: integer class value from the csv
    """
    if row_label == "textbox":
        return 1
    if row_label == "radio_button":
        return 2
    if row_label == "checkbox":
        return 3
    if row_label == "actionset":
        return 4
    else:
        return 0


def create_tf_example(group, path):
    """
    Generate tf recods by parsing the xml with 
    the properites and labels.

    @param group: filename group
    @param path: images path

    @return: the tf record
    """
    name_filename = group.filename[:group.filename.find(".")] + ".png"
    with tf.gfile.GFile(os.path.join(path, "{}".format(name_filename)),
                        "rb") as fid:
        encoded_jpg = fid.read()
    encoded_jpg_io = io.BytesIO(encoded_jpg)
    image = Image.open(encoded_jpg_io)
    width, height = image.size

    filename = group.filename.encode("utf8")
    image_format = b"png"
    xmins = []
    xmaxs = []
    ymins = []
    ymaxs = []
    classes_text = []
    classes = []

    for index, row in group.object.iterrows():
        xmins.append(row["xmin"] / width)
        xmaxs.append(row["xmax"] / width)
        ymins.append(row["ymin"] / height)
        ymaxs.append(row["ymax"] / height)
        classes_text.append(row["class"].encode("utf8"))
        classes.append(class_text_to_int(row["class"]))

    tf_example = tf.train.Example(features=tf.train.Features(feature={
        "image/height": dataset_util.int64_feature(height),
        "image/width": dataset_util.int64_feature(width),
        "image/filename": dataset_util.bytes_feature(filename),
        "image/source_id": dataset_util.bytes_feature(filename),
        "image/encoded": dataset_util.bytes_feature(encoded_jpg),
        "image/format": dataset_util.bytes_feature(image_format),
        "image/object/bbox/xmin": dataset_util.float_list_feature(xmins),
        "image/object/bbox/xmax": dataset_util.float_list_feature(xmaxs),
        "image/object/bbox/ymin": dataset_util.float_list_feature(ymins),
        "image/object/bbox/ymax": dataset_util.float_list_feature(ymaxs),
        "image/object/class/text": dataset_util.bytes_list_feature(
            classes_text),
        "image/object/class/label": dataset_util.int64_list_feature(
            classes),
    }))
    return tf_example


def main(_):
    """
    Writes the generated tensorflow records into the specified ouput
    directory
    """

    writer = tf.python_io.TFRecordWriter(FLAGS.output_path)
    path = os.path.join(FLAGS.image_dir)
    examples = pd.read_csv(FLAGS.csv_input)
    data = namedtuple("data", ["filename", "object"])
    gb = examples.groupby("filename")
    grouped = [data(filename, gb.get_group(x))
               for filename, x in zip(gb.groups.keys(), gb.groups)]
    for group in grouped:
        tf_example = create_tf_example(group, path)
        writer.write(tf_example.SerializeToString())

    writer.close()
    output_path = os.path.join(os.getcwd(), FLAGS.output_path)
    print("Successfully created the TFRecords: {}".format(output_path))


if __name__ == "__main__":
    tf.app.run()
