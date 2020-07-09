"""Module for arranging the design elements for the Card json"""

from typing import List, Dict

from .image_extraction import ImageExtraction
from .extract_properties import ExtractProperties
from mystique import default_host_configs
from .group_design_objects import ImageGrouping
from .group_design_objects import ColumnsGrouping
from .group_design_objects import ChoicesetGrouping
from .design_objects_template import ObjectTemplate


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

    def remove_overlapping_objects(self, json_object=None):
        """
        Removes the overlapping faster rcnn detected objects by
        finding the intersection between 2 objects.
        And removes the overlapping text objects on actionsets.
        @param json_object: list of design objects
        """
        image_extraction = ImageExtraction()
        positions_to_delete = []
        for i in range(len(json_object["objects"])):
            for j in range(i, len(json_object["objects"])):
                if len(
                        json_object["objects"]) > i != j < len(
                        json_object["objects"]):
                    box1 = json_object["objects"][i].get("coords")
                    box2 = json_object["objects"][j].get("coords")
                    intersection = image_extraction.find_points(box1, box2)
                    object_i = json_object["objects"][i]
                    object_j = json_object["objects"][j]
                    if intersection:
                        if object_i.get("score") > (
                                object_j.get("score")) and (
                                j not in positions_to_delete) and (
                                object_j.get("object") != "actionset"):
                            positions_to_delete.append(j)
                        elif i not in positions_to_delete and (
                                object_i.get("object") != "actionset"):
                            positions_to_delete.append(i)
                    contains = ((float(box2[0]) <= box1[0] <= float(box2[2]))
                                and (float(box2[1]) <= box1[1] <= float(box2[3]
                                                                        )))
                    if contains and not (
                            object_i.get("object") == "actionset"
                            and object_j.get("object") == "actionset"):
                        if (json_object["objects"][i].get(
                                "object") == "actionset"
                                or object_j.get("object") == "actionset"):
                            box1_area = (box1[2] - box1[0]) * (
                                    box1[3] - box1[1])
                            box2_area = (box2[2] - box2[0]) * (
                                    box2[3] - box2[1])
                            if (box1_area > box2_area
                                    and j not in positions_to_delete):
                                positions_to_delete.append(j)
                            elif i not in positions_to_delete:
                                positions_to_delete.append(i)
        json_object["objects"] = [x for ctr, x in enumerate(
                json_object["objects"]) if ctr not in positions_to_delete]

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
        template_object=getattr(object_template, design_object.get("object"))
        body.append(template_object())
        if ymins is not None:
            ymins.append(design_object.get("ymin"))

    def set_column_width(self, column_number: int, columns: List[Dict],
                         column_set: Dict) -> None:
        """
        Set Column width property

        @param column_number: the column number of the columnset
        @param columns: list of column design objects
        @param column_set: column set objects
        """
        # if x distance between 2 columns is <=50 pixels the spacing is given as auto
        if (column_number + 1 < len(columns)
            and columns[column_number + 1]
            and (float(columns[column_number + 1][-1].get("xmin"))
                 - float(columns[column_number][-1].get("xmax")) <= 50)):
            column_set["columns"][column_number]["width"] = "auto"
        # if the y distance or the height of the last column object is >=50 pixels the spacing is given as auto
        if (columns[column_number]
                and column_number == len(columns) - 1
                and (float(columns[column_number][-1].get('ymax'))
                     - float(columns[column_number][-1].get('ymin')) >= 50)
                and columns[column_number][-1].get('object') != "image"):
            column_set["columns"][column_number]["width"] = "auto"

    def add_column_objects(self, columns: List[Dict], radio_buttons_dict: Dict,
                           colummn_set: Dict) -> [List, List, int]:
        """
        Adds the grouped columns into the columnset [ individual objects and
        choicesets ]

        @param columns: List of column objects
        @param radio_buttons_dict: Dict of radiobutton objects with its position
        mapping [ inside a columnset or not ]
        @param colummn_set: Columnset object
        @return: list of collected image objects inside the columnset
                 list of each column's xmin
        """
        choiceset_grouping = ChoicesetGrouping(self)
        image_objects_columns = []
        column_xmin = []
        for ctr, obj in enumerate(columns):
            colummn_set["columns"].append({
                    "type": "Column",
                    "width": "stretch",
                    "items": []
            })
            column_flag = False
            obj = sorted(obj, key=lambda i: i["ymin"])
            for ctr1, design_object in enumerate(obj):
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
                    if not column_flag:
                        column_xmin.append(design_object.get("xmin"))
                        column_flag = True

                self.set_column_width(ctr, columns, colummn_set)

            if (len(radio_buttons_dict["columnset"]) > 0
                    and ctr <= len(colummn_set["columns"])
                    and ctr in list(radio_buttons_dict["columnset"].keys())):
                choiceset_grouping.group_choicesets(
                        radio_buttons_dict["columnset"][ctr],
                        colummn_set["columns"][ctr].get("items",
                                                        []))
                column_xmin.append(
                        radio_buttons_dict["columnset"][ctr][0].get("xmin"))
        return image_objects_columns, column_xmin, ctr

    def arrange_columns(self, columns: List[Dict], radio_buttons_dict: Dict,
                        body: List[Dict], ymins: List,
                        group: List[Dict]) -> None:
        """
        Identifies imagesets and arrange the columnset in the card json body

        @param columns: List of column objects
        @param radio_buttons_dict: Dict of radiobutton objects with its position
        mapping [ inside a columnset or not ]
        @param body: card json body
        @param ymins: list of design object's ymin values
        @param group: list of object in a particular group
        """
        image_grouping = ImageGrouping(self)
        colummn_set = {
                "type": "ColumnSet",
                "columns": []
        }
        # add individual items and radiobuttons inside the column
        image_objects_columns, column_xmin, ctr = self.add_column_objects(
                columns, radio_buttons_dict, colummn_set)

        # arrange the image objects and imageset objects inside the columns
        if len(image_objects_columns) > 0:
            image_objects_columns, xmin = image_grouping.group_image_objects(
                    image_objects_columns,
                    colummn_set["columns"][
                        ctr].get("items"),
                    image_objects_columns, is_column=True)
            if xmin:
                column_xmin.append(xmin)
            for item in image_objects_columns:
                colummn_set["columns"].append({
                        "type": "Column",
                        "width": "stretch",
                        "items": []
                })
                ctr = ctr + 1
                self.append_objects(item,
                                    colummn_set["columns"][ctr].get("items",[]))
                column_xmin.append(item.get("xmin"))

        delete_positions = []
        if colummn_set not in body:
            for ctr, column in enumerate(colummn_set["columns"]):
                if not column.get("items", []):
                    delete_positions.append(ctr)

            colummn_set["columns"] = [column for ctr, column in
                                      enumerate(colummn_set["columns"]) if
                                      ctr not in delete_positions]

            colummn_set["columns"] = [x for _, x in sorted(
                    zip(column_xmin, colummn_set["columns"]),
                    key=lambda x: x[0])]

            body.append(colummn_set)
            ymins.append(group[0].get("ymin", ""))

    def build_card_json(self, objects=None):
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
        groups = columns_grouping.object_grouping(objects,
                                                  columns_grouping.columns_condition)
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
                #group the columnset objects into different columns
                columns = columns_grouping.object_grouping(group,
                                                           columns_grouping.columns_row_condition)
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
                                     group)
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
