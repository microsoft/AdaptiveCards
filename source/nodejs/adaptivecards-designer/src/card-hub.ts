export interface ICardData {
	CardJson: string;
}

export class CardHub {
	private static _baseUrl = "https://cardhub.azurewebsites.net/api/";

	// Creates a card and returns the CardId.
	static async createCardAsync(cardData: ICardData) {
		var response = await fetch(this._baseUrl + "card", {
			method: "POST",
			headers: {
				"Content-Type": "application/json"
			},
			body: JSON.stringify(cardData)
		});

		if (!response.ok) {
            throw new Error("Network response was " + response.status);
		}
		
		var createCardResponse = await response.json();
		return createCardResponse.CardId;
	}

	static async updateCardAsync(cardId: string, cardData: ICardData) {
		var response = await fetch(this._baseUrl + "card/" + cardId, {
			method: "PUT",
			headers: {
				"Content-Type": "application/json"
			},
			body: JSON.stringify(cardData)
		});

		if (!response.ok) {
            throw new Error("Network response was " + response.status);
		}
	}
}