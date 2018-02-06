import { Container } from "../../card-elements";

test('Container should be instantiated', () => {
    const container = new Container();
    expect(container).toEqual(expect.anything());
})