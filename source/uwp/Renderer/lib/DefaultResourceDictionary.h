// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

const PCWSTR c_defaultResourceDictionary = L"\
<ResourceDictionary \
    xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\" \
    xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\"> \
\
    <Style x:Key=\"Adaptive.TouchTarget\" TargetType=\"Button\" BasedOn=\"{StaticResource DefaultButtonStyle}\"> \
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
    <Style x:Key=\"Adaptive.SelectAction\" TargetType=\"Button\" BasedOn=\"{StaticResource  Adaptive.TouchTarget}\"/> \
    <Style x:Key=\"Adaptive.Input.Text.InlineAction\" TargetType=\"Button\" BasedOn=\"{StaticResource  Adaptive.TouchTarget}\"/> \
</ResourceDictionary>";
