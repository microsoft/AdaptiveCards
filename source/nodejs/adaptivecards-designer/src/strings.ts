// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

import { __ } from './i18n';

class OverrideableString {
    private _title: string;
    private readonly _defaultKey: string;

    constructor(defaultKey: string) {
        this._defaultKey = defaultKey;
    }

    get title() : string {
        if (this._title) {
            return this._title;
        }
        else {
            return __(this._defaultKey);
        }
    }

    set title(value: string) {
        this._title = value;
    }
}

class OverrideablePropertySheetStrings extends OverrideableString {
    commands: any;

    constructor({ title, commands }) {
        super(title);
        this.commands = commands;
    }
}

export class Strings {
    static readonly toolboxes = {
        toolPalette: new OverrideableString("cardElements"),
        cardEditor: new OverrideableString("cardEditor"),
        sampleDataEditor: new OverrideableString("sampleEditor"),
        propertySheet: new OverrideablePropertySheetStrings({
            title: "elementProperties",
            commands: {
                bindData: {
                    // TODO: fix this up
                    displayText: () => __("ellipsis"),
                    accessibleText: (propertyLabel: string) => __("dataBinding")
                }
            }
        }),
        cardStructure: new OverrideableString("cardStructure"),
        dataStructure: new OverrideableString("dataStructure")
    };
    static loadingEditor = __("loadingEditor");
}
