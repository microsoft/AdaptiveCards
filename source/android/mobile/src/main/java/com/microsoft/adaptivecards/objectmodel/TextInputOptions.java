/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.microsoft.adaptivecards.objectmodel;

public class TextInputOptions {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected TextInputOptions(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(TextInputOptions obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        AdaptiveCardObjectModelJNI.delete_TextInputOptions(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setSeparation(SeparationOptions value) {
    AdaptiveCardObjectModelJNI.TextInputOptions_separation_set(swigCPtr, this, SeparationOptions.getCPtr(value), value);
  }

  public SeparationOptions getSeparation() {
    long cPtr = AdaptiveCardObjectModelJNI.TextInputOptions_separation_get(swigCPtr, this);
    return (cPtr == 0) ? null : new SeparationOptions(cPtr, false);
  }

  public TextInputOptions() {
    this(AdaptiveCardObjectModelJNI.new_TextInputOptions(), true);
  }

}
