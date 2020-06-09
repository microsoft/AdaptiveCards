// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using AdaptiveCards.Rendering;
using Microsoft.VisualStudio.TestTools.UnitTesting;

#pragma warning disable 0618
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

            Assert.IsNotNull(result);

            Assert.AreEqual(25, result.FontSizes.Small);
            Assert.AreEqual(26, result.FontSizes.Default);
            Assert.AreEqual(27, result.FontSizes.Medium);
            Assert.AreEqual(28, result.FontSizes.Large);
            Assert.AreEqual(29, result.FontSizes.ExtraLarge);
        }

        [TestMethod]
        public void TestParsingInvalidHostConfig()
        {
            Assert.ThrowsException<AdaptiveSerializationException>(() => AdaptiveHostConfig.FromJson("not json"));
        }

        [TestMethod]
        public void TestParsingFullHostConfig()
        {
            var hostConfig = AdaptiveHostConfig.FromJson(@"{
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
      ""foregroundColors"": {
        ""default"": {
          ""default"": ""#333333"",
          ""subtle"": ""#EE333333""
        },
        ""accent"": {
          ""default"": ""#2E89FC"",
          ""subtle"": ""#882E89FC""
        },
        ""attention"": {
          ""default"": ""#cc3300"",
          ""subtle"": ""#DDcc3300""
        },
        ""good"": {
          ""default"": ""#54a254"",
          ""subtle"": ""#DD54a254""
        },
        ""warning"": {
          ""default"": ""#e69500"",
          ""subtle"": ""#DDe69500""
        }
      }
    },
    ""emphasis"": {
      ""backgroundColor"": ""#08000000"",
      ""foregroundColors"": {
        ""default"": {
          ""default"": ""#333333"",
          ""subtle"": ""#EE333333""
        },
        ""accent"": {
          ""default"": ""#2E89FC"",
          ""subtle"": ""#882E89FC""
        },
        ""attention"": {
          ""default"": ""#cc3300"",
          ""subtle"": ""#DDcc3300""
        },
        ""good"": {
          ""default"": ""#54a254"",
          ""subtle"": ""#DD54a254""
        },
        ""warning"": {
          ""default"": ""#e69500"",
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
    ""actionAlignment"": ""stretch"",
    ""iconPlacement"": ""LeftOfTitle"",
    ""iconSize"": 20
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
  ""media"": {
    ""defaultPoster"": ""http://adaptivecards.io/content/media/poster.png""
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
  },
  ""inputs"": {
    ""inputLabels"": {
      ""inputSpacing"": ""small"",
      ""requiredInputs"": {
        ""weight"": ""bolder"",
        ""color"": ""attention"",
        ""size"": ""medium"",
        ""isSubtle"": false
      },
      ""optionalInputs"": {
        ""color"": ""good"",
        ""isSubtle"": true,
        ""weight"": ""lighter""
      }
    }
  }
}");

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
            Assert.AreEqual("#333333", hostConfig.ContainerStyles.Default.ForegroundColors.Default.Default);
            Assert.AreEqual("#EE333333", hostConfig.ContainerStyles.Default.ForegroundColors.Default.Subtle);
            Assert.AreEqual("#2E89FC", hostConfig.ContainerStyles.Default.ForegroundColors.Accent.Default);
            Assert.AreEqual("#882E89FC", hostConfig.ContainerStyles.Default.ForegroundColors.Accent.Subtle);
            Assert.AreEqual("#cc3300", hostConfig.ContainerStyles.Default.ForegroundColors.Attention.Default);
            Assert.AreEqual("#DDcc3300", hostConfig.ContainerStyles.Default.ForegroundColors.Attention.Subtle);
            Assert.AreEqual("#54a254", hostConfig.ContainerStyles.Default.ForegroundColors.Good.Default);
            Assert.AreEqual("#DD54a254", hostConfig.ContainerStyles.Default.ForegroundColors.Good.Subtle);
            Assert.AreEqual("#e69500", hostConfig.ContainerStyles.Default.ForegroundColors.Warning.Default);
            Assert.AreEqual("#DDe69500", hostConfig.ContainerStyles.Default.ForegroundColors.Warning.Subtle);

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
            Assert.AreEqual(IconPlacement.LeftOfTitle, hostConfig.Actions.IconPlacement);
            Assert.AreEqual(20, hostConfig.Actions.IconSize);

            // TODO: Image property not supported (I assume this is where you can set the default image size?)

            Assert.AreEqual(AdaptiveImageSize.Small, hostConfig.ImageSet.ImageSize);
            // TODO: MaxImageHeight property not supported

            Assert.AreEqual(AdaptiveTextColor.Accent, hostConfig.FactSet.Title.Color);
            Assert.AreEqual(false, hostConfig.FactSet.Title.IsSubtle);
            Assert.AreEqual(10, hostConfig.FactSet.Spacing);

            // Media config
            Assert.AreEqual("http://adaptivecards.io/content/media/poster.png", hostConfig.Media.DefaultPoster);

            // Inputs config
            Assert.AreEqual(AdaptiveSpacing.Small, hostConfig.Inputs.InputLabels.InputSpacing);

            Assert.AreEqual(AdaptiveTextWeight.Bolder, hostConfig.Inputs.InputLabels.RequiredInputs.Weight);
            Assert.AreEqual(AdaptiveTextColor.Attention, hostConfig.Inputs.InputLabels.RequiredInputs.Color);
            Assert.AreEqual(AdaptiveTextSize.Medium, hostConfig.Inputs.InputLabels.RequiredInputs.Size);
            Assert.AreEqual(false, hostConfig.Inputs.InputLabels.RequiredInputs.IsSubtle);

            Assert.AreEqual(AdaptiveTextWeight.Lighter, hostConfig.Inputs.InputLabels.OptionalInputs.Weight);
            Assert.AreEqual(AdaptiveTextColor.Good, hostConfig.Inputs.InputLabels.OptionalInputs.Color);
            Assert.AreEqual(AdaptiveTextSize.Default, hostConfig.Inputs.InputLabels.OptionalInputs.Size);
            Assert.AreEqual(true, hostConfig.Inputs.InputLabels.OptionalInputs.IsSubtle);
        }

        [TestMethod]
        public void MediaConfig()
        {
            // Default values
            var defaultHostConfig = AdaptiveHostConfig.FromJson(@"{}");

            Assert.IsNotNull(defaultHostConfig);

            Assert.IsNotNull(defaultHostConfig.Media);
            Assert.IsNull(defaultHostConfig.Media.DefaultPoster);
            Assert.IsNull(defaultHostConfig.Media.PlayButton);
            Assert.AreEqual(true, defaultHostConfig.Media.AllowInlinePlayback);

            // Default values
            var hostConfig = AdaptiveHostConfig.FromJson(@"{
  ""media"": {
    ""defaultPoster"": ""http://adaptivecards.io/content/media/poster.png"",
    ""playButton"": ""http://adaptivecards.io/content/media/playButton.png"",
    ""allowInlinePlayback"": false
  }
}");

            Assert.IsNotNull(hostConfig);

            Assert.IsNotNull(hostConfig.Media);
            Assert.AreEqual("http://adaptivecards.io/content/media/poster.png", hostConfig.Media.DefaultPoster);
            Assert.AreEqual("http://adaptivecards.io/content/media/playButton.png", hostConfig.Media.PlayButton);
            Assert.AreEqual(false, hostConfig.Media.AllowInlinePlayback);
        }

        [TestMethod]
        public void InputsConfig()
        {
            // Default values
            var defaultHostConfig = AdaptiveHostConfig.FromJson(@"{}");

            Assert.IsNotNull(defaultHostConfig);

            Assert.IsNotNull(defaultHostConfig.Inputs);
            Assert.AreEqual(AdaptiveSpacing.Default, defaultHostConfig.Inputs.InputLabels.InputSpacing);

            Assert.IsNotNull(defaultHostConfig.Inputs.InputLabels.RequiredInputs);
            Assert.AreEqual(AdaptiveTextColor.Default, defaultHostConfig.Inputs.InputLabels.RequiredInputs.Color);
            Assert.AreEqual(false, defaultHostConfig.Inputs.InputLabels.RequiredInputs.IsSubtle);
            Assert.AreEqual(AdaptiveTextSize.Default, defaultHostConfig.Inputs.InputLabels.RequiredInputs.Size);
            Assert.AreEqual(AdaptiveTextWeight.Default, defaultHostConfig.Inputs.InputLabels.RequiredInputs.Weight);

            Assert.IsNotNull(defaultHostConfig.Inputs.InputLabels.OptionalInputs);
            Assert.AreEqual(AdaptiveTextColor.Default, defaultHostConfig.Inputs.InputLabels.OptionalInputs.Color);
            Assert.AreEqual(false, defaultHostConfig.Inputs.InputLabels.OptionalInputs.IsSubtle);
            Assert.AreEqual(AdaptiveTextSize.Default, defaultHostConfig.Inputs.InputLabels.OptionalInputs.Size);
            Assert.AreEqual(AdaptiveTextWeight.Default, defaultHostConfig.Inputs.InputLabels.OptionalInputs.Weight);

            // Default values
            var hostConfig = AdaptiveHostConfig.FromJson(@"{
  ""inputs"": {
    ""inputLabels"": {
      ""inputSpacing"": ""small"",
      ""requiredInputs"": {
        ""weight"": ""bolder"",
        ""color"": ""attention"",
        ""size"": ""large"",
        ""isSubtle"": false
      },
      ""optionalInputs"": {
        ""color"": ""good"",
        ""isSubtle"": true,
        ""size"": ""medium"",
        ""weight"": ""lighter""
      }
    }
  }
}");

            Assert.IsNotNull(hostConfig);

            Assert.IsNotNull(defaultHostConfig.Inputs);
            Assert.AreEqual(AdaptiveSpacing.Small, defaultHostConfig.Inputs.InputLabels.InputSpacing);

            Assert.IsNotNull(defaultHostConfig.Inputs.InputLabels.RequiredInputs);
            Assert.AreEqual(AdaptiveTextColor.Attention, defaultHostConfig.Inputs.InputLabels.RequiredInputs.Color);
            Assert.AreEqual(false, defaultHostConfig.Inputs.InputLabels.RequiredInputs.IsSubtle);
            Assert.AreEqual(AdaptiveTextSize.Large, defaultHostConfig.Inputs.InputLabels.RequiredInputs.Size);
            Assert.AreEqual(AdaptiveTextWeight.Bolder, defaultHostConfig.Inputs.InputLabels.RequiredInputs.Weight);

            Assert.IsNotNull(defaultHostConfig.Inputs.InputLabels.OptionalInputs);
            Assert.AreEqual(AdaptiveTextColor.Good, defaultHostConfig.Inputs.InputLabels.OptionalInputs.Color);
            Assert.AreEqual(true, defaultHostConfig.Inputs.InputLabels.OptionalInputs.IsSubtle);
            Assert.AreEqual(AdaptiveTextSize.Medium, defaultHostConfig.Inputs.InputLabels.OptionalInputs.Size);
            Assert.AreEqual(AdaptiveTextWeight.Lighter, defaultHostConfig.Inputs.InputLabels.OptionalInputs.Weight);
        }
    }
}
#pragma warning restore 0618
