// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { IPoint } from "./miscellaneous";
import { KEY_ENTER, KEY_ESCAPE, KEY_SPACE, KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT } from "adaptivecards-controls";

export const DRAG_THRESHOLD = 10;

export abstract class DraggableElement {
    private _renderedElement: HTMLElement;
    private _isPointerOver: boolean;
    private _isPointerDown: boolean;
    private _isKeyboardDrag: boolean;
    private _lastClickedPoint: IPoint;
    private _dragging: boolean;

    private releasePointerCapture(pointerId: number) {
        this.getDragSourceElement().releasePointerCapture(pointerId);

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

    protected get isKeyboardDrag(): boolean {
        return this._isKeyboardDrag;
    }

    protected set isKeyboardDrag(value: boolean) {
        this._isKeyboardDrag = value;
    }

    protected startDrag() {
        if (this.isDraggable() && !this.dragging) {
            this.dragging = true;
            this._renderedElement.setAttribute("aria-grabbed", "true");

            if (this.onStartDrag) {
                this.onStartDrag(this);
            }
        }
    }

    protected pointerDown(e: PointerEvent) {
        if (!this._isPointerDown) {
            this._isPointerDown = true;
            this._lastClickedPoint = { x: e.offsetX, y: e.offsetY };

            this.getDragSourceElement().setPointerCapture(e.pointerId);
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

    protected keydown(e: KeyboardEvent) {
        if (this.isKeyboardDrag) {
            // already dragging, need to handle arrows/TAB, SPC/RET, and ESC/other keys
            switch (e.charCode) {
                case KEY_ESCAPE:
                default:
                    {
                        this.endDrag();
                        break;
                    }
            }
        }
        else {
            // not dragging yet, begin drag on correct stroke
            if (e.charCode === KEY_SPACE) {
                this.isKeyboardDrag = true;
                this.startDrag();
            }
        }
    }

    protected click(e: MouseEvent) {
        if (this.onClick) {
            this.onDoubleClick(this);
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

    protected getDragSourceElement(): HTMLElement {
        return this._renderedElement;
    }

    protected abstract internalRender(): HTMLElement;

    onStartDrag: (sender: DraggableElement) => void;
    onEndDrag: (sender: DraggableElement) => void;
    onClick: (sender: DraggableElement) => void;
    onDoubleClick: (sender: DraggableElement) => void;
    onKeydown: (sender: DraggableElement) => void;

    isDraggable(): boolean {
        return true;
    }

    endDrag() {
        if (this.dragging) {
            this.dragging = false;
            this._renderedElement.setAttribute("aria-grabbed", "false");

            if (this.onEndDrag) {
                this.onEndDrag(this);
            }
        }
    }

    updateLayout() {
        this.internalUpdateCssStyles();
        this.internalUpdateLayout();
    }

    render(): HTMLElement {
        this._renderedElement = this.internalRender();
        this._renderedElement.setAttribute("aria-grabbed", "false");
        this._renderedElement.setAttribute("draggable", "true");
        this._renderedElement.tabIndex = 0;

        let dragSourceElement = this.getDragSourceElement();
        dragSourceElement.onclick = (e: MouseEvent) => { this.click(e); };
        dragSourceElement.ondblclick = (e: MouseEvent) => { this.doubleClick(e); };

        if (this.isDraggable()) {
            dragSourceElement.onkeydown = (e: KeyboardEvent) => { this.keydown(e); };
            dragSourceElement.onmousedown = (e: MouseEvent) => { e.preventDefault(); };
            dragSourceElement.onpointerenter = () => { this.isPointerOver = true; };
            dragSourceElement.onpointerleave = () => { this.isPointerOver = false; };
            dragSourceElement.onpointerdown = (e: PointerEvent) => { this.pointerDown(e); };
            dragSourceElement.onpointerup = (e: PointerEvent) => { this.pointerUp(e); };
            dragSourceElement.onpointermove = (e: PointerEvent) => { this.pointerMove(e); };
        }

        return this._renderedElement;
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
