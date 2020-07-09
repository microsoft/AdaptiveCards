"""Module for template json for different design obejcts"""
from typing import Dict


class ObjectTemplate:
    """
    Design template class for the design objects.
    """

    def __init__(self, design_object):
        self.design_object = design_object

    def textbox(self) -> Dict:
        """
        Returns the design json for the textbox
        @return: design object
        """
        return {
            "type": "TextBlock",
            "text": self.design_object.get("data", ""),
            "size": self.design_object.get("size", ""),
            "horizontalAlignment": self.design_object.get(
                    "horizontal_alignment", ""),
            "color": self.design_object.get("color", "Default"),
            "weight": self.design_object.get("weight", ""),
            "wrap": "true"
        }

    def actionset(self) -> Dict:
        """
        Returns the design json for the actionset
        @return: design object
        """
        return {
            "type": "ActionSet",
            # "separator": "true", # Issue in data binding if
            # separator is set to True
            "actions": [{
                    "type": "Action.Submit",
                    "title": self.design_object.get("data"),
                    "style": self.design_object.get("style"),
            }],
            "spacing": "Medium"
        }

    def image(self) -> Dict:
        """
        Returns the design json for the image
        @return: design object
        """
        return {
            "type": "Image",
            "altText": "Image",
            "horizontalAlignment": self.design_object.get(
                    "horizontal_alignment", ""),
            "size": self.design_object.get("size"),
            "url": self.design_object.get("data"),
        }

    def checkbox(self) -> Dict:
        """
        Returns the design json for the checkbox
        @return: design object
        """
        return {
            "type": "Input.Toggle",
            "title": self.design_object.get("data", ""),
        }

    def richtextbox(self) -> Dict:
        """
        Returns the design json for the richtextbox
        @return: design object
        """
        return {
            "type": "RichTextBlock",
            "inlines": [{
                    "type": "TextRun",
                        "text": self.design_object.get("data", ""),
                        "size": self.design_object.get("size", ""),
                        "horizontalAlignment": self.design_object.
                            get("horizontal_alignment", ""),
                            "color": self.design_object.get("color", "Default"),
                            "weight": self.design_object.get("weight", ""),
                        }]}

    def radiobutton(self) -> Dict:
        """
        Returns the design json for the radiobutton
        @return: design object
        """
        return {
            "title": self.design_object.get("data", ""),
            "value": "",
        }
