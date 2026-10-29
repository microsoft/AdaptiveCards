// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { AdaptiveApplet } from "../../adaptive-applet";
import { IActivityRequest, LoginRequestResponse } from "../../activity-request";
import { AuthCardButton, Authentication } from "../../card-elements";
import { isHttpUrl } from "../../utils";

const nonHttpUrls = [
    "javascript:alert(document.domain)",
    "JavaScript:alert(1)",
    " javascript:alert(1)",
    "java\tscript:alert(1)",
    "data:text/html,<h1>Sign in</h1>",
    "vbscript:msgbox(1)",
    "file:///c:/windows/win.ini",
    "myapp://signin",
    "/relative/signin",
    "not a url",
    ""
];

const httpUrls = [
    "https://login.example.com/start",
    "HTTPS://login.example.com/start",
    "http://localhost:3978/signin"
];

function createSigninButton(url: string): AuthCardButton {
    const button = new AuthCardButton();
    button.type = "signin";
    button.value = url;

    return button;
}

describe("isHttpUrl", () => {
    it.each(httpUrls)("returns true for %s", (url) => {
        expect(isHttpUrl(url)).toBe(true);
    });

    it.each(nonHttpUrls)("returns false for %s", (url) => {
        expect(isHttpUrl(url)).toBe(false);
    });

    it("returns false for undefined", () => {
        expect(isHttpUrl(undefined)).toBe(false);
    });
});

describe("AdaptiveApplet built-in sign-in window", () => {
    const openSigninWindow = (button: AuthCardButton): boolean =>
        (AdaptiveApplet as any).openSigninWindow(button);
    const originalWindow = (globalThis as any).window;
    let openedUrls: string[];

    beforeEach(() => {
        openedUrls = [];
        (globalThis as any).window = {
            screenX: 0,
            screenY: 0,
            outerWidth: 1024,
            outerHeight: 768,
            open: (url: string) => {
                openedUrls.push(url);
            }
        };
    });

    afterEach(() => {
        (globalThis as any).window = originalWindow;
    });

    it.each(httpUrls)("opens http(s) signin URL %s", (url) => {
        expect(openSigninWindow(createSigninButton(url))).toBe(true);
        expect(openedUrls).toEqual([url]);
    });

    it.each(nonHttpUrls)("never opens non-http(s) signin URL %s", (url) => {
        expect(openSigninWindow(createSigninButton(url))).toBe(false);
        expect(openedUrls).toEqual([]);
    });
});

describe("LoginRequestResponse", () => {
    it("keeps the signin button for hosts that handle the sign-in prompt themselves", () => {
        const auth = new Authentication();
        auth.buttons.push(createSigninButton("myapp://signin"));

        const response = new LoginRequestResponse({} as IActivityRequest, auth);

        expect(response.signinButton?.value).toBe("myapp://signin");
    });
});
