export declare class Splitter {
    private _isVertical;
    private _sizedELement;
    private _isPointerDown;
    private _lastClickedOffset;
    private pointerDown;
    private pointerMove;
    private pointerUp;
    onResized: (sender: Splitter, newSize: number) => void;
    readonly attachedTo: HTMLElement;
    minimum: number;
    constructor(attachedTo: HTMLElement, sizedElement: HTMLElement, isVertical?: boolean);
}
