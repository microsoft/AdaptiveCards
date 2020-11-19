"""Module takes care for the exporting of the extracted
   design objects extracted to the expected renderer format"""
from typing import List, Dict, Union

from PIL import Image

from mystique.card_layout.ds_helper import (DsHelper,
                                            ContainerDetailTemplate)
from mystique.extract_properties import ContainerProperties
from mystique.card_layout import property_updates
from .adaptive_card_templates import AdaptiveCardTemplate
from .export_helper import AcContainerExport


def export_to_card(card_layout: List[Dict],
                   pil_image: Image) -> List[Dict]:
    """
    Returns the exported adaptive card design body.
    @param card_layout: Generated hierarchical layout structure.
    @param pil_image: Input design image
    @return: Exported adaptive card json body
    """
    export_card = AdaptiveCardExport()
    container_details_object = ContainerDetailTemplate()
    # update the extracted properties
    card_layout = property_updates.update_properties(
        card_layout, container_details_object, pil_image)
    # extract the general container's properties
    container_properties = ContainerProperties(pil_image=pil_image)
    card_layout = container_properties.get_container_properties(
        card_layout, pil_image, container_details_object)
    # convert it to adaptive card format
    body = export_card.build_adaptive_card(card_layout)
    return body


class AdaptiveCardExport:
    """
    Module to export the generalized layout structure to the target platform.
    """

    def __init__(self):
        """
        Initializes the target GUI needed components
        """
        self.body = []
        self.card_layout = []
        self.object_template = AdaptiveCardTemplate()
        self.container_detail = ContainerDetailTemplate()

    def export_card_body(self, body: List[Dict],
                         design_object: Union[List, Dict]) -> None:
        """
        Recursively generates the adaptive card's body
        from the layout structure.
        @param body: adaptive card json body
        @param design_object: design objects from the layout structure
        """
        if (isinstance(design_object, dict) and
                design_object.get("object", "") not in DsHelper.CONTAINERS):
            template_object = getattr(self.object_template,
                                      design_object.get("object", ""))
            card_template = template_object(design_object)
            if (body and design_object.get("object") == "radiobutton"
                    and body[-1].get("type") == "Input.ChoiceSet"):
                body[-1]["choices"].append(card_template["choices"][0])
            else:
                body.append(card_template)
        elif isinstance(design_object, list):
            for design_obj in design_object:
                self.export_card_body(body, design_obj)
        else:
            ac_containers = AcContainerExport(design_object, self)
            ac_containers_object = getattr(ac_containers,
                                           design_object.get("object", ""))
            ac_containers_object(body)

    def build_adaptive_card(self, card_layout: List[Dict]) -> List:
        """
        Returns the exported adaptive card json
        @param card_layout: the generalized layout structure
        @return: adaptive card json body
        """

        self.export_card_body(self.body, card_layout)
        y_minimum_final = [c.get("coordinates")[1] for c in
                           card_layout]
        body = [value for _, value in sorted(zip(y_minimum_final, self.body),
                                             key=lambda value: value[0])]
        return body
