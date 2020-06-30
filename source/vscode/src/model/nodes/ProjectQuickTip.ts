import { QuickPickItem } from "vscode";

export class ProjectQuickTip implements QuickPickItem {
    public readonly label: string;
    public readonly description: string;
    public readonly picked: boolean;
    constructor(public readonly name: string, public readonly id: string, public readonly isPicked: boolean) {
        this.label = name;
        this.picked = isPicked;
    }
}

export class PersonQuickTip implements QuickPickItem {
    public readonly label: string;
    public readonly description: string;
    public readonly picked: boolean;
    constructor(public readonly name: string, public readonly id: string, public readonly isPicked: boolean) {
        this.label = name;
        this.picked = isPicked;
    }
}