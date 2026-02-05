// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Linq;

namespace AdaptiveCards.SystemTextJson
{
    /// <summary>
    /// Converts between AdaptiveCard objects and DTOs for System.Text.Json serialization.
    /// </summary>
    internal static class AdaptiveCardDtoConverter
    {
        /// <summary>
        /// Converts an AdaptiveCard to its DTO representation.
        /// </summary>
        public static AdaptiveCardDto ToDto(AdaptiveCard card)
        {
            if (card == null)
                return null;

            var dto = new AdaptiveCardDto
            {
                Type = card.Type,
                Version = card.Version?.ToString(),
                FallbackText = card.FallbackText,
                Speak = card.Speak,
                Lang = card.Lang,
                MinHeight = card.MinHeight,
                Rtl = card.Rtl
            };

            // Convert background image (simplified for now)
            if (card.BackgroundImage != null)
            {
                if (card.BackgroundImage.Url != null)
                {
                    dto.BackgroundImage = card.BackgroundImage.Url;
                }
            }

            // Convert body elements
            if (card.Body != null && card.Body.Count > 0)
            {
                dto.Body = card.Body.Select(ConvertElement).Where(e => e != null).ToList();
            }

            // Convert actions
            if (card.Actions != null && card.Actions.Count > 0)
            {
                dto.Actions = card.Actions.Select(ConvertAction).Where(a => a != null).ToList();
            }

            // Convert select action
            if (card.SelectAction != null)
            {
                dto.SelectAction = ConvertAction(card.SelectAction);
            }

            // Convert vertical content alignment
            if (card.VerticalContentAlignment != AdaptiveVerticalContentAlignment.Top)
            {
                dto.VerticalContentAlignment = card.VerticalContentAlignment.ToString().ToLowerInvariant();
            }

            return dto;
        }

        /// <summary>
        /// Converts an AdaptiveCardDto back to an AdaptiveCard.
        /// </summary>
        public static AdaptiveCard FromDto(AdaptiveCardDto dto)
        {
            if (dto == null)
                return null;

            var card = new AdaptiveCard(dto.Version ?? "1.0")
            {
                FallbackText = dto.FallbackText,
                Speak = dto.Speak,
                Lang = dto.Lang,
                MinHeight = dto.MinHeight,
                Rtl = dto.Rtl
            };

            // Convert background image (simplified)
            if (dto.BackgroundImage is string backgroundImageUrl)
            {
                card.BackgroundImage = new AdaptiveBackgroundImage(backgroundImageUrl);
            }

            // Convert body elements
            if (dto.Body != null)
            {
                foreach (var elementObj in dto.Body)
                {
                    if (elementObj is System.Text.Json.JsonElement jsonElement)
                    {
                        var elementDto = System.Text.Json.JsonSerializer.Deserialize<AdaptiveElementDto>(jsonElement.GetRawText());
                        var element = ConvertElementFromDto(elementDto);
                        if (element != null)
                        {
                            card.Body.Add(element);
                        }
                    }
                }
            }

            // Convert actions
            if (dto.Actions != null)
            {
                foreach (var actionObj in dto.Actions)
                {
                    if (actionObj is System.Text.Json.JsonElement jsonElement)
                    {
                        var actionDto = System.Text.Json.JsonSerializer.Deserialize<AdaptiveActionDto>(jsonElement.GetRawText());
                        var action = ConvertActionFromDto(actionDto);
                        if (action != null)
                        {
                            card.Actions.Add(action);
                        }
                    }
                }
            }

            // Convert select action
            if (dto.SelectAction != null && dto.SelectAction is System.Text.Json.JsonElement selectActionElement)
            {
                var selectActionDto = System.Text.Json.JsonSerializer.Deserialize<AdaptiveActionDto>(selectActionElement.GetRawText());
                card.SelectAction = ConvertActionFromDto(selectActionDto);
            }

            // Convert vertical content alignment
            if (!string.IsNullOrEmpty(dto.VerticalContentAlignment))
            {
                if (Enum.TryParse<AdaptiveVerticalContentAlignment>(dto.VerticalContentAlignment, true, out var alignment))
                {
                    card.VerticalContentAlignment = alignment;
                }
            }

            return card;
        }

        private static object ConvertElement(AdaptiveElement element)
        {
            if (element == null)
                return null;

