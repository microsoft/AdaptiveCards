/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 4.0.0
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package io.adaptivecards.objectmodel;

public class CaseInsensitiveHash {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected CaseInsensitiveHash(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(CaseInsensitiveHash obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  @SuppressWarnings("deprecation")
  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        AdaptiveCardObjectModelJNI.delete_CaseInsensitiveHash(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public CaseInsensitiveHash() {
    this(AdaptiveCardObjectModelJNI.new_CaseInsensitiveHash(), true);
  }

}
