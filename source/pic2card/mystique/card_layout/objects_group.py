"""Module for grouping deisgn objects into different containers"""
from typing import List, Dict, Callable


class GroupObjects:
    """
    Handles the grouping of given list of objects for any set conditions that
    is passed.
    """

    # pylint: disable=no-self-use
    def _update_coords(
        self, previous_coords: List, current_coords: List
    ) -> List:
        """
        Update the container/group coordinates by extending the previous
        coords with the current one by taking min(xmin and ymin) and max(
        xmax,yamx).
        @param previous_coords: Group coodinates
        @param current_coords: Current design object coordinates
        @return: Updated coordinates for the group
        """

        return [
            min(previous_coords[0], current_coords[0]),
            min(previous_coords[1], current_coords[1]),
            max(previous_coords[2], current_coords[2]),
            max(previous_coords[3], current_coords[3]),
        ]

    # pylint: disable=no-self-use
    def update_group_objects(
        self, design_objects: Dict, coordinates=None
    ) -> Dict:
        """
        Build the design group element based on the passed set of design objects
        and coordinates.
        @param design_objects: set of design objects to be added to the group
        @param coordinates: list of coordinates to be added to the group
        @return: Build group element
        """
        if coordinates:
            return {"objects": design_objects, "coordinates": coordinates}
        return {
            "objects": [design_objects],
            "coordinates": list(design_objects.get("coordinates")),
        }

    def object_grouping(
        self,
        design_objects: List[Dict],
        condition: Callable[[List, List], bool],
    ) -> List[Dict]:
        """
        Groups the given List of design objects for the any given condition.
        Traverse through the x/y based sorted list of design objects and
        groups them based on the passed conditions and while grouping
        updates the grouped list of object's coordinates for each element
        addition.
        @param design_objects: objects
        @param condition: Grouping condition function
        @return: Grouped list of design objects.
        """
        groups = []
        for _, design_object in enumerate(
            design_objects
        ):  # pylint: disable=unused-variable
            if not groups:
                groups.append(self.update_group_objects(design_object))
            if groups:
                bbox_1 = list(groups[-1]["coordinates"])
                bbox_2 = list(design_object["coordinates"])
                object_names = [
                    obj.get("object") for obj in groups[-1].get("objects")
                ]
                if "image" in object_names:
                    bbox_1.append("image")
                else:
                    bbox_1.append("group")
                bbox_2.append(design_object.get("object", ""))

                if condition(bbox_1, bbox_2):
                    objects = groups[-1].get("objects")
                    if design_object not in objects:
                        objects.append(design_object)
                        coordinates = self._update_coords(bbox_1, bbox_2)
                        groups[-1].update(
                            self.update_group_objects(
                                objects, coordinates=coordinates
                            )
                        )
                else:

                    if design_object not in groups[-1].get("objects"):
                        groups.append(self.update_group_objects(design_object))
        return groups


class RowColumnGrouping(GroupObjects):
    """
    Groups the design objects into different columns of a columnset
    """

    def __init__(self, card_arrange=None):
        self.card_arrange = card_arrange

    # pylint: disable=no-self-use
    def row_condition(self, bbox_1: List, bbox_2: List, threshold=0.3) -> bool:
        """
        Simplified row grouping condition
        @param bbox_1: bounding box 1
        @param bbox_2: bounding box2
        @param threshold: cut-off threshold
        @return: boolean value for row candidates
        """
        _, y1_, _, y2_, _ = bbox_1
        _, y11, _, y22, _ = bbox_2
        intersection = (min(y2_, y22) - max(y1_, y11)) / min(
            [(y2_ - y1_), (y22 - y11)]
        )
        return intersection >= threshold

    # pylint: disable=no-self-use
    def column_condition(
        self, bbox_1: List, bbox_2: List, threshold=0.3
    ) -> bool:
        """
        Simplifies column grouping condition
        @param bbox_1: bounding box 1
        @param bbox_2: bounding box2
        @param threshold: cut-off threshold
        @return: boolean value for column candidates
        """
        x1_, _, x2_, _, _ = bbox_1
        x11, _, x22, _, _ = bbox_2

        intersection = (min(x2_, x22) - max(x1_, x11)) / min(
            [(x2_ - x1_), (x22 - x11)]
        )

        return intersection >= threshold


class ChoicesetGrouping(GroupObjects):
    """
    Groups the radiobutton objects of the adaptive card objects into a
    choiceset or individual radiobuttion objects.
    """

    def __init__(self, card_arrange=None):
        self.card_arrange = card_arrange

    # pylint: disable=no-self-use
    def choiceset_condition(
        self, bbox_1: List, bbox_2: List, threshold=0.3
    ) -> bool:
        """
        Returns a boolean value to group the radiobutton objects into a
        choice-set.
        @param bbox_1: radiobutton object one coordinates
        @param bbox_2: radiobutton object two coordinates
        @param threshold: cut-off threshold
        @return: boolean value
        """
        x1_, _, x2_, _, _ = bbox_1
        x11, _, x22, _, _ = bbox_2

        intersection = (min(x2_, x22) - max(x1_, x11)) / min(
            [(x2_ - x1_), (x22 - x11)]
        )
        return intersection >= threshold
