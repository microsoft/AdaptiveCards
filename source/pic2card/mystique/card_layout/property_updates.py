"""Module updates the primary properties extracted after the layout generation
- updates the horizontal alignment property for the individual elements
 inside the containers.
- set the horizontal alignment property for the containers"""
from typing import Dict, List, Union
from PIL import Image

from mystique.extract_properties import BaseExtractProperties

from .ds_helper import DsHelper, ContainerDetailTemplate


class DsAlignment:
    """
    Class handles the alignment property updation.
    - updates the horizontal alignment property for the individual elements
      inside the containers, by taking the respective container's coordinates
      as parent coordinates inside which the element's alignment has to be
      updated.
    - set the horizontal alignment property for the containers, by taking the
      the respective parent container's coordinates as parent coordinates
      inside which the container's alignment has to be set.
    """

    def __init__(self):
        self.base_property = BaseExtractProperties()

    def update_or_set_alignment(
            self, design_object: Union[List, Dict],
            container_details_object: ContainerDetailTemplate,
            parent_object=None,
            image=None) -> None:
        """
        traverse the card layout ds recursively and set/update the horizontal
        alignment property based on it's respective parent coordinates.
        @param image: input pil image
        @param parent_object: parent container object
        @param design_object: design element to be set or updated
        @param container_details_object: ContainerDetailTemplate object to
        extract the container details from the card layout structure.
        """
        if isinstance(design_object, dict):
            if not parent_object:
                parent_width = None
                pil_image = image
                design_element_xmin = design_object.get("coordinates",
                                                        [])[0]
                design_element_xmax = design_object.get("coordinates",
                                                        [])[2]

            else:
                parent_width = abs(parent_object.get("coordinates")[2] -
                                   parent_object.get("coordinates")[0])
                pil_image = None
                design_element_xmin = abs(
                    design_object.get("coordinates")[0] -
                    parent_object.get("coordinates")[0])
                design_element_width = abs(
                    design_object.get("coordinates")[2] -
                    design_object.get("coordinates")[0])
                design_element_xmax = (abs(
                    parent_object.get("coordinates")[2] -
                    design_object.get("coordinates")[2]
                ) + design_element_width)

            # update the element's inside the container's
            design_object.update({
                "horizontal_alignment": self.base_property.get_alignment(
                    xmin=design_element_xmin,
                    xmax=design_element_xmax,
                    width=parent_width,
                    image=pil_image)
                })

            # set the container's alignment
            if design_object.get("object", "") in DsHelper.CONTAINERS:
                container_details_template_object = getattr(
                    container_details_object,
                    design_object.get("object", ""))
                container_items = container_details_template_object(
                    design_object)
                # if a container has only one element, then extract the
                # alignment based on the line numbers and top values from
                # pytesseract data.
                if len(container_items) == 1:
                    text_data = container_items[0].get("image_data", [])
                    if text_data:
                        if self._get_number_of_lines(text_data) > 1:
                            alignment = self.base_property.get_line_alignment(
                                text_data)
                            container_items[0].update(
                                {"horizontal_alignment": alignment})
                else:
                    self.update_or_set_alignment(
                        container_items,
                        container_details_object,
                        parent_object=design_object)

        elif isinstance(design_object, list):
            for design_obj in design_object:
                # recursively update the alignment
                if parent_object:
                    self.update_or_set_alignment(
                        design_obj,
                        container_details_object,
                        parent_object=parent_object)
                else:
                    self.update_or_set_alignment(
                        design_obj,
                        container_details_object,
                        image=image)

    def _get_number_of_lines(self, text_data: Dict) -> int:
        """
        Returns the total number of lines extracted from the pytesseract
        output for a design element.
        @param text_data: pytesseract image_to_data o/p
        @return: total number of lines
        """
        number_of_lines = list(
            set(text_data.get("line_num", [])))
        if 0 in number_of_lines:
            number_of_lines.remove(0)
        number_of_lines = len(number_of_lines)
        return number_of_lines

    def update_conflicting_alignments(
            self, card_layout: List,
            container_details_object: ContainerDetailTemplate) -> None:
        """
        Update the alignment property for the element's with conflicting values
        based on the previous or next element's property inside the container.
        i.e if any element's alignment inside it's parent container satisfies
        more than one alignment value , the conflicting element's alignment is
        determined by it's next or previous element's alignment property.
        @param card_layout: card layout ds
        @param container_details_object: ContainerDetailTemplate object to
        extract the container details from the card layout structure.
        """

        if (isinstance(card_layout, dict) and
                card_layout.get("object", "") in DsHelper.CONTAINERS):
            container_details_template_object = getattr(
                container_details_object, card_layout.get("object", ""))
            self.update_conflicting_alignments(
                container_details_template_object(card_layout),
                container_details_object)

        elif isinstance(card_layout, list):
            for ctr, design_obj in enumerate(card_layout):
                if not design_obj.get("horizontal_alignment"):

                    if ctr + 1 < len(card_layout):
                        design_obj.update(
                            {"horizontal_alignment": card_layout[
                                ctr + 1].get("horizontal_alignment")})
                    elif ctr - 1 >= 0:
                        design_obj.update(
                            {"horizontal_alignment": card_layout[
                                ctr - 1].get("horizontal_alignment")})
                    if not design_obj.get("horizontal_alignment"):
                        design_obj.update({"horizontal_alignment": "Left"})
                self.update_conflicting_alignments(design_obj,
                                                   container_details_object)


def update_properties(card_layout: List,
                      container_detail_object: ContainerDetailTemplate,
                      image: Image):
    """
    Entry method handles the calling of different property updations.
    @param card_layout: card layout ds
    @param container_detail_object: ContainerDetailTemplate object to
    extract the container details from the card layout structure
    @param image: Input PIL image
    @return: card layout with the updated or set properties
    """
    ds_alignment = DsAlignment()
    ds_alignment.update_or_set_alignment(card_layout, container_detail_object,
                                         image=image)
    ds_alignment.update_conflicting_alignments(card_layout,
                                               container_detail_object)
    return card_layout
