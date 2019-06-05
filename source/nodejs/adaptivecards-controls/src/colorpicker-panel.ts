// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { ThumbPanel, ThumbMovementDirection } from "./thumbpanel";

function constrainValue(value: number, min: number, max: number): number {
    let result = value;

    if (result < min) {
        result = min;
    }
    else if (result > max) {
        result = max;
    }

    return result;
}

function toHex(value: number): string {
    let result = Math.round(value).toString(16);

    if (result.length < 2) {
        result = "0" + result;
    }

    return result;
}

function parseNumber(value: string, min: number, max: number, asInt: boolean = true): number | undefined {
    try {
        let v = asInt ? parseInt(value) : parseFloat(value);

        return v >= min && v <= max ? v : undefined;
    }
    catch (e) {
        return undefined;
    }
}

export class Color {
    private _a: number = 1;
    private _r: number = 0;
    private _g: number = 0;
    private _b: number = 0;
    private _h: number = 0;
    private _s: number = 0;
    private _v: number = 0;

    private changed() {
        if (this.onChange) {
            this.onChange(this);
        }
    }

    private computeHSV() {
        let max = Math.max(this.r, this.g, this.b);
        let min = Math.min(this.r, this.g, this.b);

        let d = max - min;
        let h: number;
        let s = (max === 0 ? 0 : d / max);
        let v = max / 255;

        switch (max) {
            case min:
                h = 0;
                break;
            case this.r:
                h = (this.g - this.b) + d * (this.g < this.b ? 6: 0);
                h /= 6 * d;
                break;
            case this.g:
                h = (this.b - this.r) + d * 2;
                h /= 6 * d;
                break;
            case this.b:
                h = (this.r - this.g) + d * 4;
                h /= 6 * d;
                break;
        }

        this._h = h * 100;
        this._s = s * 100;
        this._v = v * 100;

        this.changed();
    }

    private computeRGB() {
        let h = this.h / 100;
        let s = this.s / 100;
        let v = this.v / 100;

        let i = Math.floor(h * 6);
        let f = h * 6 - i;
        let p = v * (1 - s);
        let q = v * (1 - f * s);
        let t = v * (1 - (1 - f) * s);
    
        let r: number;
        let g: number;
        let b: number;
    
        switch (i % 6) {
            case 0:
                r = v;
                g = t;
                b = p;
                break;
            case 1:
                r = q;
                g = v;
                b = p;
                break;
            case 2:
                r = p;
                g = v;
                b = t;
                break;
            case 3:
                r = p;
                g = q;
                b = v;
                break;
            case 4:
                r = t;
                g = p;
                b = v;
                break;
            case 5:
                r = v;
                g = p;
                b = q;
                break;
        }
    
        this._r = Math.round(r * 255);
        this._g = Math.round(g * 255);
        this._b = Math.round(b * 255);

        this.changed();
    }

    static fromRGBA(r: number = 0, g: number = 0, b: number = 0, a: number = 100) {
        let result = new Color();

        result.r = r;
        result.g = g;
        result.b = b;
        result.a = a;

        return result;
    }

    static fromHSVA(h: number = 0, s: number = 100, v: number = 100, a: number = 100) {
        let result = new Color();

        result.h = h;
        result.s = s;
        result.v = v;
        result.a = a;

        return result;
    }

    tryParseCode(code: string): boolean {
        let regEx = /^([0-9A-F]{2})([0-9A-F]{2})([0-9A-F]{2})$/gi;
        let matches = regEx.exec(code);
    
        if (matches && matches[3]) {
            this._r = parseInt(matches[1], 16);
            this._g = parseInt(matches[2], 16);
            this._b = parseInt(matches[3], 16);

            this.computeHSV();

            return true;
        }
        else {
            return false;
        }
    }
    
    onChange: (color: Color) => void;

    toNonTransparentColor(): Color {
        return Color.fromRGBA(this.r, this.g, this.b);
    }

    toCssColor(): string {
        return "rgba(" + this.r + "," + this.g + "," + this.b + "," + this.a / 100 + ")";
    }

