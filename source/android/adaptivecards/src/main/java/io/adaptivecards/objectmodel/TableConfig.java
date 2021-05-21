/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 4.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package io.adaptivecards.objectmodel;

public class TableConfig {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected TableConfig(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(TableConfig obj) {
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
        AdaptiveCardObjectModelJNI.delete_TableConfig(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setCellSpacing(long value) {
    AdaptiveCardObjectModelJNI.TableConfig_cellSpacing_set(swigCPtr, this, value);
  }

  public long getCellSpacing() {
    return AdaptiveCardObjectModelJNI.TableConfig_cellSpacing_get(swigCPtr, this);
  }

  public static TableConfig Deserialize(JsonValue json, TableConfig defaultValue) {
    return new TableConfig(AdaptiveCardObjectModelJNI.TableConfig_Deserialize(JsonValue.getCPtr(json), json, TableConfig.getCPtr(defaultValue), defaultValue), true);
  }

  public TableConfig() {
    this(AdaptiveCardObjectModelJNI.new_TableConfig(), true);
  }

}
