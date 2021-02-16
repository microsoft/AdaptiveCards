import * as vscode from "vscode";
import { INode } from "./INode";

export class ProjectErrorNode implements INode {

    constructor(
        public readonly label: string,
        private readonly description: string, 
        private readonly icon: string,
        public readonly id: number) {
    }

    public getTreeItem(): vscode.TreeItem {
        return {
            label: this.label,
            description: this.description,
            iconPath: this.icon,
            collapsibleState: vscode.TreeItemCollapsibleState.None,        
            contextValue: "taskItem-label",
            command: {
                command: "twp.SetProject",
                title: "",
                arguments: [],
            }
        };
    }

    public getChildren(): INode[] {
            return  [];
    }
}
