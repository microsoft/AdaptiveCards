// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Enums from "./enums";
import * as Shared from "./shared";
import { HostConfig } from "./host-config";

export function isMobileOS(): boolean {
    let userAgent = window.navigator.userAgent;

    return !!userAgent.match(/Android/i) || !!userAgent.match(/iPad/i) || !!userAgent.match(/iPhone/i);
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
    }
    else if (typeof value === "string") {
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

export function getEnumValueByName(enumType: { [s: number]: string }, name: string) : number | undefined {
    for (let key in enumType) {
        let keyAsNumber = parseInt(key, 10);

        if (keyAsNumber >= 0) {
            let value = enumType[key];

            if (value && typeof value === "string" && value.toLowerCase() === name.toLowerCase()) {
                return keyAsNumber;
            }
        }
    }

    return undefined;
}

export function parseEnum(enumType: { [s: number]: string }, name: string, defaultValue?: number): number | undefined {
    if (!name) {
        return defaultValue;
    }

    let enumValue = getEnumValueByName(enumType, name);

    return enumValue !== undefined ? enumValue : defaultValue;
}

export function renderSeparation(hostConfig: HostConfig, separationDefinition: Shared.ISeparationDefinition, orientation: Enums.Orientation): HTMLElement | undefined {
    if (separationDefinition.spacing > 0 || (separationDefinition.lineThickness && separationDefinition.lineThickness > 0)) {
        let separator = document.createElement("div");
        separator.className = hostConfig.makeCssClassName("ac-" + (orientation == Enums.Orientation.Horizontal ? "horizontal" : "vertical") + "-separator");
        separator.setAttribute("aria-hidden", "true");

        let color = separationDefinition.lineColor ? stringToCssColor(separationDefinition.lineColor) : "";

        if (orientation == Enums.Orientation.Horizontal) {
            if (separationDefinition.lineThickness) {
                separator.style.paddingTop = (separationDefinition.spacing / 2) + "px";
                separator.style.marginBottom = (separationDefinition.spacing / 2) + "px";
                separator.style.borderBottom = separationDefinition.lineThickness + "px solid " + color;
            }
            else {
                separator.style.height = separationDefinition.spacing + "px";
            }
        }
        else {
            if (separationDefinition.lineThickness) {
                separator.style.paddingLeft = (separationDefinition.spacing / 2) + "px";
                separator.style.marginRight = (separationDefinition.spacing / 2) + "px";
                separator.style.borderRight = separationDefinition.lineThickness + "px solid " + color;
            }
            else {
                separator.style.width = separationDefinition.spacing + "px";
            }
        }

        separator.style.overflow = "hidden";
        separator.style.flex = "0 0 auto";

        return separator;
    }
    else {
        return undefined;
    }
}

export function stringToCssColor(color: string | undefined): string | undefined {
    if (color) {
        let regEx = /#([0-9A-F]{2})([0-9A-F]{2})([0-9A-F]{2})([0-9A-F]{2})?/gi;
        let matches = regEx.exec(color);

        if (matches && matches[4]) {
            let a = parseInt(matches[1], 16) / 255;
            let r = parseInt(matches[2], 16);
            let g = parseInt(matches[3], 16);
            let b = parseInt(matches[4], 16);

            return "rgba(" + r + "," + g + "," + b + "," + a + ")";
        }
    }

    return color;
}

export function truncate(element: HTMLElement,
    maxHeight: number,
    lineHeight?: number) {
    let fits = () => {
        // Allow a one pixel overflow to account for rounding differences
        // between browsers
        return maxHeight - element.scrollHeight >= -1.0;
    };

    if (fits()) return;

    let fullText = element.innerHTML;
    let truncateAt = (idx: any) => {
        element.innerHTML = fullText.substring(0, idx) + '...';
    }

    let breakableIndices = findBreakableIndices(fullText);
    let lo = 0;
    let hi = breakableIndices.length;
    let bestBreakIdx = 0;

    // Do a binary search for the longest string that fits
    while (lo < hi) {
        let mid = Math.floor((lo + hi) / 2);
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

function findBreakableIndices(html: string): number[] {
    let results: number[] = [];
    let idx = findNextCharacter(html, -1);

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
    let start = element.offsetTop;
    let end = start + element.clientHeight;

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
