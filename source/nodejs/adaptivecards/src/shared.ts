// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Enums from "./enums";

export type Refresh = {
    mode: Enums.RefreshMode;
    timeBetweenAutomaticRefreshes: number;
    maximumConsecutiveAutomaticRefreshes: number;
    allowManualRefreshesAfterAutomaticRefreshes: boolean;
};

export type AppletsSettings = {
    logEnabled: boolean;
    logLevel: Enums.LogLevel;
    maximumRetryAttempts: number;
    defaultTimeBetweenRetryAttempts: number;
    authPromptWidth: number;
    authPromptHeight: number;
    readonly refresh: Refresh;
    onLogEvent?: (level: Enums.LogLevel, message?: any, ...optionalParams: any[]) => void;
};

// eslint-disable-next-line @typescript-eslint/no-extraneous-class
export class GlobalSettings {
    static useAdvancedTextBlockTruncation: boolean = true;
    static useAdvancedCardBottomTruncation: boolean = false;
    static useMarkdownInRadioButtonAndCheckbox: boolean = true;
    static allowMarkForTextHighlighting: boolean = false;
    static alwaysBleedSeparators: boolean = false;
    static enableFullJsonRoundTrip: boolean = false;
    static displayInputValidationErrors: boolean = true;
    static allowPreProcessingPropertyValues: boolean = false;
    static setTabIndexAtCardRoot: boolean = true;
    static enableFallback: boolean = true;
    static useWebkitLineClamp: boolean = true;
    static allowMoreThanMaxActionsInOverflowMenu: boolean = false;
    static removePaddingFromContainersWithBackgroundImage: boolean = false;
    static resetInputsDirtyStateAfterActionExecution: boolean = true;

    static readonly applets: AppletsSettings = {
        logEnabled: true,
        logLevel: Enums.LogLevel.Error,
        maximumRetryAttempts: 3,
        defaultTimeBetweenRetryAttempts: 3000, // 3 seconds
        authPromptWidth: 400,
        authPromptHeight: 600,
        refresh: {
            mode: Enums.RefreshMode.Manual,
            timeBetweenAutomaticRefreshes: 3000, // 3 seconds
            maximumConsecutiveAutomaticRefreshes: 3,
            allowManualRefreshesAfterAutomaticRefreshes: true
        }
    };
}

export const ContentTypes = {
    applicationJson: "application/json",
    applicationXWwwFormUrlencoded: "application/x-www-form-urlencoded"
};

export interface ISeparationDefinition {
    spacing: number;
    lineThickness?: number;
    lineColor?: string;
}

export interface IInput {
    id?: string;
    value?: string;
    validateValue(): boolean;
}

export type Dictionary<T> = { [key: string]: T };

export class StringWithSubstitutions {
    private _isProcessed: boolean = false;
    private _original?: string;
    private _processed?: string;

    getReferencedInputs(inputs: IInput[], referencedInputs: Dictionary<IInput>) {
        if (!referencedInputs) {
            throw new Error("The referencedInputs parameter cannot be null.");
        }

        if (this._original) {
            for (const input of inputs) {
                const matches = new RegExp("\\{{2}(" + input.id + ").value\\}{2}", "gi").exec(
                    this._original
                );

                if (matches != null && input.id) {
                    referencedInputs[input.id] = input;
                }
            }
        }
    }

    substituteInputValues(inputs: Dictionary<IInput>, contentType: string) {
        this._processed = this._original;

        if (this._original) {
            const regEx = /\{{2}([a-z0-9_$@]+).value\}{2}/gi;
            let matches;

            while ((matches = regEx.exec(this._original)) !== null && this._processed) {
                for (const key of Object.keys(inputs)) {
                    if (key.toLowerCase() === matches[1].toLowerCase()) {
                        const matchedInput = inputs[key];

                        let valueForReplace = "";

                        if (matchedInput.value) {
                            valueForReplace = matchedInput.value;
                        }

                        if (contentType === ContentTypes.applicationJson) {
                            valueForReplace = JSON.stringify(valueForReplace);
                            valueForReplace = valueForReplace.slice(1, -1);
                        } else if (contentType === ContentTypes.applicationXWwwFormUrlencoded) {
                            valueForReplace = encodeURIComponent(valueForReplace);
                        }

                        this._processed = this._processed.replace(matches[0], valueForReplace);

                        break;
                    }
                }
            }
        }

        this._isProcessed = true;
    }

    getOriginal(): string | undefined {
        return this._original;
    }

