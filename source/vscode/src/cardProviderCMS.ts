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
        var listUri = "https://adaptivecms.azurewebsites.net/template?isClient=true&sortBy=alphabetical"
        var token = "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImtpZCI6Imh1Tjk1SXZQZmVocTM0R3pCRFoxR1hHaXJuTSJ9.eyJhdWQiOiI0ODAzZjY2YS0xMzZkLTQxNTUtYTUxZS02ZDk4NDAwZDU1MDYiLCJpc3MiOiJodHRwczovL2xvZ2luLm1pY3Jvc29mdG9ubGluZS5jb20vYzE0ODAzZDgtN2RiZS00NjEzLThhYTctYWU3MWRiNzFkYWQzL3YyLjAiLCJpYXQiOjE1OTQzMDgzOTQsIm5iZiI6MTU5NDMwODM5NCwiZXhwIjoxNTk0MzEyMjk0LCJhaW8iOiJBVFFBeS84UUFBQUEyY0tydm1CWlhxbXdjbjAzMzJDK2V2N0EzN0NIMnJBUlpXamZOcUxjKy8yazNVVmwyNU9ObXJtNDFyVmwyYzlIIiwiYXpwIjoiNDgwM2Y2NmEtMTM2ZC00MTU1LWE1MWUtNmQ5ODQwMGQ1NTA2IiwiYXpwYWNyIjoiMCIsIm5hbWUiOiJUaW0gQ2FkZW5iYWNoIiwib2lkIjoiZGJmMDU2ZWQtZmRhYS00OTYxLWEyYWEtYWU3ZGZkNzk4OTY2IiwicHJlZmVycmVkX3VzZXJuYW1lIjoiZGVlamF5QHRjZGV2LmRlIiwic2NwIjoiVGVtcGxhdGVzLkFsbCIsInN1YiI6IldIcUVBdV9Nc0w0bXZhekRyNUJZck4zQlRtMGkwN3d1czh5TVoxMFAteEEiLCJ0aWQiOiJjMTQ4MDNkOC03ZGJlLTQ2MTMtOGFhNy1hZTcxZGI3MWRhZDMiLCJ1dGkiOiJGU3ZPMTlTTDhreUhLbWVteGlvZkFBIiwidmVyIjoiMi4wIn0.gGZYD0dGXBIUwZWIBEhaFnzH5kIRjtq50lB5b2YyYhVu-CvGrrSaO6N2lYDlSZDMvbdlJjjMUAGq_f1h8LH9ZgGvlGAsB4J_rS79QROsSd-O1jBMgWW21wGTQ9fHvUKqAjQYhaCGta8Ur4n8aCv2xlwkkIGIDica1xaApIRtEoGVn7MAhfDLHRmvXRCBTK4pz8ZDjBKfClR-muWhxK4mQbbMs8x04kQ6aPntr5ByTyGekPD0kcMPQlV1FZHuc2rwPBF3vKyAn9aPMWsjVF1zXb71avIK1q9R6vtf685ymhB5peR29Qzg0qSnUv1IFUJ634irk5ZI0TuMGzmWANvk2Q"
        //https://adaptivecms.azurewebsites.net/template/5eb99db44e800c004f9e2020?isClient=true

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
                var node = new CardNodeCMS(element.name, element["_id"], i, "Matt Hidinger", "07.07.2020", true, element.instances[0].state, this.acm);
                this.acm.templates.push(element)
                i++;
                items.push(node); 
              });
              console.log("Loaded Items");
              return items;
          })
          .catch((error) => {
            console.log(error);
            return items;
          })
          return items;
    }


    public getTreeItem(element: INode): Promise<vscode.TreeItem> | vscode.TreeItem  {
        return element.getTreeItem();
    }

}