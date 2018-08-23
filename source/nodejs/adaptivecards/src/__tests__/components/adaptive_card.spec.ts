import { AdaptiveCard, SubmitAction } from "../../card-elements";

test('AdaptiveCard should be instantiated', () => {
    const adaptiveCard = new AdaptiveCard();
    expect(adaptiveCard).toEqual(expect.anything());
})

test('Can get actions for AdaptiveCard', () => {
	const adaptiveCard = new AdaptiveCard();
	const adaptiveCardAction1 = new SubmitAction();
	const adaptiveCardAction2 = new SubmitAction();

	adaptiveCard.addAction(adaptiveCardAction1);
	adaptiveCard.addAction(adaptiveCardAction2);
	
	let actions = adaptiveCard.getActions();
	expect(actions && actions.length).toEqual(2);
});
