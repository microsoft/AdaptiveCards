import {OpenUrlAction} from "../../src/card-elements";

test('OpenUrlAction should be instantiated', ()=>{
    const openUrlAction = new OpenUrlAction();
    expect(openUrlAction).toEqual(expect.anything());
})