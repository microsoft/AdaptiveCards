import * as vscode from "vscode";

export interface INode {

    id: number;

    getTreeItem(): Promise<vscode.TreeItem> | vscode.TreeItem;

    getChildren(context?: vscode.ExtensionContext): Promise<INode[]> | INode[];
}