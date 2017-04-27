import * as Enums from "./enums";
import * as HostConfig from "./host-configuration";

import markdownIt = require("markdown-it");
let markdownProcessor = new markdownIt();

export function processMarkdown(text: string): any {
    return markdownProcessor.render(text);
}

export function getValueOrDefault<T>(obj: any, defaultValue: T): T {
    return obj ? <T>obj : defaultValue;
}

export function isNullOrEmpty(value: string): boolean {
    return value === undefined || value === null || value === "";
}

export function appendChild(node: Node, child: Node) {
    if (child != null && child != undefined) {
        node.appendChild(child);
    }
}

export function renderSeparation(separationDefinition: HostConfig.ISeparationDefinition, orientation: Enums.Orientation): HTMLElement {
    var separator = document.createElement("div");

    if (orientation == "vertical") {
        if (separationDefinition.lineThickness) {
            separator.style.marginTop = (separationDefinition.spacing / 2) + "px";
            separator.style.paddingTop = (separationDefinition.spacing / 2) + "px";
            separator.style.borderTop = separationDefinition.lineThickness + "px solid " + stringToCssColor(separationDefinition.lineColor);
        }
        else {
            separator.style.height = separationDefinition.spacing + "px";
        }
    }
    else {
        if (separationDefinition.lineThickness) {
            separator.style.marginLeft = (separationDefinition.spacing / 2) + "px";
            separator.style.paddingLeft = (separationDefinition.spacing / 2) + "px";
            separator.style.borderLeft = separationDefinition.lineThickness + "px solid " + stringToCssColor(separationDefinition.lineColor);
        }
        else {
            separator.style.width = separationDefinition.spacing + "px";
        }
    }

    return separator;
}

export function stringToCssColor(color: string): string {
    var regEx = /#([0-9A-F]{2})([0-9A-F]{2})([0-9A-F]{2})([0-9A-F]{2})?/gi;

    var matches = regEx.exec(color);

    if (matches[4]) {
        var a = parseInt(matches[1], 16) / 255;
        var r = parseInt(matches[2], 16);
        var g = parseInt(matches[3], 16);
        var b = parseInt(matches[4], 16);

        return "rgba(" + r + "," + g + "," + b + "," + a + ")";
    }
    else {
        return color;
    }
}

export interface IInput {
    id: string;
    value: string;
}

export class StringWithSubstitutions {
    private _isProcessed: boolean = false;
    private _original: string = null;
    private _processed: string = null;

    substituteInputValues(inputs: Array<IInput>) {
        this._processed = this._original;

        var regEx = /\{{2}([a-z0-9_$@]+).value\}{2}/gi;
        var matches;

        while ((matches = regEx.exec(this._original)) != null) {
            var matchedInput: IInput = null;

            for (var i = 0; i < inputs.length; i++) {
                if (inputs[i].id.toLowerCase() == matches[1].toLowerCase()) {
                    matchedInput = inputs[i];
                    break;
                }
            }

            if (matchedInput) {
                this._processed = this._processed.replace(matches[0], matchedInput.value ? matchedInput.value : "");
            }
        };

        this._isProcessed = true;
    }

    get(): string {
        if (!this._isProcessed) {
            return this._original;
        }
        else {
            return this._processed;
        }
    }

    set(value: string) {
        this._original = value;
        this._isProcessed = false;
    }
}