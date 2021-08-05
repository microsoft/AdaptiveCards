"""Module responsible for grouping the related row of elements and to it's
respective columns"""
from multiprocessing import Process, Queue
from typing import List, Dict

# pylint: disable=relative-beyond-top-level
import pandas as pd
from PIL import Image
from mystique.extract_properties import CollectProperties

from .container_group import ContainerGroup
from .ds_helper import DsHelper, ContainerDetailTemplate
from .objects_group import RowColumnGrouping


def get_layout_structure(predicted_objects: List, queue=None) -> List:
    """
    method handles the hierarchical layout generating
    @param predicted_objects: detected list of design objects from the model
    @param queue: Queue object of the calling process
    as a part of multi-process queue
    @return: generated hierarchical card layout
    """
    card_layout = []
    # group row and columns
    # sorting the design objects y way
    predicted_objects = [
        value
        for _, value in sorted(
            zip(
                pd.DataFrame(predicted_objects).to_dict(orient="list")["ymin"],
                predicted_objects,
            ),
            key=lambda value: value[0],
        )
    ]
    row_column_group = RowColumnGroup()
    card_layout = row_column_group.row_column_grouping(
        predicted_objects, card_layout
    )
    # merge items to containers
    container_group = ContainerGroup()
    card_layout = container_group.merge_items(card_layout)
    if queue:
        queue.put(card_layout)
    return card_layout


def generate_card_layout_multi(
    predicted_objects: List, image: Image, predict_card_object=None
) -> RowColumnGrouping:
    """
    Performs the property extraction and hierarchical layout structuring
    in parallel and merges both on completion and returns the card layout
    with the spatial and property details.
    @param predicted_objects: List of extracted design objects
    @param image: input design image
    @param predict_card_object: PredictCard object
    @return: card layout with the primitive properties merged
    """
    queue1 = Queue()
    queue2 = Queue()
    try:
        process1 = Process(
            target=predict_card_object.get_object_properties,
            args=(
                predicted_objects["objects"],
                image,
                queue1,
            ),
        )
        process2 = Process(
            target=get_layout_structure,
            args=(
                predicted_objects["objects"],
                queue2,
            ),
        )
        process1.start()
        process2.start()

        properties = queue1.get()
        card_layout = queue2.get()

        process1.join()
        process2.join()
        # merge the card layout and extracted properties
        ds_helper = DsHelper()
        container_detail_object = ContainerDetailTemplate()
        ds_helper.merge_properties(
            properties, card_layout, container_detail_object
        )
        return card_layout
    except Exception:  # pylint: disable=broad-except
        return None


def generate_card_layout_seq(
    predicted_objects: List, image: Image, predict_card_object=None
) -> List[Dict]:
    """
    Performs the property extraction and hierarchical layout structuring
    in a sequential way and merges both on completion and returns the card
    layout with the spatial and property details.
    @param predicted_objects: List of extracted design objects
    @param image: input design image
    @param predict_card_object: PredictCard object
    @return: card layout with the primitive properties merged
    """

    card_layout = get_layout_structure(predicted_objects["objects"])
    properties = predict_card_object.get_object_properties(
        predicted_objects["objects"], image
    )
    # merge the card layout and extracted properties
    ds_helper = DsHelper()
    container_detail_object = ContainerDetailTemplate()
    ds_helper.merge_properties(properties, card_layout, container_detail_object)
    return card_layout


# pylint: disable=too-few-public-methods
class RowColumnGroup:
    """
    Groups the predicted design elements into it's related rows and columns
    and generates a hiearchical data structure of grouped elements
    i.e into a column-set container as per adaptive card's notation
    """

    same_iteration = False

    def __init__(self):
        self.collect_properties = CollectProperties()
        self.ds_helper = DsHelper()
        self.columns_grouping = RowColumnGrouping()
        self.ds_template = DsHelper()

    # pylint: disable=inconsistent-return-statements
    def _add_rows(
        self, column_set: Dict, card_layout: List[Dict]
    ) -> [None, List[Dict]]:
        """
        Add the grouped rows to the card layout and update the row's
        new coordinates.
        :param column_set: List of Row elements
        :param card_layout: Design structure layout
        :return: Collected columns if any
        """
        if len(column_set["objects"]) == 1:
            self.ds_template.add_element_to_ds(
                "item", card_layout, element=column_set["objects"][0]
            )
        elif len(column_set["objects"]) > 1:
            # sort x wise for columns grouping
            column_set["objects"] = [
                value
                for _, value in sorted(
                    zip(
                        pd.DataFrame(column_set["objects"]).to_dict(
                            orient="list"
                        )["xmin"],
                        column_set["objects"],
                    ),
                    key=lambda value: value[0],
                )
            ]
            columns = self.columns_grouping.object_grouping(
                column_set["objects"], self.columns_grouping.column_condition
            )

            return columns

    def _add_columns(
        self,
        columns: List[Dict],
        card_layout: List[Dict],
        column_set_coords=None,
    ) -> None:
        """
        Iterate and add the column and column items and update the column's
        new coordinates.
        @param columns: List of columns with column items
        @param column_set_coords: list of coordinates for the row
        @param card_layout: Design structure layout
        """
        self.ds_template.add_element_to_ds(
            "row", card_layout, coords=column_set_coords
        )
        row_counter = len(card_layout) - 1
        for column in columns:
            row_columns = card_layout[row_counter]["row"]
            self.ds_template.add_element_to_ds(
                "column", row_columns, coords=column["coordinates"]
            )
            column_counter = len(row_columns) - 1
            column["objects"] = [
                value
                for _, value in sorted(
                    zip(
                        pd.DataFrame(column["objects"]).to_dict(orient="list")[
                            "ymin"
                        ],
                        column["objects"],
                    ),
                    key=lambda value: value[0],
                )
            ]
            self.row_column_grouping(
                column["objects"],
                row_columns[column_counter]["column"]["items"],
                column_coords=column["coordinates"],
            )
            row_counter = len(card_layout) - 1

    def row_column_grouping(
        self, design_objects, card_layout: List[Dict], column_coords=None
    ) -> List[Dict]:
        """
        Group the detected design elements recursively
        into columns and column_sets and individual objects, considering each
        columns as smallest unit [i.e. a separate card hierarchy].
        @param design_objects: list of detected design objects
        @param card_layout: layout data structure
        @param column_coords: list of column coordinates
        @return: The grouped and updated card layout structure
        """
        columns_grouping = RowColumnGrouping()
        column_sets = columns_grouping.object_grouping(
            design_objects, columns_grouping.row_condition
        )
        for column_set in column_sets:
            columns = self._add_rows(column_set, card_layout)
            if (
                columns
                and column_coords
                and len(columns) == 1
                and columns[0]["coordinates"] == column_coords
            ):
                for item in columns[0]["objects"]:
                    self.ds_template.add_element_to_ds(
                        "item", card_layout, element=item
                    )
            elif columns:
                self._add_columns(
                    columns, card_layout, column_set["coordinates"]
                )

        return card_layout
