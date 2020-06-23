"""
Generate mAP score for given model, use the given test dataset with labels.

We are using the mAP tool developed by
https://github.com/Cartucho/mAP, This command generate the ground
truth and predicted values in a files that are compatible to the
mAP command.

NOTE: This project isn't including that command, use it externally.
"""
import os
import click
import pathlib
import numpy as np
import pandas as pd
from mystique.initial_setups import set_graph_and_tensors
from mystique.detect_objects import ObjectDetection
from mystique.utils import xml_to_csv


@click.command()
@click.option(
    "--test-dir",
    help="Test image directory, it should be labelmg generated directory",
    required=True)
@click.option(
    "--ground-truth-dir",
    help="Export the ground trught labels to this dir, use the same img name",
    required=True)
@click.option(
    "--pred-truth-dir",
    help="Export the ground trught labels to this dir, use the same img name",
    required=True)
@click.option(
    "--model-fw",
    type=click.Choice(["tf", "pytorch"], case_sensitive=False),
    help="Model framework tf/pytorch",
    required=True)
@click.option(
    "--bbox-min-score",
    help="Minimum bbox score from the model to be considered.",
    default=0.9,
    required=False)
@click.option(
    "--image-pipeline",
    help="Use the custom image pipeline for image coordinate extraction.",
    is_flag=True)
def generate_map(test_dir, ground_truth_dir, pred_truth_dir,
                 model_fw,
                 bbox_min_score,
                 image_pipeline):
    # columns used: filename, xmin, ymin, xmax, ymax
    gt_dir = pathlib.Path(ground_truth_dir)
    pd_dir = pathlib.Path(pred_truth_dir)
    gt_dir.mkdir(parents=True, exist_ok=True)
    pd_dir.mkdir(parents=True, exist_ok=True)

    not os.path.exists(ground_truth_dir) and os.mkdir(ground_truth_dir)
    not os.path.exists(pred_truth_dir) and os.mkdir(pred_truth_dir)

    if model_fw == "tf":
        object_detection = ObjectDetection(*set_graph_and_tensors())
    elif model_fw == "pytorch":
        from mystique.detect_objects_pth import PtObjectDetection
        object_detection = PtObjectDetection()

    data_df = xml_to_csv(test_dir)
    images = np.unique(data_df['filename'].tolist())

    for img_name in images:
        img_path = f"{test_dir}/{img_name}"
        classes, scores, boxes = object_detection.get_bboxes(img_path,
                                                             image_pipeline)

        # import pdb; pdb.set_trace()
        preds = []
        pred_iter = zip(classes, scores, boxes)
        for pred in pred_iter:
            label, bbox, score = pred
            if score > bbox_min_score:
                preds.append(
                    (label, score, bbox[0], bbox[1], bbox[2], bbox[3])
                )

        columns = ['class', 'score', 'xmin', 'ymin', 'xmax', 'ymax']
        fname = img_name.split('.')[0]
        pd.DataFrame.from_records(preds, columns=columns).to_csv(
            f"{pd_dir}/{fname}.txt", header=False, sep=" ", index=False
        )
        # Save the ground truth labels.
        columns = ['class', 'xmin', 'ymin', 'xmax', 'ymax']
        data_df[data_df.filename == img_name][columns].to_csv(
            f"{gt_dir}/{fname}.txt",
            header=False, sep=" ", index=False
        )


if __name__ == "__main__":
    generate_map()
