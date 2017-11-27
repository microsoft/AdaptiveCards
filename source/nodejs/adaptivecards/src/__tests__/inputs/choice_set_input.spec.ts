import {ChoiceSetInput} from "../../card-elements";

test('ChoiceSetInput should be instantiated', ()=>{
    const choiceSetInput = new ChoiceSetInput();
    expect(choiceSetInput).toEqual(expect.anything());
})