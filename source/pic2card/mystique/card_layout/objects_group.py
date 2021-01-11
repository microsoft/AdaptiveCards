"""Module for grouping deisgn objects into different containers"""
from operator import itemgetter
from typing import List, Dict, Callable, Tuple, Optional

from mystique import config
from mystique.card_layout import bbox_utils


class GroupObjects:
    """
    Handles the grouping of given list of objects for any set conditions that
    is passed.
    """
    def max_min_difference(self, bbox_1: List,
                           bbox_2: List, min_way: int,
                           max_way: int) -> float:
        """
        Returns the ymax-ymin difference of the 2 deisgn objects

        @param bbox_1: design object one's coordinates
        @param bbox_2: design object two's coordinates
        @param min_way: x or y way minimum position
        @param max_way: x or y way maximum position
        @return: max-min difference ratios
        """
        mid_point1_y = abs(bbox_1[3] -
                           bbox_1[1]) / 2 + bbox_1[1]
        mid_point1_x = abs(bbox_1[2] -
                           bbox_1[0]) / 2 + bbox_1[0]

        mid_point2_y = abs(bbox_2[3] -
                           bbox_2[1]) / 2 + bbox_2[1]
        mid_point2_x = abs(bbox_2[2] -
                           bbox_2[0]) / 2 + bbox_2[0]

        mid_point_y = abs(mid_point1_y - mid_point2_y)
        mid_point_x = abs(mid_point1_x - mid_point2_x)

        mid_size = mid_point_y
        if min_way == 0:
            mid_size = mid_point_x
        if bbox_1[max_way] < bbox_2[min_way]:
            value = round(
                abs(bbox_2[min_way] - bbox_1[max_way]))
        else:
            value = round(
                abs(bbox_1[min_way] - bbox_2[max_way]))
        if mid_size > 0:
            return value / mid_size
        else:
            return 0

    def object_grouping(self, design_objects: List[Dict],
                        condition: Callable[[List, List],
                                            bool]) -> List[List[Dict]]:
        """
        Groups the given List of design objects for the any given condition.
        @param design_objects: objects
        @param condition: Grouping condition function
        @return: Grouped list of design objects.
        """
        groups = []
        grouped_positions = []
        for ctr1, design_object1 in enumerate(design_objects):
            temp_list = []
            for ctr2, design_object2 in enumerate(design_objects):
                bbox_1 = list(design_object1.get(
                    "coords", design_object1.get("coordinates")))
                bbox_2 = list(design_object2.get(
                    "coords", design_object2.get("coordinates")))
                bbox_1.append(design_object1.get("object", ""))
                bbox_2.append(design_object2.get("object", ""))
                if condition(bbox_1, bbox_2):
                    present = False
                    present_position = -1
                    append_object = False
                    append_position = -1
                    for ctr, gr in enumerate(groups):
                        if design_object2 in gr:
                            present = True
                            present_position = ctr
                        if design_object1 in gr:
                            append_object = True
                            append_position = ctr
                    if not present and not append_object:
                        temp_list.append(design_object2)
                        grouped_positions.append(ctr2)
                    elif not present and append_object:
                        groups[append_position].append(design_object2)
                        grouped_positions.append(ctr2)
                    elif present and not append_object:
                        groups[present_position].append(design_object1)
                        grouped_positions.append(ctr1)
                    elif (present and append_object and
                          present_position != append_position):
                        groups[present_position] += groups[append_position]
                        del groups[append_position]
            if temp_list:
                groups.append(temp_list)

        for ctr, design_object in enumerate(design_objects):
            if ctr not in grouped_positions:
                groups.append([design_object])
        return groups


