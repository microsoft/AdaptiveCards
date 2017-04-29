/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.microsoft.adaptivecards.objectmodel;

public class SeparationOptions {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected SeparationOptions(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(SeparationOptions obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        AdaptiveCardObjectModelJNI.delete_SeparationOptions(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setSpacing(int value) {
    AdaptiveCardObjectModelJNI.SeparationOptions_spacing_set(swigCPtr, this, value);
  }

  public int getSpacing() {
    return AdaptiveCardObjectModelJNI.SeparationOptions_spacing_get(swigCPtr, this);
  }

  public void setLineThickness(int value) {
    AdaptiveCardObjectModelJNI.SeparationOptions_lineThickness_set(swigCPtr, this, value);
  }

  public int getLineThickness() {
    return AdaptiveCardObjectModelJNI.SeparationOptions_lineThickness_get(swigCPtr, this);
  }

  public void setLineColor(String value) {
    AdaptiveCardObjectModelJNI.SeparationOptions_lineColor_set(swigCPtr, this, value);
  }

  public String getLineColor() {
    return AdaptiveCardObjectModelJNI.SeparationOptions_lineColor_get(swigCPtr, this);
  }

  public SeparationOptions() {
    this(AdaptiveCardObjectModelJNI.new_SeparationOptions(), true);
  }

}
