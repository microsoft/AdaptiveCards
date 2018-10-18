export declare const DRAG_THRESHOLD = 10;
export declare abstract class DraggableElement {
    private _renderedElement;
    private _isPointerOver;
    private _isPointerDown;
    private _lastClickedPoint;
    private _dragging;
    private releasePointerCapture;
    protected isPointerOver: boolean;
    protected startDrag(): void;
    protected pointerDown(e: PointerEvent): void;
    protected pointerUp(e: PointerEvent): void;
    protected pointerMove(e: PointerEvent): void;
    protected doubleClick(e: MouseEvent): void;
    protected internalUpdateCssStyles(): void;
    protected internalUpdateLayout(): void;
    protected abstract internalRender(): HTMLElement;
    onStartDrag: (sender: DraggableElement) => void;
    onEndDrag: (sender: DraggableElement) => void;
    onDoubleClick: (sender: DraggableElement) => void;
    isDraggable(): boolean;
    endDrag(): void;
    updateLayout(): void;
    render(): void;
    readonly renderedElement: HTMLElement;
    dragging: boolean;
}
