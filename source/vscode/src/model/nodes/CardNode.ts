import * as vscode from "vscode";
import { INode } from "./INode";
import * as path from 'path';

export class CardNode implements INode {

    public IsActiveProject : boolean;

    constructor(private readonly label: string, readonly path: string, readonly id: number) {
    }

    public getTreeItem(): vscode.TreeItem {
        return {
            //iconPath: this.GetIcon(),
            label: this.label,
            collapsibleState: vscode.TreeItemCollapsibleState.None,
            command: {
                command: "cardList.showElement",
                title: "",
                arguments: [this],
            }
        };
    }

    public GetIcon() {
    }

    public async getChildren(context: vscode.ExtensionContext): Promise<INode[]> {

        try {
            return [];//await this.twp.getTaskLists(context,this);
          } catch (error) {
              vscode.window.showErrorMessage(error);
              return [];
        }
    }

}
