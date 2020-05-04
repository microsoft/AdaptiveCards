// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as AAF from "adaptivecards-aaf";
import * as Shared from "./shared";
import "adaptivecards-aaf/dist/aaf.css";
import "adaptivecards-aaf/dist/adaptivecards.css";
import { TestHttpChannelAdapter } from "./test-http-channel-adapter";

window.onload = function() {
    AAF.GlobalSettings.allowTemplates = true;
    AAF.GlobalSettings.refresh.mode = AAF.RefreshMode.Automatic;

    let sampleCardAndData = Shared.sampleCard;
    sampleCardAndData["$data"] = Shared.sampleData;

    let applet = new AAF.AdaptiveApplet();
    /*
    applet.onCardChanged = (sender: AAF.AdaptiveApplet) => {
        if (sender.card) {
            if (sender.card.autoRefresh) {
                alert(JSON.stringify(sender.card.autoRefresh.toJSON()));
            }
        }
    };
    */

    // applet.channelAdapter = new LocalChannelAdapter();

    applet.channelAdapter = new TestHttpChannelAdapter("https://acv2testbot.azurewebsites.net/aaftestbot/invoke");

    applet.setCard(sampleCardAndData);
    // applet.onActivityRequestFailed = (sender, response) => { return 2000; }
    applet.onActivityRequestSucceeded = (sender, response) => {
        if (typeof response.content === "string") {
            alert(response.content);
        }
    }
    document.getElementById("appHost").appendChild(applet.renderedElement);
}
