/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.microsoft.adaptivecards.objectmodel;

public class OpenUrlAction extends BaseActionElement {
  private transient long swigCPtr;
  private transient boolean swigCMemOwnDerived;

  protected OpenUrlAction(long cPtr, boolean cMemoryOwn) {
    super(AdaptiveCardObjectModelJNI.OpenUrlAction_SWIGSmartPtrUpcast(cPtr), true);
    swigCMemOwnDerived = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(OpenUrlAction obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwnDerived) {
        swigCMemOwnDerived = false;
        AdaptiveCardObjectModelJNI.delete_OpenUrlAction(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public OpenUrlAction() {
    this(AdaptiveCardObjectModelJNI.new_OpenUrlAction(), true);
  }

  public SWIGTYPE_p_Json__Value SerializeToJsonValue() {
    return new SWIGTYPE_p_Json__Value(AdaptiveCardObjectModelJNI.OpenUrlAction_SerializeToJsonValue(swigCPtr, this), true);
  }

  public String GetUrl() {
    return AdaptiveCardObjectModelJNI.OpenUrlAction_GetUrl(swigCPtr, this);
  }

  public void SetUrl(String value) {
    AdaptiveCardObjectModelJNI.OpenUrlAction_SetUrl(swigCPtr, this, value);
  }

  public static OpenUrlAction dynamic_cast(BaseActionElement baseActionElement) {
    long cPtr = AdaptiveCardObjectModelJNI.OpenUrlAction_dynamic_cast(BaseActionElement.getCPtr(baseActionElement), baseActionElement);
    return (cPtr == 0) ? null : new OpenUrlAction(cPtr, true);
  }

}
