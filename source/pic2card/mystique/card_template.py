"""Module to generate data binding payload for the card design payload"""
from typing import Dict, List
from collections import OrderedDict


class DataBinding:
    """
    Class separates the card design object's data from the card paylaod
    by building a mapping data payload json
    """

    def group_imagesets(self, design_object: Dict, key_dict: Dict,
                        root_elements: str):
        """
        Update Imagset data with grouped image data.
        @param design_object: The deisgn obeject with the template data to be
                              grouped
        @param key_dict: Dict where the design object should be grouped
        @param root_elements: The json path of the deisgn object's position
        """
        key_dict["ImageSet"] = {}
        # extract the template data and variable mapping name for each image
        # inside an imageset
        for ctr, image in enumerate(design_object.get("images")):
            key_dict["ImageSet"].update({
                "Image"+str(ctr+1): image.get("url", "")})
            # update the design_object with the binding variable
            design_object["images"][ctr]["url"] = (root_elements
                                                   + "ImageSet.Image"
                                                   + str(ctr+1)
                                                   + "}")

    def group_choicesets(self, design_object: Dict, key_dict: Dict,
                         root_elements: str):
        """
        Update Choiceset data with grouped choices data.
        @param design_object: The deisgn obeject with the template data to be
                              grouped
        @param key_dict: Dict where the design object should be grouped
        @param root_elements: The json path of the deisgn object's position
        """
        choiceset_number = len(
            [key[-1]for key in list(key_dict.keys())
             if "InputChoiceSet" in key]
        )
        choiceset_number = "InputChoiceSet" + str(choiceset_number+1)
        key_dict[choiceset_number] = {}
        # extract template data and variable mapping for each choice inside
        # a choice set
        for choice_ctr, choice in enumerate(
                design_object.get("choices", [""])):
            key_dict[choiceset_number].update({
                "choice"+str(choice_ctr+1): choice.get("title", "")
            })
            # update the design_object with the binding variable
            design_object["choices"][choice_ctr]["title"] = (
                root_elements + choiceset_number + ".choice" +
                str(choice_ctr+1) + "}"
            )

    def group_text_and_image(self, design_object: Dict, key_dict: Dict,
                             root_elements: str):
        """
        Update Individual image and text objects to the template data json.
        @param design_object: The deisgn obeject with the template data to be
                              grouped
        @param key_dict: Dict where the design object should be grouped
        @param root_elements: The json path of the deisgn object's position
        """
        object_type = design_object.get("type", "").replace(".", "")
        object_number = len(
            [key[-1]for key in list(key_dict.keys()) if object_type in key]
            )
        # extract the template data and variable name mapping
        key_dict.update({
            design_object.get("type", "")+str(object_number+1): (
                design_object.get(
                    "text", design_object.get("inlines", [{}])[0].get(
                        "text", design_object.get("url", ""))
                )
            )
        })
        template_variable = (root_elements
                             + design_object.get("type", "")
                             + str(object_number+1)
                             + "}")
        # update the design_object with the binding variable
        if "text" in list(design_object.keys()):
            design_object["text"] = template_variable
        elif "inlines" in list(design_object.keys()):
            design_object["inlines"][0]["text"] = template_variable
        else:
            design_object["url"] = template_variable

    def group_actionset_and_inputtoogle(self, design_object: Dict,
                                        key_dict: Dict,
                                        root_elements: str):
        """
        Update Individual actionsets and input toogle objects to the template
        data json.

        @param design_object: The deisgn obeject with the template data to be
                              grouped
        @param key_dict: Dict where the design object should be grouped
        @param root_elements: The json path of the deisgn object's position
        """
        object_type = design_object.get("type", "").replace(".", "")
        object_number = len(
            [key[-1]for key in list(key_dict.keys()) if object_type in key]
            )
        text_label = "Text"+str(object_number+1)
        object_number = object_type + str(object_number+1)
        key_dict[object_number] = {}
        # extract template data and variable mapping
        key_dict[object_number].update({
            text_label: (
                design_object.get("actions", [{}])[0].get(
                    "title", design_object.get("title", "")
                )
            )
        })
        template_variable = (root_elements
                             + object_number
                             + "."
                             + text_label
                             + "}")
        # update the design_object with the binding variable
        if "actions" in list(design_object.keys()):
            design_object["actions"][0]["title"] = template_variable
        else:
            design_object["title"] = template_variable

    def group_elements(self, design_object: Dict, key_dict: Dict,
                       root_elements: str):
        """
        Groups the template data objects in card payload's format

        @param design_object: The deisgn obeject with the template data to be
                              grouped
        @param key_dict: Dict where the design object should be grouped
        @param root_elements: The json path of the deisgn object's position
        """
        if design_object.get("type", "") in [
                "TextBlock", "RichTextBlock", "Image"]:
            self.group_text_and_image(design_object, key_dict, root_elements)
        if design_object.get("type", "") == "ImageSet":
            self.group_imagesets(design_object, key_dict, root_elements)

        if design_object.get("type", "") in ["ActionSet", "Input.Toggle"]:
            self.group_actionset_and_inputtoogle(
                design_object, key_dict, root_elements)

        if design_object.get("type", "") == "Input.ChoiceSet":
            self.group_choicesets(design_object, key_dict, root_elements)

    def build_data_binding_payload(self, objects: List[Dict]):
        """
        Build the data binding payload from the design objects

        @param objects: list of deisgn objects

        @return: data binding payload json
        """
        grouped_objects = OrderedDict()
        column_set_number = 0
        for ctr, obj in enumerate(objects):
            if obj.get("type", "") == "ColumnSet":
                column_set_number += 1
                grouped_objects["ColumnSet" + str(column_set_number)] = []
                for column_ctr, column in enumerate(obj.get("columns", [""])):
                    columns = {}
                    for items_ctr, item in enumerate(
                            column.get("items", [""])):
                        root_elements = ("${$root.ColumnSet"
                                         + str(column_set_number)
                                         + "["
                                         + str(column_ctr)
                                         + "].")

                        self.group_elements(
                            item, columns, root_elements)
                    grouped_objects["ColumnSet" +
                                    str(column_set_number)].append(columns)
            else:
                self.group_elements(obj, grouped_objects, "${$root.")
        return grouped_objects, objects
