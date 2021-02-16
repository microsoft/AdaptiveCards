"""Module maintains the needed design and exporting templates and utilities
 for target rendering"""
from .adaptive_card_templates import AdaptiveCardTemplate


class AcContainerExport:
    """
    This class is responsible for calling the appropriate design templates
    for the container structure.
    """
    def __init__(self, design_object, export_object):
        self.design_object = design_object
        self.export_object = export_object
        self.object_template = AdaptiveCardTemplate()

    def columnset(self, body) -> None:
        """
        Returns the design element template for the column-set container
        @param body: design element's layout structure
        """
        template_object = getattr(self.object_template,
                                  self.design_object.get("object", ""))
        body.append(template_object(self.design_object))
        body = body[-1].get("columns", [])
        self.export_object.export_card_body(body,
                                            self.design_object.get("row", []))

    def column(self, body) -> None:
        """
        Returns the design element template for the column container
        @param body: design element's layout structure
        """
        template_object = getattr(self.object_template,
                                  self.design_object.get("object", ""))
        body.append(template_object(self.design_object))
        body = body[-1].get("items", [])
        self.export_object.export_card_body(
            body, self.design_object.get("column", {}).get("items", []))

    def imageset(self, body) -> None:
        """
        Returns the design element template for the image-set container
        @param body: design element's layout structure
        """
        template_object = getattr(self.object_template,
                                  self.design_object.get("object", ""))
        body.append(template_object(self.design_object))
        body = body[-1].get("images", [])
        self.export_object.export_card_body(
            body, self.design_object.get("imageset", {}).get("items", []))

    def choiceset(self, body) -> None:
        """
        Returns the design element template for the choice-set container
        @param body: design element's layout structure
        """
        template_object = getattr(self.object_template,
                                  self.design_object.get("object", ""))
        body.append(template_object(self.design_object))
        # body = body[-1].get("choices", [])
        self.export_object.export_card_body(
            body, self.design_object.get("choiceset", {}).get("items", []))
