import { FullScreenDocument, FullScreenElement } from "../adaptive-card-schema";

export default class FullScreenHandler {
    private _body: FullScreenElement;
    private _fullScreenBtn: HTMLElement;
    private _fullScreenDocument: FullScreenDocument;


    public constructor(button: HTMLElement) {
        this._body = document.body as FullScreenElement;
        this._fullScreenBtn = button;
        this._fullScreenDocument = document as FullScreenDocument;
    }

    public init() {
        this._fullScreenBtn.addEventListener("click", () => {
            if (this._fullScreenDocument.fullscreen || this._fullScreenDocument.webkitIsFullScreen || this._fullScreenDocument.mozFullScreen) {
                if (this._fullScreenDocument.exitFullscreen) {
                    this._fullScreenDocument.exitFullscreen();
                } else if (this._fullScreenDocument.webkitExitFullscreen) {
                    this._fullScreenDocument.webkitExitFullscreen();
                } else if (this._fullScreenDocument.mozCancelFullScreen) {
                    this._fullScreenDocument.mozCancelFullScreen();
                } else if (this._fullScreenDocument.msExitFullscreen) {
                    this._fullScreenDocument.msExitFullscreen();
                }
            } else {
                if (this._body.requestFullscreen) {
                    this._body.requestFullscreen();
                } else if (this._body.webkitRequestFullscreen) {
                    this._body.webkitRequestFullscreen();
                } else if (this._body.mozRequestFullScreen) {
                    this._body.mozRequestFullScreen();
                } else if (this._body.msRequestFullscreen) {
                    this._body.msRequestFullscreen();
                } else {
                    alert("Your browser doesn't support fullscreen.");
                }
            }
        });

        if (typeof this._body.onfullscreenchange !== "undefined") {
            this._body.onfullscreenchange = () => this.fullScreenHandle();
        } else if (typeof this._body.onwebkitfullscreenchange !== "undefined") {
            this._body.onwebkitfullscreenchange = () => this.fullScreenHandle();
        } else if (typeof this._body.onwebkitfullscreenchange !== "undefined") {
            this._body.onmozfullscreenchange = () => this.fullScreenHandle();
        } else if (typeof this._body.onwebkitfullscreenchange !== "undefined") {
            this._body.MSFullscreenChange = () => this.fullScreenHandle();
        }
    }

    private fullScreenHandle() {
        if (this._fullScreenDocument.fullscreen || this._fullScreenDocument.webkitIsFullScreen || this._fullScreenDocument.mozFullScreen) {
            this._fullScreenBtn.innerHTML = "Exit Full Screen";
        } else {
            this._fullScreenBtn.innerHTML = "Enter Full Screen";
        }
    }
}
