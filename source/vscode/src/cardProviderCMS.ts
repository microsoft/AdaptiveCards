import * as vscode from "vscode";
import {INode} from "./model/nodes/INode";
import * as glob from "glob";
import * as path from "path";
import * as fs from "fs";
import { ProjectErrorNode } from "./model/nodes/ProjectErrorNode";
import { CardNode } from "./model/CardNode";
import { AdaptiveCardsMain } from "./adaptiveCards";

export class CardProviderCMS implements vscode.TreeDataProvider<INode> {
    private readonly acm: AdaptiveCardsMain;

    public _onDidChangeTreeData: vscode.EventEmitter<INode | undefined> = new vscode.EventEmitter<INode | undefined>();
    public readonly onDidChangeTreeData: vscode.Event<INode | undefined> = this._onDidChangeTreeData.event;

    constructor(private context: vscode.ExtensionContext,  acm: AdaptiveCardsMain) {
        this.acm = acm;
    }

	refresh(node?: INode): void {

        if(node) {
            this._onDidChangeTreeData.fire(node);
        }

		this._onDidChangeTreeData.fire();
	}

    public async getChildren(element?: INode): Promise<INode[]> {
        if(!element) {
            vscode.window.showInformationMessage("Searching for Adaptive Cards in your workspace");
        }
        return element.getChildren(this.context);
    }


    public getTreeItem(element: INode): Promise<vscode.TreeItem> | vscode.TreeItem  {
        return element.getTreeItem();
    }

}