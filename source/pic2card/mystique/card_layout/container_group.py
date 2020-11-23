"""Module responsible for merging the same type items into it's respective
containers like image-set[images], choice-set[radio-buttons]. This merging
criteria is checked for both root level and column level elements """
from typing import List, Dict, Union

from .objects_group import ChoicesetGrouping
from .objects_group import ImageGrouping
from .ds_helper import DsHelper, ContainerTemplate


class ContainerGroup:
    """
    Helps in grouping a set of similar design elements inside a column of
    or in the root level of the card layout design
    """

    def collect_items_for_container(self, card_layout: List[Dict],
                                    object_class: int) -> [List, List]:
        """
        Gets the list of individual design items of a given type of container
        from the passed layout structure.
        @param card_layout: Container of design elements
        @param object_class: type of the design elements to be returned

        @return: The list design elements of given type and the list of
                 other elements inside the passed container
        """
        items = []
        for design_object in card_layout:
            if design_object.get("class", 0) == object_class:
                items.append(design_object)
        remaining_items = [design_object for design_object in card_layout
                           if design_object not in items]
        return items, remaining_items

    def add_merged_items(self, design_items: List[Dict],
                         card_layout: List[Dict],
                         object_type: str,
                         grouping_object: Union[ImageGrouping,
                                                ChoicesetGrouping],
                         grouping_condition: bool,
                         order_key: int) -> List[Dict]:
        """
        Returns the grouped layout structure for the given grouping object type
        @param design_items: list of design items to be grouped.
        @param card_layout: the container structure where the design
                                 elements needs to be grouped
        @param object_type: type of grouping
        @param grouping_object: grouping logic object
        @param grouping_condition: grouping condition for the given type
        @param order_key: positional key for the container by which it has to
                          be sorted [ x-way or y-way ]
        @return: The new layout structure after grouping
        """

        container_items = grouping_object.object_grouping(design_items,
                                                          grouping_condition)
        ds_template = DsHelper()
        for items in container_items:
            if len(items) > 1:
                sorted_items = []
                for item in items:
                    if items.count(item) == 1:
                        sorted_items.append(item)
                    elif items.count(item) > 1 and item not in sorted_items:
                        sorted_items.append(item)
                items = sorted_items
                ds_template.add_element_to_ds(object_type, card_layout)
                coordinates = []
                key = [key for key, values in
                       card_layout[-1][object_type].items()
                       if isinstance(values, list)][0]
                for item in items:
                    card_layout[-1][object_type][key].append(item)
                    coordinates.append(item.get("coordinates", []))

                container_coords = [c.get("coordinates")
                                    for c in card_layout[-1][object_type][key]]
                card_layout[-1][
                    "coordinates"] = ds_template.build_container_coordinates(
                        container_coords)
                order_values = [c[order_key] for c in coordinates]
                card_layout[-1][object_type][key] = [
                    value for _, value in sorted(
                        zip(order_values, card_layout[-1][object_type][key]),
                        key=lambda value: value[0])]

                card_layout = [item for item in
                               card_layout if item not in items]
        return card_layout

    def merge_column_items(self, card_layout: List[Dict],
                           object_class: int,
                           grouping_type: str,
                           grouping_object: Union[ImageGrouping,
                                                  ChoicesetGrouping],
                           grouping_condition: bool,
                           order_key: int) -> None:
        """
        Calls the object grouping for list of design element inside a particular
        column.
        @param card_layout: the generated layout structure
        @param object_class: The class value of the grouping container
        @param grouping_type: The name of the container type
        @param grouping_object: The object of the respective grouping class
        @param grouping_condition: The condition needed for the respective
                                   container grouping
        @param order_key:positional key for the container by which it has to
                          be sorted [ x-way or y-way ]
        """

        for row_counter, design_object in enumerate(card_layout):
            if design_object.get("object") == "columnset":
                columns = design_object.get("row", [])
                for column_counter, column_item in enumerate(columns):
                    items, remaining_items = self.collect_items_for_container(
                        column_item.get("column", {}).get("items", []),
                        object_class)
                    remaining_items = [remaining_item
                                       for remaining_item in remaining_items
                                       if design_object.get("object",
                                                            "") == "columnset"]

                    row_columns = card_layout[row_counter]["row"]
                    card_layout[row_counter]["row"][column_counter]["column"][
                        "items"] = self.add_merged_items(
                            items,
                            row_columns[column_counter]["column"]["items"],
                            grouping_type, grouping_object,
                            grouping_condition,
                            order_key)
                    column_y_minimums = [c.get("coordinates")[1]
                                         for c in row_columns[column_counter][
                                             "column"]["items"]]
                    card_layout[row_counter]["row"][
                        column_counter]["column"]["items"] = [
                            value for _, value in sorted(
                                zip(column_y_minimums,
                                    row_columns[column_counter]["column"][
                                        "items"]),
                                key=lambda value: value[0])]

                    if remaining_items:
                        self.merge_column_items(
                            row_columns[column_counter]["column"]["items"],
                            object_class,
                            grouping_type,
                            grouping_object,
                            grouping_condition,
                            order_key)

    def merge_items(self, card_layout: List[Dict]) -> List[Dict]:
        """
        Calls the object grouping for list of design element in the root level
        of the design.
        @param card_layout: the generated layout structure
        @return: Grouped layout structure
        """
        # get the list of container names for merging the items
        container_items = DsHelper.MERGING_CONTAINERS_LIST
        container_template = ContainerTemplate()
        for container_name in container_items:
            container_template_object = getattr(container_template,
                                                container_name)
            card_layout = container_template_object(card_layout, self)

        return card_layout
