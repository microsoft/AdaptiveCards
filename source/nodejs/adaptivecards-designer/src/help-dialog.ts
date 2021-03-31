// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Adaptive from "adaptivecards";
import { Dialog } from "./dialog";

export class HelpDialog extends Dialog {
    private _renderedElement: HTMLElement;

    private _getShortcutRow(shortcut: string, description: string, isHeader: boolean=false) : HTMLElement {
        let shortcutText = document.createElement("b");
        shortcutText.innerText = shortcut;
        let shortcutCell = document.createElement(isHeader ? "th" : "td");
        shortcutCell.style.textAlign = "left";
        shortcutCell.appendChild(shortcutText);

        let descriptionCell = document.createElement(isHeader ? "th" : "td");
        descriptionCell.style.textAlign = "left";
        descriptionCell.innerText = description;

        let row = document.createElement("tr");
        row.appendChild(shortcutCell);
        row.appendChild(descriptionCell);
        return row;
    }

    protected renderContent(): HTMLElement {
        this._renderedElement = document.createElement("div");

        let cardHeading = document.createElement("h1");
        cardHeading.innerText = "Card Payload and Sample Data Editors";
        this._renderedElement.appendChild(cardHeading);

        let keyboardHeading = document.createElement("h2");
        keyboardHeading.innerText = "Keyboard Shortcuts";
        this._renderedElement.appendChild(keyboardHeading);

        let keyboardText = document.createElement("div");
        keyboardText.innerText = "These keyboard shortcuts only work when the keyboard focus is within either the card payload or sample data editors";
        this._renderedElement.appendChild(keyboardText);
        this._renderedElement.appendChild(document.createElement("br"));

        let shortcutTable = document.createElement("table");
        shortcutTable.appendChild(this._getShortcutRow("Shortcut", "Description", true));
        shortcutTable.appendChild(this._getShortcutRow("Alt-F1", "Show help dialog for editor"));
        shortcutTable.appendChild(this._getShortcutRow("Ctrl-M", "Toggle behavior of TAB key. By default, pressing TAB will insert a TAB character. When toggled, pressing TAB will navigate to the next focusable item."));

        this._renderedElement.appendChild(shortcutTable);
        return this._renderedElement;
    }
}
