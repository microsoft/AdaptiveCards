// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { IActivityRequest, LoginRequestResponse } from "../../activity-request";
import { AuthCardButton, Authentication } from "../../card-elements";

function createAuthentication(...signinUrls: string[]): Authentication {
    const auth = new Authentication();

    for (const url of signinUrls) {
        const button = new AuthCardButton();
        button.type = "signin";
        button.value = url;

        auth.buttons.push(button);
    }

    return auth;
}

const request = {} as IActivityRequest;

describe("LoginRequestResponse", () => {
    it.each(["https://login.example.com/start", "http://localhost:3978/signin"])(
        "accepts http(s) signin URL %s",
        (url) => {
            const response = new LoginRequestResponse(request, createAuthentication(url));

            expect(response.signinButton?.value).toBe(url);
        }
    );

    it.each([
        "javascript:alert(document.domain)",
        "JavaScript:alert(1)",
        "data:text/html,<h1>Sign in</h1>",
        "vbscript:msgbox(1)",
        "file:///c:/windows/win.ini",
        "not a url"
    ])("ignores non-http(s) signin URL %s", (url) => {
        const response = new LoginRequestResponse(request, createAuthentication(url));

        expect(response.signinButton).toBeUndefined();
    });

    it("skips non-http(s) signin URLs and selects the first http(s) one", () => {
        const response = new LoginRequestResponse(
            request,
            createAuthentication("javascript:alert(1)", "https://login.example.com/")
        );

        expect(response.signinButton?.value).toBe("https://login.example.com/");
    });
});
