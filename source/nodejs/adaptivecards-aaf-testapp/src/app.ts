// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Shared from "./shared";
import * as Adaptive from "adaptivecards";
import "adaptivecards/dist/adaptivecards.css";
import { TestHttpChannelAdapter } from "./test-http-channel-adapter";
import { ExecuteAction } from "adaptivecards";

window.onload = function() {
    Adaptive.GlobalSettings.applets.refresh.mode = Adaptive.RefreshMode.Automatic;

    let applet = new Adaptive.AdaptiveApplet();
    /*
    applet.onCardChanged = (sender: Adaptive.AdaptiveApplet) => {
        if (sender.card) {
            if (sender.card.autoRefresh) {
                alert(JSON.stringify(sender.card.autoRefresh.toJSON()));
            }
        }
    };
    */

    // applet.channelAdapter = new LocalChannelAdapter();

    applet.channelAdapter = new TestHttpChannelAdapter("https://acv2testbot.azurewebsites.net/aaftestbot/invoke");

    applet.setCard(Shared.sampleCard);
    // applet.onActivityRequestFailed = (sender, response) => { return 2000; }
    applet.onActivityRequestSucceeded = (sender: Adaptive.AdaptiveApplet, response: Adaptive.SuccessResponse, parsedContent: string | Adaptive.AdaptiveCard) => {
        if (parsedContent !== undefined && typeof parsedContent === "string") {
            alert(parsedContent);
        }
    }
    document.getElementById("appHost").appendChild(applet.renderedElement);
}
