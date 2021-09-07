// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

import * as React from "react";
import * as ReactDOM from "react-dom";
import * as AC from "adaptivecards";
import * as Shared from "../utils/shared";
import { ActionButton } from "./ActionButton";

export const createActionDiv = (
    title: string,
    iconUrl: string,
    baseCssClass: string,
    iconPlacement: AC.ActionIconPlacement,
    iconSize: number): HTMLDivElement => {
    const div = Shared.getDiv();
    ReactDOM.render(
        <ActionButton
            text={title}
            className={baseCssClass}
            iconUrl={iconUrl}
            iconPlacement={iconPlacement}
            iconSize={iconSize}></ActionButton>, div);
    return div;
};

export class OpenUrlActionFabric extends AC.OpenUrlAction {

    renderedElement: HTMLElement;

    public render(baseCssClass?: string) {
        let actionsConfig = this.parent.hostConfig.actions;
        const div = createActionDiv(this.title, this.iconUrl, baseCssClass, actionsConfig.iconPlacement, actionsConfig.iconSize);
        this.renderedElement = div;
    }
}

export class SubmitActionFabric extends AC.SubmitAction {

    renderedElement: HTMLElement;

    public render(baseCssClass?: string): void {
        let actionsConfig = this.parent.hostConfig.actions;
        const div = createActionDiv(this.title, this.iconUrl, baseCssClass, actionsConfig.iconPlacement, actionsConfig.iconSize);
        this.renderedElement = div;
    }
}

export class ShowCardActionFabric extends AC.ShowCardAction {

    renderedElement: HTMLElement;

    public render(baseCssClass?: string): void {
        let actionsConfig = this.parent.hostConfig.actions;
        const div = createActionDiv(this.title, this.iconUrl, baseCssClass, actionsConfig.iconPlacement, actionsConfig.iconSize);
        this.renderedElement = div;
    }
}

export class ToggleVisibilityActionFabric extends AC.ToggleVisibilityAction {

    renderedElement: HTMLElement;

    public render(baseCssClass?: string): void {
        const div = Shared.getDiv();
        ReactDOM.render(<ActionButton text={this.title} className={baseCssClass} />, div);
        this.renderedElement = div;
    }
}
