/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 4.0.0
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package io.adaptivecards.objectmodel;

public class TextInput extends BaseInputElement {
  private transient long swigCPtr;
  private transient boolean swigCMemOwnDerived;

  protected TextInput(long cPtr, boolean cMemoryOwn) {
    super(AdaptiveCardObjectModelJNI.TextInput_SWIGSmartPtrUpcast(cPtr), true);
    swigCMemOwnDerived = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(TextInput obj) {
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
        AdaptiveCardObjectModelJNI.delete_TextInput(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public TextInput() {
    this(AdaptiveCardObjectModelJNI.new_TextInput__SWIG_0(), true);
  }

  public TextInput(TextInput arg0) {
    this(AdaptiveCardObjectModelJNI.new_TextInput__SWIG_1(TextInput.getCPtr(arg0), arg0), true);
  }

  public JsonValue SerializeToJsonValue() {
    return new JsonValue(AdaptiveCardObjectModelJNI.TextInput_SerializeToJsonValue(swigCPtr, this), true);
  }

  public String GetPlaceholder() {
    return AdaptiveCardObjectModelJNI.TextInput_GetPlaceholder(swigCPtr, this);
  }

  public void SetPlaceholder(String value) {
    AdaptiveCardObjectModelJNI.TextInput_SetPlaceholder(swigCPtr, this, value);
  }

  public String GetValue() {
    return AdaptiveCardObjectModelJNI.TextInput_GetValue(swigCPtr, this);
  }

  public void SetValue(String value) {
    AdaptiveCardObjectModelJNI.TextInput_SetValue(swigCPtr, this, value);
  }

  public boolean GetIsMultiline() {
    return AdaptiveCardObjectModelJNI.TextInput_GetIsMultiline(swigCPtr, this);
  }

  public void SetIsMultiline(boolean value) {
    AdaptiveCardObjectModelJNI.TextInput_SetIsMultiline(swigCPtr, this, value);
  }

  public long GetMaxLength() {
    return AdaptiveCardObjectModelJNI.TextInput_GetMaxLength(swigCPtr, this);
  }

  public void SetMaxLength(long value) {
    AdaptiveCardObjectModelJNI.TextInput_SetMaxLength(swigCPtr, this, value);
  }

  public TextInputStyle GetTextInputStyle() {
    return TextInputStyle.swigToEnum(AdaptiveCardObjectModelJNI.TextInput_GetTextInputStyle(swigCPtr, this));
  }

  public void SetTextInputStyle(TextInputStyle value) {
    AdaptiveCardObjectModelJNI.TextInput_SetTextInputStyle(swigCPtr, this, value.swigValue());
  }

  public BaseActionElement GetInlineAction() {
    long cPtr = AdaptiveCardObjectModelJNI.TextInput_GetInlineAction(swigCPtr, this);
    return (cPtr == 0) ? null : new BaseActionElement(cPtr, true);
  }

  public void SetInlineAction(BaseActionElement action) {
    AdaptiveCardObjectModelJNI.TextInput_SetInlineAction(swigCPtr, this, BaseActionElement.getCPtr(action), action);
  }

  public String GetRegex() {
    return AdaptiveCardObjectModelJNI.TextInput_GetRegex(swigCPtr, this);
  }

  public void SetRegex(String value) {
    AdaptiveCardObjectModelJNI.TextInput_SetRegex(swigCPtr, this, value);
  }

  public static TextInput dynamic_cast(BaseCardElement baseCardElement) {
    long cPtr = AdaptiveCardObjectModelJNI.TextInput_dynamic_cast(BaseCardElement.getCPtr(baseCardElement), baseCardElement);
    return (cPtr == 0) ? null : new TextInput(cPtr, true);
  }

}
