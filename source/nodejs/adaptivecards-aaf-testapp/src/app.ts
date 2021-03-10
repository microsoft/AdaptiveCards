// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Shared from "./shared";
import * as Adaptive from "adaptivecards";
import "adaptivecards/dist/adaptivecards.css";
import { TestChannelAdapter } from "./test-channel-adapter";

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

    applet.channelAdapter = new TestChannelAdapter("https://acv2testbot.azurewebsites.net/aaftestbot/invoke");

    applet.setCard(Shared.sampleCard);
    // applet.onActivityRequestFailed = (sender, response) => { return 2000; }
    applet.onActivityRequestSucceeded = (sender: Adaptive.AdaptiveApplet, response: Adaptive.SuccessResponse, parsedContent: string | Adaptive.AdaptiveCard) => {
        if (parsedContent !== undefined && typeof parsedContent === "string") {
            alert(parsedContent);
        }
    }
    applet.onSSOTokenNeeded = (sender: Adaptive.AdaptiveApplet, request: Adaptive.IActivityRequest, tokenExchangeResource: Adaptive.TokenExchangeResource) => {
        request.authToken = "valid_sso_token";
        request.retryAsync();

        return true;
    }
    applet.onShowSigninPrompt = (sender: Adaptive.AdaptiveApplet, request: Adaptive.IActivityRequest, signinButton: Adaptive.AuthCardButton) => {
        alert("Simulating auth prompt...");

        request.authCode = request.attemptNumber > 1 ? "valid_auth_code" : "invalid_auth_code";
        request.retryAsync();
    }
    
    document.getElementById("appHost").appendChild(applet.renderedElement);
}
