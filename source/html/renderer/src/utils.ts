import markdownIt = require("markdown-it");
let markdownProcessor = new markdownIt();

export function processMarkdown(text: string): any {
    return markdownProcessor.render(text);
}

export function isNullOrEmpty(value: string): boolean {
    return value === undefined || value === null || value === "";
}

export function appendChild(node: Node, child: Node) {
    if (child != null && child != undefined) {
        node.appendChild(child);
    }
}

export function getClassNameFromInstance(instance: any) {
    return getClassNameFromConstructor(instance.constructor);
}

export function getClassNameFromConstructor(constructor: any) {
    // There is a cleaner way to do this in ES6, but in order to support
    // IE11 we need to stick to ES5.
    var constructorString: string = constructor.toString();

    return constructorString.match(/\w+/g)[1];
}

export interface IPadding {
    left: number;
    top: number;
    right: number;
    bottom: number;
}

export function getHasBottomPadding(element: HTMLElement): boolean {
    return parseInt(window.getComputedStyle(element).paddingBottom) > 0;
}

function getActualPaddingInternal(element: HTMLElement, padding: IPadding) {
    var computedStyle = window.getComputedStyle(element);

    if (padding.top == 0) {
        padding.top = parseInt(computedStyle.paddingTop);
    }

    if (padding.right == 0) {
        padding.right = parseInt(computedStyle.paddingRight);
    }

    if (padding.bottom == 0) {
        padding.bottom = parseInt(computedStyle.paddingBottom);
    }

    if (padding.left == 0) {
        padding.left = parseInt(computedStyle.paddingLeft);
    }

    if (element.className.indexOf("rootContainer") >= 0) {
        return;
    }

    if (element.parentElement) {
        getActualPaddingInternal(element.parentElement, padding);
    }
}

export function getActualPadding(element: HTMLElement): IPadding {
    var padding: IPadding = { top: 0, right: 0, bottom: 0, left: 0 };

    getActualPaddingInternal(element, padding);

    return padding;
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