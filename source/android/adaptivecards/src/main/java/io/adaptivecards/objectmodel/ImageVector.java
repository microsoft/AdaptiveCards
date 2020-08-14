/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 4.0.1
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package io.adaptivecards.objectmodel;

public class ImageVector extends java.util.AbstractList<Image> implements java.util.RandomAccess {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected ImageVector(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(ImageVector obj) {
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
        AdaptiveCardObjectModelJNI.delete_ImageVector(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public ImageVector(Image[] initialElements) {
    this();
    reserve(initialElements.length);

    for (Image element : initialElements) {
      add(element);
    }
  }

  public ImageVector(Iterable<Image> initialElements) {
    this();
    for (Image element : initialElements) {
      add(element);
    }
  }

  public Image get(int index) {
    return doGet(index);
  }

  public Image set(int index, Image e) {
    return doSet(index, e);
  }

  public boolean add(Image e) {
    modCount++;
    doAdd(e);
    return true;
  }

  public void add(int index, Image e) {
    modCount++;
    doAdd(index, e);
  }

  public Image remove(int index) {
    modCount++;
    return doRemove(index);
  }

  protected void removeRange(int fromIndex, int toIndex) {
    modCount++;
    doRemoveRange(fromIndex, toIndex);
  }

  public int size() {
    return doSize();
  }

  public ImageVector() {
    this(AdaptiveCardObjectModelJNI.new_ImageVector__SWIG_0(), true);
  }

  public ImageVector(ImageVector other) {
    this(AdaptiveCardObjectModelJNI.new_ImageVector__SWIG_1(ImageVector.getCPtr(other), other), true);
  }

  public long capacity() {
    return AdaptiveCardObjectModelJNI.ImageVector_capacity(swigCPtr, this);
  }

  public void reserve(long n) {
    AdaptiveCardObjectModelJNI.ImageVector_reserve(swigCPtr, this, n);
  }

  public boolean isEmpty() {
    return AdaptiveCardObjectModelJNI.ImageVector_isEmpty(swigCPtr, this);
  }

  public void clear() {
    AdaptiveCardObjectModelJNI.ImageVector_clear(swigCPtr, this);
  }

  public ImageVector(int count, Image value) {
    this(AdaptiveCardObjectModelJNI.new_ImageVector__SWIG_2(count, Image.getCPtr(value), value), true);
  }

  private int doSize() {
    return AdaptiveCardObjectModelJNI.ImageVector_doSize(swigCPtr, this);
  }

  private void doAdd(Image x) {
    AdaptiveCardObjectModelJNI.ImageVector_doAdd__SWIG_0(swigCPtr, this, Image.getCPtr(x), x);
  }

  private void doAdd(int index, Image x) {
    AdaptiveCardObjectModelJNI.ImageVector_doAdd__SWIG_1(swigCPtr, this, index, Image.getCPtr(x), x);
  }

  private Image doRemove(int index) {
    long cPtr = AdaptiveCardObjectModelJNI.ImageVector_doRemove(swigCPtr, this, index);
    return (cPtr == 0) ? null : new Image(cPtr, true);
  }

  private Image doGet(int index) {
    long cPtr = AdaptiveCardObjectModelJNI.ImageVector_doGet(swigCPtr, this, index);
    return (cPtr == 0) ? null : new Image(cPtr, true);
  }

  private Image doSet(int index, Image val) {
    long cPtr = AdaptiveCardObjectModelJNI.ImageVector_doSet(swigCPtr, this, index, Image.getCPtr(val), val);
    return (cPtr == 0) ? null : new Image(cPtr, true);
  }

  private void doRemoveRange(int fromIndex, int toIndex) {
    AdaptiveCardObjectModelJNI.ImageVector_doRemoveRange(swigCPtr, this, fromIndex, toIndex);
  }

}
