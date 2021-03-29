// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

import * as React from "react";
import * as ReactDOM from "react-dom";
import * as AC from "adaptivecards";
import * as Shared from "../utils/shared";
import { ActionButton } from "./ActionButton";

export const createActionDiv = (
    action: AC.Action,
    baseCssClass: string,
    iconPlacement: AC.ActionIconPlacement,
    iconSize: number): HTMLDivElement => {
    const div = Shared.getDiv();
    ReactDOM.render(
        <ActionButton
            action={action}
            className={baseCssClass}
            iconPlacement={iconPlacement}
            iconSize={iconSize}></ActionButton>, div);
    return div;
};

export class OpenUrlActionFluentUI extends AC.OpenUrlAction {

    private internalRenderedElement: any;

    get renderedElement(): HTMLElement {
        return this.internalRenderedElement;
    }

    public render(baseCssClass?: string) {
        let actionsConfig = this.parent.hostConfig.actions;
        const div = createActionDiv(this, baseCssClass, actionsConfig.iconPlacement, actionsConfig.iconSize);
        this.internalRenderedElement = div;
    }
}

export class SubmitActionFluentUI extends AC.SubmitAction {

    private internalRenderedElement: HTMLElement;

    get renderedElement(): HTMLElement {
        return this.internalRenderedElement;
    }

    public render(baseCssClass?: string): void {
        let actionsConfig = this.parent.hostConfig.actions;
        const div = createActionDiv(this, baseCssClass, actionsConfig.iconPlacement, actionsConfig.iconSize);
        this.internalRenderedElement = div;
    }
}

export class ShowCardActionFluentUI extends AC.ShowCardAction {

    private internalRenderedElement: HTMLElement;

    get renderedElement(): HTMLElement {
        return this.internalRenderedElement;
    }

    public render(baseCssClass?: string): void {
        let actionsConfig = this.parent.hostConfig.actions;
        const div = createActionDiv(this, baseCssClass, actionsConfig.iconPlacement, actionsConfig.iconSize);
        this.internalRenderedElement = div;
    }
}

export class ToggleVisibilityActionFluentUI extends AC.ToggleVisibilityAction {

    private internalRenderedElement: HTMLElement;

    get renderedElement(): HTMLElement {
        return this.internalRenderedElement;
    }

    public render(baseCssClass?: string): void {
        const div = Shared.getDiv();
        ReactDOM.render(<ActionButton action={this} className={baseCssClass} />, div);
        this.internalRenderedElement = div;
    }
}