class ImageGrouping(GroupObjects):
    """
    Groups the image objects of the adaptive card objects into a imagesets or
    individual image objects.
    """

    Y_MIN_THRESHOLD = config.CONTAINER_GROUPING.get("ymin_difference")
    X_THRESHOLD = config.CONTAINER_GROUPING.get("xmax_xmin_difference")

    def __init__(self, card_arrange=None):
        self.card_arrange = card_arrange

    def imageset_condition(self, bbox_1: List,
                           bbox_2: List) -> bool:
        """
        Returns a boolean value to group the list of images into image-set.
        @param bbox_1: image object one's coordinates
        @param bbox_2: image object two's coordinates
        @return: boolean value
        """
        y_min_difference = abs(bbox_1[1] - bbox_2[1])

        if bbox_1[1] < bbox_2[1]:
            y_min_difference = y_min_difference / (
                abs(bbox_1[1] - bbox_2[3]))
        else:
            y_min_difference = y_min_difference / (
                abs(bbox_2[1] - bbox_1[3]))
        x_diff = self.max_min_difference(bbox_1,
                                         bbox_2,
                                         min_way=0,
                                         max_way=2)
        return (round(y_min_difference, 2) <= self.Y_MIN_THRESHOLD
                and round(x_diff, 2) <= self.X_THRESHOLD)

    def group_image_objects(self, image_objects, body, objects, ymins=None,
                            is_column=None) -> [List, Optional[Tuple]]:
        """
        Groups the image objects into image-sets which are in
        closer ymin range.
        @param image_objects: list of image objects
        @param body: list card deisgn elements.
        @param ymins: list of ymins of card design
                                  elements
        @param objects: list of all design objects
        @param is_column: boolean value to check if an object is inside a
        columnset or not
        @return: List of remaining image objects after the grouping if the
                 grouping is done outside the columnset container
                 else returned list of remaining image objects along
                 with its coordinate values.
        """
        # group the image objects based on ymin
        groups = self.object_grouping(image_objects, self.imageset_condition)
        delete_positions = []
        design_object_coords = []
        for group in groups:
            group = [dict(t) for t in {tuple(d.items()) for d in group}]
            # group = self.remove_duplicates(group)
            if len(group) > 1:
                group = sorted(group, key=lambda i: i["xmin"])
                image_set = {
                    "type": "ImageSet",
                    "imageSize": "Auto",
                    "images": []
                }
                sizes = []
                alignment = []
                image_xmins = []
                for ctr, design_object in enumerate(group):
                    index = objects.index(design_object)
                    if index not in delete_positions:
                        delete_positions.append(index)
                    sizes.append(design_object.get("size", "Auto"))
                    alignment.append(design_object.get(
                        "horizontal_alignment", "Left"))
                    image_xmins.append(design_object["xmin"])
                    self.card_arrange.append_objects(design_object,
                                                     image_set["images"])
                image_set["images"] = [x for _, x in sorted(
                    zip(image_xmins,
                        image_set["images"]),
                    key=lambda x: x[0])]
                # Assign the imageset's size and alignment property based on
                # each image's alignment and size properties inside the imgaeset
                image_set["imageSize"] = max(set(sizes), key=sizes.count)
                preference_order = ["Left", "Center", "Right"]
                if len(alignment) == len(list(set(alignment))):
                    alignment.sort(key=(preference_order + alignment).index)
                    image_set["horizontalAlignment"] = alignment[0]
                else:
                    image_set["horizontalAlignment"] = max(set(alignment),
                                                           key=alignment.count)
                image_set["coords"] = str(group[0])
                body.append(image_set)
                if ymins:
                    ymins.append(design_object["ymin"])
                if is_column:
                    design_object_coords.append(group[0]["xmin"])
                    design_object_coords.append(group[0]["ymin"])
                    design_object_coords.append(group[0]["xmax"])
                    design_object_coords.append(group[0]["ymax"])
        objects = [design_objects for ctr, design_objects in enumerate(objects)
                   if ctr not in delete_positions]
        if is_column:
            return objects, design_object_coords
        else:
            return objects


