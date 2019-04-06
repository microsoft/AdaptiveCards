import { PeerConnections } from "./peer-connections"
import { QRCode } from "qrcode-generator-ts/js";
import { CardDesigner } from "./card-designer";

export class JoinDialog {

    readonly _cardDesigner: CardDesigner;

    private _clientPeerConn: any;
    private _hostDataChannel: any;

    constructor(
        cardDesigner: CardDesigner) {
        this._cardDesigner = cardDesigner;
        this.startJoinProcess();
    }

    private async startJoinProcess() {
        var respondId = prompt("Enter respond id");

        try {
            var joinInfo = await PeerConnections.getJoinInfo(respondId);
            await this.receivedOfferAndCandidates(joinInfo, respondId);
        } catch (err) {
            alert(err);
        }
    }

    private async receivedOfferAndCandidates(offerAndCandidates: any, respondId: string) {
		var candidates = [];
        this._clientPeerConn = PeerConnections.createPeerConnection();
        
		this._clientPeerConn.ondatachannel = (e) => {
			var dataChannel = e.channel;
			dataChannel.onopen = (e) => {
                console.log('Connected');
                this._cardDesigner.markJoined();
			};
			dataChannel.onmessage = (e) => {
				console.log('Got message');
				var dataMessage = JSON.parse(e.data);
				if (dataMessage.cardPayload !== undefined) {
                    var cardPayload: string = dataMessage.cardPayload;
                    this._cardDesigner.setJsonPayloadAsString(cardPayload);
				}
				if (dataMessage.hostConfigPayload !== undefined) {
                    //var hostConfigPayload: string = dataMessage.hostConfigPayload;
                    // TODO: Figure out how to set host config
					//this.activeHostContainer.getHostConfig
				}
			}
        };
        
		this._clientPeerConn.onicecandidate = async function (e) {
			if (e.candidate != null) {
				candidates.push(e.candidate);
			} else {
				var answerAndCandidates = {
					sdp: this._clientPeerConn.localDescription.sdp,
					candidates: candidates
				};

                await PeerConnections.sendAnswerInfo(respondId, answerAndCandidates);
			}
        }.bind(this);
        
		var offer: any = {
			type: "offer",
			sdp: offerAndCandidates.sdp
		};
		var offerDesc = new RTCSessionDescription(offer);
		await this._clientPeerConn.setRemoteDescription(offerDesc);
		await PeerConnections.addIceCandidates(this._clientPeerConn, offerAndCandidates.candidates);
		var answerDesc = await this._clientPeerConn.createAnswer({});
		await this._clientPeerConn.setLocalDescription(answerDesc);
	}
}