    toColorCode(): string {
        return (toHex(this.r) + toHex(this.g) + toHex(this.b)).toUpperCase();
    }

    get a(): number {
        return this._a;
    }

    set a(value: number) {
        this._a = constrainValue(value, 0, 100);

        this.changed();
    }

    get r(): number {
        return this._r;
    }

    set r(value: number) {
        this._r = constrainValue(value, 0, 255);

        this.computeHSV();
    }

    get g(): number {
        return this._g;
    }

    set g(value: number) {
        this._g = constrainValue(value, 0, 255);

        this.computeHSV();
    }

    get b(): number {
        return this._b;
    }

    set b(value: number) {
        this._b = constrainValue(value, 0, 255);

        this.computeHSV();
    }

    get h(): number {
        return this._h;
    }

    set h(value: number) {
        this._h = constrainValue(value, 0, 100);

        this.computeRGB();
    }

    get s(): number {
        return this._s;
    }

    set s(value: number) {
        this._s = constrainValue(value, 0, 100);

        this.computeRGB();
    }

    get v(): number {
        return this._v;
    }

    set v(value: number) {
        this._v = constrainValue(value, 0, 100);

        this.computeRGB();
    }
}

export class ColorPickerPanel {
    private readonly _currentColor: Color;

    private _colorShadePanel: ThumbPanel;
    private _huePanel: ThumbPanel;
    private _transparencyPanel: ThumbPanel;
    private _transparencyOverlay: HTMLElement;
    private _selectedColorContainer: HTMLElement;
    private _rInput: HTMLInputElement;
    private _gInput: HTMLInputElement;
    private _bInput: HTMLInputElement;
    private _aInput: HTMLInputElement;
    private _hexInput: HTMLInputElement;
    private _isUpdatingFromRGBInputs: boolean = false;
    private _isUpdatingFromCodeInput: boolean = false;

    private updateLayout() {
        let selectedColorAsCssColor = this._currentColor.toCssColor();

        this._colorShadePanel.renderedElement.style.backgroundColor = Color.fromHSVA(this._currentColor.h, 100, 100).toCssColor();
        this._colorShadePanel.setThumbColor(selectedColorAsCssColor);

        this._transparencyOverlay.style.background = "linear-gradient(to right, transparent 0px, " + this._currentColor.toNonTransparentColor().toCssColor() + " 100%)";

        this._selectedColorContainer.style.backgroundColor = selectedColorAsCssColor;

        if (!this._isUpdatingFromRGBInputs) {
            this._rInput.value = this._currentColor.r.toString();
            this._gInput.value = this._currentColor.g.toString();
            this._bInput.value = this._currentColor.b.toString();
            this._aInput.value = this._currentColor.a.toFixed(2);
        }

        if (!this._isUpdatingFromCodeInput) {
            this._hexInput.value = this._currentColor.toColorCode();
        }
    }

    private updateThumbPositions() {
        this._huePanel.position = { x: this._currentColor.h, y: 0 };
        this._colorShadePanel.position = { x: this._currentColor.v, y: 100 - this._currentColor.s };
        this._transparencyPanel.position = { x: this._currentColor.a, y: 0 };
    }

    private updateColorFromCodeInput() {
        if (!this._isUpdatingFromCodeInput) {
            this._isUpdatingFromCodeInput = true;

            try {
                if (this._currentColor.tryParseCode(this._hexInput.value)) {
                    this.updateThumbPositions();
                }
            }
            finally {
                this._isUpdatingFromCodeInput = false;
            }
        }
    }

    private updateColorFromRGBInputs() {
        if (!this._isUpdatingFromRGBInputs) {
            this._isUpdatingFromRGBInputs = true;

            try {
                let r = parseNumber(this._rInput.value, 0, 255);
                let g = parseNumber(this._gInput.value, 0, 255);
                let b = parseNumber(this._bInput.value, 0, 255);
                let a = parseNumber(this._aInput.value, 0, 100);

                if (r != undefined && g != undefined && b != undefined && a != undefined) {
                    this._currentColor.r = r;
                    this._currentColor.g = g;
                    this._currentColor.b = b;
                    this._currentColor.a = a;

                    this.updateThumbPositions();
                }

                /*
                this._huePanel.position = { x: this._currentColor.h, y: 0 };
                this._colorShadePanel.position = { x: this._currentColor.v, y: 100 - this._currentColor.s };
                this._transparencyPanel.position = { x: this._currentColor.a, y: 0 };
                */
            }
            finally {
                this._isUpdatingFromRGBInputs = false;
            }
        }
    }