class RowColumnGrouping(GroupObjects):
    """
    Groups the design objects into different columns of a columnset
    """
    Y_MIN_THESHOLD = config.CONTAINER_GROUPING.get("ymin_difference", "")
    Y_THRESHOLD = config.CONTAINER_GROUPING.get("ymax_ymin_difference", "")
    X_THRESHOLD = config.CONTAINER_GROUPING.get("xmax_xmin_difference", "")

    def __init__(self, card_arrange=None):
        self.card_arrange = card_arrange

    def _check_intersection_over_range(self, bbox_1: List, bbox_2: List,
                                       axis: str, threshold=0.1) -> bool:
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
        if axis == 'y':
            min_range, max_range = 1, 3
        iou_min = max(bbox_1[min_range], bbox_2[min_range])
        iou_max = min(bbox_1[max_range], bbox_2[max_range])
        iou_size = iou_max - iou_min

        range_size = None
        intersection_ratio = 0.0
        range1 = [bbox_1[min_range], bbox_1[max_range]]
        range2 = [bbox_2[min_range], bbox_2[max_range]]
        if (range1[0] <= iou_min <= range1[1]
                and range1[0] <= iou_max <= range1[1]):
            range_size = range1[1] - range1[0]
        elif (range2[0] <= iou_min <= range2[1]
              and range2[0] <= iou_max <= range2[1]):
            range_size = range2[1] - range2[0]

        if range_size:
            intersection_ratio = iou_size / range_size
        if range_size and intersection_ratio >= threshold:
            return True
        return False

    def row_condition(self, bbox_1: List,
                      bbox_2: List) -> bool:
        """
        Returns a boolean value to group different design objects in a row
        @param bbox_1: design object1 coordinates
        @param bbox_2: design object2 coordinates
        @return: boolean value
        """

        y_diff = self.max_min_difference(bbox_1, bbox_2,
                                         min_way=1, max_way=3)
        y_min_difference = abs(bbox_1[1] - bbox_2[1])
        object_one, object_two = self._get_highest_range_object(bbox_1,
                                                                bbox_2,
                                                                min_way=1,
                                                                max_way=3)
        y_min_difference = y_min_difference / (
            abs(object_two[1] - object_one[3]))

        object_one = None
        object_two = None
        if (bbox_1[4] == "image"
                and bbox_2[4] != "image"):
            object_one = bbox_1
            object_two = bbox_2
        elif (bbox_2[4] == "image"
              and bbox_1[4] != "image"):
            object_one = bbox_2
            object_two = bbox_1
        elif (bbox_2[4] == "image"
              and bbox_1[4] == "image"):
            object_one = bbox_1
            object_two = bbox_2

        y_minimum_condition = (round(y_min_difference, 2)
                               <= self.Y_MIN_THESHOLD + 0.010)

        vertical_inclusive = False
        horizontal_inclusive = False

        if object_one and object_two:
            vertical_inclusive = self._check_intersection_over_range(bbox_1,
                                                                     bbox_2,
                                                                     'y')
            horizontal_inclusive = self._check_intersection_over_range(bbox_1,
                                                                       bbox_2,
                                                                       'x')
        horizontal_inclusive = (round(y_diff, 2) < self.Y_THRESHOLD
                                and horizontal_inclusive)

        return (bbox_1 != bbox_2 and (y_minimum_condition
                                      or vertical_inclusive
                                      or horizontal_inclusive))

    def _get_highest_range_object(self, bbox_1: List, bbox_2: List,
                                  min_way: int,
                                  max_way: int) -> Tuple[List, List]:
        """
        Returns the (greater, lesser) design objects based on the given x or y
        range
        @param bbox_1: design object one
        @param bbox_2: design object two
        @param min_way: x or y way minimum position
        @param max_way: x or y way maximum position
        @return: Tuple(greater , lesser) among the design objects
        """
        if (bbox_1[max_way] - bbox_1[min_way]) >= (
                bbox_2[max_way] - bbox_2[min_way]):
            return bbox_1, bbox_2
        else:
            return bbox_2, bbox_1

    def check_overlap_ties(self, bbox_1: List, bbox_2: List,
                           x_way_overlap_distance: float,
                           y_way_overlap_distance: float) -> bool:
        """
        Checks which way of overlap is greatest and return true i.e should be
        inside a column of x-way overlap percentage is greater than y-way
        overlap between the 2 design objects.
        @param bbox_1: design object one coordinates
        @param bbox_2: design object two coordinates
        @param x_way_overlap_distance: overlapping region's width
        @param y_way_overlap_distance: overlapping region's height
        @return: a boolean value
        """
        object_one, object_two = self._get_highest_range_object(bbox_1,
                                                                bbox_2,
                                                                min_way=0,
                                                                max_way=2)
        width = abs(object_one[2] - object_one[0])
        object_one, object_two = self._get_highest_range_object(bbox_1,
                                                                bbox_2,
                                                                min_way=1,
                                                                max_way=3)
        height = abs(object_one[3] - object_one[1])

        if x_way_overlap_distance / width >= y_way_overlap_distance / height:
            return True

    def column_condition(self, bbox_1: List,
                         bbox_2: List) -> bool:
        """
        Returns a boolean value for grouping items into a column of a particular
        row.
        @param bbox_1: design object coordinates
        @param bbox_2: design object coordinates
        @return: boolean value
        """
        x_diff = self.max_min_difference(bbox_1, bbox_2,
                                         min_way=0, max_way=2)
        y_min_difference = abs(bbox_1[1] - bbox_2[1])

        object_one, object_two = self._get_highest_range_object(bbox_1,
                                                                bbox_2,
                                                                min_way=1,
                                                                max_way=3)
        y_min_difference = y_min_difference / (
            abs(object_two[1] - object_one[3]))

        if bbox_1[1] < bbox_2[1]:
            object_one = bbox_1
            object_two = bbox_2
        else:
            object_one = bbox_2
            object_two = bbox_1

        y_minimum_condition = round(y_min_difference, 2) <= self.Y_MIN_THESHOLD
        x_minimum_condition = round(x_diff, 2) <= self.X_THRESHOLD
        images_check = (bbox_1[4] == "image" and bbox_2[4] == "image"
                        and y_minimum_condition
                        and x_minimum_condition)
        horizontal_inclusive = False
        if object_one and object_two:
            horizontal_inclusive = self._check_intersection_over_range(bbox_1,
                                                                       bbox_2,
                                                                       'x')
        condition = (bbox_1 != bbox_2
                     and (images_check or horizontal_inclusive))

        object_one, object_two = self._get_highest_range_object(bbox_1,
                                                                bbox_2,
                                                                min_way=1,
                                                                max_way=3)
        x_way_overlap = (
            object_one[1] <= object_two[1] <= object_one[3]
            or object_one[1] <= object_two[3] <= object_one[3])
        object_one, object_two = self._get_highest_range_object(bbox_1,
                                                                bbox_2,
                                                                min_way=0,
                                                                max_way=2)
        y_way_overlap = (
            object_one[0] <= object_two[0] <= object_one[2]
            or object_one[0] <= object_two[2] <= object_one[2])
        intersection = bbox_utils.find_iou(bbox_1, bbox_2, columns_group=True)
        if intersection[0] and bbox_1 != bbox_2:
            if x_way_overlap and y_way_overlap:
                x_way_overlap_distance = intersection[1]
                y_way_overlap_distance = intersection[2]
                condition = self.check_overlap_ties(
                    bbox_1, bbox_2, x_way_overlap_distance,
                    y_way_overlap_distance)
            else:
                condition = condition and y_way_overlap
        return condition


