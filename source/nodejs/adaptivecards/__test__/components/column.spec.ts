import { Column } from "../../src/card-elements";

test('Column should be instantiated', () => {
    const column = new Column();
    expect(column).toEqual(expect.anything());
})