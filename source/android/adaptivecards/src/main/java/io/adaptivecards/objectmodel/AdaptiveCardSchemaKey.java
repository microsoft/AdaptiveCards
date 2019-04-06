/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 4.0.0
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package io.adaptivecards.objectmodel;

public enum AdaptiveCardSchemaKey {
  Accent(0),
  ActionAlignment,
  ActionMode,
  ActionOrientation,
  ActionSet,
  ActionSetConfig,
  Actions,
  ActionsOrientation,
  AdaptiveCard,
  AllowCustomStyle,
  AllowInlinePlayback,
  AltText,
  Attention,
  BackgroundColor,
  BackgroundImage,
  BackgroundImageUrl,
  BaseCardElement,
  BaseContainerStyle,
  Bleed,
  Body,
  Bolder,
  BorderColor,
  BorderThickness,
  Bottom,
  ButtonSpacing,
  Card,
  Center,
  ChoiceSet,
  Choices,
  Color,
  ColorConfig,
  Column,
  ColumnSet,
  Columns,
  Container,
  ContainerStyles,
  Dark,
  Data,
  DateInput,
  Default,
  DefaultPoster,
  ElementId,
  Emphasis,
  ExtraLarge,
  FactSet,
  Facts,
  Fallback,
  FallbackText,
  FontFamily,
  FontSizes,
  FontStyle,
  FontStyles,
  FontWeights,
  ForegroundColor,
  ForegroundColors,
  Good,
  Height,
  Highlight,
  HighlightColor,
  HighlightColors,
  HorizontalAlignment,
  IconPlacement,
  IconSize,
  IconUrl,
  Id,
  Image,
  ImageBaseUrl,
  ImageSet,
  ImageSize,
  ImageSizes,
  Images,
  InlineAction,
  Inlines,
  InlineTopMargin,
  IsMultiSelect,
  IsMultiline,
  IsRequired,
  IsSelected,
  IsSubtle,
  IsVisible,
  Items,
  Language,
  Large,
  Left,
  Light,
  Lighter,
  LineColor,
  LineThickness,
  Max,
  MaxActions,
  MaxImageHeight,
  MaxLength,
  MaxLines,
  MaxWidth,
  Media,
  Medium,
  Method,
  MimeType,
  Min,
  MinHeight,
  Mode,
  Monospace,
  NumberInput,
  Padding,
  Paragraphs,
  Placeholder,
  PlayButton,
  Poster,
  Repeat,
  RepeatHorizontally,
  RepeatVertically,
  Requires,
  RichTextBlock,
  Right,
  SelectAction,
  Sentiment,
  Separator,
  ShowActionMode,
  ShowCard,
  ShowCardActionConfig,
  Size,
  Small,
  Sources,
  Spacing,
  SpacingDefinition,
  Speak,
  Stretch,
  Style,
  Subtle,
  SupportsInteractivity,
  TargetElements,
  Text,
  TextBlock,
  TextConfig,
  TextInput,
  TextWeight,
  Thickness,
  TimeInput,
  Title,
  ToggleInput,
  Top,
  Type,
  Url,
  Value,
  ValueOff,
  ValueOn,
  Version,
  VerticalAlignment,
  VerticalContentAlignment,
  Warning,
  Weight,
  Width,
  Wrap;

  public final int swigValue() {
    return swigValue;
  }

  public static AdaptiveCardSchemaKey swigToEnum(int swigValue) {
    AdaptiveCardSchemaKey[] swigValues = AdaptiveCardSchemaKey.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (AdaptiveCardSchemaKey swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + AdaptiveCardSchemaKey.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private AdaptiveCardSchemaKey() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private AdaptiveCardSchemaKey(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private AdaptiveCardSchemaKey(AdaptiveCardSchemaKey swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}

