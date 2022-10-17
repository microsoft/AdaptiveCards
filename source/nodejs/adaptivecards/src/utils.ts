// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Enums from "./enums";
import * as Shared from "./shared";

// To work around TypeScript complaining about documentMode not being declared
// on type Document
declare global {
    // eslint-disable-next-line @typescript-eslint/naming-convention
    interface Document {
        documentMode?: any;
    }
}

export function isInternetExplorer(): boolean {
    // The documentMode property only exists in IE
    return window.document.documentMode !== undefined;
}

export function isMobileOS(): boolean {
    const userAgent = window.navigator.userAgent;

    return (
        !!userAgent.match(/Android/i) || !!userAgent.match(/iPad/i) || !!userAgent.match(/iPhone/i)
    );
}

/**
 * Generate a UUID prepended with "__ac-"
 */
export function generateUniqueId(): string {
    return "__ac-" + Shared.UUID.generate();
}

export function appendChild(node: Node, child: Node | undefined) {
    if (child) {
        node.appendChild(child);
    }
}

export function parseString(obj: any, defaultValue?: string): string | undefined {
    return typeof obj === "string" ? obj : defaultValue;
}

export function parseNumber(obj: any, defaultValue?: number): number | undefined {
    return typeof obj === "number" ? obj : defaultValue;
}

export function parseBool(value: any, defaultValue?: boolean): boolean | undefined {
    if (typeof value === "boolean") {
        return value;
    } else if (typeof value === "string") {
        switch (value.toLowerCase()) {
            case "true":
                return true;
            case "false":
                return false;
            default:
                return defaultValue;
        }
    }

    return defaultValue;
}

export function getEnumValueByName(
    enumType: { [s: number]: string },
    name: string
): number | undefined {
    // eslint-disable-next-line guard-for-in
    for (const key in enumType) {
        const keyAsNumber = parseInt(key, 10);

        if (keyAsNumber >= 0) {
            const value = enumType[key];

            if (value && typeof value === "string" && value.toLowerCase() === name.toLowerCase()) {
                return keyAsNumber;
            }
        }
    }

    return undefined;
}

export function parseEnum(
    enumType: { [s: number]: string },
    name: string,
    defaultValue?: number
): number | undefined {
    if (!name) {
        return defaultValue;
    }

    const enumValue = getEnumValueByName(enumType, name);

    return enumValue !== undefined ? enumValue : defaultValue;
}

export function stringToCssColor(color: string | undefined): string | undefined {
    if (color) {
        const regEx = /#([0-9A-F]{2})([0-9A-F]{2})([0-9A-F]{2})([0-9A-F]{2})?/gi;
        const matches = regEx.exec(color);

        if (matches && matches[4]) {
            const a = parseInt(matches[1], 16) / 255;
            const r = parseInt(matches[2], 16);
            const g = parseInt(matches[3], 16);
            const b = parseInt(matches[4], 16);

            return "rgba(" + r + "," + g + "," + b + "," + a + ")";
        }
    }

    return color;
}

function truncateWorker(
    element: HTMLElement,
    maxHeight: number,
    fullText: string,
    truncateAt: (text: string, idx: number) => void,
    lineHeight?: number
) {
    const fits = () => {
        // Allow a one pixel overflow to account for rounding differences
        // between browsers
        return maxHeight - element.scrollHeight >= -1.0;
    };

    if (fits()) {
        return;
    }

    const breakableIndices = findBreakableIndices(fullText);
    let lo = 0;
    let hi = breakableIndices.length;
    let bestBreakIdx = 0;

    // Do a binary search for the longest string that fits
    while (lo < hi) {
        const mid = Math.floor((lo + hi) / 2);
        truncateAt(fullText, breakableIndices[mid]);

        if (fits()) {
            bestBreakIdx = breakableIndices[mid];
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }

    truncateAt(fullText, bestBreakIdx);

    // If we have extra room, try to expand the string letter by letter
    // (covers the case where we have to break in the middle of a long word)
    if (lineHeight && maxHeight - element.scrollHeight >= lineHeight - 1.0) {
        let idx = findNextCharacter(fullText, bestBreakIdx);

        while (idx < fullText.length) {
            truncateAt(fullText, idx);

            if (fits()) {
                bestBreakIdx = idx;
                idx = findNextCharacter(fullText, idx);
            } else {
                break;
            }
        }

        truncateAt(fullText, bestBreakIdx);
    }
}

export function truncateText(element: HTMLElement, maxHeight: number, lineHeight?: number) {
    truncateWorker(
        element,
        maxHeight,
        element.innerText,
        (text: string, idx: number) => {
            element.innerText = text.substring(0, idx) + "...";
        },
        lineHeight
    );
}

/**
 * {@link truncate} has been deprecated and is no longer in use internally. This policy passes
 * content through as it always has, which is _supposed_ to be dealing with text only (see {@link
 * TextBlock.truncateIfSupported}), but had a bug where it might actually pass through an element
 * for which innerHTML yielded actual HTML (since fixed).
 */
const ttDeprecatedPolicy = (typeof window === 'undefined') ? undefined : window.trustedTypes?.createPolicy("adaptivecards#deprecatedExportedFunctionPolicy", {
    createHTML: (value) => value
});

/** @deprecated Use {@link truncateText} instead. */
export function truncate(element: HTMLElement, maxHeight: number, lineHeight?: number) {
    truncateWorker(
        element,
        maxHeight,
        element.innerHTML,
        (text: string, idx: number) => {
            const truncatedString = text.substring(0, idx) + "...";
            const truncatedHTML =
                ttDeprecatedPolicy?.createHTML(truncatedString) ?? truncatedString;
            element.innerHTML = truncatedHTML as string;
        },
        lineHeight
    );
}

function findBreakableIndices(html: string): number[] {
    const results: number[] = [];
    let idx = findNextCharacter(html, -1);

    while (idx < html.length) {
        if (html[idx] === " ") {
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
    while (currIdx < html.length && html[currIdx] === "<") {
        while (currIdx < html.length && html[currIdx++] !== ">") {
            continue;
        }
    }

    return currIdx;
}

export function getFitStatus(element: HTMLElement, containerEnd: number): Enums.ContainerFitStatus {
    const start = element.offsetTop;
    const end = start + element.clientHeight;

    if (end <= containerEnd) {
        return Enums.ContainerFitStatus.FullyInContainer;
    } else if (start < containerEnd) {
        return Enums.ContainerFitStatus.Overflowing;
    } else {
        return Enums.ContainerFitStatus.FullyOutOfContainer;
    }
}

export function getScrollX(): number {
    return window.pageXOffset;
}

export function getScrollY(): number {
    return window.pageYOffset;
}

export function clearElementChildren(element: HTMLElement) {
    while (element.firstChild) {
        element.removeChild(element.firstChild);
    }
}

export function addCancelSelectActionEventHandler(element: HTMLElement) {
    element.onclick = (e) => {
        e.preventDefault();
        e.cancelBubble = true;
    };
}
