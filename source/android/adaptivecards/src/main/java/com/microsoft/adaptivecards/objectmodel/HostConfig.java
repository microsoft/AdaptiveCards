/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.microsoft.adaptivecards.objectmodel;

public class HostConfig {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected HostConfig(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(HostConfig obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        AdaptiveCardObjectModelJNI.delete_HostConfig(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setFontFamily(String value) {
    AdaptiveCardObjectModelJNI.HostConfig_fontFamily_set(swigCPtr, this, value);
  }

  public String getFontFamily() {
    return AdaptiveCardObjectModelJNI.HostConfig_fontFamily_get(swigCPtr, this);
  }

  public void setFontSizes(FontSizesConfig value) {
    AdaptiveCardObjectModelJNI.HostConfig_fontSizes_set(swigCPtr, this, FontSizesConfig.getCPtr(value), value);
  }

  public FontSizesConfig getFontSizes() {
    long cPtr = AdaptiveCardObjectModelJNI.HostConfig_fontSizes_get(swigCPtr, this);
    return (cPtr == 0) ? null : new FontSizesConfig(cPtr, false);
  }

  public void setSupportsInteractivity(boolean value) {
    AdaptiveCardObjectModelJNI.HostConfig_supportsInteractivity_set(swigCPtr, this, value);
  }

  public boolean getSupportsInteractivity() {
    return AdaptiveCardObjectModelJNI.HostConfig_supportsInteractivity_get(swigCPtr, this);
  }

  public void setColors(ColorsConfig value) {
    AdaptiveCardObjectModelJNI.HostConfig_colors_set(swigCPtr, this, ColorsConfig.getCPtr(value), value);
  }

  public ColorsConfig getColors() {
    long cPtr = AdaptiveCardObjectModelJNI.HostConfig_colors_get(swigCPtr, this);
    return (cPtr == 0) ? null : new ColorsConfig(cPtr, false);
  }

  public void setImageSizes(ImageSizesConfig value) {
    AdaptiveCardObjectModelJNI.HostConfig_imageSizes_set(swigCPtr, this, ImageSizesConfig.getCPtr(value), value);
  }

  public ImageSizesConfig getImageSizes() {
    long cPtr = AdaptiveCardObjectModelJNI.HostConfig_imageSizes_get(swigCPtr, this);
    return (cPtr == 0) ? null : new ImageSizesConfig(cPtr, false);
  }

  public void setMaxActions(long value) {
    AdaptiveCardObjectModelJNI.HostConfig_maxActions_set(swigCPtr, this, value);
  }

  public long getMaxActions() {
    return AdaptiveCardObjectModelJNI.HostConfig_maxActions_get(swigCPtr, this);
  }

  public void setStrongSeparation(SeparationConfig value) {
    AdaptiveCardObjectModelJNI.HostConfig_strongSeparation_set(swigCPtr, this, SeparationConfig.getCPtr(value), value);
  }

  public SeparationConfig getStrongSeparation() {
    long cPtr = AdaptiveCardObjectModelJNI.HostConfig_strongSeparation_get(swigCPtr, this);
    return (cPtr == 0) ? null : new SeparationConfig(cPtr, false);
  }

  public void setAdaptiveCard(AdaptiveCardConfig value) {
    AdaptiveCardObjectModelJNI.HostConfig_adaptiveCard_set(swigCPtr, this, AdaptiveCardConfig.getCPtr(value), value);
  }

  public AdaptiveCardConfig getAdaptiveCard() {
    long cPtr = AdaptiveCardObjectModelJNI.HostConfig_adaptiveCard_get(swigCPtr, this);
    return (cPtr == 0) ? null : new AdaptiveCardConfig(cPtr, false);
  }

  public void setImageSet(ImageSetConfig value) {
    AdaptiveCardObjectModelJNI.HostConfig_imageSet_set(swigCPtr, this, ImageSetConfig.getCPtr(value), value);
  }

  public ImageSetConfig getImageSet() {
    long cPtr = AdaptiveCardObjectModelJNI.HostConfig_imageSet_get(swigCPtr, this);
    return (cPtr == 0) ? null : new ImageSetConfig(cPtr, false);
  }

  public void setImage(ImageConfig value) {
    AdaptiveCardObjectModelJNI.HostConfig_image_set(swigCPtr, this, ImageConfig.getCPtr(value), value);
  }

  public ImageConfig getImage() {
    long cPtr = AdaptiveCardObjectModelJNI.HostConfig_image_get(swigCPtr, this);
    return (cPtr == 0) ? null : new ImageConfig(cPtr, false);
  }

  public void setFactSet(FactSetConfig value) {
    AdaptiveCardObjectModelJNI.HostConfig_factSet_set(swigCPtr, this, FactSetConfig.getCPtr(value), value);
  }

  public FactSetConfig getFactSet() {
    long cPtr = AdaptiveCardObjectModelJNI.HostConfig_factSet_get(swigCPtr, this);
    return (cPtr == 0) ? null : new FactSetConfig(cPtr, false);
  }

  public void setColumn(ColumnConfig value) {
    AdaptiveCardObjectModelJNI.HostConfig_column_set(swigCPtr, this, ColumnConfig.getCPtr(value), value);
  }

  public ColumnConfig getColumn() {
    long cPtr = AdaptiveCardObjectModelJNI.HostConfig_column_get(swigCPtr, this);
    return (cPtr == 0) ? null : new ColumnConfig(cPtr, false);
  }

  public void setContainer(ContainerConfig value) {
    AdaptiveCardObjectModelJNI.HostConfig_container_set(swigCPtr, this, ContainerConfig.getCPtr(value), value);
  }

  public ContainerConfig getContainer() {
    long cPtr = AdaptiveCardObjectModelJNI.HostConfig_container_get(swigCPtr, this);
    return (cPtr == 0) ? null : new ContainerConfig(cPtr, false);
  }

  public void setColumnSet(ColumnSetConfig value) {
    AdaptiveCardObjectModelJNI.HostConfig_columnSet_set(swigCPtr, this, ColumnSetConfig.getCPtr(value), value);
  }

  public ColumnSetConfig getColumnSet() {
    long cPtr = AdaptiveCardObjectModelJNI.HostConfig_columnSet_get(swigCPtr, this);
    return (cPtr == 0) ? null : new ColumnSetConfig(cPtr, false);
  }

  public void setTextBlock(TextBlockConfig value) {
    AdaptiveCardObjectModelJNI.HostConfig_textBlock_set(swigCPtr, this, TextBlockConfig.getCPtr(value), value);
  }

  public TextBlockConfig getTextBlock() {
    long cPtr = AdaptiveCardObjectModelJNI.HostConfig_textBlock_get(swigCPtr, this);
    return (cPtr == 0) ? null : new TextBlockConfig(cPtr, false);
  }

  public void setDateInput(DateInputConfig value) {
    AdaptiveCardObjectModelJNI.HostConfig_dateInput_set(swigCPtr, this, DateInputConfig.getCPtr(value), value);
  }

  public DateInputConfig getDateInput() {
    long cPtr = AdaptiveCardObjectModelJNI.HostConfig_dateInput_get(swigCPtr, this);
    return (cPtr == 0) ? null : new DateInputConfig(cPtr, false);
  }

  public void setTimeInput(TimeInputConfig value) {
    AdaptiveCardObjectModelJNI.HostConfig_timeInput_set(swigCPtr, this, TimeInputConfig.getCPtr(value), value);
  }

  public TimeInputConfig getTimeInput() {
    long cPtr = AdaptiveCardObjectModelJNI.HostConfig_timeInput_get(swigCPtr, this);
    return (cPtr == 0) ? null : new TimeInputConfig(cPtr, false);
  }

  public void setNumberInput(NumberInputConfig value) {
    AdaptiveCardObjectModelJNI.HostConfig_numberInput_set(swigCPtr, this, NumberInputConfig.getCPtr(value), value);
  }

  public NumberInputConfig getNumberInput() {
    long cPtr = AdaptiveCardObjectModelJNI.HostConfig_numberInput_get(swigCPtr, this);
    return (cPtr == 0) ? null : new NumberInputConfig(cPtr, false);
  }

  public void setToggleInput(ToggleInputConfig value) {
    AdaptiveCardObjectModelJNI.HostConfig_toggleInput_set(swigCPtr, this, ToggleInputConfig.getCPtr(value), value);
  }

  public ToggleInputConfig getToggleInput() {
    long cPtr = AdaptiveCardObjectModelJNI.HostConfig_toggleInput_get(swigCPtr, this);
    return (cPtr == 0) ? null : new ToggleInputConfig(cPtr, false);
  }

  public void setTextInput(TextInputConfig value) {
    AdaptiveCardObjectModelJNI.HostConfig_textInput_set(swigCPtr, this, TextInputConfig.getCPtr(value), value);
  }

  public TextInputConfig getTextInput() {
    long cPtr = AdaptiveCardObjectModelJNI.HostConfig_textInput_get(swigCPtr, this);
    return (cPtr == 0) ? null : new TextInputConfig(cPtr, false);
  }

  public void setChoiceSet(ChoiceSetConfig value) {
    AdaptiveCardObjectModelJNI.HostConfig_choiceSet_set(swigCPtr, this, ChoiceSetConfig.getCPtr(value), value);
  }

  public ChoiceSetConfig getChoiceSet() {
    long cPtr = AdaptiveCardObjectModelJNI.HostConfig_choiceSet_get(swigCPtr, this);
    return (cPtr == 0) ? null : new ChoiceSetConfig(cPtr, false);
  }

  public void setActions(ActionsConfig value) {
    AdaptiveCardObjectModelJNI.HostConfig_actions_set(swigCPtr, this, ActionsConfig.getCPtr(value), value);
  }

  public ActionsConfig getActions() {
    long cPtr = AdaptiveCardObjectModelJNI.HostConfig_actions_get(swigCPtr, this);
    return (cPtr == 0) ? null : new ActionsConfig(cPtr, false);
  }

  public HostConfig() {
    this(AdaptiveCardObjectModelJNI.new_HostConfig(), true);
  }

}
