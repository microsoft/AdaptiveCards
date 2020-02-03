/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 4.0.0
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package io.adaptivecards.objectmodel;

public class AdaptiveCardConfig {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected AdaptiveCardConfig(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(AdaptiveCardConfig obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        AdaptiveCardObjectModelJNI.delete_AdaptiveCardConfig(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setAllowCustomStyle(boolean value) {
    AdaptiveCardObjectModelJNI.AdaptiveCardConfig_allowCustomStyle_set(swigCPtr, this, value);
  }

  public boolean getAllowCustomStyle() {
    return AdaptiveCardObjectModelJNI.AdaptiveCardConfig_allowCustomStyle_get(swigCPtr, this);
  }

  public static AdaptiveCardConfig Deserialize(JsonValue json, AdaptiveCardConfig defaultValue) {
    return new AdaptiveCardConfig(AdaptiveCardObjectModelJNI.AdaptiveCardConfig_Deserialize(JsonValue.getCPtr(json), json, AdaptiveCardConfig.getCPtr(defaultValue), defaultValue), true);
  }

  public AdaptiveCardConfig() {
    this(AdaptiveCardObjectModelJNI.new_AdaptiveCardConfig(), true);
  }

}
