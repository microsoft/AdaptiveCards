"""Module for grouping deisgn objects into different containers"""
from typing import List, Dict, Callable

from mystique import config


class GroupObjects:
    """
    Handles the grouping of given list of objects for any set conditions that
    is passed.
    """

    # pylint: disable=no-self-use
    def max_min_difference(
        self, bbox_1: List, bbox_2: List, min_way: int, max_way: int
    ) -> float:
        """
        Returns the ymax-ymin difference of the 2 deisgn objects

        @param bbox_1: design object one's coordinates
        @param bbox_2: design object two's coordinates
        @param min_way: x or y way minimum position
        @param max_way: x or y way maximum position
        @return: max-min difference ratios
        """
        mid_point1_y = abs(bbox_1[3] - bbox_1[1]) / 2 + bbox_1[1]
        mid_point1_x = abs(bbox_1[2] - bbox_1[0]) / 2 + bbox_1[0]

        mid_point2_y = abs(bbox_2[3] - bbox_2[1]) / 2 + bbox_2[1]
        mid_point2_x = abs(bbox_2[2] - bbox_2[0]) / 2 + bbox_2[0]

        mid_point_y = abs(mid_point1_y - mid_point2_y)
        mid_point_x = abs(mid_point1_x - mid_point2_x)

        mid_size = mid_point_y
        if min_way == 0:
            mid_size = mid_point_x
        if bbox_1[max_way] < bbox_2[min_way]:
            value = round(abs(bbox_2[min_way] - bbox_1[max_way]))
        else:
            value = round(abs(bbox_1[min_way] - bbox_2[max_way]))
        if mid_size > 0:
            return value / mid_size
        return 0

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
            "coordinates": design_objects.get(
                "coords", design_objects.get("coordinates")
            ),
        }

    def object_grouping(
        self,
        design_objects: List[Dict],
        condition: Callable[[List, List], bool],
    ) -> List[List[Dict]]:
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
                bbox_1 = list(groups[-1].get("coordinates"))
                bbox_2 = list(
                    design_object.get(
                        "coords", design_object.get("coordinates")
                    )
                )
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
        # TODO: this updated coordinates removal will be removed after the
        #  row-column grouping optimization works
        groups = [gr.get("objects") for gr in groups]
        return groups

    # pylint: disable=no-self-use, too-many-arguments
    def _check_intersection_over_range(
        self,
        bbox_1: List,
        bbox_2: List,
        axis: str,
        threshold=0.25,
        get_ratio=False,
    ) -> bool:
        """
        Check if any one of the bounding boxes is inclusive of another. i.e
        finding x or y range intersection between the bbox_1 and bbox_2
        The inclusive check has to satisfy 2 conditions:
        1. the iou min and max should be within any one of the 2 bounding boxes
        2. The intersection ratio should be greater than the threshold
        @param bbox_1: bounding box 1
        @param bbox_2: bounding box 2
        @param axis: the axis value - x or y
        @param threshold: The intersection cut-off ratio to
                          check inclusive
        @return: boolean value for the intersection condition
        """
        min_range, max_range = 0, 2
        if axis == "y":
            min_range, max_range = 1, 3
        iou_min = max(bbox_1[min_range], bbox_2[min_range])
        iou_max = min(bbox_1[max_range], bbox_2[max_range])
        iou_size = iou_max - iou_min

        range_size = None
        range1 = [bbox_1[min_range], bbox_1[max_range]]
        range2 = [bbox_2[min_range], bbox_2[max_range]]
        if (
            range1[0] <= iou_min <= range1[1]
            and range1[0] <= iou_max <= range1[1]
        ):
            range_size = range1[1] - range1[0]
        if (
            range2[0] <= iou_min <= range2[1]
            and range2[0] <= iou_max <= range2[1]
        ):
            range_size = range2[1] - range2[0]
        intersection_area_ratio = 0
        if ((bbox_1[2] - bbox_1[0]) * (bbox_1[3] - bbox_1[1])) <= (
            (bbox_2[2] - bbox_2[0]) * (bbox_2[3] - bbox_2[1])
        ):
            intersection_area_ratio = iou_size / (range1[1] - range1[0])

        else:
            intersection_area_ratio = iou_size / (range2[1] - range2[0])

        if get_ratio:
            return intersection_area_ratio

        if range_size and intersection_area_ratio >= threshold:
            return True
        return False


class RowColumnGrouping(GroupObjects):
    """
    Groups the design objects into different columns of a columnset
    """

    Y_MIN_THESHOLD = config.CONTAINER_GROUPING.get("ymin_difference", "")
    Y_THRESHOLD = config.CONTAINER_GROUPING.get("ymax_ymin_difference", "")
    X_THRESHOLD = config.CONTAINER_GROUPING.get("xmax_xmin_difference", "")

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

    Y_THRESHOLD = config.CONTAINER_GROUPING.get(
        "choiceset_ymax_ymin_difference"
    )
    Y_MIN_THRESHOLD = config.CONTAINER_GROUPING.get(
        "choiceset_y_min_difference"
    )

    def __init__(self, card_arrange=None):
        self.card_arrange = card_arrange

    def choiceset_condition(self, bbox_1: List, bbox_2: List) -> bool:
        """
        Returns a boolean value to group the radiobutton objects into a
        choice-set.
        @param bbox_1: radiobutton object one coordinates
        @param bbox_2: radiobutton object two coordinates
        @return: boolean value
        """
        y_diff = self.max_min_difference(bbox_1, bbox_2, min_way=1, max_way=3)

        return self._check_intersection_over_range(bbox_1, bbox_2, "x") and (
            round(y_diff, 2) <= self.Y_THRESHOLD or round(y_diff, 2) >= 1
        )
