// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { IPoint } from "./miscellaneous";

export const DRAG_THRESHOLD = 10;

export abstract class DraggableElement {
    private _renderedElement: HTMLElement;
    private _isPointerOver: boolean;
    private _isPointerDown: boolean;
    private _lastClickedPoint: IPoint;
    private _dragging: boolean;

    private releasePointerCapture(pointerId: number) {
        this.renderedElement.releasePointerCapture(pointerId);

        this._isPointerDown = false;
    }

    protected get isPointerOver(): boolean {
        return this._isPointerOver;
    }

    protected set isPointerOver(value: boolean) {
        if (value != this._isPointerOver) {
            this._isPointerOver = value;

            this.updateLayout();
        }
    }

    protected startDrag() {
        if (this.isDraggable() && !this.dragging) {
            this.dragging = true;

            if (this.onStartDrag) {
                this.onStartDrag(this);
            }
        }
    }

    protected pointerDown(e: PointerEvent) {
        if (!this._isPointerDown) {
            this._isPointerDown = true;
            this._lastClickedPoint = { x: e.offsetX, y: e.offsetY };

            this.renderedElement.setPointerCapture(e.pointerId);
        }
    }

    protected pointerUp(e: PointerEvent) {
        if (this._isPointerDown) {
            this.releasePointerCapture(e.pointerId);

            this.endDrag();
        }
    }

    protected pointerMove(e: PointerEvent) {
        if (this._isPointerDown) {
            if (Math.abs(e.offsetX - this._lastClickedPoint.x) >= DRAG_THRESHOLD || Math.abs(e.offsetY - this._lastClickedPoint.y) >= DRAG_THRESHOLD) {
                this.releasePointerCapture(e.pointerId);

                this.startDrag();
            }
        }
    }

    protected doubleClick(e: MouseEvent) {
        if (this.onDoubleClick) {
            this.onDoubleClick(this);
        }
    }

    protected internalUpdateCssStyles() {
        // Do nothing in base implementation
    }

    protected internalUpdateLayout() {
        // Do nothing in base implementation
    }

    protected abstract internalRender(): HTMLElement;

    onStartDrag: (sender: DraggableElement) => void;
    onEndDrag: (sender: DraggableElement) => void;
    onDoubleClick: (sender: DraggableElement) => void;

    isDraggable(): boolean {
        return true;
    }

    endDrag() {
        if (this.dragging) {
            this.dragging = false;

            if (this.onEndDrag) {
                this.onEndDrag(this);
            }
        }
    }

    updateLayout() {
        this.internalUpdateCssStyles();
        this.internalUpdateLayout();
    }

    render() {
        this._renderedElement = this.internalRender();

        this._renderedElement.onmousedown = (e: MouseEvent) => { e.preventDefault(); };
        this._renderedElement.ondblclick = (e: MouseEvent) => { this.doubleClick(e); };

        this._renderedElement.onpointerenter = () => { this.isPointerOver = true; };
        this._renderedElement.onpointerleave = () => { this.isPointerOver = false; };
        this._renderedElement.onpointerdown = (e: PointerEvent) => { this.pointerDown(e); };
        this._renderedElement.onpointerup = (e: PointerEvent) => { this.pointerUp(e); };
        this._renderedElement.onpointermove = (e: PointerEvent) => { this.pointerMove(e); };
    }

    get renderedElement(): HTMLElement {
        return this._renderedElement;
    }

    get dragging(): boolean {
        return this._dragging;
    }

    set dragging(value: boolean) {
        this._dragging = value;

        this.internalUpdateCssStyles();
    }
}
