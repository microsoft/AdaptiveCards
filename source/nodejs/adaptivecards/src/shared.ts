// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Enums from "./enums";
import * as Utils from "./utils";

export class GlobalSettings {
    static useAdvancedTextBlockTruncation: boolean = true;
    static useAdvancedCardBottomTruncation: boolean = false;
    static useMarkdownInRadioButtonAndCheckbox: boolean = true;
    static allowMarkForTextHighlighting: boolean = false;
    static alwaysBleedSeparators: boolean = false;
    static enableFullJsonRoundTrip: boolean = false;
    static useBuiltInInputValidation: boolean = true;
    static displayInputValidationErrors: boolean = true;
}

export const ContentTypes = {
	applicationJson: "application/json",
	applicationXWwwFormUrlencoded: "application/x-www-form-urlencoded"
}

export interface IValidationError {
    error: Enums.ValidationError,
    message: string;
}

export interface ISeparationDefinition {
	spacing: number,
	lineThickness?: number,
	lineColor?: string
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
            throw new Error("The referencedInputs parameter cannot be null.")
        }

        for (let input of inputs) {
            let matches = new RegExp("\\{{2}(" + input.id + ").value\\}{2}", "gi").exec(<string>this._original);

            if (matches != null && input.id) {
                referencedInputs[input.id] = input;
            }
        }
    }

	substituteInputValues(inputs: Dictionary<IInput>, contentType: string) {
		this._processed = this._original;

        if (this._original) {
            let regEx = /\{{2}([a-z0-9_$@]+).value\}{2}/gi;
            let matches;

            while ((matches = regEx.exec(<string>this._original)) != null) {
                let matchedInput: IInput | undefined = undefined;

                for (let key of Object.keys(inputs)) {
                    if (key.toLowerCase() == matches[1].toLowerCase()) {
                        matchedInput = inputs[key];
                        break;
                    }
                }

                if (matchedInput) {
                    let valueForReplace = "";

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

                    this._processed = (<string>this._processed).replace(matches[0], valueForReplace);
                }
            };
        }

        this._isProcessed = true;
	}

	getOriginal(): string | undefined {
		return this._original;
	}

	get(): string | undefined {
		if (!this._isProcessed) {
			return this._original;
		}
		else {
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

	constructor(top: number = 0,
		right: number = 0,
		bottom: number = 0,
		left: number = 0) {
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

	constructor(top: Enums.Spacing = Enums.Spacing.None,
		right: Enums.Spacing = Enums.Spacing.None,
		bottom: Enums.Spacing = Enums.Spacing.None,
		left: Enums.Spacing = Enums.Spacing.None) {
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
		let result = new SizeAndUnit(0, Enums.SizeUnit.Weight);

		let regExp = /^([0-9]+)(px|\*)?$/g;
		let matches = regExp.exec(input);
		let expectedMatchCount = requireUnitSpecifier ? 3 : 2;

		if (matches && matches.length >= expectedMatchCount) {
			result.physicalSize = parseInt(matches[1]);

			if (matches.length == 3) {
				if (matches[2] == "px") {
					result.unit = Enums.SizeUnit.Pixel;
				}
			}

			return result;
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
export class UUID {
	private static lut: string[] = [];

	static generate(): string {
		let d0 = Math.random() * 0xffffffff | 0;
		let d1 = Math.random() * 0xffffffff | 0;
		let d2 = Math.random() * 0xffffffff | 0;
		let d3 = Math.random() * 0xffffffff | 0;

		return UUID.lut[d0 & 0xff] + UUID.lut[d0 >> 8 & 0xff] + UUID.lut[d0 >> 16 & 0xff] + UUID.lut[d0 >> 24 & 0xff] + '-' +
			UUID.lut[d1 & 0xff] + UUID.lut[d1 >> 8 & 0xff] + '-' + UUID.lut[d1 >> 16 & 0x0f | 0x40] + UUID.lut[d1 >> 24 & 0xff] + '-' +
			UUID.lut[d2 & 0x3f | 0x80] + UUID.lut[d2 >> 8 & 0xff] + '-' + UUID.lut[d2 >> 16 & 0xff] + UUID.lut[d2 >> 24 & 0xff] +
			UUID.lut[d3 & 0xff] + UUID.lut[d3 >> 8 & 0xff] + UUID.lut[d3 >> 16 & 0xff] + UUID.lut[d3 >> 24 & 0xff];
	}

	static initialize() {
		for (let i = 0; i < 256; i++) {
			UUID.lut[i] = (i < 16 ? '0' : '') + i.toString(16);
		}
	}
}

UUID.initialize();

export class Version {
    private _versionString: string;
    private _major: number;
    private _minor: number;
    private _isValid: boolean = true;
    private _label?: string;

    constructor(major: number = 1, minor: number = 1, label?: string) {
        this._major = major;
        this._minor = minor;
        this._label = label;
    }

    static parse(versionString: string, errors?: IValidationError[]): Version | undefined {
        if (!versionString) {
            return undefined;
        }

        let result = new Version();
        result._versionString = versionString;

        let regEx = /(\d+).(\d+)/gi;
        let matches = regEx.exec(versionString);

        if (matches != null && matches.length == 3) {
            result._major = parseInt(matches[1]);
            result._minor = parseInt(matches[2]);
        }
        else {
            result._isValid = false;
        }

        if (!result._isValid && errors) {
            errors.push(
                {
                    error: Enums.ValidationError.InvalidPropertyValue,
                    message: "Invalid version string: " + result._versionString
                }
            );
        }

        return result;
    }

    toString(): string {
        return !this._isValid ? this._versionString : this._major + "." + this._minor;
    }

    toJSON(): any {
        return this.toString();
    }

    compareTo(otherVersion: Version): number {
        if (!this.isValid || !otherVersion.isValid) {
            throw new Error("Cannot compare invalid version.");
        }

        if (this.major > otherVersion.major) {
            return 1;
        }
        else if (this.major < otherVersion.major) {
            return -1;
        }
        else if (this.minor > otherVersion.minor) {
            return 1;
        }
        else if (this.minor < otherVersion.minor) {
            return -1;
        }

        return 0;
    }

    get label(): string {
        return this._label ? this._label : this.toString();
    }

    get major(): number {
        return this._major;
    }

    get minor(): number {
        return this._minor;
    }

    get isValid(): boolean {
        return this._isValid;
    }
}

export type TargetVersion = Version | "*";

export class Versions {
    static readonly v1_0 = new Version(1, 0);
    static readonly v1_1 = new Version(1, 1);
    static readonly v1_2 = new Version(1, 2);
    static readonly latest = Versions.v1_2;
    static readonly vNext = new Version(1000, 0, "vNext");
}

export function isVersionLessOrEqual(version: TargetVersion, targetVersion: TargetVersion): boolean {
    if (version instanceof Version) {
        if (targetVersion instanceof Version) {
            return targetVersion.compareTo(version) >= 0;
        }
        else {
            // Target version is *
            return true;
        }
    }
    else {
        // Version is *
        return true;
    }
}