"""Module responsible for merging the same type items into it's respective
containers like image-set[images], choice-set[radio-buttons]. This merging
criteria is checked for both root level and column level elements """
from operator import itemgetter
from typing import List, Dict, Union, Tuple

# pylint: disable=relative-beyond-top-level
import pandas as pd

from .ds_helper import DsHelper, ContainerTemplate, ContainerDetailTemplate


class ContainerGroup:
    """
    Helps in grouping a set of similar design elements inside a column of
    or in the root level of the card layout design
    """

    container_detail = ContainerDetailTemplate()
    merged_layout = []

    # pylint: disable=no-self-use
    def collect_items_for_container(
        self, card_layout: List[Dict], object_class: int
    ) -> [List, List]:
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
        remaining_items = [
            design_object
            for design_object in card_layout
            if design_object not in items
        ]
        return items, remaining_items

    def add_merged_items(
        self, design_items: List[Dict], card_layout: List[Dict], payload: Dict
    ) -> List[Dict]:
        """
        Returns the grouped layout structure for the given grouping object type
        @param design_items: list of design items to be grouped.
        @param card_layout: the container structure where the design
                                 elements needs to be grouped
        @param payload: merging payload
        @return: The new layout structure after grouping
        """
        object_type = payload["grouping_type"]
        grouping_object = payload["grouping_object"]
        grouping_condition = payload["grouping_condition"]

        container_items = grouping_object.object_grouping(
            design_items, grouping_condition
        )
        ds_template = DsHelper()
        for items in container_items:
            if len(items["objects"]) > 1:
                ds_template.add_element_to_ds(
                    object_type, card_layout, coords=items["coordinates"]
                )
                coordinates = []
                sub_layout = card_layout[-1][object_type]
                sub_layout_values = sub_layout.values()

                key = list(sub_layout)[
                    list(sub_layout_values).index(
                        list(
                            filter(
                                lambda ele: isinstance(ele, list),
                                sub_layout_values,
                            )
                        )[0]
                    )
                ]
                for item in items["objects"]:
                    card_layout[-1][object_type][key].append(item)
                    coordinates.append(item.get("coordinates", []))

                card_layout = [
                    item for item in card_layout if item not in items["objects"]
                ]
        return card_layout

    def _column_items_to_merge(self, column_items: List, payload: Dict) -> List:
        """
        Iterate through the column items and merge the items with the passed
        object class as the respective container type.
        @param column_items: List of column items
        @param payload: Merging payload
        @return: List of updated column items
        """
        object_class = payload["object_class"]
        order_key = payload["order_key"]

        items, remaining_items = self.collect_items_for_container(
            column_items, object_class
        )
        if items:
            # order the container elements based on the order_key
            items = [
                value
                for _, value in sorted(
                    zip(
                        list(zip(*pd.DataFrame(items)["coordinates"]))[
                            order_key
                        ],
                        items,
                    ),
                    key=lambda value: value[0],
                )
            ]
        updated_column_items = self.add_merged_items(
            items, column_items, payload
        )
        if updated_column_items:
            updated_column_items = [
                value
                for _, value in sorted(
                    zip(
                        list(
                            zip(
                                *pd.DataFrame(updated_column_items)[
                                    "coordinates"
                                ]
                            )
                        )[1],
                        updated_column_items,
                    ),
                    key=lambda value: value[0],
                )
            ]
        if remaining_items:
            self.merge_column_items(updated_column_items, payload)
        return updated_column_items

    # pylint: disable=inconsistent-return-statements
    def merge_column_items(
        self, card_layout: List[Dict], payload: Dict
    ) -> Union[None, List]:
        """
        Calls the object grouping for list of design element inside a particular
        column.
        @param card_layout: the generated layout structure
        @param payload: merging payload
        @return: List of merged elements
        """
        if (
            isinstance(card_layout, dict)
            and card_layout.get("object", "") == "columnset"
        ):
            container_details_template_object = getattr(
                self.container_detail, card_layout.get("object", "")
            )
            columns = container_details_template_object(card_layout)
            self.merge_column_items(columns, payload)

        elif isinstance(card_layout, list):
            for design_obj in card_layout:
                self.merge_column_items(design_obj, payload)
            return self.merged_layout
        elif (
            isinstance(card_layout, dict)
            and card_layout.get("object", "") == "column"
        ):
            container_details_template_object = getattr(
                self.container_detail, card_layout.get("object", "")
            )
            column_items = container_details_template_object(card_layout)
            column_items = self._column_items_to_merge(column_items, payload)
            card_layout["column"]["items"] = column_items
            self.merged_layout.append(card_layout)
        else:
            self.merged_layout.append(card_layout)

    def _extract_image_data(self, design_object: Dict) -> Tuple[List, List]:
        """
        Extract the single element [image] info from the passed column-set
        design object
        @param design_object: any column-set design object
        @return: the extracted column-wise image data
        """
        imageset_data = []
        column_wise_imageset_data = []
        to_remove = []
        for ctr, column in enumerate(design_object["row"]):
            current_column_types = []
            current_column_data = []
            for item in column["column"]["items"]:
                current_column_types.append(item["object"])
                current_column_data.append(item)
            compare_column_types = []
            if ctr + 1 < len(design_object["row"]):
                compare_column_types = [
                    item["object"]
                    for item in design_object["row"][ctr + 1]["column"]["items"]
                ]
            elif ctr == len(design_object["row"]) - 1:
                compare_column_types = [
                    item["object"]
                    for item in design_object["row"][ctr - 1]["column"]["items"]
                ]

            if (
                len(set(current_column_types)) == 1
                and len(list(set(compare_column_types))) == 1
                and current_column_types[0]
                == compare_column_types[0]
                == "image"
            ):
                to_remove.append(ctr)
                imageset_data.extend(current_column_data)

            elif (
                len(set(current_column_types)) == 1
                and current_column_types[0] == "image"
            ):
                if ctr - 1 >= 0 and ctr - 1 in to_remove:
                    to_remove.append(ctr)
                    imageset_data.extend(current_column_data)

            if ctr not in to_remove:
                if imageset_data:
                    column_wise_imageset_data.append(imageset_data)
                else:
                    column_wise_imageset_data.append([])
        return imageset_data, column_wise_imageset_data

    def _update_column_wise_image_data(
        self, column_wise_imageset_data: List, design_object: Dict
    ) -> Dict:
        """
        Update the columns as image-sets having candidate image-set data.
        :param column_wise_imageset_data: List of column-wise candidate
                                          image-set data
        :param design_object: Column-set that needs updating
        :return: Updated column-set element
        """

        # If there's other elements in the column-set column as well
        update_element = {"object": "columnset", "row": []}
        counter = 0
        for data in column_wise_imageset_data:
            if not data and counter < len(design_object["row"]):
                # if it's any non image-set element extract it from the
                # design object's row
                update_element["row"].append(design_object["row"][counter])
                counter += 1
            else:
                # if it's a image-set column
                container_coords = list(map(itemgetter("coordinates"), data))
                ds_template = DsHelper()
                container_coords = ds_template.build_container_coordinates(
                    container_coords
                )
                # build image-set
                image_set = {
                    "imageset": {"items": data},
                    "object": "imageset",
                    "coordinates": container_coords,
                }
                # add image-set to the column
                update_element["row"].append(
                    {
                        "column": {"items": [image_set]},
                        "object": "column",
                        "coordinates": container_coords,
                    }
                )
        return update_element

    def _build_imageset(self, design_object: Dict) -> Dict:
        """
        Build the image-set from the passed column-set design object and
        return the updated column-set design element
        @param design_object: any column-set design element
        @return: updated column-set dict
        """
        # extract the image data from columns
        imageset_data, column_wise_imageset_data = self._extract_image_data(
            design_object
        )

        if not any(column_wise_imageset_data) and imageset_data:
            column_wise_imageset_data.append(imageset_data)

        # if the column-set has only columns of images, then change it to
        # image-set from the root level
        if not column_wise_imageset_data and imageset_data:
            container_coords = list(
                map(itemgetter("coordinates"), imageset_data)
            )
            ds_template = DsHelper()
            container_coords = ds_template.build_container_coordinates(
                container_coords
            )
            design_object = {
                "imageset": {"items": imageset_data},
                "object": "imageset",
                "coordinates": container_coords,
            }
        elif any(column_wise_imageset_data):
            update_element = self._update_column_wise_image_data(
                column_wise_imageset_data, design_object
            )

            if update_element["row"]:
                # build column-set coordinates
                container_coords = list(
                    map(itemgetter("coordinates"), update_element["row"])
                )
                ds_template = DsHelper()
                container_coords = ds_template.build_container_coordinates(
                    container_coords
                )
                update_element.update({"coordinates": container_coords})
                return update_element
        return design_object

    def _get_imageset_from_columns(
        self, card_layout: List, design_object: Dict
    ) -> None:
        """
        Traverse the card layout and from the column-set build image-set from
        continuous columns having only one design element - image.
        @param card_layout: final card layout after extracting
        @param design_object: design element while traversing
        """
        # pylint: disable=isinstance-second-argument-not-valid-type
        if (
            isinstance(design_object, Dict)
            and design_object.get("object", "") == "columnset"
        ):
            updated_object = self._build_imageset(design_object)
            if updated_object:
                card_layout.append(updated_object)
            else:
                card_layout.append(design_object)
        elif isinstance(design_object, list):
            for design_obj in design_object:
                self._get_imageset_from_columns(card_layout, design_obj)
        else:
            card_layout.append(design_object)

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
            container_template_object = getattr(
                container_template, container_name
            )
            card_layout = container_template_object(card_layout, self)
        # extract and update - image-set from the list of columns of any
        # column-set
        updated_card_layout = []
        self._get_imageset_from_columns(updated_card_layout, card_layout)
        if updated_card_layout:
            return updated_card_layout
        return card_layout
