// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
export abstract class InputControl {
    private _rootElement: HTMLElement;

    protected validateRootElement(rootElement: HTMLElement) {
        // Do nothing - all root element types are valid.
    }

    protected keyDown(e: KeyboardEvent) {
        // Do nothing in base implementation
    }

    protected get rootElement(): HTMLElement {
        return this._rootElement;
    }

    attach(rootElement: HTMLElement) {
        this.validateRootElement(rootElement);

        this._rootElement = rootElement;
        this._rootElement.onkeydown = (e) => { this.keyDown(e); };
    }
}
