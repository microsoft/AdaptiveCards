// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace AdaptiveCards.Test
{
    [TestClass]
    public class AdaptiveDimensionTests
    {
        [TestMethod]
        public void TestAdaptiveHeightParse()
        {
            var height = AdaptiveHeight.Parse(null);
            Assert.AreEqual(AdaptiveHeightType.Auto, height.HeightType);
            Assert.IsNull(height.Unit);

            height = AdaptiveHeight.Parse("100");
            Assert.AreEqual(AdaptiveHeightType.Pixel, height.HeightType);
            Assert.AreEqual((uint)100, height.Unit);

            height = AdaptiveHeight.Parse("110px");
            Assert.AreEqual(AdaptiveHeightType.Pixel, height.HeightType);
            Assert.AreEqual((uint)110, height.Unit);

            height = AdaptiveHeight.Parse("AuTo");
            Assert.AreEqual(AdaptiveHeightType.Auto, height.HeightType);
            Assert.IsNull(height.Unit);

            height = AdaptiveHeight.Parse("StRetch");
            Assert.AreEqual(AdaptiveHeightType.Stretch, height.HeightType);
            Assert.IsNull(height.Unit);
        }

        [TestMethod]
        public void TestAdaptiveHeightCtor()
        {
            var height = new AdaptiveHeight(null);
            Assert.AreEqual(AdaptiveHeightType.Auto, height.HeightType);
            Assert.IsNull(height.Unit);

            height = new AdaptiveHeight("100");
            Assert.AreEqual(AdaptiveHeightType.Pixel, height.HeightType);
            Assert.AreEqual((uint)100, height.Unit);

            height = new AdaptiveHeight("110px");
            Assert.AreEqual(AdaptiveHeightType.Pixel, height.HeightType);
            Assert.AreEqual((uint)110, height.Unit);

            height = new AdaptiveHeight("AuTo");
            Assert.AreEqual(AdaptiveHeightType.Auto, height.HeightType);
            Assert.IsNull(height.Unit);

            height = new AdaptiveHeight("StRetch");
            Assert.AreEqual(AdaptiveHeightType.Stretch, height.HeightType);
            Assert.IsNull(height.Unit);

            height = new AdaptiveHeight(AdaptiveHeightType.Stretch);
            Assert.AreEqual(AdaptiveHeightType.Stretch, height.HeightType);
            Assert.IsNull(height.Unit);
        }

        [TestMethod]
        public void TestAdaptiveHeightOperatorAssignment()
        {
            AdaptiveHeight height = "100";
            Assert.AreEqual(AdaptiveHeightType.Pixel, height.HeightType);
            Assert.AreEqual((uint)100, height.Unit);

            height = "110px";
            Assert.AreEqual(AdaptiveHeightType.Pixel, height.HeightType);
            Assert.AreEqual((uint)110, height.Unit);

            height = "AuTo";
            Assert.AreEqual(AdaptiveHeightType.Auto, height.HeightType);
            Assert.IsNull(height.Unit);

            height = "StRetch";
            Assert.AreEqual(AdaptiveHeightType.Stretch, height.HeightType);
            Assert.IsNull(height.Unit);

            height = AdaptiveHeightType.Stretch;
            Assert.AreEqual(AdaptiveHeightType.Stretch, height.HeightType);
            Assert.IsNull(height.Unit);
        }

        [TestMethod]
        public void TestAdaptiveWidthParse()
        {
            var width = AdaptiveWidth.Parse(null);
            Assert.AreEqual(AdaptiveWidthType.Auto, width.WidthType);
            Assert.IsNull(width.Unit);

            width = AdaptiveWidth.Parse("100");
            Assert.AreEqual(AdaptiveWidthType.Pixel, width.WidthType);
            Assert.AreEqual((uint)100, width.Unit);

            width = AdaptiveWidth.Parse("110px");
            Assert.AreEqual(AdaptiveWidthType.Pixel, width.WidthType);
            Assert.AreEqual((uint)110, width.Unit);

            width = AdaptiveWidth.Parse("AuTo");
            Assert.AreEqual(AdaptiveWidthType.Auto, width.WidthType);
            Assert.IsNull(width.Unit);

            width = AdaptiveWidth.Parse("StRetch");
            Assert.AreEqual(AdaptiveWidthType.Stretch, width.WidthType);
            Assert.IsNull(width.Unit);
        }

        [TestMethod]
        public void TestAdaptiveWidthCtor()
        {
            var width = new AdaptiveWidth(null);
            Assert.AreEqual(AdaptiveWidthType.Auto, width.WidthType);
            Assert.IsNull(width.Unit);

            width = new AdaptiveWidth("100");
            Assert.AreEqual(AdaptiveWidthType.Pixel, width.WidthType);
            Assert.AreEqual((uint)100, width.Unit);

            width = new AdaptiveWidth("110px");
            Assert.AreEqual(AdaptiveWidthType.Pixel, width.WidthType);
            Assert.AreEqual((uint)110, width.Unit);

            width = new AdaptiveWidth("AuTo");
            Assert.AreEqual(AdaptiveWidthType.Auto, width.WidthType);
            Assert.IsNull(width.Unit);

            width = new AdaptiveWidth("StRetch");
            Assert.AreEqual(AdaptiveWidthType.Stretch, width.WidthType);
            Assert.IsNull(width.Unit);

            width = new AdaptiveWidth(AdaptiveWidthType.Stretch);
            Assert.AreEqual(AdaptiveWidthType.Stretch, width.WidthType);
            Assert.IsNull(width.Unit);
        }

        [TestMethod]
        public void TestAdaptiveWidthOperatorAssignment()
        {
            AdaptiveWidth width = "100";
            Assert.AreEqual(AdaptiveWidthType.Pixel, width.WidthType);
            Assert.AreEqual((uint)100, width.Unit);

            width = "110px";
            Assert.AreEqual(AdaptiveWidthType.Pixel, width.WidthType);
            Assert.AreEqual((uint)110, width.Unit);

            width = "AuTo";
            Assert.AreEqual(AdaptiveWidthType.Auto, width.WidthType);
            Assert.IsNull(width.Unit);

            width = "StRetch";
            Assert.AreEqual(AdaptiveWidthType.Stretch, width.WidthType);
            Assert.IsNull(width.Unit);

            width = AdaptiveWidthType.Stretch;
            Assert.AreEqual(AdaptiveWidthType.Stretch, width.WidthType);
            Assert.IsNull(width.Unit);
        }

    }
}
