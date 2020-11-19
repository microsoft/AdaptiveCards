"""Module responsible for grouping the related row of elements and to it's
respective columns"""
from typing import List, Dict
from multiprocessing import Process, Queue
from PIL import Image

from mystique.extract_properties import CollectProperties
from .container_group import ContainerGroup
from .objects_group import RowColumnGrouping
from .ds_helper import DsHelper, ContainerDetailTemplate


def get_layout_structure(json_objects: List, queue: Queue) -> None:
    """
    method handles the hierarchical layout generating
    @param json_objects: detected list of design objects from the model
    @param queue: Queue object of the calling process
    @return: generated hierarchical card layout
    """
    card_layout = []
    # group row and columns
    row_column_group = RowColumnGroup()
    row_column_group.row_column_grouping(json_objects, card_layout)
    # merge items to containers
    container_group = ContainerGroup()
    card_layout = container_group.merge_items(card_layout)
    if queue:
        queue.put(card_layout)


def generate_card_layout(json_objects: List,
                         image: Image,
                         predict_card_object=None) -> RowColumnGrouping:
    """
    Performs the property extraction and hierarchical layout structuring
    in parallel and merges both on completion and returns the card layout
    with the spatial and property details.
    @param json_objects: List of extracted design objects
    @param image: input design image
    @param predict_card_object: PredictCard object
    @return: card layout with the primitive properties merged
    """
    queue1 = Queue()
    queue2 = Queue()
    try:
        process1 = Process(target=predict_card_object.get_object_properties,
                           args=(json_objects["objects"], image, queue1,))
        process2 = Process(target=get_layout_structure,
                           args=(json_objects["objects"], queue2,))
        process1.start()
        process2.start()

        properties = queue1.get()
        card_layout = queue2.get()

        process1.join()
        process2.join()
        # merge the card layout and extracted properties
        ds_helper = DsHelper()
        container_detail_object = ContainerDetailTemplate()
        ds_helper.merge_properties(properties, card_layout,
                                   container_detail_object)
        return card_layout
    except Exception:
        return None


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

    def _check_same_iteration(self, previous: List[Dict],
                              current: List[Dict]) -> bool:
        """
        Checks the if the previous and current grouped column have same
        objects or not.
        @param previous: Previous column objects
        @param current: Current column objects
        @return: Boolean value of the check
        """
        if not previous:
            return False
        same = True
        for item in current:
            if item not in previous:
                same = False
                break
        return same

    def row_column_grouping(self, design_objects,
                            card_layout:
                            List[Dict],
                            previous_column=None
                            ) -> None:
        """
        Group the detected design elements recursively
        into columns and column_sets and individual objects, considering each
        columns as smallest unit [i.e. a separate card hierarchy].
        @param design_objects: list of detected design objects
        @param card_layout: layout data structure
        @param previous_column: previous grouped column objects to check for
                                same grouping happening repeatedly
        """
        columns_grouping = RowColumnGrouping()
        column_sets = columns_grouping.object_grouping(
            design_objects, columns_grouping.row_condition)
        ds_template = DsHelper()
        for column_set in column_sets:
            if len(column_set) == 1:
                ds_template.add_element_to_ds("item", card_layout,
                                              element=column_set[0])
            if len(column_set) > 1:
                columns = columns_grouping.object_grouping(
                    column_set, columns_grouping.column_condition)
                ds_template.add_element_to_ds("row", card_layout)
                row_counter = len(card_layout) - 1
                for column in columns:
                    if len(column) == 1:
                        row_columns = card_layout[row_counter]["row"]
                        ds_template.add_element_to_ds("column", row_columns)
                        ds_template.add_element_to_ds(
                            "item",
                            row_columns[-1]["column"]["items"],
                            element=column[0])
                        card_layout[row_counter]["row"][-1][
                            "coordinates"] = column[0].get("coords")
                    else:
                        row_columns = card_layout[row_counter]["row"]
                        if not self._check_same_iteration(previous_column,
                                                          column):
                            ds_template.add_element_to_ds("column", row_columns)
                            column_counter = len(row_columns) - 1
                            self.row_column_grouping(
                                column,
                                row_columns[column_counter]["column"]["items"],
                                previous_column=column)
                            if self.same_iteration:
                                card_layout[row_counter][
                                    "row"][column_counter]["column"][
                                        "items"] = row_columns[column_counter][
                                            "column"]["items"][:-1]
                                for item in column:
                                    ds_template.add_element_to_ds(
                                        "item",
                                        row_columns[column_counter]
                                        ["column"].get("items", []),
                                        element=item)

                                self.same_iteration = False

                            coordinates = [c.get("coordinates") for c in
                                           row_columns[column_counter]["column"]
                                           ["items"]]
                            card_layout[row_counter]["row"][column_counter][
                                "coordinates"] = \
                                ds_template.build_container_coordinates(
                                    coordinates)

                            column_y_minimums = [c.get("coordinates")[1]
                                                 for c in row_columns[
                                                     column_counter]["column"]
                                                 ["items"]]

                            card_layout[row_counter]["row"][
                                column_counter]["column"]["items"] = [
                                    value for _, value in sorted(
                                        zip(column_y_minimums,
                                            card_layout[row_counter]["row"][
                                                column_counter]["column"]
                                            ["items"]),
                                        key=lambda value: value[0])]
                        else:
                            self.same_iteration = True

                    if not self.same_iteration:
                        coordinates = [c.get("coordinates") for c in
                                       card_layout[row_counter]["row"]]
                        card_layout[row_counter]["coordinates"] = \
                            ds_template.build_container_coordinates(
                                coordinates)
                        row_counter = len(card_layout) - 1
                        row_x_minimums = [c.get("coordinates")[0] for c in
                                          card_layout[row_counter]["row"]]
                        card_layout[row_counter]["row"] = [
                            value for _, value in sorted(
                                zip(row_x_minimums,
                                    card_layout[row_counter]["row"]),
                                key=lambda value: value[0])]
