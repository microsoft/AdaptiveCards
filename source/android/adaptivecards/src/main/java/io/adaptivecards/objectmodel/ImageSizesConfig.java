/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 4.0.0
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package io.adaptivecards.objectmodel;

public class ImageSizesConfig {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected ImageSizesConfig(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(ImageSizesConfig obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        AdaptiveCardObjectModelJNI.delete_ImageSizesConfig(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setSmallSize(long value) {
    AdaptiveCardObjectModelJNI.ImageSizesConfig_smallSize_set(swigCPtr, this, value);
  }

  public long getSmallSize() {
    return AdaptiveCardObjectModelJNI.ImageSizesConfig_smallSize_get(swigCPtr, this);
  }

  public void setMediumSize(long value) {
    AdaptiveCardObjectModelJNI.ImageSizesConfig_mediumSize_set(swigCPtr, this, value);
  }

  public long getMediumSize() {
    return AdaptiveCardObjectModelJNI.ImageSizesConfig_mediumSize_get(swigCPtr, this);
  }

  public void setLargeSize(long value) {
    AdaptiveCardObjectModelJNI.ImageSizesConfig_largeSize_set(swigCPtr, this, value);
  }

  public long getLargeSize() {
    return AdaptiveCardObjectModelJNI.ImageSizesConfig_largeSize_get(swigCPtr, this);
  }

  public static ImageSizesConfig Deserialize(JsonValue json, ImageSizesConfig defaultValue) {
    return new ImageSizesConfig(AdaptiveCardObjectModelJNI.ImageSizesConfig_Deserialize(JsonValue.getCPtr(json), json, ImageSizesConfig.getCPtr(defaultValue), defaultValue), true);
  }

  public ImageSizesConfig() {
    this(AdaptiveCardObjectModelJNI.new_ImageSizesConfig(), true);
  }

}
