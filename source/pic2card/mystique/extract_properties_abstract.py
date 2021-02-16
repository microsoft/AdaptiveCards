"""
Module for all abstract classes used for property extraction
used for providing modularity to the extract properties class.
"""

import abc
from typing import Dict, Tuple
from PIL import Image


class AbstractBaseExtractProperties(metaclass=abc.ABCMeta):
    """
    Abstract base class for properties.
    """
    @abc.abstractmethod
    def get_text(self, image: Image, coords: Tuple):
        pass

    @abc.abstractmethod
    def get_alignment(self, image: Image, xmin=None, xmax=None):
        pass


class AbstractFontSizeAndWeight(metaclass=abc.ABCMeta):
    """
    Abstract class for extracting the font size property.
    """
    @abc.abstractmethod
    def get_size(self, image: Image, coords: Tuple, img_data: Dict):
        pass

    """
    Abstract class for extracting the font weight property.
    """
    @abc.abstractmethod
    def get_weight(self, image: Image, coords: Tuple):
        pass


class AbstractFontColor(metaclass=abc.ABCMeta):
    """
    Abstract class for extracting the font color property.
    """
    @abc.abstractmethod
    def get_colors(self, image: Image, coords: Tuple):
        pass


class AbstractChoiceExtraction(AbstractBaseExtractProperties):
    """
    Abstract class for extracting the property related to Choice buttons.
    """
    pass


class AbstractTextExtraction(AbstractBaseExtractProperties,
                             AbstractFontSizeAndWeight,
                             AbstractFontColor):
    """
    Abstract class for extracting all properties related to text extraction.
    """
    pass