            switch (element)
            {
                case AdaptiveTextBlock textBlock:
                    return new AdaptiveTextBlockDto
                    {
                        Type = textBlock.Type,
                        Id = textBlock.Id,
                        Text = textBlock.Text,
                        Color = textBlock.Color != AdaptiveTextColor.Default ? textBlock.Color.ToString().ToLowerInvariant() : null,
                        Size = textBlock.Size != AdaptiveTextSize.Default ? textBlock.Size.ToString().ToLowerInvariant() : null,
                        Weight = textBlock.Weight != AdaptiveTextWeight.Default ? textBlock.Weight.ToString().ToLowerInvariant() : null,
                        Wrap = textBlock.Wrap,
                        MaxLines = textBlock.MaxLines,
                        HorizontalAlignment = textBlock.HorizontalAlignment != AdaptiveHorizontalAlignment.Left ? 
                            textBlock.HorizontalAlignment.ToString().ToLowerInvariant() : null,
                        Spacing = textBlock.Spacing != AdaptiveSpacing.Default ? textBlock.Spacing.ToString().ToLowerInvariant() : null,
                        Separator = textBlock.Separator,
                        IsVisible = textBlock.IsVisible
                    };

                default:
                    // For other element types, create a basic DTO
                    return new AdaptiveElementDto
                    {
                        Type = element.Type,
                        Id = element.Id,
                        Spacing = element.Spacing != AdaptiveSpacing.Default ? element.Spacing.ToString().ToLowerInvariant() : null,
                        Separator = element.Separator,
                        IsVisible = element.IsVisible
                    };
            }
        }

        private static AdaptiveElement ConvertElementFromDto(AdaptiveElementDto elementDto)
        {
            if (elementDto == null)
                return null;

            switch (elementDto.Type)
            {
                case "TextBlock":
                    if (elementDto is AdaptiveTextBlockDto textBlockDto)
                    {
                        var textBlock = new AdaptiveTextBlock(textBlockDto.Text)
                        {
                            Id = textBlockDto.Id,
                            Wrap = textBlockDto.Wrap,
                            MaxLines = textBlockDto.MaxLines,
                            Separator = textBlockDto.Separator,
                            IsVisible = textBlockDto.IsVisible
                        };

                        // Parse enum values
                        if (!string.IsNullOrEmpty(textBlockDto.Color) && 
                            Enum.TryParse<AdaptiveTextColor>(textBlockDto.Color, true, out var color))
                        {
                            textBlock.Color = color;
                        }

                        if (!string.IsNullOrEmpty(textBlockDto.Size) && 
                            Enum.TryParse<AdaptiveTextSize>(textBlockDto.Size, true, out var size))
                        {
                            textBlock.Size = size;
                        }

                        if (!string.IsNullOrEmpty(textBlockDto.Weight) && 
                            Enum.TryParse<AdaptiveTextWeight>(textBlockDto.Weight, true, out var weight))
                        {
                            textBlock.Weight = weight;
                        }

                        if (!string.IsNullOrEmpty(textBlockDto.HorizontalAlignment) && 
                            Enum.TryParse<AdaptiveHorizontalAlignment>(textBlockDto.HorizontalAlignment, true, out var alignment))
                        {
                            textBlock.HorizontalAlignment = alignment;
                        }

                        if (!string.IsNullOrEmpty(textBlockDto.Spacing) && 
                            Enum.TryParse<AdaptiveSpacing>(textBlockDto.Spacing, true, out var spacing))
                        {
                            textBlock.Spacing = spacing;
                        }

                        return textBlock;
                    }
                    break;

                default:
                    // For unknown element types, we can't create them without more information
                    break;
            }

            return null;
        }

        private static object ConvertAction(AdaptiveAction action)
        {
            if (action == null)
                return null;

            return new AdaptiveActionDto
            {
                Type = action.Type,
                Id = action.Id,
                Title = action.Title,
                IconUrl = action.IconUrl
            };
        }

        private static AdaptiveAction ConvertActionFromDto(AdaptiveActionDto actionDto)
        {
            if (actionDto == null)
                return null;

            switch (actionDto.Type)
            {
                case "Action.Submit":
                    return new AdaptiveSubmitAction
                    {
                        Id = actionDto.Id,
                        Title = actionDto.Title,
                        IconUrl = actionDto.IconUrl
                    };

                case "Action.OpenUrl":
                    return new AdaptiveOpenUrlAction
                    {
                        Id = actionDto.Id,
                        Title = actionDto.Title,
                        IconUrl = actionDto.IconUrl
                    };

                default:
                    // For other action types, return a basic submit action as fallback
                    return new AdaptiveSubmitAction
                    {
                        Id = actionDto.Id,
                        Title = actionDto.Title,
                        IconUrl = actionDto.IconUrl
                    };
            }
        }
    }
}