import * as vscode from "vscode";
import {INode} from "./model/nodes/INode";
import { ProjectErrorNode } from "./model/nodes/ProjectErrorNode";
import { CardNodeCMS } from "./model/CardNodeCMS";
import { AdaptiveCardsMain } from "./adaptiveCards";
import axios from "axios";

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
            console.log("ACSTUDIO - Get CMS Nodes");
            vscode.window.showInformationMessage("Searching for Adaptive Cards in the CMS");
            return await this.GetCardsFromCMS();

        }
        return element.getChildren(this.context);
    }

    public async GetCardsFromCMS() : Promise<INode[]> {
        var items: INode[] = [];

        var config = vscode.workspace.getConfiguration('acstudio');
        var listUri: string = config.get("cmsAccessUrl");
        var token: string = config.get("cmsAccessToken");

        if(token !== ""){
            await axios.get(listUri, {
                headers: {
                  'Authorization': `Bearer ${token}`
                }
              })
              .then((res) => {
                console.log("ACSTUDIO - Found CMS Nodes");
                  var templates = res.data.templates;
                  var i: number = 0;
                  console.log(templates);
                  templates.forEach(element => {
                    var node = new CardNodeCMS(element.name, element["_id"], i, "Matt Hidinger",
                      "07.07.2020", true, element.instances[0].state, this.acm);
                    this.acm.templates.push(element);
                    i++;
                    items.push(node);
                  });
                  console.log("Loaded Items");
                  return items;
              })
              .catch((error) => {
                console.log(error);
                items.push(new ProjectErrorNode("CMS Access not available",error,"",1));
                return items;
              });
          } else {
            items.push(new ProjectErrorNode("CMS Access not available","","",1));
          }
          return items;
    }


    public getTreeItem(element: INode): Promise<vscode.TreeItem> | vscode.TreeItem  {
        return element.getTreeItem();
    }

}