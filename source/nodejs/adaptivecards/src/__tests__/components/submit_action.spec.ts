import {SubmitAction} from "../../card-elements";

test('SubmitAction should be instantiated', ()=>{
    const submitAction = new SubmitAction();
    expect(submitAction).toEqual(expect.anything());
})