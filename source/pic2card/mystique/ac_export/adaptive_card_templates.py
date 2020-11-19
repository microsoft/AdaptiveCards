"""Maintains the design templates for the different adaptive card design
element type"""
from typing import Dict


class AdaptiveCardTemplate:
    """
    Design template class for the design objects.
    """

    def textbox(self, design_object: Dict) -> Dict:
        """
        Returns the design json for the textbox
        @param: design element
        @return: design object
        """
        return {
            "type": "TextBlock",
            "text": design_object.get("data", ""),
            "size": design_object.get("size", ""),
            "horizontalAlignment": design_object.get(
                "horizontal_alignment", ""),
            "color": design_object.get("color", "Default"),
            "weight": design_object.get("weight", ""),
            "wrap": "true"
        }

    def actionset(self, design_object: Dict) -> Dict:
        """
        Returns the design json for the actionset
        @param: design element
        @return: design object
        """
        return {
            "type": "ActionSet",
            # "separator": "true", # Issue in data binding if
            # separator is set to True
            "actions": [{
                "type": "Action.Submit",
                "title": design_object.get("data"),
                "style": design_object.get("style"),
            }],
            "spacing": "Medium",
            "horizontalAlignment": design_object.get(
                "horizontal_alignment", "")
        }

    def image(self, design_object: Dict) -> Dict:
        """
        Returns the design json for the image
        @param: design element
        @return: design object
        """
        return {
            "type": "Image",
            "altText": "Image",
            "horizontalAlignment": design_object.get(
                "horizontal_alignment", ""),
            "size": design_object.get("size"),
            "url": design_object.get("data"),
        }

    def checkbox(self, design_object: Dict) -> Dict:
        """
        Returns the design json for the checkbox
        @param: design element
        @return: design object
        """
        return {
            "type": "Input.Toggle",
            "title": design_object.get("data", ""),
            "horizontalAlignment": design_object.get(
                "horizontal_alignment", "")
        }

    def richtextbox(self, design_object: Dict) -> Dict:
        """
        Returns the design json for the richtextbox
        @param: design element
        @return: design object
        """
        return {
            "type": "RichTextBlock",
            "inlines": [{
                "type": "TextRun",
                "text": design_object.get("data", ""),
                "size": design_object.get("size", ""),
                "horizontalAlignment": design_object.get(
                    "horizontal_alignment", ""),
                "color": design_object.get("color", "Default"),
                "weight": design_object.get("weight", ""),
            }]
        }

    def radiobutton(self, design_object: Dict) -> Dict:
        """
        Returns the design json for the radiobutton
        @param: design element
        @return: design object
        """
        choice_set = {
            "type": "Input.ChoiceSet",
            "choices": [],
            "style": "expanded"
        }
        if isinstance(design_object, list):
            for design_obj in design_object:
                item = {
                    "title": design_obj.get("data", ""),
                    "value": "",
                    "horizontalAlignment": design_obj.get(
                        "horizontal_alignment", "")
                }
                choice_set["choices"].append(item)
        else:
            item = {
                "title": design_object.get("data", ""),
                "value": "",
                "horizontalAlignment": design_object.get(
                    "horizontal_alignment", "")
            }
            choice_set["choices"].append(item)
            # choice_set = item

        return choice_set

    def columnset(self, design_object: Dict) -> Dict:
        """
        Returns the design json for the column set container
        @param: design element
        @return: design object
        """
        return {
            "type": "ColumnSet",
            "columns": [],
            "horizontalAlignment": design_object.get(
                "horizontal_alignment", "")
        }

    def column(self, design_object: Dict) -> Dict:
        """
        Returns the design json for the column of the column set container
        @param: design element
        @return: design object
        """
        return {
            "type": "Column",
            "width": design_object.get(
                "width", ""),

            "items": [],
            "horizontalAlignment": design_object.get(
                "horizontal_alignment", "")
        }

    def imageset(self, design_object: Dict) -> Dict:
        """
        Returns the design json for the image set container
        @param: design element
        @return: design object
        """
        return {
            "type": "ImageSet",
            "imageSize": design_object.get("size", ""),
            "images": [],
            "horizontalAlignment": design_object.get(
                "horizontal_alignment", "")
        }

    def choiceset(self, design_object: Dict) -> Dict:
        """
        Returns the design json for the choice set container
        @param: design element
        @return: design object
        """
        return {
            "type": "Input.ChoiceSet",
            "choices": [],
            "style": "expanded",
            "horizontalAlignment": design_object.get(
                "horizontal_alignment", "")
        }
