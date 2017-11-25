import {TextBlock} from "../../src/card-elements";

test('TextBlock should be instantiated', ()=>{
    const textBlock = new TextBlock();
    expect(textBlock).toEqual(expect.anything());
})