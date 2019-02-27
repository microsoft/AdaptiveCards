import * as Adaptive from "adaptivecards";
import * as Designer from "../../adaptivecards-designer";
import * as webChatConfiguration from "../../../../../../samples/HostConfig/webchat.json"

export class WebChatContainer extends Designer.HostContainer {
    public renderTo(hostElement: HTMLElement) {
        this.cardHost.classList.add("webChatOuterContainer");

        let frame = document.createElement("div");
        frame.className = "webChatInnerContainer";
        frame.appendChild(this.cardHost);

        hostElement.appendChild(frame);
    }

    public getHostConfig(): Adaptive.HostConfig {
        return new Adaptive.HostConfig(webChatConfiguration);
    }
}
