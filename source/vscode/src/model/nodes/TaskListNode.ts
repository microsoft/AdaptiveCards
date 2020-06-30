// import * as vscode from "vscode";
// import { INode } from "./INode";
// import { TaskItemNode } from "./TaskItemNode";
// import { TaskListConverter,TaskListResponse } from '../responses/TaskListResponse';
// import { TeamworkProjects } from "../../teamworkProjects";
// import { ProjectNode } from "./ProjectNode";
// import { TaskProvider } from "../../taskProvider";

// export class TaskListNode implements INode {


//     constructor(
//         private readonly label: string, 
//         readonly id: number,
//         public parentNode: ProjectNode,
//         private readonly provider: TaskProvider,  
//         private readonly twp: TeamworkProjects) {
//     }

//     public getTreeItem(): vscode.TreeItem {
//         return {
//             label: this.label,
//             collapsibleState: vscode.TreeItemCollapsibleState.Collapsed,
//             contextValue: "twp-TaskList",
//         };
//     }

//     public async getChildren(context: vscode.ExtensionContext): Promise<INode[]> {
//         try {
//             return await this.twp.getTaskItems(context,this,this.provider);
//           } catch (error) {
//               vscode.window.showErrorMessage(error);
//               return [];
//         }
//     }




// }