    private colorChanged() {
        if (this.onColorChanged) {
            this.onColorChanged(this);
        }
    }

    private render(): HTMLElement {
        let outerContainer = document.createElement("div");
        outerContainer.className = "ms-ctrl ms-ctrl-colorPicker-panel";

        let selectorsContainer = document.createElement("div");
        selectorsContainer.style.display = "flex";
        selectorsContainer.style.flexDirection = "column";
        selectorsContainer.style.flex = "1 1 auto";

        this._colorShadePanel = new ThumbPanel();
        this._colorShadePanel.renderedElement.style.border = "1px solid #CCCCCC";
        this._colorShadePanel.onPositionChanged = (panel: ThumbPanel) => {
            this._currentColor.v = panel.position.x;
            this._currentColor.s = 100 - panel.position.y;
        }
        this._colorShadePanel.position = { x: this._currentColor.v, y: 100 - this._currentColor.s };

        let overlay = document.createElement("div");
        overlay.style.position = "absolute";
        overlay.style.left = "0";
        overlay.style.top = "0";
        overlay.style.width = "100%";
        overlay.style.height = "100%";
        overlay.style.background = "linear-gradient(transparent 0px, white 100%)";

        this._colorShadePanel.appendChild(overlay);

        overlay = document.createElement("div");
        overlay.style.position = "absolute";
        overlay.style.left = "0";
        overlay.style.top = "0";
        overlay.style.width = "100%";
        overlay.style.height = "100%";
        overlay.style.background = "linear-gradient(to right, rgb(0, 0, 0) 0px, transparent 100%)";

        this._colorShadePanel.appendChild(overlay);

        selectorsContainer.appendChild(this._colorShadePanel.renderedElement);

        this._huePanel = new ThumbPanel(ThumbMovementDirection.Horizontal);
        this._huePanel.renderedElement.style.marginTop = "10px";
        this._huePanel.renderedElement.style.border = "1px solid #CCCCCC";
        this._huePanel.renderedElement.style.width = "100%";
        this._huePanel.renderedElement.style.height = "20px";
        this._huePanel.renderedElement.style.background = "linear-gradient(to left, red 0px, rgb(255, 0, 153) 10%, rgb(205, 0, 255) 20%, rgb(50, 0, 255) 30%, rgb(0, 102, 255) 40%, rgb(0, 255, 253) 50%, rgb(0, 255, 102) 60%, rgb(53, 255, 0) 70%, rgb(205, 255, 0) 80%, rgb(255, 153, 0) 90%, red 100%)";
        this._huePanel.onPositionChanged = (panel: ThumbPanel) => {
            this._currentColor.h = panel.position.x;
        }
        this._huePanel.position = { x: this._currentColor.h, y: 0 };

        selectorsContainer.appendChild(this._huePanel.renderedElement);

        this._transparencyPanel = new ThumbPanel(ThumbMovementDirection.Horizontal);
        this._transparencyPanel.renderedElement.style.backgroundImage = 'url("data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAoAAAAKCAYAAACNMs+9AAAAJUlEQVQYV2N89erVfwY0ICYmxoguxjgUFKI7GsTH5m4M3w1ChQC1/Ca8i2n1WgAAAABJRU5ErkJggg==")';
        this._transparencyPanel.renderedElement.style.marginTop = "10px";
        this._transparencyPanel.renderedElement.style.border = "1px solid #CCCCCC";
        this._transparencyPanel.renderedElement.style.width = "100%";
        this._transparencyPanel.renderedElement.style.height = "20px";
        this._transparencyPanel.onPositionChanged = (panel: ThumbPanel) => {
            this._currentColor.a = panel.position.x;
        }
        this._transparencyPanel.position = { x: this._currentColor.a, y: 0 };

        this._transparencyOverlay = document.createElement("div");
        this._transparencyOverlay.style.position = "absolute";
        this._transparencyOverlay.style.left = "0";
        this._transparencyOverlay.style.top = "0";
        this._transparencyOverlay.style.width = "100%";
        this._transparencyOverlay.style.height = "100%";

        this._transparencyPanel.appendChild(this._transparencyOverlay);

        selectorsContainer.appendChild(this._transparencyPanel.renderedElement);

        let selectionContainer = document.createElement("div");
        selectionContainer.style.flex = "0 0 auto";
        selectionContainer.style.marginLeft = "10px";

        this._selectedColorContainer = document.createElement("div");
        this._selectedColorContainer.style.width = "100%";
        this._selectedColorContainer.style.height = "80px";
        this._selectedColorContainer.style.border = "1px solid #CCCCCC";

        let table = document.createElement("table");
        table.style.borderCollapse = "collapse";
        table.style.marginTop = "10px";

        function addTableRow(rowData: { caption: string, inputType: string, min?: string, max?: string, onInput?: () => void }): HTMLInputElement {
            let input = document.createElement("input");
            input.className = "ms-ctrl ms-ctrl-colorPicker-input";
            input.type = rowData.inputType;
            input.style.width = "74px";

            if (rowData.min) {
                input.min = rowData.min;
            }

            if (rowData.max) {
                input.max = rowData.max;
            }

            if (rowData.onInput) {
                input.oninput = () => {
                    rowData.onInput();
                }
            }

            let row = document.createElement("tr");
            row.style.marginBottom = "5px";

            let captionCell = document.createElement("td");
            captionCell.style.paddingBottom = "5px";
            captionCell.innerText = rowData.caption;

            let inputCell = document.createElement("td");
            inputCell.style.paddingLeft = "4px";
            inputCell.style.paddingBottom = "5px";
            inputCell.appendChild(input);

            row.append(captionCell, inputCell);

            table.appendChild(row);

            return input;
        }
        
        this._rInput = addTableRow({ caption: "Red", inputType: "number", min: "0", max: "255", onInput: () => { this.updateColorFromRGBInputs(); }});
        this._gInput = addTableRow({ caption: "Green", inputType: "number", min: "0", max: "255", onInput: () => { this.updateColorFromRGBInputs(); }});
        this._bInput = addTableRow({ caption: "Blue", inputType: "number", min: "0", max: "255", onInput: () => { this.updateColorFromRGBInputs(); }});
        this._aInput = addTableRow({ caption: "Alpha", inputType: "number", min: "0", max: "255", onInput: () => { this.updateColorFromRGBInputs(); }});
        this._hexInput = addTableRow({ caption: "Code", inputType: "text", onInput: () => { this.updateColorFromCodeInput(); }});

        selectionContainer.appendChild(this._selectedColorContainer);
        selectionContainer.appendChild(table);

        outerContainer.appendChild(selectorsContainer);
        outerContainer.appendChild(selectionContainer);

        this.updateLayout();

        return outerContainer;
    }

    onColorChanged: (sender: ColorPickerPanel) => void;

    readonly renderedElement: HTMLElement;

    constructor() {
        this._currentColor = Color.fromHSVA(66, 0, 0);
        this._currentColor.onChange = () => {
            this.updateLayout();
            this.colorChanged();
        }

        this.renderedElement = this.render();
    }

    focus() {
        this._rInput.focus();
    }

    get color(): Color {
        return Color.fromRGBA(
            this._currentColor.r,
            this._currentColor.g,
            this._currentColor.b,
            this._currentColor.a);
    }

    set color(value: Color) {
        if (value) {
            this._currentColor.r = value.r;
            this._currentColor.g = value.g;
            this._currentColor.b = value.b;
            this._currentColor.a = value.a;

            this.updateColorFromRGBInputs();
        }
    }
}
