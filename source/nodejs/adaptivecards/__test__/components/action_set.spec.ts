import { ActionSet } from "../../src/card-elements";

test('ActionSet should be instantiated', () => {
    const actionSet = new ActionSet();
    expect(actionSet).toEqual(expect.anything());
})