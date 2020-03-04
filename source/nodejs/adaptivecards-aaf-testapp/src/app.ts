// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as AAF from "adaptivecards-aaf";
import * as Shared from "./shared";
import "adaptivecards-aaf/dist/aaf.css";
import "adaptivecards-aaf/dist/adaptivecards.css";
import { LocalChannelAdapter } from "./local-channel-adapter";

window.onload = function() {
    let sampleCardAndData = Shared.sampleCard;
    sampleCardAndData["$data"] = Shared.sampleData;

    let applet = new AAF.AdaptiveApplet();
    applet.onCardChanged = (sender: AAF.AdaptiveApplet) => {
        if (sender.card) {
            if (sender.card.autoRefresh) {
                alert(JSON.stringify(sender.card.autoRefresh.toJSON()));
            }
        }
    };

    // applet.channelAdapter = new LocalChannelAdapter();

    applet.channelAdapter = new AAF.HttpChannelAdapter("https://aaftestbot.azurewebsites.net/aaftestbot/invoke");

    applet.setCard(sampleCardAndData);
    applet.onActivityRequestCompleted = (sender, response) => {
        if (response.status === AAF.ActivityStatus.Failure) {
            return 2000;
        }
    }

    document.getElementById("appHost").appendChild(applet.renderedElement);
}
