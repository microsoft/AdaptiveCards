import * as Adaptive from "adaptivecards";
import * as Designer from "../../adaptivecards-designer";
import * as renderToImageConfiguration from "../../../../../../samples/HostConfig/render-to-image.json"

export class BotFrameworkContainer extends Designer.HostContainer {
    public renderTo(hostElement: HTMLElement) {
        this.cardHost.classList.add("bf-images-card");

        let frame = document.createElement("div");
        frame.className = "bf-images-frame";
        frame.appendChild(this.cardHost);

        hostElement.appendChild(frame);
    }

    public getHostConfig(): Adaptive.HostConfig {
        return new Adaptive.HostConfig(renderToImageConfiguration);
    }
}
