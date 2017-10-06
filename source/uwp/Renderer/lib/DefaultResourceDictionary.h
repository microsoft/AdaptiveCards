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
    <Style TargetType=\"TextBlock\" x:Key=\"TextBlock.ExtraLarge\"> \
        <Setter Property=\"FontSize\" Value=\"30\"/> \
    </Style> \
    <Style TargetType=\"TextBlock\" x:Key=\"TextBlock.Large\"> \
        <Setter Property=\"FontSize\" Value=\"24\"/> \
    </Style> \
    <Style TargetType=\"TextBlock\" x:Key=\"TextBlock.Medium\"> \
        <Setter Property=\"FontSize\" Value=\"18\"/> \
    </Style> \
    <Style TargetType=\"TextBlock\" x:Key=\"TextBlock.Normal\"> \
        <Setter Property=\"FontSize\" Value=\"12\"/> \
    </Style> \
    <Style TargetType=\"TextBlock\" x:Key=\"TextBlock.Small\"> \
        <Setter Property=\"FontSize\" Value=\"8\"/> \
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
\
    <Style x:Key=\"SelectAction\" TargetType=\"Button\"> \
        <Setter Property=\"Background\" Value=\"{ThemeResource ListViewItemBackground}\" /> \
        <Setter Property=\"BorderThickness\" Value=\"0\" /> \
        <Setter Property=\"Padding\" Value=\"0\" /> \
        <Setter Property=\"HorizontalAlignment\" Value=\"Stretch\" /> \
        <Setter Property=\"HorizontalContentAlignment\" Value=\"Stretch\" /> \
        <Setter Property=\"VerticalAlignment\" Value=\"Center\" /> \
        <Setter Property=\"UseSystemFocusVisuals\" Value=\"True\" /> \
        <Setter Property=\"FocusVisualMargin\" Value=\"0\" /> \
        <Setter Property=\"FocusVisualPrimaryBrush\" Value=\"{ThemeResource ListViewItemFocusVisualPrimaryBrush}\" /> \
        <Setter Property=\"FocusVisualPrimaryThickness\" Value=\"2\" /> \
        <Setter Property=\"FocusVisualSecondaryBrush\" Value=\"{ThemeResource ListViewItemFocusVisualSecondaryBrush}\" /> \
        <Setter Property=\"FocusVisualSecondaryThickness\" Value=\"1\" /> \
        <Setter Property=\"Template\"> \
            <Setter.Value> \
                <ControlTemplate TargetType=\"Button\"> \
                    <Grid x:Name=\"RootGrid\" Background=\"{TemplateBinding Background}\"> \
                        <VisualStateManager.VisualStateGroups> \
                            <VisualStateGroup x:Name=\"CommonStates\"> \
                                <VisualState x:Name=\"Normal\"> \
                                    <Storyboard> \
                                        <PointerUpThemeAnimation Storyboard.TargetName=\"RootGrid\" /> \
                                    </Storyboard> \
                                </VisualState> \
                                <VisualState x:Name=\"PointerOver\"> \
                                    <Storyboard> \
                                        <ObjectAnimationUsingKeyFrames Storyboard.TargetName=\"RootGrid\" Storyboard.TargetProperty=\"Background\"> \
                                            <DiscreteObjectKeyFrame KeyTime=\"0\" Value=\"{ThemeResource ListViewItemBackgroundPointerOver}\" /> \
                                        </ObjectAnimationUsingKeyFrames> \
                                        <PointerUpThemeAnimation Storyboard.TargetName=\"RootGrid\" /> \
                                    </Storyboard> \
                                </VisualState> \
                                <VisualState x:Name=\"Pressed\"> \
                                    <Storyboard> \
                                        <ObjectAnimationUsingKeyFrames Storyboard.TargetName=\"RootGrid\" Storyboard.TargetProperty=\"Background\"> \
                                            <DiscreteObjectKeyFrame KeyTime=\"0\" Value=\"{ThemeResource ListViewItemBackgroundPressed}\" /> \
                                        </ObjectAnimationUsingKeyFrames> \
                                        <PointerDownThemeAnimation Storyboard.TargetName=\"RootGrid\" /> \
                                    </Storyboard> \
                                </VisualState> \
                            </VisualStateGroup> \
                        </VisualStateManager.VisualStateGroups> \
                        <ContentPresenter x:Name=\"ContentPresenter\" \
                            BorderBrush=\"{TemplateBinding BorderBrush}\" \
                            BorderThickness=\"{TemplateBinding BorderThickness}\" \
                            Content=\"{TemplateBinding Content}\" \
                            ContentTransitions=\"{TemplateBinding ContentTransitions}\" \
                            ContentTemplate=\"{TemplateBinding ContentTemplate}\" \
                            Padding=\"{TemplateBinding Padding}\" \
                            HorizontalContentAlignment=\"{TemplateBinding HorizontalContentAlignment}\" \
                            VerticalContentAlignment=\"{TemplateBinding VerticalContentAlignment}\" \
                            AutomationProperties.AccessibilityView=\"Raw\" /> \
                    </Grid> \
                </ControlTemplate> \
            </Setter.Value> \
        </Setter> \
    </Style> \
</ResourceDictionary>";