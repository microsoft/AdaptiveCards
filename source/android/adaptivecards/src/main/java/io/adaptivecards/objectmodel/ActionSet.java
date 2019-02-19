/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 4.0.0
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package io.adaptivecards.objectmodel;

public class ActionSet extends BaseCardElement {
  private transient long swigCPtr;
  private transient boolean swigCMemOwnDerived;

  protected ActionSet(long cPtr, boolean cMemoryOwn) {
    super(AdaptiveCardObjectModelJNI.ActionSet_SWIGSmartPtrUpcast(cPtr), true);
    swigCMemOwnDerived = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(ActionSet obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void swigSetCMemOwn(boolean own) {
    swigCMemOwnDerived = own;
    super.swigSetCMemOwn(own);
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwnDerived) {
        swigCMemOwnDerived = false;
        AdaptiveCardObjectModelJNI.delete_ActionSet(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public ActionSet() {
    this(AdaptiveCardObjectModelJNI.new_ActionSet__SWIG_0(), true);
  }

  public ActionSet(BaseActionElementVector actions) {
    this(AdaptiveCardObjectModelJNI.new_ActionSet__SWIG_1(BaseActionElementVector.getCPtr(actions), actions), true);
  }

  public JsonValue SerializeToJsonValue() {
    return new JsonValue(AdaptiveCardObjectModelJNI.ActionSet_SerializeToJsonValue(swigCPtr, this), true);
  }

  public BaseActionElementVector GetActions() {
    return new BaseActionElementVector(AdaptiveCardObjectModelJNI.ActionSet_GetActions__SWIG_0(swigCPtr, this), false);
  }

  public static ActionSet dynamic_cast(BaseCardElement baseCardElement) {
    long cPtr = AdaptiveCardObjectModelJNI.ActionSet_dynamic_cast(BaseCardElement.getCPtr(baseCardElement), baseCardElement);
    return (cPtr == 0) ? null : new ActionSet(cPtr, true);
  }

}
