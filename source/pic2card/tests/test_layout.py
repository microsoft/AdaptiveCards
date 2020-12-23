from multiprocessing import Queue
import unittest
from unittest.mock import patch

from tests.variables import (debug_string_test, test_img_obj1,
                             test_img_obj2, test_cset_obj1,
                             test_cset_obj2)
from mystique.extract_properties import CollectProperties
from mystique.ac_export.adaptive_card_export import (
    AdaptiveCardExport)
from mystique.card_layout.objects_group import (RowColumnGrouping,
                                                ImageGrouping,
                                                ChoicesetGrouping)
from mystique.card_layout import row_column_group
from mystique.card_layout.ds_helper import DsHelper
from mystique.card_layout import bbox_utils

from tests.base_test_class import BaseSetUpClass


class TestIOU(BaseSetUpClass):
    """ Tests for the IOU class """

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
        extracted_sizes = self.test_util.collect_image_sizes(self.json_objects,
                                                             self.image)
        self.assertEqual(extracted_sizes, ["Small", "Small"])

    @patch('mystique.config.NEW_LAYOUT_STRUCTURE', False)
    def test_build_card_json(self):
        """
        Tests the length of the card json and the
         y mininum coordinates List built
        """
        card_json, y_mins = self.card_arrange.build_card_json(
            self.json_objects["objects"], self.image)
        self.assertEqual(len(card_json), 14)
        self.assertEqual(len(y_mins), 14)

    def test_find_iou_overlap_false(self):
        """Tests the overlap between the given objects coordinates"""
        collect = bbox_utils.find_iou(
            self.test_coord1, self.test_coord2)[0]
        self.assertFalse(collect, msg="No overlap of textboxes")

    def test_find_iou_overlap_true(self):
        """Tests the overlap between the given objects coordinates"""
        c_1 = (27.695425741374493, 0.0, 479.0481896996498, 310.30650806427)
        c_2 = (11.564019257202744, 116.06978577375412, 332.18910133838654,
               332.81780552864075)
        collect = bbox_utils.find_iou(c_1, c_2)[0]
        self.assertTrue(collect, msg="Overlap of textboxes")


class TestLayoutStructure(BaseSetUpClass):
    """ Tests for the new layout structure """

    def setUp(self):
        super().setUp()
        self.test_queue = Queue()
        self.export_card = AdaptiveCardExport()

    @patch('mystique.config.NEW_LAYOUT_STRUCTURE', True)
    def test_new_layout_generation(self):
        """
        Tests the generated layout length and datatype for the given test image
        """
        new_layout = row_column_group.generate_card_layout(self.json_objects,
                                                           self.image,
                                                           self.model_instance)
        self.assertEqual(len(new_layout), 14)
        self.assertEqual(type(new_layout).__name__, "list")

    @patch('mystique.config.NEW_LAYOUT_STRUCTURE', True)
    def test_build_adaptive_card(self):
        """
        Tests the adaptive card builded using the testing Format
        for the given test image
        """
        final_ds = row_column_group.generate_card_layout(
            self.json_objects, self.image, self.model_instance)
        ds_helper = DsHelper()
        debug_string = ds_helper.build_serialized_layout_string(final_ds)
        card_json = self.export_card.build_adaptive_card(final_ds)
        self.assertEqual(debug_string, debug_string_test)
        self.assertEqual(len(final_ds), len(card_json))

    def tearDown(self):
        """ Changing the env variable to default value """
        patch.stopall()


class TestColumnsGrouping(BaseSetUpClass):
    """ Tests for the column grouping objects """

    def setUp(self):
        super().setUp()
        self.groupobj = RowColumnGrouping(card_arrange=self.card_arrange)

    def test_horizontal_inclusive(self):
        """ Tests for the horizontal inclusion of two design objects """
        horiz_inc = self.groupobj._check_intersection_over_range(
			self.test_coord1,
            self.test_coord2, 'x')
        self.assertFalse(horiz_inc)

    def test_vertical_inclusive(self):
        """ Tests for the vertical inclusion of two design objects """
        vert_inc = self.groupobj._check_intersection_over_range(
			self.test_coord1,
            self.test_coord2, 'y')
        self.assertFalse(vert_inc)

    def test_columns_condition(self):
        """ Tests if columns are in columnset two design objects """
        coordinates_1 = list(self.json_objects['objects'][3].get("coords", ()))
        coordinates_1.append("image")
        coordinates_2 = list(self.json_objects['objects'][4].get("coords", ()))
        coordinates_2.append("textbox")

        column_condition_true = self.groupobj.row_condition(coordinates_1,
                                                            coordinates_2)
        coordinates_1 = list(self.test_coord1)
        coordinates_1.append("textbox")
        coordinates_2 = list(self.test_coord2)
        coordinates_2.append("textbox")
        column_condition_false = self.groupobj.row_condition(
            coordinates_1, coordinates_2)
        self.assertTrue(column_condition_true)
        self.assertFalse(column_condition_false)


class TestImageGrouping(BaseSetUpClass):
    """ Tests for the Image grouping objects """

    def test_imageset_condition(self):
        """ Tests if images are in imageset """
        groupobj = ImageGrouping(self.card_arrange)
        condition_true = groupobj.imageset_condition(test_img_obj1,
                                                     test_img_obj2)
        condition_false = groupobj.imageset_condition(self.test_coord1,
                                                      self.test_coord2)
        self.assertTrue(condition_true)
        self.assertFalse(condition_false)


class TestChoiceSetGrouping(BaseSetUpClass):
    """ Tests for the Choiceset grouping objects """

    def test_choiceset_condition(self):
        """ Tests if choice set obj are in choiceset """
        groupobj = ChoicesetGrouping(self.card_arrange)
        condition_true = groupobj.choiceset_condition(test_cset_obj1,
                                                      test_cset_obj2)
        condition_false = groupobj.choiceset_condition(self.test_coord1,
                                                       self.test_coord2)
        self.assertTrue(condition_true)
        self.assertFalse(condition_false)


if __name__ == '__main__':
    unittest.main()
