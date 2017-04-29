/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.microsoft.adaptivecards.objectmodel;

public class AdaptiveCardOptions {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected AdaptiveCardOptions(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(AdaptiveCardOptions obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        AdaptiveCardObjectModelJNI.delete_AdaptiveCardOptions(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setPadding(BoundaryOptions value) {
    AdaptiveCardObjectModelJNI.AdaptiveCardOptions_padding_set(swigCPtr, this, BoundaryOptions.getCPtr(value), value);
  }

  public BoundaryOptions getPadding() {
    long cPtr = AdaptiveCardObjectModelJNI.AdaptiveCardOptions_padding_get(swigCPtr, this);
    return (cPtr == 0) ? null : new BoundaryOptions(cPtr, false);
  }

  public void setBorderColor(String value) {
    AdaptiveCardObjectModelJNI.AdaptiveCardOptions_borderColor_set(swigCPtr, this, value);
  }

  public String getBorderColor() {
    return AdaptiveCardObjectModelJNI.AdaptiveCardOptions_borderColor_get(swigCPtr, this);
  }

  public void setMaxActions(int value) {
    AdaptiveCardObjectModelJNI.AdaptiveCardOptions_maxActions_set(swigCPtr, this, value);
  }

  public int getMaxActions() {
    return AdaptiveCardObjectModelJNI.AdaptiveCardOptions_maxActions_get(swigCPtr, this);
  }

  public void setActionsOrientation(ActionsOrientation value) {
    AdaptiveCardObjectModelJNI.AdaptiveCardOptions_actionsOrientation_set(swigCPtr, this, value.swigValue());
  }

  public ActionsOrientation getActionsOrientation() {
    return ActionsOrientation.swigToEnum(AdaptiveCardObjectModelJNI.AdaptiveCardOptions_actionsOrientation_get(swigCPtr, this));
  }

  public void setActionAlignment(HorizontalAlignment value) {
    AdaptiveCardObjectModelJNI.AdaptiveCardOptions_actionAlignment_set(swigCPtr, this, value.swigValue());
  }

  public HorizontalAlignment getActionAlignment() {
    return HorizontalAlignment.swigToEnum(AdaptiveCardObjectModelJNI.AdaptiveCardOptions_actionAlignment_get(swigCPtr, this));
  }

  public void setTextColor(String value) {
    AdaptiveCardObjectModelJNI.AdaptiveCardOptions_textColor_set(swigCPtr, this, value);
  }

  public String getTextColor() {
    return AdaptiveCardObjectModelJNI.AdaptiveCardOptions_textColor_get(swigCPtr, this);
  }

  public void setBackgroundColor(String value) {
    AdaptiveCardObjectModelJNI.AdaptiveCardOptions_backgroundColor_set(swigCPtr, this, value);
  }

  public String getBackgroundColor() {
    return AdaptiveCardObjectModelJNI.AdaptiveCardOptions_backgroundColor_get(swigCPtr, this);
  }

  public AdaptiveCardOptions() {
    this(AdaptiveCardObjectModelJNI.new_AdaptiveCardOptions(), true);
  }

}
