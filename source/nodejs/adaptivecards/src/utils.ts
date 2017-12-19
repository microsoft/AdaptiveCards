import * as Enums from "./enums";
import * as HostConfig from "./host-config";

export const ContentTypes = {
    applicationJson : "application/json",
    applicationXWwwFormUrlencoded : "application/x-www-form-urlencoded"
}

export interface ISeparationDefinition {
    spacing: number,
    lineThickness?: number,
    lineColor?: string
}

export interface IInput {
    id: string;
    value: string;
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

export function getEnumValueOrDefault(targetEnum: { [s: number]: string }, name: string, defaultValue: number): number {
    if (isNullOrEmpty(name)) {
        return defaultValue;
    }

    for (var key in targetEnum) {
        let isValueProperty = parseInt(key, 10) >= 0

        if (isValueProperty) {
            let value = targetEnum[key];

            if (value && typeof value === "string") {
                if (value.toLowerCase() === name.toLowerCase()) {
                    return parseInt(key, 10);
                }
            }
        }
    }

    return defaultValue;
}

export function parseHostConfigEnum(targetEnum: { [s: number]: string }, value: string | number, defaultValue: any): any {
    if (typeof value === "string") {
        return getEnumValueOrDefault(targetEnum, value, defaultValue);
    } else if (typeof value === "number") {
        return getValueOrDefault<typeof targetEnum>(value, defaultValue);
    } else {
        return defaultValue;
    }
}

export function renderSeparation(separationDefinition: ISeparationDefinition, orientation: Enums.Orientation): HTMLElement {
    if (separationDefinition.spacing > 0 || separationDefinition.lineThickness > 0) {
        var separator = document.createElement("div");

        if (orientation == Enums.Orientation.Horizontal) {
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

        separator.style.overflow = "hidden";

        return separator;
    }
    else {
        return null;
    }
}

export function stringToCssColor(color: string): string {
    var regEx = /#([0-9A-F]{2})([0-9A-F]{2})([0-9A-F]{2})([0-9A-F]{2})?/gi;

    var matches = regEx.exec(color);

    if (matches && matches[4]) {
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

export class StringWithSubstitutions {
    private _isProcessed: boolean = false;
    private _original: string = null;
    private _processed: string = null;

    substituteInputValues(inputs: Array<IInput>, contentType: string) {
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
                var valueForReplace = "";

                if (matchedInput.value) {
                    valueForReplace = matchedInput.value;
                }

                if (contentType === ContentTypes.applicationJson) {
                    valueForReplace = JSON.stringify(valueForReplace);
                    valueForReplace = valueForReplace.slice(1, -1);
                }
                else if (contentType === ContentTypes.applicationXWwwFormUrlencoded) {
                    valueForReplace = encodeURIComponent(valueForReplace);
                }

                this._processed = this._processed.replace(matches[0], valueForReplace);
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

export function truncate(element: HTMLElement,
                         maxHeight: number,
                         lineHeight?: number) {
    var fits = () => {
        // Allow a one pixel overflow to account for rounding differences
        // between browsers
        return maxHeight - element.scrollHeight >= -1.0;
    };

    if (fits()) return;

    var fullText = element.innerHTML;
    var truncateAt = (idx) => {
        element.innerHTML = fullText.substring(0, idx) + '...';
    }

    var breakableIndices = findBreakableIndices(fullText);
    var lo = 0;
    var hi = breakableIndices.length;
    var bestBreakIdx = 0;

    // Do a binary search for the longest string that fits
    while (lo < hi) {
        var mid = Math.floor((lo + hi) / 2);
        truncateAt(breakableIndices[mid]);

        if (fits()) {
            bestBreakIdx = breakableIndices[mid];
            lo = mid + 1;
        }
        else {
            hi = mid;
        }
    }

    truncateAt(bestBreakIdx);

    // If we have extra room, try to expand the string letter by letter
    // (covers the case where we have to break in the middle of a long word)
    if (lineHeight && maxHeight - element.scrollHeight >= lineHeight - 1.0) {
        let idx = findNextCharacter(fullText, bestBreakIdx);

        while (idx < fullText.length) {
            truncateAt(idx);

            if (fits()) {
                bestBreakIdx = idx;
                idx = findNextCharacter(fullText, idx);
            }
            else {
                break;
            }
        }

        truncateAt(bestBreakIdx);
    }
}

function findBreakableIndices(html: string): Array<number> {
    var results: Array<number> = [];
    var idx = findNextCharacter(html, -1);

    while (idx < html.length) {
        if (html[idx] == ' ') {
            results.push(idx);
        }

        idx = findNextCharacter(html, idx);
    }

    return results;
}

function findNextCharacter(html: string, currIdx: number): number {
    currIdx += 1;

    // If we found the start of an HTML tag, keep advancing until we get
    // past it, so we don't end up truncating in the middle of the tag
    while (currIdx < html.length && html[currIdx] == '<') {
        while (currIdx < html.length && html[currIdx++] != '>');
    }

    return currIdx;
}

export function getFitStatus(element: HTMLElement, containerEnd: number): Enums.ContainerFitStatus {
    var start = element.offsetTop;
    var end = start + element.clientHeight;

    if (end <= containerEnd) {
        return Enums.ContainerFitStatus.FullyInContainer;
    }
    else if (start < containerEnd) {
        return Enums.ContainerFitStatus.Overflowing;
    }
    else {
        return Enums.ContainerFitStatus.FullyOutOfContainer;
    }
}
