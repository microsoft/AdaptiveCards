/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 4.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package io.adaptivecards.objectmodel;

public class TableRow extends BaseCardElement {
  private transient long swigCPtr;
  private transient boolean swigCMemOwnDerived;

  protected TableRow(long cPtr, boolean cMemoryOwn) {
    super(AdaptiveCardObjectModelJNI.TableRow_SWIGSmartPtrUpcast(cPtr), true);
    swigCMemOwnDerived = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(TableRow obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void swigSetCMemOwn(boolean own) {
    swigCMemOwnDerived = own;
    super.swigSetCMemOwn(own);
  }

  @SuppressWarnings("deprecation")
  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwnDerived) {
        swigCMemOwnDerived = false;
        AdaptiveCardObjectModelJNI.delete_TableRow(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public TableRow() {
    this(AdaptiveCardObjectModelJNI.new_TableRow__SWIG_0(), true);
  }

  public TableRow(TableRow arg0) {
    this(AdaptiveCardObjectModelJNI.new_TableRow__SWIG_1(TableRow.getCPtr(arg0), arg0), true);
  }

  public JsonValue SerializeToJsonValue() {
    return new JsonValue(AdaptiveCardObjectModelJNI.TableRow_SerializeToJsonValue(swigCPtr, this), true);
  }

  public TableCellVector GetCells() {
    return new TableCellVector(AdaptiveCardObjectModelJNI.TableRow_GetCells__SWIG_0(swigCPtr, this), false);
  }

  public void SetCells(TableCellVector value) {
    AdaptiveCardObjectModelJNI.TableRow_SetCells(swigCPtr, this, TableCellVector.getCPtr(value), value);
  }

  public @androidx.annotation.Nullable VerticalContentAlignment GetVerticalCellContentAlignment() {
    StdOptionalVerticalContentAlignment optvalue = new StdOptionalVerticalContentAlignment(AdaptiveCardObjectModelJNI.TableRow_GetVerticalCellContentAlignment(swigCPtr, this), false);
    return optvalue.has_value() ? optvalue.value() : null;
  }

  public void SetVerticalCellContentAlignment(@androidx.annotation.Nullable VerticalContentAlignment value) {
    StdOptionalVerticalContentAlignment optvalue = (value == null) ? new StdOptionalVerticalContentAlignment() : new StdOptionalVerticalContentAlignment(value);
    {
      AdaptiveCardObjectModelJNI.TableRow_SetVerticalCellContentAlignment(swigCPtr, this, StdOptionalVerticalContentAlignment.getCPtr(optvalue), optvalue);
    }
  }

  public @androidx.annotation.Nullable HorizontalAlignment GetHorizontalCellContentAlignment() {
    StdOptionalHorizontalAlignment optvalue = new StdOptionalHorizontalAlignment(AdaptiveCardObjectModelJNI.TableRow_GetHorizontalCellContentAlignment(swigCPtr, this), false);
    return optvalue.has_value() ? optvalue.value() : null;
  }

  public void SetHorizontalCellContentAlignment(@androidx.annotation.Nullable HorizontalAlignment value) {
    StdOptionalHorizontalAlignment optvalue = (value == null) ? new StdOptionalHorizontalAlignment() : new StdOptionalHorizontalAlignment(value);
    {
      AdaptiveCardObjectModelJNI.TableRow_SetHorizontalCellContentAlignment(swigCPtr, this, StdOptionalHorizontalAlignment.getCPtr(optvalue), optvalue);
    }
  }

  public ContainerStyle GetStyle() {
    return ContainerStyle.swigToEnum(AdaptiveCardObjectModelJNI.TableRow_GetStyle(swigCPtr, this));
  }

  public void SetStyle(ContainerStyle value) {
    AdaptiveCardObjectModelJNI.TableRow_SetStyle(swigCPtr, this, value.swigValue());
  }

  public static TableRow DeserializeTableRowFromString(ParseContext context, String root) {
    long cPtr = AdaptiveCardObjectModelJNI.TableRow_DeserializeTableRowFromString(ParseContext.getCPtr(context), context, root);
    return (cPtr == 0) ? null : new TableRow(cPtr, true);
  }

  public static TableRow DeserializeTableRow(ParseContext context, JsonValue root) {
    long cPtr = AdaptiveCardObjectModelJNI.TableRow_DeserializeTableRow(ParseContext.getCPtr(context), context, JsonValue.getCPtr(root), root);
    return (cPtr == 0) ? null : new TableRow(cPtr, true);
  }

}
