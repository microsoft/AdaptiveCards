import { ColumnSet } from "../../src/card-elements";

test('Container should be instantiated', () => {
    const columnSet = new ColumnSet();
    expect(columnSet).toEqual(expect.anything());
})
