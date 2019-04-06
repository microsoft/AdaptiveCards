export class PeerConnections {
    
	private static _signalingServerBaseUrl = "signalingserver.azurewebsites.net/api/subscriptions";
    
    static createPeerConnection() {
		return new RTCPeerConnection({
			iceServers: [
				{
                    urls: [ "stun:ws-turn3.xirsys.com" ]
                 },
                 {
                    username: "e-HcX5lqoTEzSQetY5biyT3YzM45GIl3HK4FQuo3y73xvsLAmts_gF8PylqkwBR6AAAAAFyoMKphbGVhZGVy",
                    credential: "d97cbeee-5827-11e9-bef6-069f0817bf63",
                    urls: [
                        "turn:ws-turn3.xirsys.com:80?transport=udp",
                        "turn:ws-turn3.xirsys.com:3478?transport=udp",
                        "turn:ws-turn3.xirsys.com:80?transport=tcp",
                        "turn:ws-turn3.xirsys.com:3478?transport=tcp",
                        "turns:ws-turn3.xirsys.com:443?transport=tcp",
                        "turns:ws-turn3.xirsys.com:5349?transport=tcp"
                    ]
                 }
			]
		});
    }
    
    static async createSubscription(offerAndCandidates: any) : Promise<string> {
        var response = await fetch("https://" + this._signalingServerBaseUrl, {
            method: "POST",
            body: JSON.stringify(offerAndCandidates)
        });

        if (!response.ok) {
            throw new Error("Network response was " + response.status);
        }

        var respondId: string = await response.text();
        return respondId;
    }

    static async getJoinInfo(respondId: string) : Promise<any> {
        var response = await fetch("https://" + this._signalingServerBaseUrl + "/" + respondId);
        if (!response.ok) {
            throw new Error("Network response was " + response.status);
        }

        var joinInfo = await response.json();
        return joinInfo;
    }

    static async sendAnswerInfo(respondId: string, answerAndCandidates: any) : Promise<any> {
        var response = await fetch("https://" + this._signalingServerBaseUrl + "/" + respondId, {
            method: "PUT",
            body: JSON.stringify(answerAndCandidates)
        });
        if (!response.ok) {
            throw new Error("Network response wasn't ok");
        }

        // Otherwise, success! Don't have anything to return
    }

    static getWebSocketUrl(respondId: string) {
        return "wss://" + this._signalingServerBaseUrl + "/" + respondId;
    }

	static async addIceCandidates(peerConn: any, candidates: any) {
		for (var i = 0; i < candidates.length; i++) {
			await peerConn.addIceCandidate(candidates[i]);
		}
	}
}