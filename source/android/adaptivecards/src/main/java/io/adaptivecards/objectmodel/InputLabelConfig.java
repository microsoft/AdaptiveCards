/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 4.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package io.adaptivecards.objectmodel;

public class InputLabelConfig {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected InputLabelConfig(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(InputLabelConfig obj) {
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
        AdaptiveCardObjectModelJNI.delete_InputLabelConfig(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setColor(ForegroundColor value) {
    AdaptiveCardObjectModelJNI.InputLabelConfig_color_set(swigCPtr, this, value.swigValue());
  }

  public ForegroundColor getColor() {
    return ForegroundColor.swigToEnum(AdaptiveCardObjectModelJNI.InputLabelConfig_color_get(swigCPtr, this));
  }

  public void setIsSubtle(boolean value) {
    AdaptiveCardObjectModelJNI.InputLabelConfig_isSubtle_set(swigCPtr, this, value);
  }

  public boolean getIsSubtle() {
    return AdaptiveCardObjectModelJNI.InputLabelConfig_isSubtle_get(swigCPtr, this);
  }

  public void setSize(TextSize value) {
    AdaptiveCardObjectModelJNI.InputLabelConfig_size_set(swigCPtr, this, value.swigValue());
  }

  public TextSize getSize() {
    return TextSize.swigToEnum(AdaptiveCardObjectModelJNI.InputLabelConfig_size_get(swigCPtr, this));
  }

  public void setSuffix(String value) {
    AdaptiveCardObjectModelJNI.InputLabelConfig_suffix_set(swigCPtr, this, value);
  }

  public String getSuffix() {
    return AdaptiveCardObjectModelJNI.InputLabelConfig_suffix_get(swigCPtr, this);
  }

  public void setWeight(TextWeight value) {
    AdaptiveCardObjectModelJNI.InputLabelConfig_weight_set(swigCPtr, this, value.swigValue());
  }

  public TextWeight getWeight() {
    return TextWeight.swigToEnum(AdaptiveCardObjectModelJNI.InputLabelConfig_weight_get(swigCPtr, this));
  }

  public static InputLabelConfig Deserialize(JsonValue json, InputLabelConfig defaultValue) {
    return new InputLabelConfig(AdaptiveCardObjectModelJNI.InputLabelConfig_Deserialize(JsonValue.getCPtr(json), json, InputLabelConfig.getCPtr(defaultValue), defaultValue), true);
  }

  public InputLabelConfig() {
    this(AdaptiveCardObjectModelJNI.new_InputLabelConfig(), true);
  }

}
