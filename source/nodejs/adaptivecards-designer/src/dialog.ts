export abstract class Dialog {
    private _overlayElement: HTMLElement;
    private _isOpen: boolean = false;

    protected abstract renderContent(): HTMLElement;

    onClose: (sender: Dialog) => void = null;

    title: string;
    width: string;
    height: string;

    open() {
        if (!this._isOpen) {
            this._overlayElement = document.createElement("div");
            this._overlayElement.className = "acd-dialog-overlay";

            let dialogFrameElement = document.createElement("div");
            dialogFrameElement.className = "acd-dialog-frame";
            dialogFrameElement.style.width = this.width;
            dialogFrameElement.style.height = this.height;

            let content = this.renderContent();
            content.style.flex = "1 1 auto";

            dialogFrameElement.appendChild(content);

            this._overlayElement.appendChild(dialogFrameElement);

            document.body.appendChild(this._overlayElement);

            this._isOpen = true;
        }
    }

    close() {
        if (this._isOpen) {
            document.body.removeChild(this._overlayElement);

            this._isOpen = false;

            if (this.onClose) {
                this.onClose(this);
            }
        }
    }
}