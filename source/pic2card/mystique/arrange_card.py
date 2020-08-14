"""Module for arranging the design elements for the Card json"""

from typing import List, Dict, Union

from mystique import config
from mystique import default_host_configs
from .design_objects_template import ObjectTemplate
from .extract_properties import CollectProperties
from .extract_properties import ExtractProperties
from .group_design_objects import ChoicesetGrouping
from .group_design_objects import ColumnsGrouping
from .group_design_objects import ImageGrouping


class CardArrange:
    """
    Handles the collecting all the design objects and arranging them
    positionally.
    -Grouping the closer y range image objects into image sets
    -Grouping the closer y range design objects into columnset
    -Grouping the closer x range radiobuttons into choicesets
    -Removing the overlapping design objects detected in faster rcnn
    model
    """
    column_coords = [[]] * 4
    columns_ymins = []
    columns_xmins = []

    def find_iou(self, coord1, coord2, inter_object=False) -> List:
        """
        Finds the intersecting bounding boxes by finding
           the highest x and y ranges of the 2 coordinates
           and determine the intersection by deciding weather
           the new xmin>xmax or the new ymin>ymax.
           For non image objects, includes finding the intersection
           area to a threshold to determine intersection

        @param coord1: list of coordinates of 1st object
        @param coord2: list of coordinates of 2nd object
        @param inter_object: check for cleaning between different overlapping
                             objects.
        @return: [True/False, point1 area, point2 area]

        """
        x5 = max(coord1[0], coord2[0])
        y5 = max(coord1[1], coord2[1])
        x6 = min(coord1[2], coord2[2])
        y6 = min(coord1[3], coord2[3])

        # no intersection
        if x6 - x5 <= 0 or y6 - y5 <= 0:
            return [False]

        intersection_area = (x6 - x5) * (y6 - y5)
        point1_area = (coord1[2] - coord1[0]) * (coord1[3] - coord1[1])
        point2_area = (coord2[2] - coord2[0]) * (coord2[3] - coord2[1])
        iou = (intersection_area
               / (point1_area + point2_area - intersection_area))

        # -if iou check is for inter object overlap removal check only for
        # intersection.
        # -if not for inter objects overlap check for iou >= threshold
        if ((point1_area + point2_area - intersection_area == 0)
                or (inter_object and iou > 0)
                or (iou >= config.IOU_THRESHOLD)):
            return [True, point1_area, point2_area]

        return [False]

    def remove_actionset_textbox_overlapping(self, design_object1: Dict,
                                             design_object2: Dict,
                                             box1: List[float],
                                             box2: List[float],
                                             position1: int,
                                             position2: int) -> Union[int,
                                                                      None]:
        """
        If the passed 2 design objects are actionset and textbox, then
        returns the position to remove the textboxes detected inside the
        actionset objects.

        @param design_object1: design object 1
        @param design_object2: design object 1
        @param box2: design object 1's coordinates
        @param box1: design object 1's coordinates
        @param position1: design object 1's position
        @param position2: design object 2's position

        @return: Returns the position if overlaps else returns None
        """
        # TODO: This workaround will be removed once the model is able to
        #       differentiate the text-boxes and action-sets efficiently.
        if len({design_object1.get("object", ""),
                design_object2.get("object", "")} & {"actionset",
                                                     "textbox"}) == 2:
            contains = (
                    (box2[0] <= box1[0] <= box2[2])
                    and (box2[1] <= box1[1] <= box2[3])
            )
            intersection = self.find_iou(box1, box2, inter_object=True)
            if contains or intersection[0]:
                if design_object1.get("object") == "textbox":
                    return position1
                else:
                    return position2
            else:
                return None

    def remove_noise_objects(self, json_objects: Dict):
        """
        Removes all noisy objects by eliminating all smaller and intersecting
                objects within / with the bigger objects.

        @param json_objects: list of detected objects.
        """
        points = []
        for deisgn_object in json_objects["objects"]:
            points.append(deisgn_object.get("coords"))
        positions_to_delete = []
        for ctr, point in enumerate(points):
            box1 = point
            for ctr1 in range(ctr + 1, len(points)):
                box2 = points[ctr1]
                # check if there's a textbox vs actionset overlap
                # remove the textbox
                position = self.remove_actionset_textbox_overlapping(
                        json_objects["objects"][ctr],
                        json_objects["objects"][ctr1],
                        box1, box2, ctr, ctr1)
                if position:
                    positions_to_delete.append(position)
                else:
                    # if a textbox vs actionset overlap remove with iuo
                    iou = self.find_iou(box1, box2)
                    if iou[0]:
                        box1_area = iou[1]
                        box2_area = iou[2]
                        if (box1_area > box2_area
                                and ctr1 not in positions_to_delete):
                            positions_to_delete.append(ctr1)
                        elif ctr not in positions_to_delete:
                            positions_to_delete.append(ctr)
        points = [p for ctr, p in enumerate(
                points) if ctr not in positions_to_delete]
        json_objects["objects"] = [deisgn_object for deisgn_object in
                                   json_objects["objects"] if
                                   deisgn_object.get("coords") in points]

    def append_image_objects(self, image_urls=None, image_coords=None,
                             pil_image=None, json_object=None,
                             image_sizes=None):
        """
        Appends the extracted image objects to the list of design objects
        along with its proprties extarcted.
        @param image_urls: list of image object urls
        @param image_coords: list of image object cooridnates
        @param pil_image: input PIL image
        @param json_object: list of design objects
        @param image_sizes: list of image object sizes
        """

        extract_properties = ExtractProperties()
        for ctr, im in enumerate(image_urls):
            coords = image_coords[ctr]
            coords = (coords[0], coords[1], coords[2], coords[3])
            object_json = dict().fromkeys(
                    ["object", "xmin", "ymin", "xmax", "ymax"], "")
            object_json["object"] = "image"
            object_json[
                "horizontal_alignment"] = extract_properties.get_alignment(
                    image=pil_image, xmin=float(coords[0]),
                    xmax=float(coords[2]))
            object_json["data"] = im
            object_json["xmin"] = coords[0]
            object_json["ymin"] = coords[1]
            object_json["xmax"] = coords[2]
            object_json["ymax"] = coords[3]
            object_json["image_size"] = pil_image.size
            # resize the image object size if the deisgn image is
            # greater than 1000px width and height
            width, height = image_sizes[ctr]
            keys = list(default_host_configs.IMAGE_SIZE.keys())
            size = "Auto"
            width_key = min(keys, key=lambda x: abs(x - width))
            height_key = min(keys, key=lambda x: abs(x - height))
            if width_key == height_key:
                size = default_host_configs.IMAGE_SIZE[width_key]
            object_json["size"] = size
            object_json["coords"] = ",".join([str(coords[0]),
                                              str(coords[1]), str(coords[2]),
                                              str(coords[3])])
            json_object["objects"].append(object_json)

    def return_position(self, groups, obj):
        """
        Returns the position of an dictionary inside
        a list of dictionaries
        @param groups: list of dictionaries
        @param obj: dictionary
        @return: position if found else -1
        """
        for i in range(len(groups)):
            if obj in groups[i]:
                return i
        return -1

    def append_objects(self, design_object: Dict, body: List[Dict],
                       ymins=None) -> None:
        """
        Appends the individaul design elements to card body

        @param design_object: design element to append
        @param body: list of design elements
        @param ymins: list of ymin of design elements
        """
        object_template = ObjectTemplate(design_object)
        template_object = getattr(object_template, design_object.get("object"))
        body.append(template_object())
        if ymins is not None:
            ymins.append(design_object.get("ymin"))

    def add_column_objects(self, columns: List[Dict], radio_buttons_dict: Dict,
                           colummn_set: Dict) -> List[Dict]:
        """
        Adds the grouped columns into the columnset [ individual objects and
        choicesets ]

        @param columns: List of column objects
        @param radio_buttons_dict: Dict of radiobutton objects with its
                                   position
        mapping [ inside a columnset or not ]
        @param colummn_set: Columnset object
        @return: list of collected image objects inside the columnset
        """
        choiceset_grouping = ChoicesetGrouping(self)
        image_objects_columns = []
        self.column_coords[0] = []
        self.column_coords[1] = []
        self.column_coords[2] = []
        self.column_coords[3] = []
        for ctr, design_objects in enumerate(columns):
            colummn_set["columns"].append({
                    "type": "Column",
                    "width": "stretch",
                    "items": []
            })
            design_objects = sorted(design_objects, key=lambda i: i["ymin"])
            all_columns_value = [[]] * 4
            all_columns_value[0] = []
            all_columns_value[1] = []
            all_columns_value[2] = []
            all_columns_value[3] = []
            for ctr1, design_object in enumerate(design_objects):
                # collect ratio buttons and image objects and add other
                # design objects to the card json
                if design_object.get("object") == "radiobutton":
                    if ctr not in list(radio_buttons_dict["columnset"].keys()):
                        radio_buttons_dict["columnset"] = radio_buttons_dict[
                            "columnset"].fromkeys([ctr], {})
                    radio_buttons_dict["columnset"][ctr].update(
                            {ctr1: design_object})
                elif design_object.get("object") == "image":
                    image_objects_columns.append(design_object)
                else:
                    self.append_objects(
                            design_object, colummn_set["columns"][ctr].get(
                                    "items", []))
                    # collect the coords value for the deisgn objects
                    self.columns_ymins.append(design_object.get("ymin"))
                    all_columns_value[0].append(design_object.get("xmin"))
                    all_columns_value[1].append(design_object.get("ymin"))
                    all_columns_value[2].append(design_object.get("xmax"))
                    all_columns_value[3].append(design_object.get("ymax"))
                    if ctr1 == len(design_objects) - 1:
                        # get the max value of the collected column coordinates
                        self.columns_xmins.append(design_object.get("xmin"))
                        self.column_coords[0].append(max(all_columns_value[0]))
                        self.column_coords[1].append(max(all_columns_value[1]))
                        self.column_coords[2].append(max(all_columns_value[2]))
                        self.column_coords[3].append(max(all_columns_value[3]))

            # choiceset grouping
            if (len(radio_buttons_dict["columnset"]) > 0
                    and ctr <= len(colummn_set["columns"])
                    and ctr in list(radio_buttons_dict["columnset"].keys())):
                choiceset_grouping.group_choicesets(
                        radio_buttons_dict["columnset"][ctr],
                        colummn_set["columns"][ctr].get("items",
                                                        []))
                key = next(iter(radio_buttons_dict["columnset"][0]))
                # collect coords for grouped choice sets
                self.column_coords[0].append(
                        radio_buttons_dict["columnset"][ctr][key].get("xmin"))
                self.column_coords[1].append(
                        radio_buttons_dict["columnset"][ctr][key].get("ymin"))
                self.column_coords[2].append(
                        radio_buttons_dict["columnset"][ctr][key].get("xmax"))
                self.column_coords[3].append(
                        radio_buttons_dict["columnset"][ctr][key].get("ymax"))
                self.columns_ymins.append(
                        radio_buttons_dict["columnset"][ctr][key].get("ymin"))
                self.columns_xmins.append(
                        radio_buttons_dict["columnset"][ctr][key].get("xmin"))

            # sort the design objects within the columns of the
            # columnset based on ymin values
            colummn_set["columns"][ctr]["items"] = [x for _, x in sorted(
                    zip(all_columns_value[1],
                        colummn_set["columns"][ctr]["items"]),
                    key=lambda x: x[0])]
        return image_objects_columns

    def arrange_columns(self, columns: List[Dict], radio_buttons_dict: Dict,
                        body: List[Dict], ymins: List,
                        group: List[Dict], image) -> None:
        """
        Identifies imagesets and arrange the columnset in the card json body

        @param columns: List of column objects
        @param radio_buttons_dict: Dict of radiobutton objects with its
                                   position
        mapping [ inside a columnset or not ]
        @param body: card json body
        @param ymins: list of design object's ymin values
        @param group: list of object in a particular group
        @param image: input PIL image for column width extraction
        """
        image_grouping = ImageGrouping(self)
        collect_properties = CollectProperties()
        colummn_set = {
                "type": "ColumnSet",
                "columns": []
        }
        # add individual items and radiobuttons inside the column
        image_objects_columns = self.add_column_objects(columns,
                                                        radio_buttons_dict,
                                                        colummn_set)
        ctr = len(columns) - 1
        # arrange the image objects and imageset objects inside the columns
        if len(image_objects_columns) > 0:
            (image_objects_columns,
             imageset_coords) = image_grouping.group_image_objects(
                    image_objects_columns,
                    colummn_set["columns"][ctr].get("items"),
                    image_objects_columns,
                    is_column=True)
            if imageset_coords:
                self.column_coords[0].append(imageset_coords[0])
                self.column_coords[1].append(imageset_coords[1])
                self.column_coords[2].append(imageset_coords[2])
                self.column_coords[3].append(imageset_coords[3])
                self.columns_ymins.append(imageset_coords[1])
                self.columns_xmins.append(imageset_coords[0])

            # after arranging the image set objects collect and add the
            # individual images to the card json
            for item in image_objects_columns:
                colummn_set["columns"].append({
                        "type": "Column",
                        "width": "stretch",
                        "items": []
                })
                ctr = ctr + 1
                self.append_objects(
                        item,
                        colummn_set["columns"][ctr].get("items", [])
                )
                self.column_coords[0].append(item.get("xmin"))
                self.column_coords[1].append(item.get("ymin"))
                self.column_coords[2].append(item.get("xmax"))
                self.column_coords[3].append(item.get("ymax"))
                self.columns_ymins.append(item.get("ymin"))
                self.columns_xmins.append(item.get("xmin"))

        delete_positions = []
        if colummn_set not in body:
            # delete empty columns
            for ctr, column in enumerate(colummn_set["columns"]):
                if not column.get("items", []):
                    delete_positions.append(ctr)

            colummn_set["columns"] = [column for ctr, column in
                                      enumerate(colummn_set["columns"]) if
                                      ctr not in delete_positions]

            # sort the columnset columns based on xmin values
            colummn_set["columns"] = [x for _, x in sorted(
                    zip(self.column_coords[0], colummn_set["columns"]),
                    key=lambda x: x[0])]

            # sort the collected columns coords for column width extraction
            self.column_coords[2] = [x for _, x in sorted(
                    zip(self.column_coords[0], self.column_coords[2]),
                    key=lambda x: x[0])]
            self.column_coords[0] = sorted(self.column_coords[0])
            # collect column and columnset alignment property and column's width
            # property
            collect_properties.column(colummn_set["columns"])
            collect_properties.columnset(colummn_set, self.column_coords, image)
            # add the columnset to the card json body
            body.append(colummn_set)
            ymins.append(group[0].get("ymin", ""))

    def build_card_json(self, objects=None, image=None):
        """
        Builds the Adaptive card json

        @param objects: list of all design objects

        @return: card body and ymins of deisgn elements
        """
        image_grouping = ImageGrouping(self)
        columns_grouping = ColumnsGrouping(self)
        choiceset_grouping = ChoicesetGrouping(self)
        body = []
        ymins = []
        # group all objects into columnset or individual objects
        groups = columns_grouping.object_grouping(
                objects,
                columns_grouping.columns_condition
        )
        radio_buttons_dict = {"normal": []}
        if len(groups) == 1:
            groups = [[gr] for gr in groups[0]]

        image_objects = []
        for group in groups:
            # sort the group based on x axes value
            group = sorted(group, key=lambda i: i["xmin"])

            radio_buttons_dict["columnset"] = {}
            # if the group is an individual object
            if len(group) == 1:
                if group[0].get("object") == "radiobutton":
                    radio_buttons_dict["normal"].append(group[0])
                elif group[0].get("object") == "image":
                    image_objects.append(group[0])
                else:
                    self.append_objects(group[0], body, ymins=ymins)
            # if the group is a columnset
            elif len(group) > 1:
                # group the columnset objects into different columns
                columns = columns_grouping.object_grouping(
                        group,
                        columns_grouping.columns_row_condition
                )
                # If the columnset has only on column flatten it
                if len(columns) == 1:
                    columns = columns[0]
                    for item in columns:
                        if item.get("object") == "radiobutton":
                            radio_buttons_dict["normal"].append(item)
                        elif item.get("object") == "image":
                            image_objects.append(item)
                        else:
                            self.append_objects(item, body, ymins=ymins)
                    continue
                # if more than one column arrange the columns
                self.arrange_columns(columns, radio_buttons_dict, body, ymins,
                                     group, image)
        # perform imageset anc choiceset grouping for design objects outside
        # the column-sets.
        if len(radio_buttons_dict["normal"]) > 0:
            choiceset_grouping.group_choicesets(
                    radio_buttons_dict["normal"], body, ymins=ymins)
        if len(image_objects) > 0:
            image_objects = image_grouping.group_image_objects(image_objects,
                                                               body,
                                                               image_objects,
                                                               ymins=ymins)
            for objects in image_objects:
                self.append_objects(objects, body, ymins=ymins)
        return body, ymins
