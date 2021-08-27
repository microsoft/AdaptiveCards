"""Test for the layout"""
from multiprocessing import Queue
import unittest
from unittest.mock import patch
from mystique.extract_properties import CollectProperties
from mystique.ac_export.adaptive_card_export import AdaptiveCardExport
from mystique.card_layout.objects_group import RowColumnGrouping
from mystique.card_layout import row_column_group
from mystique.card_layout.ds_helper import DsHelper
from mystique.card_layout import bbox_utils

# pylint: disable=no-name-in-module
from tests.variables import debug_string_test

# pylint: disable=no-name-in-module
from tests.base_test_class import BaseSetUpClass


class TestIOU(BaseSetUpClass):
    """Tests for the IOU class"""

    collect_properties = CollectProperties()

    def test_object_collection(self):
        """Tests the collected object's count"""
        self.assertEqual(len(self.json_objects["objects"]), 20)

    def test_remove_noise_objects(self):
        """Tests the iou based noise removal count"""
        bbox_utils.remove_noise_objects(self.json_objects)
        self.assertEqual(len(self.json_objects["objects"]), 20)

    def test_image_size(self):
        """Tests the image object sizes"""
        extracted_sizes = self.test_util.collect_image_sizes(
            self.json_objects, self.image
        )
        self.assertEqual(extracted_sizes, ["Small", "Small"])

    def test_find_iou_overlap_false(self):
        """Tests the overlap between the given objects coordinates"""
        collect = bbox_utils.find_iou(self.test_coord1, self.test_coord2)[0]
        self.assertFalse(collect, msg="No overlap of textboxes")

    def test_find_iou_overlap_true(self):
        """Tests the overlap between the given objects coordinates"""
        c_1 = (27.695425741374493, 0.0, 479.0481896996498, 310.30650806427)
        c_2 = (
            11.564019257202744,
            116.06978577375412,
            332.18910133838654,
            332.81780552864075,
        )
        collect = bbox_utils.find_iou(c_1, c_2)[0]
        self.assertTrue(collect, msg="Overlap of textboxes")


class TestLayoutStructure(BaseSetUpClass):
    """Tests for the new layout structure"""

    def setUp(self):
        super().setUp()
        self.test_queue = Queue()
        self.export_card = AdaptiveCardExport()

    def test_new_layout_generation(self):
        """
        Tests the generated layout length and datatype for the given test image
        """
        new_layout = row_column_group.generate_card_layout_seq(
            self.json_objects, self.image, self.model_instance
        )
        self.assertEqual(len(new_layout), 13)
        self.assertEqual(type(new_layout).__name__, "list")

    def test_build_adaptive_card(self):
        """
        Tests the adaptive card builded using the testing Format
        for the given test image
        """
        final_ds = row_column_group.generate_card_layout_seq(
            self.json_objects, self.image, self.model_instance
        )
        ds_helper = DsHelper()
        debug_string = ds_helper.build_serialized_layout_string(final_ds)
        card_json = self.export_card.build_adaptive_card(final_ds)
        self.assertEqual(debug_string, debug_string_test)
        self.assertEqual(len(final_ds), len(card_json))

    def tearDown(self):
        """Changing the env variable to default value"""
        patch.stopall()


class TestColumnsGrouping(BaseSetUpClass):
    """Tests for the column grouping objects"""

    def setUp(self):
        super().setUp()
        self.groupobj = RowColumnGrouping()

    def test_horizontal_inclusive(self):
        """Tests for the horizontal inclusion of two design objects"""
        self.test_coord1 = list(self.test_coord1)
        self.test_coord1.append("textbox")
        self.test_coord2 = list(self.test_coord2)
        self.test_coord2.append("textbox")
        # pylint: disable=protected-access
        horiz_inc = self.groupobj.column_condition(
            self.test_coord1, self.test_coord2
        )
        self.assertFalse(horiz_inc)

    def test_vertical_inclusive(self):
        """Tests for the vertical inclusion of two design objects"""
        # pylint: disable=protected-access
        self.test_coord1 = list(self.test_coord1)
        self.test_coord1.append("textbox")
        self.test_coord2 = list(self.test_coord2)
        self.test_coord2.append("textbox")
        vert_inc = self.groupobj.row_condition(
            self.test_coord1, self.test_coord2
        )
        self.assertFalse(vert_inc)

    def test_columns_condition(self):
        """Tests if columns are in columnset two design objects"""
        coordinates_1 = list(
            self.json_objects["objects"][3].get("coordinates", ())
        )
        coordinates_1.append("image")
        coordinates_2 = list(
            self.json_objects["objects"][4].get("coordinates", ())
        )
        coordinates_2.append("textbox")

        column_condition_true = self.groupobj.row_condition(
            coordinates_1, coordinates_2
        )
        coordinates_1 = list(self.test_coord1)
        coordinates_1.append("textbox")
        coordinates_2 = list(self.test_coord2)
        coordinates_2.append("textbox")
        column_condition_false = self.groupobj.row_condition(
            coordinates_1, coordinates_2
        )
        self.assertTrue(column_condition_true)
        self.assertFalse(column_condition_false)


if __name__ == "__main__":
    unittest.main()
