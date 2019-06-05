// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
export type Position = { x: number, y: number };

export enum ThumbMovementDirection {
    Horizontal,
    Vertical,
    Both
}

export class ThumbPanel {
    private _rootElement: HTMLElement;
    private _isPointerDown: boolean = false;
    private _thumb: HTMLElement;
    private _position: Position = { x: 0, y: 0 };

    private positionChanged() {
        if (this.onPositionChanged) {
            this.onPositionChanged(this);
        }
    }

    onPositionChanged: (sender: ThumbPanel) => void;

    constructor(readonly movementDirection: ThumbMovementDirection = ThumbMovementDirection.Both) {
        this._rootElement = document.createElement("div");
        this._rootElement.style.position = "relative";
        this._rootElement.style.width = "100%";
        this._rootElement.style.height = "100%";

        this._thumb = document.createElement("div");
        this._thumb.className = "ms-ctrl-thumbedPanel-thumb";
        this._thumb.style.position = "absolute";

        this._rootElement.onpointerdown = (ev: PointerEvent) => {
            this._isPointerDown = true;

            this._rootElement.setPointerCapture(ev.pointerId);

            ev.preventDefault();
        }
        this._rootElement.onpointerup = (ev: PointerEvent) => {
            this._isPointerDown = false;

            this._rootElement.releasePointerCapture(ev.pointerId);

            ev.preventDefault();
        }
        this._rootElement.onpointermove = (ev: PointerEvent) => {
            if (this._isPointerDown) {
                let rect = this._rootElement.getBoundingClientRect();
                let position = { x: ev.offsetX, y: ev.offsetY };

                if (position.x < 0) {
                    position.x = 0;
                }
                else if (position.x > rect.width) {
                    position.x = rect.width;
                }

                if (position.y < 0) {
                    position.y = 0;
                }
                else if (position.y > rect.height) {
                    position.y = rect.height;
                }

                this.position = {
                    x: 100 / rect.width * position.x,
                    y: 100 / rect.height * position.y
                }

                this.positionChanged();
            }

            ev.preventDefault();
        }

        this._rootElement.appendChild(this._thumb);

        this.position = { x: 0, y: 0 };
    }

    appendChild(child: HTMLElement) {
        this._rootElement.insertBefore(child, this._thumb);
    }

    setThumbColor(cssColor: string) {
        this._thumb.style.backgroundColor = cssColor;
    }

    get renderedElement(): HTMLElement {
        return this._rootElement;
    }

    get position(): Position {
        return this._position;
    }

    set position(value: Position) {
        if (value.x < 0) {
            value.x = 0;
        }

        if (value.x > 100) {
            value.x = 100;
        }

        if (value.y < 0) {
            value.y = 0;
        }

        if (value.y > 100) {
            value.y = 100;
        }

        if (this.movementDirection == ThumbMovementDirection.Vertical) {
            value.x = 50;
        }
        else if (this.movementDirection == ThumbMovementDirection.Horizontal) {
            value.y = 50;
        }

        this._position = value;

        this._thumb.style.left = this._position.x + "%";
        this._thumb.style.top = this._position.y + "%";
    }
}
