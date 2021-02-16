import * as vscode from "vscode";
import { INode } from "./nodes/INode";
import * as path from "path";
import { AdaptiveCardsMain } from "../adaptiveCards";

export class CardNodeChild implements INode {

    private readonly acm: AdaptiveCardsMain;
    public Type : string;
    constructor(private readonly label: string, readonly path: string, type: string, readonly id: number, acm: AdaptiveCardsMain) {
        this.acm = acm;
        this.Type = type;
    }

    public getTreeItem(): vscode.TreeItem {
        return {
            label: this.label,
            iconPath: this.getIcon(this.Type),
            collapsibleState: vscode.TreeItemCollapsibleState.None,
            command: {
                command: "cardList.showElement",
                title: "",
                arguments: [this],
            }
        };
    }
    public async getChildren(context: vscode.ExtensionContext): Promise<INode[]> {
      return [];
    }

    // tslint:disable-next-line: typedef
    public getIcon(type: string) {
      if(type === "data") {
          return {
              light: path.join(this.acm._context.extensionPath, "resources/light", "folder.svg"),
              dark: path.join(this.acm._context.extensionPath, "resources/dark", "folder.svg"),
          };
      }
      return {
        light: path.join(this.acm._context.extensionPath, "resources/light", "number.svg"),
        dark: path.join(this.acm._context.extensionPath, "resources/dark", "number.svg"),
      };
  }
}
