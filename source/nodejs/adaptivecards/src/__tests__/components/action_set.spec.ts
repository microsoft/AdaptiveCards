// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { ActionSet, SubmitAction } from "../../card-elements";

test('ActionSet should be instantiated', () => {
    const actionSet = new ActionSet();
    expect(actionSet).toEqual(expect.anything());
})

test('getActionById returns action', () =>{
	const actionSet = new ActionSet()
	const action = new SubmitAction()
	const id = 'Card.LastActionHero'
	action.id = id

	actionSet.addAction(action)

	const result = actionSet.getActionById(id)

	expect(result).not.toBeUndefined()
})
