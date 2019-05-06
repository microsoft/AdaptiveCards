import * as Adaptive from "adaptivecards";
import * as Designer from "../../adaptivecards-designer/lib/adaptivecards-designer";
import * as HostConfig from "../samples/HostConfig.json";

export class CheckInAction extends Adaptive.Action {
    text: string;

    getJsonTypeName(): string {
        return "Contoso.Action.CheckIn";
    }

    execute() {
        alert(this.text);
    }

    parse(json: any) {
        super.parse(json);
		this.text = Adaptive.getStringValue(json["text"], "Alert!");
       
    }

    toJSON() {
        let result = super.toJSON();

        Adaptive.setProperty(result, "text", this.text);

        return result;
    }
}

export class CheckInActionPeer extends Designer.TypedActionPeer<CheckInAction> {

}

export class ContosoHostContainer extends Designer.HostContainer {

	constructor() {
		super("ContosoMedical", "");		
	}
	public initialize() {
        super.initialize();

        //Adaptive.AdaptiveCard.actionTypeRegistry.unregisterType("Action.Submit");
        Adaptive.AdaptiveCard.actionTypeRegistry.registerType("Contoso.Action.CheckIn", () => { return new CheckInAction(); });

        Adaptive.AdaptiveCard.useMarkdownInRadioButtonAndCheckbox = false;
    }


    public renderTo(hostElement: HTMLElement) {
        this.cardHost.classList.add("webChatOuterContainer");

        let frame = document.createElement("div");
        frame.className = "webChatInnerContainer";
        frame.appendChild(this.cardHost);

        hostElement.appendChild(frame);
    }

    public getHostConfig(): Adaptive.HostConfig {
        return new Adaptive.HostConfig(HostConfig);
    }
}
