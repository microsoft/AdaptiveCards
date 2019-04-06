import { PeerConnections } from "./peer-connections"
import { QRCode } from "qrcode-generator-ts/js";
import { CardDesigner } from "./card-designer";

export class ShareDialog {

    readonly attachedTo: HTMLElement = null;
    readonly _cardDesigner: CardDesigner;
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

    private _hostPeerConn: any;
    private _hostDataChannel: any;
    
    private _unsubOnCardPayloadChanged: Function;
    private _unsubOnHostConfigPayloadChanged: Function;

    constructor(
        attachedTo: HTMLElement,
        cardDesigner: CardDesigner) {

        this.attachedTo = attachedTo;
        this._cardDesigner = cardDesigner;

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

        this.startShareProcess();
    }

    close() {
        this.attachedTo.removeChild(this._modalElement);
    }

    private async startShareProcess() {
        // Code from https://github.com/jameshfisher/serverless-webrtc/blob/master/index.html
        if (!this._hostPeerConn) {
            this._hostPeerConn = PeerConnections.createPeerConnection();
            var dataChannel = this._hostPeerConn.createDataChannel('test');
            dataChannel.onopen = (e) => {
                console.log("Opened data channel");
                this.close();
                this._hostDataChannel = dataChannel;
                this._unsubOnCardPayloadChanged = this._cardDesigner.onCardPayloadChanged.subscribe(this.onCardPayloadChanged.bind(this));
                this._unsubOnHostConfigPayloadChanged = this._cardDesigner.onHostConfigPayloadChanged.subscribe(this.onHostConfigPayloadChanged.bind(this));
                this.sendCardAndHostConfigToClients();
                this._cardDesigner.markShared();
            };
        }
        var desc = await this._hostPeerConn.createOffer({});
        this._hostPeerConn.setLocalDescription(desc);

        var candidates = [];
        this._hostPeerConn.onicecandidate = async function(e) {
            if (e.candidate != null) {
                candidates.push(e.candidate);
            } else {
                var offerAndCandidates = {
                    sdp: this._hostPeerConn.localDescription.sdp,
                    candidates: candidates
                };

                // Create the subscription
                try {
                    var respondId = await PeerConnections.createSubscription(offerAndCandidates);

                    // Create the web socket
                    var webSocketUrl = PeerConnections.getWebSocketUrl(respondId);
                    this._hostWebSocket = new WebSocket(webSocketUrl);

                    this._hostWebSocket.onopen = function() {
                        // Show QR code
                        var qr = new QRCode();
                        qr.setTypeNumber(4);
                        qr.addData(respondId);
                        qr.make();
                        var dataUrl = qr.toDataURL();
                        this._qrCodeElement.setAttribute("src", dataUrl);
                        this._qrCodeElement.style.display = "block";
                        this._progressElement.style.display = "none";

                        // And also the manual respond ID
                        this._manualJoinRespondIdElement.innerText = respondId;
                        this._manualJoinContainerElement.style.display = "block";
                    }.bind(this);

                    this._hostWebSocket.onerror = function(error) {
                        this.fail("Error with web socket" + JSON.stringify(error));
                    }.bind(this);

                    this._hostWebSocket.onmessage = function(event) {
                        this.onSocketReceivedMessage(event);
                    }.bind(this);
                } catch(err) {
                    this.fail("Failed to publish offer. Make sure you're connected to the internet.");
                }
            }
        }.bind(this);
    }

    private onCardPayloadChanged() {
        this.sendCardToClients();
    }

    private onHostConfigPayloadChanged() {
        this.sendHostConfigToClients();
    }

    private async onSocketReceivedMessage(event) {
		console.log("Socket received message: " + event.data);
		var answerAndCandidatesStr: string = event.data;
		var answerAndCandidates = JSON.parse(answerAndCandidatesStr);
		if (!this._hostPeerConn) {
			this.fail("Host null");
			return;
		}
		var answer: any = {
			type: "answer",
			sdp: answerAndCandidates.sdp
		};

		
		await this._hostPeerConn.setRemoteDescription(new RTCSessionDescription(answer));
		await PeerConnections.addIceCandidates(this._hostPeerConn, answerAndCandidates.candidates);
		console.log("Client connected!");
    }
    
    private sendCardToClients() {
		this.sendToClients(true, false);
	}

	private sendCardAndHostConfigToClients() {
		this.sendToClients(true, true);
	}

	private sendHostConfigToClients() {
		this.sendToClients(false, true);
	}

	private sendToClients(includeCardPayload: boolean, includeHostConfigPayload: boolean) {
		if (this._hostDataChannel) {
			try {
				var dataMessage: any = {};
				if (includeCardPayload)
				{
					dataMessage.cardPayload = this._cardDesigner.getCurrentJsonPayload();
				}
				if (includeHostConfigPayload)
				{
					dataMessage.hostConfigPayload = this._cardDesigner.getCurrentHostConfigPayload();
				}
				this._hostDataChannel.send(JSON.stringify(dataMessage));
			} catch (ex) {
                this.cleanup();
			}
		}
    }
    
    private cleanup() {
        this._hostDataChannel = null;
        if (this._unsubOnCardPayloadChanged) {
            this._unsubOnCardPayloadChanged();
            this._unsubOnCardPayloadChanged = null;
        }
        if (this._unsubOnHostConfigPayloadChanged) {
            this._unsubOnHostConfigPayloadChanged();
            this._unsubOnHostConfigPayloadChanged = null;
        }
    }
    
    private fail(message: string) {
        this._errorElement.innerText = message;
        this._errorElement.style.display = "block";
        this._progressElement.style.display = "none";
        this._qrCodeElement.style.display = "none";
    }
}