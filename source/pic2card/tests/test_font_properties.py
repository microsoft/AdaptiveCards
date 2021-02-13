from tests.base_test_class import BaseSetUpClass
from tests.variables import mock_desing_obj, mock_desing_obj_eq_weight
from mystique.font_properties import classify_font_weights


class TestClassifyFont(BaseSetUpClass):
    """ Tests for the Font weight classification method """

    def test_font_weights_default(self, design_objects=mock_desing_obj):
        """
        Tests if the font weight for the
        test variable results in default
        """
        value = classify_font_weights(design_objects)
        self.assertEqual(value[0]["weight"], "Default")

    def test_font_weights_empty(self, design_objects=[]):
        """
        Tests if the font weight results in
        empty list for the null design_objects
        """
        value = classify_font_weights(design_objects)
        self.assertEqual(len(value), 0)

    def test_font_weights_none(self, design_objects=None):
        """
        Tests if the font weight results in
         empty list for the null design_objects
        """
        self.assertRaises(TypeError, classify_font_weights, design_objects)

    def test_font_weights_not_textbox(self, design_objects=mock_desing_obj):
        """
        Tests if the font weight is default
        for design objects that aren't textbox
        """
        mock_desing_obj[0]["object"] = None
        value = classify_font_weights(design_objects)
        self.assertEqual(value[0]["weight"], "Default")

    def test_same_font_weights(self, design_objects=mock_desing_obj_eq_weight):
        """
        Tests if the same font weights gets uses limit from default_host_config
        """
        value = classify_font_weights(design_objects)
        self.assertEqual(value[0]["weight"], "Lighter")
        self.assertEqual(value[1]["weight"], "Lighter")
