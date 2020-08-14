"""Module for grouping deisgn objects into different containers"""
from typing import List, Dict, Callable, Tuple, Optional
from operator import itemgetter


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
            group = sorted(group, key=lambda i: i["xmin"])
            if len(group) > 1:
                image_set = {
                        "type": "ImageSet",
                        "imageSize": "Auto",
                        "images": []
                }
                sizes = []
                alignment = []
                for ctr, design_object in enumerate(group):
                    index = objects.index(design_object)
                    if index not in delete_positions:
                        delete_positions.append(index)
                    sizes.append(design_object.get("size", "Auto"))
                    alignment.append(design_object.get(
                            "horizontal_alignment", "Left"))
                    self.card_arrange.append_objects(design_object,
                                                     image_set["images"])
                # Assign the imageset's size and alignment property based on
                # each image's alignment and size properties inside the imgaeset
                image_set["imageSize"] = max(set(sizes), key=sizes.count)
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

    # design objects inside each column-set are grouped into columns based on 2
    # conditions on the axis difference:
    # If both are non-image objects the objects should be within 25px of
    # y range  [ymax- ymin ] and 100px of xmin range or vice versa .
    # If any one is a image object then objects should be within the range of
    #    100px in both x and y range
    COLUMNS_ROW_DIFF_1 = 25.0
    COLUMNS_ROW_DIFF_2 = 100.0

    # design objects are grouped into a column-set based on 3 conditions:
    # If y range between any objects are within 11px
    # If ymax - ymin range between any objects are within 15px and x range
    #    within 100px
    # If there's a image object then the adjacent non image object should be
    #   within the y ranges of the image object provided exception of 2 cases
    #   where either one of the ymin range or ymax range can go beyond the
    #   image range for the given set of design objects.[ Not both ]
    COLUMNSET_YMIN_RANGE = 11
    COLUMNSET_Y_RANGE = 15
    COLUMNSET_X_RANGE = 100

    def __init__(self, card_arrange):
        self.card_arrange = card_arrange

    def columns_condition(self, design_object1: Dict,
                          design_object2: Dict) -> bool:
        """
        Returns a condition boolean value for grouping objects into
        columnsets

        @param design_object1: design object
        @param design_object2: design object
        @return: boolean value
        """
        if design_object1.get("ymin") < design_object2.get("ymin"):
            ymax = design_object1.get("ymax")
            ymin = design_object2.get("ymin")
        else:
            ymax = design_object2.get("ymax")
            ymin = design_object1.get("ymin")
        y_diff = round(abs(ymin - ymax))
        xmin_diff = abs(
                design_object1.get("xmin") - design_object2.get("xmin"))

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
                (abs(
                    design_object1.get(
                        "ymin", 0
                    ) - design_object2.get("ymin", 0)
                ) <= self.COLUMNSET_YMIN_RANGE)
                or (y_diff <= self.COLUMNSET_Y_RANGE
                    and xmin_diff <= self.COLUMNSET_X_RANGE)
                or ((object_one and object_two) and (
                    (object_one.get("ymin") <= object_two.get(
                        "ymin") <= object_one.get("ymax") and object_one.get(
                        "ymin") <= object_two.get("ymax") <= object_one.get(
                        "ymax"))
                    or (object_two.get("ymin") <= object_one.get(
                        "ymin") and object_two.get("ymax") <= object_one.get(
                            "ymax") and object_one.get(
                                "ymin") <= object_two.get(
                                    "ymax") <= object_one.get("ymax")
                        ) or (object_one.get("ymin") <= object_two.get(
                            "ymin") <= object_one.get(
                                "ymax") <= object_two.get(
                                    "ymax") and object_two.get(
                                        "ymax") >= object_one.get("ymin")
                        )
                ))))

    def columns_row_condition(self, design_object1: Dict,
                              design_object2: Dict) -> bool:
        """
        Returns a condition boolean value for grouping columnset grouped
        objects into different columns.

        @param design_object1: design object
        @param design_object2: design object
        @return: boolean value
        """
        if design_object1.get("ymin") < design_object2.get("ymin"):
            ymax = design_object1.get("ymax")
            ymin = design_object2.get("ymin")
        else:
            ymax = design_object2.get("ymax")
            ymin = design_object1.get("ymin")
        y_diff = round(abs(ymin - ymax))
        xmin_diff = abs(
            design_object1.get("xmin") - design_object2.get("xmin")
        )
        return (design_object1 != design_object2 and (
                (y_diff <= self.COLUMNS_ROW_DIFF_1
                 and xmin_diff <= self.COLUMNS_ROW_DIFF_2)
                or (design_object1.get("object", "") == "image"
                    and y_diff <= self.COLUMNS_ROW_DIFF_2
                    and xmin_diff <= self.COLUMNS_ROW_DIFF_2)
                or (y_diff <= self.COLUMNS_ROW_DIFF_2
                    and xmin_diff <= self.COLUMNS_ROW_DIFF_1)))


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
            for design_object in group:
                self.card_arrange.append_objects(design_object,
                                                 choice_set["choices"])

            body.append(choice_set)
            if ymins is not None and len(group) > 0:
                ymins.append(design_object.get("ymin"))
