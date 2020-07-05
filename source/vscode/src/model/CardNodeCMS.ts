import * as vscode from "vscode";
import { INode } from "./nodes/INode";
import { CardNodeChild } from "./CardNodeChild";
import { AdaptiveCardsMain } from "../adaptiveCards";

export class CardNode implements INode {

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
    }

    public getTreeItem(): vscode.TreeItem {
        return {
            label: this.label,
            collapsibleState: vscode.TreeItemCollapsibleState.Collapsed,
            contextValue: "ac-CardBase",
            command: {
                command: "cardList.showElement",
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
