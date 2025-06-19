// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Text.Json.Serialization;

namespace AdaptiveCards.SystemTextJson
{
    /// <summary>
    /// DTO for AdaptiveCard serialization with System.Text.Json.
    /// This ensures clean JSON output matching Newtonsoft.Json format.
    /// </summary>
    internal class AdaptiveCardDto
    {
        [JsonPropertyName("type")]
        public string Type { get; set; } = "AdaptiveCard";

        [JsonPropertyName("version")]
        public string Version { get; set; }

        [JsonPropertyName("fallbackText")]
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        public string FallbackText { get; set; }

        [JsonPropertyName("speak")]
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        public string Speak { get; set; }

        [JsonPropertyName("lang")]
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        public string Lang { get; set; }

        [JsonPropertyName("backgroundImage")]
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        public object BackgroundImage { get; set; }

        [JsonPropertyName("minHeight")]
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        public string MinHeight { get; set; }

        [JsonPropertyName("body")]
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        public List<object> Body { get; set; }

        [JsonPropertyName("actions")]
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        public List<object> Actions { get; set; }

        [JsonPropertyName("selectAction")]
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        public object SelectAction { get; set; }

        [JsonPropertyName("verticalContentAlignment")]
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        public string VerticalContentAlignment { get; set; }

        [JsonPropertyName("rtl")]
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        public bool? Rtl { get; set; }
    }

    /// <summary>
    /// Base DTO for AdaptiveElement serialization.
    /// </summary>
    internal class AdaptiveElementDto
    {
        [JsonPropertyName("type")]
        public string Type { get; set; }

        [JsonPropertyName("id")]
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        public string Id { get; set; }

        [JsonPropertyName("spacing")]
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        public string Spacing { get; set; }

        [JsonPropertyName("separator")]
        public bool Separator { get; set; }

        [JsonPropertyName("height")]
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        public string Height { get; set; }

        [JsonPropertyName("isVisible")]
        public bool IsVisible { get; set; } = true;
    }

    /// <summary>
    /// DTO for AdaptiveTextBlock serialization.
    /// </summary>
    internal class AdaptiveTextBlockDto : AdaptiveElementDto
    {
        [JsonPropertyName("text")]
        public string Text { get; set; }

        [JsonPropertyName("color")]
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        public string Color { get; set; }

        [JsonPropertyName("fontType")]
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        public string FontType { get; set; }

        [JsonPropertyName("size")]
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        public string Size { get; set; }

        [JsonPropertyName("weight")]
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        public string Weight { get; set; }

        [JsonPropertyName("wrap")]
        public bool Wrap { get; set; }

        [JsonPropertyName("maxLines")]
        public int MaxLines { get; set; }

        [JsonPropertyName("horizontalAlignment")]
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        public string HorizontalAlignment { get; set; }
    }

    /// <summary>
    /// Base DTO for AdaptiveAction serialization.
    /// </summary>
    internal class AdaptiveActionDto
    {
        [JsonPropertyName("type")]
        public string Type { get; set; }

        [JsonPropertyName("id")]
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        public string Id { get; set; }

        [JsonPropertyName("title")]
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        public string Title { get; set; }

        [JsonPropertyName("iconUrl")]
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        public string IconUrl { get; set; }
    }
}