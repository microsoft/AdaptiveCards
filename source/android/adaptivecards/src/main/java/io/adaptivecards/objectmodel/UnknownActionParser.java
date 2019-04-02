/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 4.0.0
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package io.adaptivecards.objectmodel;

public class UnknownActionParser extends ActionElementParser {
  private transient long swigCPtr;
  private transient boolean swigCMemOwnDerived;

  protected UnknownActionParser(long cPtr, boolean cMemoryOwn) {
    super(AdaptiveCardObjectModelJNI.UnknownActionParser_SWIGSmartPtrUpcast(cPtr), true);
    swigCMemOwnDerived = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(UnknownActionParser obj) {
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
        AdaptiveCardObjectModelJNI.delete_UnknownActionParser(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public BaseActionElement Deserialize(ParseContext context, JsonValue root) {
    long cPtr = AdaptiveCardObjectModelJNI.UnknownActionParser_Deserialize(swigCPtr, this, ParseContext.getCPtr(context), context, JsonValue.getCPtr(root), root);
    return (cPtr == 0) ? null : new BaseActionElement(cPtr, true);
  }

}
