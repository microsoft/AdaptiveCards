import { HttpAction } from "../../src/card-elements";

test('HttpAction should be instantiate', () => {
    const httpAction = new HttpAction();
    expect(httpAction).toEqual(expect.anything());
})