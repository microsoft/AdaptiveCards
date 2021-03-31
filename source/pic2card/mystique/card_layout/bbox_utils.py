"""Handles the functionalities based on the collected design object's bbox
- IOU finding
- nosie objects [ i.e overlapping objects ] removal
"""
from typing import List, Dict, Union

from mystique import config


def find_iou(coord1, coord2, inter_object=False,
             columns_group=False) -> List:
    """
    Finds the intersecting bounding boxes by finding
       the highest x and y ranges of the 2 coordinates
       and determine the intersection by deciding weather
       the new xmin > xmax or the new ymin > ymax.
       For non image objects, includes finding the intersection
       area to a threshold to determine intersection

    @param coord1: list of coordinates of 1st object
    @param coord2: list of coordinates of 2nd object
    @param inter_object: check for cleaning between different overlapping
                         objects.

    @param columns_group: If the intersection finding is needed in columns
                          grouping use case

    @return: [True/False, point1 area, point2 area]
    """
    iou_xmin = max(coord1[0], coord2[0])
    iou_ymin = max(coord1[1], coord2[1])
    iou_xmax = min(coord1[2], coord2[2])
    iou_ymax = min(coord1[3], coord2[3])

    # no intersection
    if iou_xmax - iou_xmin <= 0 or iou_ymax - iou_ymin <= 0:
        return [False]

    intersection_area = (iou_xmax - iou_xmin) * (iou_ymax - iou_ymin)
    point1_area = (coord1[2] - coord1[0]) * (coord1[3] - coord1[1])
    point2_area = (coord2[2] - coord2[0]) * (coord2[3] - coord2[1])
    iou = (intersection_area
           / (point1_area + point2_area - intersection_area))

    # find if given 2 objects intersects or not
    if columns_group:
        if ((point1_area + point2_area - intersection_area == 0)
                or iou > 0):
            return [True, abs(iou_xmax - iou_xmin), abs(iou_ymax - iou_ymin)]
        return [True, abs(iou_xmax - iou_xmin), abs(iou_ymax - iou_ymin)]

    # -if iou check is for inter object overlap removal check only for
    # intersection.
    # -if not for inter objects overlap check for iou >= threshold
    # -if the intersection area covers more than 50% of the smaller object
    if ((point1_area + point2_area - intersection_area == 0)
            or (inter_object and iou > 0)
            or (iou >= config.IOU_THRESHOLD)
            or (iou <= config.IOU_THRESHOLD
                and
                (intersection_area /
                 min(point1_area, point2_area)) >= 0.50)):
        return [True, point1_area, point2_area]

    return [False]


def remove_actionset_textbox_overlapping(design_object1: Dict,
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
        intersection = find_iou(box1, box2,
                                inter_object=True)
        if contains or intersection[0]:
            if design_object1.get("object") == "textbox":
                return position1
            else:
                return position2
        else:
            return None


def remove_noise_objects(json_objects: Dict):
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
            position = remove_actionset_textbox_overlapping(
                json_objects["objects"][ctr],
                json_objects["objects"][ctr1],
                box1, box2, ctr, ctr1)
            if position:
                positions_to_delete.append(position)
            else:
                iou = find_iou(box1, box2)
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
