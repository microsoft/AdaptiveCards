import {ToggleInput} from "../../src/card-elements";

test('ToggleInput should be instantiated', ()=>{
    const toggleInput = new ToggleInput();
    expect(toggleInput).toEqual(expect.anything());
})