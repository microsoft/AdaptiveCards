import * as vscode from "vscode";
import { INode } from "./INode";

export class EmptyNode implements INode {


    constructor(
        private readonly label: string, 
        readonly id: number,) {
    }

    public getTreeItem(): vscode.TreeItem {
        return {
            label: this.label,
            collapsibleState: vscode.TreeItemCollapsibleState.None,
            contextValue: "twp-Empty",
        };
    }

    public async getChildren(context: vscode.ExtensionContext): Promise<INode[]> {
         return [];
    }




}
