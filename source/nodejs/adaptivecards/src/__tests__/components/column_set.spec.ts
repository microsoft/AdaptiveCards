import { ColumnSet } from "../../card-elements";

test('Container should be instantiated', () => {
    const columnSet = new ColumnSet();
    expect(columnSet).toEqual(expect.anything());
})
