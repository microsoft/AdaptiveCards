/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 4.0.0
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package io.adaptivecards.objectmodel;

public class MediaSourceParser {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected MediaSourceParser(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(MediaSourceParser obj) {
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
        AdaptiveCardObjectModelJNI.delete_MediaSourceParser(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public MediaSourceParser() {
    this(AdaptiveCardObjectModelJNI.new_MediaSourceParser__SWIG_0(), true);
  }

  public MediaSourceParser(MediaSourceParser arg0) {
    this(AdaptiveCardObjectModelJNI.new_MediaSourceParser__SWIG_1(MediaSourceParser.getCPtr(arg0), arg0), true);
  }

  public static MediaSource Deserialize(ParseContext context, JsonValue root) {
    long cPtr = AdaptiveCardObjectModelJNI.MediaSourceParser_Deserialize(ParseContext.getCPtr(context), context, JsonValue.getCPtr(root), root);
    return (cPtr == 0) ? null : new MediaSource(cPtr, true);
  }

  public static MediaSource DeserializeFromString(ParseContext context, String jsonString) {
    long cPtr = AdaptiveCardObjectModelJNI.MediaSourceParser_DeserializeFromString(ParseContext.getCPtr(context), context, jsonString);
    return (cPtr == 0) ? null : new MediaSource(cPtr, true);
  }

}
