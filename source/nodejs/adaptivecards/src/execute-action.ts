import { SubmitAction } from "./card-elements";
import { StringProperty, Versions, property } from "./serialization";

export class ExecuteAction extends SubmitAction {
    //#region Schema

    static readonly verbProperty = new StringProperty(Versions.v1_2, "verb");

    @property(ExecuteAction.verbProperty)
    verb: string;

    //#endregion

    getJsonTypeName(): string {
        return "Action.Execute";
    }
}