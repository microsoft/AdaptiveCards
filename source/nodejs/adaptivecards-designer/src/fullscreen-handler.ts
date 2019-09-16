// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
export class FullScreenHandler {
    private fullScrerenChanged() {
        if (this.onFullScreenChanged) {
            this.onFullScreenChanged(this.isFullScreen);
        }
    }

    onFullScreenChanged: (isFullScreen: boolean) => void;

    constructor() {
        let untypedBody = <any>document.body;

        if (typeof untypedBody.onfullscreenchange !== "undefined") {
            untypedBody.onfullscreenchange = () => this.fullScrerenChanged();
        }
        else if (typeof untypedBody.onwebkitfullscreenchange !== "undefined") {
            untypedBody.onwebkitfullscreenchange = () => this.fullScrerenChanged();
        }
        else if (typeof untypedBody.onwebkitfullscreenchange !== "undefined") {
            untypedBody.onmozfullscreenchange = () => this.fullScrerenChanged();
        }
        else if (typeof untypedBody.onwebkitfullscreenchange !== "undefined") {
            untypedBody.MSFullscreenChange = () => this.fullScrerenChanged();
        }
    }

    enterFullScreen() {
        if (!this.isFullScreen) {
            let untypedBody = <any>document.body;

            if (untypedBody.requestFullscreen) {
                untypedBody.requestFullscreen();
            }
            else if (untypedBody.webkitRequestFullscreen) {
                untypedBody.webkitRequestFullscreen();
            }
            else if (untypedBody.mozRequestFullScreen) {
                untypedBody.mozRequestFullScreen();
            }
            else if (untypedBody.msRequestFullscreen) {
                untypedBody.msRequestFullscreen();
            }
            else {
                alert("Your browser doesn't support fullscreen.");
            }
        }
    }

    exitFullScreen() {
        if (this.isFullScreen) {
            let untypedDocument = <any>document;

            if (untypedDocument.exitFullscreen) {
                untypedDocument.exitFullscreen();
            }
            else if (untypedDocument.webkitExitFullscreen) {
                untypedDocument.webkitExitFullscreen();
            }
            else if (untypedDocument.mozCancelFullScreen) {
                untypedDocument.mozCancelFullScreen();
            }
            else if (untypedDocument.msExitFullscreen) {
                untypedDocument.msExitFullscreen();
            }
        }
    }

    toggleFullScreen() {
        if (this.isFullScreen) {
            this.exitFullScreen();
        }
        else {
            this.enterFullScreen();
        }
    }

    get isFullScreen(): boolean {
        let untypedDocument = <any>document;

        return untypedDocument.fullscreen || untypedDocument.webkitIsFullScreen || untypedDocument.mozFullScreen;
    }
}
