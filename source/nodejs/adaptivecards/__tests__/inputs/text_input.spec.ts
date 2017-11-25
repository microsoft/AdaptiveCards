import {TextInput} from "../../src/card-elements";

test('TextInput should be instantiated', ()=>{
    const textInput = new TextInput();
    expect(textInput).toEqual(expect.anything());
})