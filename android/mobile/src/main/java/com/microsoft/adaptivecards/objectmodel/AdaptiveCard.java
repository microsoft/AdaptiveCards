/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.microsoft.adaptivecards.objectmodel;

public class AdaptiveCard {
  private transient long swigCPtr;
  private transient boolean swigCMemOwn;

  protected AdaptiveCard(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(AdaptiveCard obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        AdaptiveCardObjectModelJNI.delete_AdaptiveCard(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public AdaptiveCard() {
    this(AdaptiveCardObjectModelJNI.new_AdaptiveCard__SWIG_0(), true);
  }

  public AdaptiveCard(String title, String description1, String description2, Container root) {
    this(AdaptiveCardObjectModelJNI.new_AdaptiveCard__SWIG_1(title, description1, description2, Container.getCPtr(root), root), true);
  }

  public String GetTitle() {
    return AdaptiveCardObjectModelJNI.AdaptiveCard_GetTitle(swigCPtr, this);
  }

  public void SetTitle(String value) {
    AdaptiveCardObjectModelJNI.AdaptiveCard_SetTitle(swigCPtr, this, value);
  }

  public String GetDescription1() {
    return AdaptiveCardObjectModelJNI.AdaptiveCard_GetDescription1(swigCPtr, this);
  }

  public void SetDescription1(String value) {
    AdaptiveCardObjectModelJNI.AdaptiveCard_SetDescription1(swigCPtr, this, value);
  }

  public String GetDescription2() {
    return AdaptiveCardObjectModelJNI.AdaptiveCard_GetDescription2(swigCPtr, this);
  }

  public void SetDescription2(String value) {
    AdaptiveCardObjectModelJNI.AdaptiveCard_SetDescription2(swigCPtr, this, value);
  }

  public Container GetRoot() {
    long cPtr = AdaptiveCardObjectModelJNI.AdaptiveCard_GetRoot(swigCPtr, this);
    return (cPtr == 0) ? null : new Container(cPtr, true);
  }

  public void SetRoot(Container value) {
    AdaptiveCardObjectModelJNI.AdaptiveCard_SetRoot(swigCPtr, this, Container.getCPtr(value), value);
  }

  public CardElementType GetElementType() {
    return CardElementType.swigToEnum(AdaptiveCardObjectModelJNI.AdaptiveCard_GetElementType(swigCPtr, this));
  }

  public static AdaptiveCard DeserializeFromFile(String jsonFile) {
    long cPtr = AdaptiveCardObjectModelJNI.AdaptiveCard_DeserializeFromFile(jsonFile);
    return (cPtr == 0) ? null : new AdaptiveCard(cPtr, true);
  }

  public static AdaptiveCard Deserialize(SWIGTYPE_p_Json__Value json) {
    long cPtr = AdaptiveCardObjectModelJNI.AdaptiveCard_Deserialize(SWIGTYPE_p_Json__Value.getCPtr(json));
    return (cPtr == 0) ? null : new AdaptiveCard(cPtr, true);
  }

}