class ChoicesetGrouping(GroupObjects):
    """
    Groups the radiobutton objects of the adaptive card objects into a
    choiceset or individual radiobuttion objects.
    """

    Y_THRESHOLD = config.CONTAINER_GROUPING.get(
        "choiceset_ymax_ymin_difference")
    Y_MIN_THRESHOLD = config.CONTAINER_GROUPING.get(
        "choiceset_y_min_difference")

    def __init__(self, card_arrange):
        self.card_arrange = card_arrange

    def choiceset_condition(self, bbox_1: List,
                            bbox_2: List) -> bool:
        """
        Returns a boolean value to group the radiobutton objects into a
        choice-set.
        @param bbox_1: radiobutton object one coordinates
        @param bbox_2: radiobutton object two coordinates
        @return: boolean value
        """
        y_min_difference = abs(bbox_1[1] - bbox_2[1])

        if bbox_1[1] < bbox_2[1]:
            y_min_difference = y_min_difference / (abs(bbox_1[1] -
                                                       bbox_2[3]))
        else:
            y_min_difference = y_min_difference / (
                abs(bbox_2[1] - bbox_1[3]))
        y_diff = self.max_min_difference(bbox_1,
                                         bbox_2,
                                         min_way=1, max_way=3)

        return (round(y_diff, 2) <= self.Y_THRESHOLD
                and round(y_min_difference, 2) <= self.Y_MIN_THRESHOLD)

    def group_choicesets(self, radiobutton_objects: Dict, body: List[Dict],
                         ymins=None) -> None:
        """
        Groups the choice elements into choicesets based on
        the closer ymin range
        @param radiobutton_objects: list of individual choice
                                                 elements
        @param body: list of card deisgn elements
        @param ymins: list of ymin of deisgn elements
        """
        groups = []
        radio_buttons = []
        if isinstance(radiobutton_objects, dict):
            for key, values in radiobutton_objects.items():
                radio_buttons.append(values)
            radiobutton_objects = radio_buttons
        if len(radiobutton_objects) == 1:
            # radiobutton_objects = [radiobutton_objects]
            groups = [radiobutton_objects]
        if not groups:
            groups = self.object_grouping(radiobutton_objects,
                                          self.choiceset_condition)
        for group in groups:
            group = sorted(group, key=itemgetter("ymin"))
            choice_set = {
                "type": "Input.ChoiceSet",
                "choices": [],
                "style": "expanded"
            }
            alignment = []
            for design_object in group:
                choice_set["choices"].append({
                    "title": design_object.get("data", ""),
                    "value": "",
                    "horizontalAlignment": design_object.get(
                        "horizontal_alignment", "")
                })
                # self.card_arrange.append_objects(design_object,
                #                                  choice_set["choices"])
                alignment.append(design_object.get("horizontal_alignment",
                                                   "Left"))
            preference_order = ["Left", "Center", "Right"]
            if len(alignment) == len(list(set(alignment))):
                alignment.sort(key=(preference_order + alignment).index)
                choice_set["horizontalAlignment"] = alignment[0]
            else:
                choice_set["horizontalAlignment"] = max(set(alignment),
                                                        key=alignment.count)

            body.append(choice_set)
            if ymins is not None and len(group) > 0:
                ymins.append(design_object.get("ymin"))
