import * as vscode from "vscode";
import { INode } from "./nodes/INode";
import { CardNodeChild } from "./CardNodeChild";
import { AdaptiveCardsMain } from "../adaptiveCards";
import * as path from 'path';

export class CardNodeCMS implements INode {

    private readonly acm: AdaptiveCardsMain;
    private readonly Author: string;
    private readonly LastChange : Date;
    private readonly IsShareable: boolean;
    private readonly State: string;


    constructor(
        readonly label: string,
        readonly path: string,
        readonly id: number,
        author: string,
        lastChange: string,
        isShareable: boolean,
        state: string,
        acm: AdaptiveCardsMain) {
        this.acm = acm;
        this.Author = author;
        this.State = state;
    }

    public getIcon(priority: string) {
        console.log(priority);
         return {
          light: path.join(this.acm._context.extensionPath, 'resources/light', `${priority}.svg`),
          dark: path.join(this.acm._context.extensionPath, 'resources/dark', `${priority}.svg`),
      };


  }

    public getTreeItem(): vscode.TreeItem {
        return {
            label: this.label,
            collapsibleState: vscode.TreeItemCollapsibleState.Collapsed,
            description: this.Author,
            iconPath: this.getIcon(this.State),
            contextValue: "ac-CardBase",
            command: {
                command: "cardListCMS.showElement",
                title: "",
                arguments: [this],
            }
        };
    }
    public async getChildren(context: vscode.ExtensionContext): Promise<INode[]> {

        try {
            var list: INode[] = [];
            list.push(new CardNodeChild("Template",this.path,"template",0,this.acm));
            list.push(new CardNodeChild("Data",this.path.replace(".json",".data.json"),"data",1,this.acm));
            return list;
          } catch (error) {
              vscode.window.showErrorMessage(error);
              return [];
        }
    }

}
