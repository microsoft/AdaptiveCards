"""Module for grouping deisgn objects into different containers"""
from operator import itemgetter
from typing import List, Dict, Callable, Tuple, Optional

from mystique import config
from mystique.extract_properties import CollectProperties


class GroupObjects:
    """
    Handles the grouping of given list of objects for any set conditions that
    is passed.
    """
    def object_grouping(self, design_objects: List[Dict],
                        condition: Callable[[Dict, Dict],
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
                if condition(design_object1, design_object2):
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

    # Image objects within the 10px ymin range and 100px range difference are
    # grouped into imagesets.
    IMAGE_SET_YMIN_RANGE = 10.0
    IMAGE_SET_X_RANGE = 100.0

    def __init__(self, card_arrange):
        self.card_arrange = card_arrange

    def imageset_condition(self, design_object1: Dict,
                           design_object2: Dict) -> bool:
        """
        Returns a condition boolean value for grouping image objects into
        imagesets
        @param design_object1: image object
        @param design_object2: image object
        @return: boolean value
        """
        if design_object1.get("xmin") < design_object2.get("xmin"):
            xmax = design_object1.get("xmax")
            xmin = design_object2.get("xmin")
        else:
            xmax = design_object2.get("xmax")
            xmin = design_object1.get("xmin")
        ymin_diff = abs(
                design_object1.get("ymin") - design_object2.get("ymin")
        )
        x_diff = abs(xmax - xmin)
        return (ymin_diff <= self.IMAGE_SET_YMIN_RANGE
                and x_diff <= self.IMAGE_SET_X_RANGE)

    def group_image_objects(self, image_objects, body, objects, ymins=None,
                            is_column=None) -> [List, Optional[Tuple]]:
        """
        Groups the image objects into imagesets which are in
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
                    image_xmins.append(design_object.get("xmin"))
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
                image_set["coords"] = str(group[0].get("coords"))
                body.append(image_set)
                if ymins:
                    ymins.append(design_object.get("ymin"))
                if is_column:
                    design_object_coords.append(group[0].get("xmin"))
                    design_object_coords.append(group[0].get("ymin"))
                    design_object_coords.append(group[0].get("xmax"))
                    design_object_coords.append(group[0].get("ymax"))
        objects = [design_objects for ctr, design_objects in enumerate(objects)
                   if ctr not in delete_positions]
        if is_column:
            return objects, design_object_coords
        else:
            return objects


class ColumnsGrouping(GroupObjects):
    """
    Groups the design objects into different columns of a columnset
    """
    def __init__(self, card_arrange):
        self.card_arrange = card_arrange

    def horizontal_inclusive(self, object_one: Dict, object_two: Dict) -> bool:
        """
        Returns the horizonral inclusive condition
        @param object_one: design object one
        @param object_two: design object two
        @return: the boolean value of the inclusive condition
        """

        return (((object_one and object_two) and (
                                (object_one.get("xmin") <= object_two.get(
                                        "xmin") <= object_one.get(
                                        "xmax") and object_one.get(
                                        "xmin") <= object_two.get(
                                        "xmax") <= object_one.get(
                                        "xmax"))
                                or (object_two.get("xmin") <= object_one.get(
                                    "xmin") <= object_two.get(
                                    "xmax") <= object_one.get("xmax") and
                                    object_two.get(
                                    "xmax") <= object_one.get(
                                    "xmax")
                                    ) or (object_one.get(
                                          "xmin") <= object_two.get(
                                          "xmin") <= object_one.get(
                                          "xmax") <= object_two.get(
                                          "xmax") and object_two.get(
                                          "xmax") >= object_one.get("xmin")
                                          ))
                 ) or ((object_two and object_one) and
                       ((object_two.get("xmin")
                         <= object_one.get("xmin")
                        <= object_two.get("xmax")
                         and object_two.get("xmin")
                         <= object_one.get("xmax")
                         <= object_two.get("xmax"))
                        or (object_one.get("xmin")
                            <= object_one.get("xmin")
                            and object_one.get("xmax")
                            <= object_two.get("xmax")
                            and object_two.get("xmin")
                            <= object_one.get("xmax")
                            <= object_two.get("xmax"))
                        or (object_two.get("xmin")
                            <= object_one.get("xmin")
                            <= object_two.get("xmax")
                            <= object_one.get("xmax")
                            and object_one.get("xmax")
                            >= object_two.get("xmin"))))
                )

    def vertical_inclusive(self, object_one: Dict, object_two: Dict) -> bool:
        """
        Returns the vertical inclusive condition

        @param object_one: design object one
        @param object_two: design object two
        @return: the boolean value of the inclusive condition
        """
        return (
                ((object_one and object_two) and
                    ((object_one.get("ymin")
                      <= object_two.get("ymin") <= object_one.get("ymax")
                      and object_one.get("ymin") <= object_two.get("ymax")
                      <= object_one.get("ymax"))
                     or (object_two.get("ymin") <= object_one.get(
                                    "ymin") <= object_two.get(
                                    "ymax") <= object_one.get("ymax")
                         and object_two.get("ymax") <= object_one.get("ymax"))
                     or (object_one.get("ymin") <= object_two.get("ymin")
                         <= object_one.get("ymax") <= object_two.get("ymax")
                         and object_two.get("ymax") >= object_one.get("ymin"))
                     ))
                or ((object_two and object_one)
                    and ((object_two.get("ymin") <= object_one.get("ymin")
                          <= object_two.get("ymax") and object_two.get("ymin")
                          <= object_one.get("ymax") <= object_two.get("ymax"))
                         or (object_one.get("ymin") <= object_one.get("ymin")
                             and object_one.get("ymax")
                             <= object_two.get("ymax")
                             and object_two.get("ymin")
                             <= object_one.get("ymax")
                             <= object_two.get("ymax"))
                         or (object_two.get("ymin") <= object_one.get("ymin")
                             <= object_two.get("ymax")
                             <= object_one.get("ymax")
                             and object_one.get("ymax")
                             >= object_two.get("ymin"))
                         ))
        )

    def max_min_difference(self, design_object1: Dict,
                           design_object2: Dict, way: str) -> float:
        """
        Returns the ymax-ymin difference of the 2 deisgn objects

        @param design_object1: design object one
        @param design_object2: design object two
        @param way: xmax-xmin or ymax-ymin difference

        @return: rounded ymax-ymin difference
        """
        max = "ymax"
        min = "ymin"
        if way == "x":
            max = "xmax"
            min = "xmin"

        if design_object1.get(min) < design_object2.get(min):
            return round(abs(design_object2.get(min) - design_object1.get(max)))
        else:
            return round(abs(design_object1.get(min) - design_object2.get(max)))

    def columns_condition(self, design_object1: Dict,
                          design_object2: Dict) -> bool:
        """
        Returns a condition boolean value for grouping objects into
        columnsets
        @param design_object1: design object
        @param design_object2: design object
        @return: boolean value
        """

        y_diff = self.max_min_difference(design_object1, design_object2,
                                         way="y")

        object_one = None
        object_two = None
        if (design_object1.get("object") == "image"
                and design_object2.get("object") != "image"):
            object_one = design_object1
            object_two = design_object2
        elif (design_object2.get("object") == "image"
              and design_object1.get("object") != "image"):
            object_one = design_object2
            object_two = design_object1
        elif (design_object2.get("object") == "image"
              and design_object1.get("object") == "image"):
            object_one = design_object1
            object_two = design_object2
        return (design_object1 != design_object2 and (
                (abs(design_object1.get("ymin", 0)
                     - design_object2.get("ymin", 0))
                 <= config.COLUMNSET_GROUPING.get("ymin_difference", ""))
                or self.vertical_inclusive(object_one, object_two)
                or (y_diff <
                    config.COLUMNSET_GROUPING.get("ymax-ymin_difference", "")
                    and self.horizontal_inclusive(object_one, object_two)
                    )))

    def columns_row_condition(self, design_object1: Dict,
                              design_object2: Dict) -> bool:
        """
        Returns a condition boolean value for grouping columnset grouped
        objects into different columns.
        @param design_object1: design object
        @param design_object2: design object
        @return: boolean value
        """
        extract_properites = CollectProperties()
        x_diff = self.max_min_difference(design_object1, design_object2,
                                         way="x")
        point1 = (design_object1.get("xmin"), design_object1.get("ymin"),
                  design_object1.get("xmax"), design_object1.get("ymax"))
        point2 = (design_object2.get("xmin"), design_object2.get("ymin"),
                  design_object2.get("xmax"), design_object2.get("ymax"))

        if design_object1.get("ymin") < design_object2.get("ymin"):
            object_one = design_object1
            object_two = design_object2
        else:
            object_one = design_object2
            object_two = design_object1

        condition = (design_object1 != design_object2
                     and ((design_object1.get("object") == "image"
                           and design_object2.get("object") == "image"
                           and abs(design_object1.get("ymin")
                                   - design_object2.get("ymin"))
                           <= config.COLUMNSET_GROUPING.get("ymin_difference")
                           and x_diff <= config.COLUMNSET_GROUPING.get(
                                "xmax-xmin_difference", ""))
                          or self.horizontal_inclusive(object_one, object_two)
                          )
                     )

        intersection = extract_properites.find_iou(point1, point2,
                                                   columns_group=True)[0]
        if intersection and point1 != point2:
            condition = condition and (
                    intersection
                    and (
                            (object_one.get("xmin") <=
                             object_two.get("xmin") <= object_one.get("xmax")
                             and object_one.get("xmin") <=
                             object_two.get("xmax") <= object_one.get("xmax")
                             )
                            or (object_two.get("xmin") <=
                                object_one.get("xmin") <= object_two.get("xmax")
                                and object_two.get("xmin") <=
                                object_one.get("xmax") <= object_two.get("xmax")
                                )
                    )
            )

        return condition


class ChoicesetGrouping(GroupObjects):
    """
    Groups the radiobutton objects of the adaptive card objects into a
    choiceset or individual radiobuttion objects.
    """
    # The design objects are grouped in choicesets based on 2 conditions:
    # If the radiobuttons are within the range of 10px of ymax - ymin
    # If the radiobuttons are within the rnage of 30px of ymins.
    CHOICESET_Y_RANGE = 10
    CHOICESET_YMIN_RANGE = 30

    def __init__(self, card_arrange):
        self.card_arrange = card_arrange

    def choiceset_condition(self, design_object1: Dict,
                            design_object2: Dict) -> bool:
        """
        Returns a condition boolean value for grouping radio buttion objects
        into choiceset
        @param design_object1: image object
        @param design_object2: image object
        @return: boolean value
        """
        design_object1_ymin = float(design_object1.get("ymin"))
        design_object2_ymin = float(design_object2.get("ymin"))
        difference_in_ymin = abs(design_object1_ymin - design_object2_ymin)
        if design_object1_ymin > design_object2_ymin:
            difference_in_y = float(
                    design_object2.get("ymax")) - design_object1_ymin
        else:
            difference_in_y = float(
                    design_object1.get("ymax")) - design_object2_ymin

        return (abs(difference_in_y) <= self.CHOICESET_Y_RANGE
                and difference_in_ymin <= self.CHOICESET_YMIN_RANGE)

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
                self.card_arrange.append_objects(design_object,
                                                 choice_set["choices"])
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
