#pragma once

const PCWSTR c_defaultResourceDictionary = L"\
<ResourceDictionary \
    xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\" \
    xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\"> \
\
    <ResourceDictionary.ThemeDictionaries> \
        <ResourceDictionary x:Key=\"Dark\"> \
          <SolidColorBrush x:Key=\"TextColor.Accent\" Color=\"{ThemeResource SystemAccentColor}\"/> \
          <SolidColorBrush x:Key=\"TextColor.Default\" Color=\"{ThemeResource SystemBaseHighColor}\"/> \
        </ResourceDictionary> \
\
        <ResourceDictionary x:Key=\"Light\"> \
          <SolidColorBrush x:Key=\"TextColor.Accent\" Color=\"{ThemeResource SystemAccentColor}\"/> \
          <SolidColorBrush x:Key=\"TextColor.Default\" Color=\"{ThemeResource SystemBaseHighColor}\"/> \
        </ResourceDictionary> \
\
        <ResourceDictionary x:Key=\"HighContrast\"> \
          <SolidColorBrush x:Key=\"TextColor.Accent\" Color=\"{ThemeResource SystemColorWindowColor}\"/> \
          <SolidColorBrush x:Key=\"TextColor.Default\" Color=\"{ThemeResource SystemColorButtonTextColor}\"/> \
        </ResourceDictionary> \
    </ResourceDictionary.ThemeDictionaries> \
\
    <SolidColorBrush x:Key=\"TextColor.Good\" Color=\"Green\"/> \
    <SolidColorBrush x:Key=\"TextColor.Warning\" Color=\"Yellow\"/> \
    <SolidColorBrush x:Key=\"TextColor.Attention\" Color=\"Red\"/> \
\
    <FontWeight x:Key=\"TextWeight.Lighter\">Light</FontWeight> \
    <FontWeight x:Key=\"TextWeight.Normal\">Normal</FontWeight> \
    <FontWeight x:Key=\"TextWeight.Bolder\">Bold</FontWeight> \
\
    <Style TargetType=\"TextBlock\" x:Key=\"TextBlock.Large\"> \
        <Setter Property=\"FontSize\" Value=\"24\"/> \
    </Style> \
    <Style TargetType=\"TextBlock\" x:Key=\"TextBlock.Medium\"> \
        <Setter Property=\"FontSize\" Value=\"18\"/> \
    </Style> \
    <Style TargetType=\"TextBlock\" x:Key=\"TextBlock.Small\"> \
        <Setter Property=\"FontSize\" Value=\"12\"/> \
    </Style> \
\
    <Style TargetType=\"StackPanel\" x:Key=\"Container\"> \
        <Setter Property=\"Margin\" Value=\"0,0,0,0\"/> \
    </Style> \
    <Style TargetType=\"StackPanel\" x:Key=\"Container.StartGroup\"> \
        <Setter Property=\"Margin\" Value=\"0,10,0,0\"/> \
    </Style> \
\
    <Style TargetType=\"Grid\" x:Key=\"ColumnSet\"> \
        <Setter Property=\"Margin\" Value=\"0,0,0,0\"/> \
    </Style> \
</ResourceDictionary>";