using System;
using AdaptiveCards.Rendering;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace AdaptiveCards.Test
{
    [TestClass]
    public class HostConfigApiTests
    {
        [TestMethod]
        public void TestParsingHostConfig()
        {
            var result = AdaptiveHostConfig.FromJson(@"{
    ""fontSizes"": {
        ""small"": 25,
        ""default"": 26,
        ""medium"": 27,
        ""large"": 28,
        ""extraLarge"": 29
    }
}");

            Assert.IsNotNull(result.HostConfig);

            Assert.AreEqual(25, result.HostConfig.FontSizes.Small);
            Assert.AreEqual(26, result.HostConfig.FontSizes.Default);
            Assert.AreEqual(27, result.HostConfig.FontSizes.Medium);
            Assert.AreEqual(28, result.HostConfig.FontSizes.Large);
            Assert.AreEqual(29, result.HostConfig.FontSizes.ExtraLarge);
        }

        [TestMethod]
        public void TestParsingInvalidHostConfig()
        {
            var result = AdaptiveHostConfig.FromJson("not json");

            Assert.IsNull(result.HostConfig);
        }

        [TestMethod]
        public void TestParsingFullHostConfig()
        {
            var result = AdaptiveHostConfig.FromJson(@"{
  ""spacing"": {
    ""small"": 3,
    ""default"": 4,
    ""medium"": 5,
    ""large"": 6,
    ""extraLarge"": 7,
    ""padding"": 8
  },
  ""separator"": {
    ""lineThickness"": 4,
    ""lineColor"": ""#ABCDEF""
  },
""supportsInteractivity"": true,
""fontFamily"": ""Segoe UI"",
""fontSizes"": {
   ""small"": 12,
   ""default"": 14,
   ""medium"": 17,
   ""large"": 21,
   ""extraLarge"": 26
  },
  ""fontWeights"": {
    ""lighter"": 100,
    ""default"": 200,
    ""bolder"": 300
  },
  ""containerStyles"": {
    ""default"": {
      ""backgroundColor"": ""#AABBCC"",
      ""fontColors"": {
        ""default"": {
          ""normal"": ""#333333"",
          ""subtle"": ""#EE333333""
        },
        ""accent"": {
          ""normal"": ""#2E89FC"",
          ""subtle"": ""#882E89FC""
        },
        ""attention"": {
          ""normal"": ""#cc3300"",
          ""subtle"": ""#DDcc3300""
        },
        ""good"": {
          ""normal"": ""#54a254"",
          ""subtle"": ""#DD54a254""
        },
        ""warning"": {
          ""normal"": ""#e69500"",
          ""subtle"": ""#DDe69500""
        }
      }
    },
    ""emphasis"": {
      ""backgroundColor"": ""#08000000"",
      ""fontColors"": {
        ""default"": {
          ""normal"": ""#333333"",
          ""subtle"": ""#EE333333""
        },
        ""accent"": {
          ""normal"": ""#2E89FC"",
          ""subtle"": ""#882E89FC""
        },
        ""attention"": {
          ""normal"": ""#cc3300"",
          ""subtle"": ""#DDcc3300""
        },
        ""good"": {
          ""normal"": ""#54a254"",
          ""subtle"": ""#DD54a254""
        },
        ""warning"": {
          ""normal"": ""#e69500"",
          ""subtle"": ""#DDe69500""
        }
      }
    }
  },
  ""imageSizes"": {
    ""small"": 40,
    ""medium"": 80,
    ""large"": 160
  },
  ""actions"": {
    ""maxActions"": 20,
    ""spacing"": ""default"",
    ""buttonSpacing"": 10,
    ""showCard"": {
      ""actionMode"": ""inline"",
      ""inlineTopMargin"": 16
    },
    ""actionsOrientation"": ""vertical"",
    ""actionAlignment"": ""stretch""
  },
  ""adaptiveCard"": {
    ""allowCustomStyle"": false
  },
  ""image"": {
    ""size"": ""medium""
  },
  ""imageSet"": {
    ""imageSize"": ""small"",
    ""maxImageHeight"": 100
  },
  ""factSet"": {
    ""title"": {
      ""color"": ""accent"",
      ""size"": ""default"",
      ""isSubtle"": false,
      ""weight"": ""bolder"",
      ""wrap"": true,
      ""maxWidth"": 150
    },
    ""value"": {
      ""color"": ""default"",
      ""size"": ""default"",
      ""isSubtle"": false,
      ""weight"": ""default"",
      ""wrap"": true
    },
    ""spacing"": 10
  }
}");

            var hostConfig = result.HostConfig;
            Assert.IsNotNull(hostConfig);

            Assert.AreEqual(3, hostConfig.Spacing.Small);
            Assert.AreEqual(4, hostConfig.Spacing.Default);
            Assert.AreEqual(5, hostConfig.Spacing.Medium);
            Assert.AreEqual(6, hostConfig.Spacing.Large);
            Assert.AreEqual(7, hostConfig.Spacing.ExtraLarge);
            Assert.AreEqual(8, hostConfig.Spacing.Padding);

            Assert.AreEqual(4, hostConfig.Separator.LineThickness);
            Assert.AreEqual("#ABCDEF", hostConfig.Separator.LineColor);

            Assert.AreEqual(true, hostConfig.SupportsInteractivity);

            Assert.AreEqual("Segoe UI", hostConfig.FontFamily);

            Assert.AreEqual(12, hostConfig.FontSizes.Small);
            Assert.AreEqual(14, hostConfig.FontSizes.Default);
            Assert.AreEqual(17, hostConfig.FontSizes.Medium);
            Assert.AreEqual(21, hostConfig.FontSizes.Large);
            Assert.AreEqual(26, hostConfig.FontSizes.ExtraLarge);

            // TODO: FontWeights aren't supported

            Assert.AreEqual("#AABBCC", hostConfig.ContainerStyles.Default.BackgroundColor);
            Assert.AreEqual("#333333", hostConfig.ContainerStyles.Default.FontColors.Default.Normal);
            Assert.AreEqual("#EE333333", hostConfig.ContainerStyles.Default.FontColors.Default.Subtle);
            Assert.AreEqual("#2E89FC", hostConfig.ContainerStyles.Default.FontColors.Accent.Normal);
            Assert.AreEqual("#882E89FC", hostConfig.ContainerStyles.Default.FontColors.Accent.Subtle);
            Assert.AreEqual("#cc3300", hostConfig.ContainerStyles.Default.FontColors.Attention.Normal);
            Assert.AreEqual("#DDcc3300", hostConfig.ContainerStyles.Default.FontColors.Attention.Subtle);
            Assert.AreEqual("#54a254", hostConfig.ContainerStyles.Default.FontColors.Good.Normal);
            Assert.AreEqual("#DD54a254", hostConfig.ContainerStyles.Default.FontColors.Good.Subtle);
            Assert.AreEqual("#e69500", hostConfig.ContainerStyles.Default.FontColors.Warning.Normal);
            Assert.AreEqual("#DDe69500", hostConfig.ContainerStyles.Default.FontColors.Warning.Subtle);

            Assert.AreEqual("#08000000", hostConfig.ContainerStyles.Emphasis.BackgroundColor);

            Assert.AreEqual(40, hostConfig.ImageSizes.Small);
            Assert.AreEqual(80, hostConfig.ImageSizes.Medium);
            Assert.AreEqual(160, hostConfig.ImageSizes.Large);

            Assert.AreEqual(20, hostConfig.Actions.MaxActions);
            // TODO: Spacing property not supported
            Assert.AreEqual(10, hostConfig.Actions.ButtonSpacing);
            Assert.AreEqual(ShowCardActionMode.Inline, hostConfig.Actions.ShowCard.ActionMode);
            Assert.AreEqual(16, hostConfig.Actions.ShowCard.InlineTopMargin);
            Assert.AreEqual(ActionsOrientation.Vertical, hostConfig.Actions.ActionsOrientation);
            Assert.AreEqual(AdaptiveHorizontalAlignment.Stretch, hostConfig.Actions.ActionAlignment);

            // TODO: Image property not supported (I assume this is where you can set the default image size?)

            Assert.AreEqual(AdaptiveImageSize.Small, hostConfig.ImageSet.ImageSize);
            // TODO: MaxImageHeight property not supported

            Assert.AreEqual(AdaptiveTextColor.Accent, hostConfig.FactSet.Title.Color);
            Assert.AreEqual(false, hostConfig.FactSet.Title.IsSubtle);
            Assert.AreEqual(10, hostConfig.FactSet.Spacing);
        }
    }
}
