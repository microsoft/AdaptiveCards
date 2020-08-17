/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 4.0.1
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package io.adaptivecards.objectmodel;

public class LabelConfig {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected LabelConfig(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(LabelConfig obj) {
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
        AdaptiveCardObjectModelJNI.delete_LabelConfig(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setInputSpacing(Spacing value) {
    AdaptiveCardObjectModelJNI.LabelConfig_inputSpacing_set(swigCPtr, this, value.swigValue());
  }

  public Spacing getInputSpacing() {
    return Spacing.swigToEnum(AdaptiveCardObjectModelJNI.LabelConfig_inputSpacing_get(swigCPtr, this));
  }

  public void setRequiredInputs(InputLabelConfig value) {
    AdaptiveCardObjectModelJNI.LabelConfig_requiredInputs_set(swigCPtr, this, InputLabelConfig.getCPtr(value), value);
  }

  public InputLabelConfig getRequiredInputs() {
    long cPtr = AdaptiveCardObjectModelJNI.LabelConfig_requiredInputs_get(swigCPtr, this);
    return (cPtr == 0) ? null : new InputLabelConfig(cPtr, false);
  }

  public void setOptionalInputs(InputLabelConfig value) {
    AdaptiveCardObjectModelJNI.LabelConfig_optionalInputs_set(swigCPtr, this, InputLabelConfig.getCPtr(value), value);
  }

  public InputLabelConfig getOptionalInputs() {
    long cPtr = AdaptiveCardObjectModelJNI.LabelConfig_optionalInputs_get(swigCPtr, this);
    return (cPtr == 0) ? null : new InputLabelConfig(cPtr, false);
  }

  public static LabelConfig Deserialize(JsonValue json, LabelConfig defaultValue) {
    return new LabelConfig(AdaptiveCardObjectModelJNI.LabelConfig_Deserialize(JsonValue.getCPtr(json), json, LabelConfig.getCPtr(defaultValue), defaultValue), true);
  }

  public LabelConfig() {
    this(AdaptiveCardObjectModelJNI.new_LabelConfig(), true);
  }

}