    get(): string | undefined {
        if (!this._isProcessed) {
            return this._original;
        } else {
            return this._processed;
        }
    }

    set(value: string | undefined) {
        this._original = value;
        this._isProcessed = false;
    }
}

export class SpacingDefinition {
    left: number = 0;
    top: number = 0;
    right: number = 0;
    bottom: number = 0;

    constructor(top: number = 0, right: number = 0, bottom: number = 0, left: number = 0) {
        this.top = top;
        this.right = right;
        this.bottom = bottom;
        this.left = left;
    }
}

export class PaddingDefinition {
    top: Enums.Spacing = Enums.Spacing.None;
    right: Enums.Spacing = Enums.Spacing.None;
    bottom: Enums.Spacing = Enums.Spacing.None;
    left: Enums.Spacing = Enums.Spacing.None;

    constructor(
        top: Enums.Spacing = Enums.Spacing.None,
        right: Enums.Spacing = Enums.Spacing.None,
        bottom: Enums.Spacing = Enums.Spacing.None,
        left: Enums.Spacing = Enums.Spacing.None
    ) {
        this.top = top;
        this.right = right;
        this.bottom = bottom;
        this.left = left;
    }
}

export class SizeAndUnit {
    physicalSize: number;
    unit: Enums.SizeUnit;

    static parse(input: string, requireUnitSpecifier: boolean = false): SizeAndUnit {
        const result = new SizeAndUnit(0, Enums.SizeUnit.Weight);

        if (typeof input === "number") {
            result.physicalSize = input;

            return result;
        } else if (typeof input === "string") {
            const regExp = /^([0-9]+)(px|\*)?$/g;
            const matches = regExp.exec(input);
            const expectedMatchCount = requireUnitSpecifier ? 3 : 2;

            if (matches && matches.length >= expectedMatchCount) {
                result.physicalSize = parseInt(matches[1]);

                if (matches.length === 3) {
                    if (matches[2] === "px") {
                        result.unit = Enums.SizeUnit.Pixel;
                    }
                }

                return result;
            }
        }

        throw new Error("Invalid size: " + input);
    }

    constructor(physicalSize: number, unit: Enums.SizeUnit) {
        this.physicalSize = physicalSize;
        this.unit = unit;
    }
}

export interface IResourceInformation {
    url: string;
    mimeType: string;
}

/**
 * Fast UUID generator, RFC4122 version 4 compliant.
 * @author Jeff Ward (jcward.com).
 * @license MIT license
 * @link http://stackoverflow.com/questions/105034/how-to-create-a-guid-uuid-in-javascript/21963136#21963136
 **/
/* eslint-disable @typescript-eslint/no-extraneous-class, @typescript-eslint/naming-convention, no-bitwise */
export class UUID {
    private static lut: string[] = [];

    static generate(): string {
        const d0 = (Math.random() * 0xffffffff) | 0;
        const d1 = (Math.random() * 0xffffffff) | 0;
        const d2 = (Math.random() * 0xffffffff) | 0;
        const d3 = (Math.random() * 0xffffffff) | 0;

        return (
            UUID.lut[d0 & 0xff] +
            UUID.lut[(d0 >> 8) & 0xff] +
            UUID.lut[(d0 >> 16) & 0xff] +
            UUID.lut[(d0 >> 24) & 0xff] +
            "-" +
            UUID.lut[d1 & 0xff] +
            UUID.lut[(d1 >> 8) & 0xff] +
            "-" +
            UUID.lut[((d1 >> 16) & 0x0f) | 0x40] +
            UUID.lut[(d1 >> 24) & 0xff] +
            "-" +
            UUID.lut[(d2 & 0x3f) | 0x80] +
            UUID.lut[(d2 >> 8) & 0xff] +
            "-" +
            UUID.lut[(d2 >> 16) & 0xff] +
            UUID.lut[(d2 >> 24) & 0xff] +
            UUID.lut[d3 & 0xff] +
            UUID.lut[(d3 >> 8) & 0xff] +
            UUID.lut[(d3 >> 16) & 0xff] +
            UUID.lut[(d3 >> 24) & 0xff]
        );
    }

    static initialize() {
        for (let i = 0; i < 256; i++) {
            UUID.lut[i] = (i < 16 ? "0" : "") + i.toString(16);
        }
    }
}

UUID.initialize();
/* eslint-enable @typescript-eslint/no-extraneous-class, @typescript-eslint/naming-convention, no-bitwise */
