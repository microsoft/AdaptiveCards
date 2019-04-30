import { CardHub, ICardData } from "./card-hub"
import { QRCode } from "qrcode-generator-ts/js";
import { CardDesigner } from "./card-designer";

export class ShareDialog {

    readonly attachedTo: HTMLElement = null;
    private _modalElement: HTMLElement;
    private _modalContentElement: HTMLElement;
    private _modalCloseButtonElement: HTMLElement;
    private _modalTitleElement: HTMLElement;
    private _modalDescriptionElement: HTMLElement;
    private _qrCodeElement: HTMLElement;
    private _progressElement: HTMLElement;
    private _manualJoinContainerElement: HTMLElement;
    private _manualJoinRespondIdElement: HTMLElement;
	private _errorElement: HTMLElement;
	
	private _successfullyShared: boolean;
	private _cardId?: string;
	private _token?: string;

    constructor(
        attachedTo: HTMLElement) {

        this.attachedTo = attachedTo;

        this._modalElement = document.createElement("div");
        this._modalElement.style.display = "block";
        this._modalElement.classList.add("modal");
        this._modalElement.onclick = function (event)
        {
            if (event.target == this._modalElement) {
                this.close();
            }
        }.bind(this);
        {
            this._modalContentElement = document.createElement("div");
            this._modalContentElement.classList.add("modal-content");
            {
                this._modalCloseButtonElement = document.createElement("span");
                this._modalCloseButtonElement.classList.add("close");
                this._modalCloseButtonElement.innerHTML = "&times;";
                this._modalCloseButtonElement.onclick = this.close.bind(this);
                this._modalContentElement.appendChild(this._modalCloseButtonElement);

                this._modalTitleElement = document.createElement("h1");
                this._modalTitleElement.innerText = "Live share card";
                this._modalContentElement.appendChild(this._modalTitleElement);

                this._modalDescriptionElement = document.createElement("p");
                this._modalDescriptionElement.innerText = "Want to see the card you're working on from an Android device? Scan the QR code below using the Android app!";
                this._modalContentElement.appendChild(this._modalDescriptionElement);

                this._errorElement = document.createElement("p");
                this._errorElement.classList.add("error");
                this._errorElement.style.display = "none";
                this._modalContentElement.appendChild(this._errorElement);

                // Indeterminate progress bar
                this._progressElement = document.createElement("progress");
                this._modalContentElement.appendChild(this._progressElement);

                this._qrCodeElement = document.createElement("img");
                this._qrCodeElement.classList.add("qr-code");
                this._qrCodeElement.style.display = "none";
                this._modalContentElement.appendChild(this._qrCodeElement);

                this._manualJoinContainerElement = document.createElement("div");
                this._manualJoinContainerElement.style.display = "none";
                {
                    var manualJoinExplanation = document.createElement("p");
                    manualJoinExplanation.innerText = "You can also join from another web browser by using the following respond ID...";
                    this._manualJoinContainerElement.appendChild(manualJoinExplanation);

                    this._manualJoinRespondIdElement = document.createElement("code");
                    this._manualJoinContainerElement.appendChild(this._manualJoinRespondIdElement);
                }
                this._modalContentElement.appendChild(this._manualJoinContainerElement);
            }
            this._modalElement.appendChild(this._modalContentElement);
        }

        this.attachedTo.appendChild(this._modalElement);
	}

    close() {
		this._modalElement.style.display = "none";
	}
	
	show() {
		this._modalElement.style.display = "block";
	}

    async shareAsync(cardData: ICardData) {
		try {
			var createCardResponse = await CardHub.createCardAsync(cardData);
			var cardId = createCardResponse.CardId;
			this._token = createCardResponse.Token;

			// Show QR code
			var qr = new QRCode();
			qr.setTypeNumber(4);
			qr.addData(cardId);
			qr.make();
			var dataUrl = qr.toDataURL(35);
			this._qrCodeElement.setAttribute("src", dataUrl);
			this._qrCodeElement.style.display = "block";
			this._progressElement.style.display = "none";

			// And also the manual respond ID
			this._manualJoinRespondIdElement.innerText = cardId;
			this._manualJoinContainerElement.style.display = "block";
			this._successfullyShared = true;
			this._cardId = cardId;
		} catch (err) {
			this.fail(err);
			throw err;
		}
	}
	
	private _isUpdating: boolean = false;
	private _queuedUpdate?: ICardData;
	sendUpdate(cardData: ICardData) {
		if (!this._successfullyShared) {
			return;
		}

		if (this._isUpdating) {
			this._queuedUpdate = cardData;
		} else {
			this.actuallySendUpdateAsync(cardData);
		}
	}

	private async actuallySendUpdateAsync(cardData: ICardData) {
		this._isUpdating = true;
		try {
			await CardHub.updateCardAsync(this._cardId!, this._token!, cardData);
		} catch (err) {
			console.log("Failed to send update: " + err);
		}
		this._isUpdating = false;

		if (this._queuedUpdate) {
			var queuedUpdate = this._queuedUpdate;
			this._queuedUpdate = undefined;
			this.actuallySendUpdateAsync(queuedUpdate);
		}
	}
    
    private fail(message: string) {
        this._errorElement.innerText = message;
        this._errorElement.style.display = "block";
        this._progressElement.style.display = "none";
        this._qrCodeElement.style.display = "none";
    }
}