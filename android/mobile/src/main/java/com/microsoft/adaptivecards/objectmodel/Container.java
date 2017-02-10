/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.microsoft.adaptivecards.objectmodel;

public class Container extends BaseCardElement {
  private transient long swigCPtr;
  private transient boolean swigCMemOwnDerived;

  protected Container(long cPtr, boolean cMemoryOwn) {
    super(AdaptiveCardObjectModelJNI.Container_SWIGSmartPtrUpcast(cPtr), true);
    swigCMemOwnDerived = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(Container obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwnDerived) {
        swigCMemOwnDerived = false;
        AdaptiveCardObjectModelJNI.delete_Container(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public Container() {
    this(AdaptiveCardObjectModelJNI.new_Container(), true);
  }

  public String Serialize() {
    return AdaptiveCardObjectModelJNI.Container_Serialize(swigCPtr, this);
  }

  public BaseCardElementVector GetItems() {
    return new BaseCardElementVector(AdaptiveCardObjectModelJNI.Container_GetItems(swigCPtr, this), false);
  }

  public void AddItem(BaseCardElement item) {
    AdaptiveCardObjectModelJNI.Container_AddItem(swigCPtr, this, BaseCardElement.getCPtr(item), item);
  }

  public BaseCardElement GetItem(long index) {
    long cPtr = AdaptiveCardObjectModelJNI.Container_GetItem(swigCPtr, this, index);
    return (cPtr == 0) ? null : new BaseCardElement(cPtr, true);
  }

  public static Container Deserialize(SWIGTYPE_p_Json__Value root) {
    long cPtr = AdaptiveCardObjectModelJNI.Container_Deserialize(SWIGTYPE_p_Json__Value.getCPtr(root));
    return (cPtr == 0) ? null : new Container(cPtr, true);
  }

}
