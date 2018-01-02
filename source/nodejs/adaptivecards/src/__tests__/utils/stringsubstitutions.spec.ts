import { StringWithSubstitutions, IInput}  from "../../utils";
import { TextInput } from "../../card-elements";

test('application/json encoding works', () => {
    let v = new StringWithSubstitutions();

    let input1: IInput = {
        id: "input1",
        value: "text:\n{value}\"quote\"end"
    }

    let inputs = [input1];

    v.set("key:{{input1.value}}")

    v.substituteInputValues(inputs, "application/json");

    expect(v.get()).toEqual("key:text:\\n\{value\}\\\"quote\\\"end");
})

test('application/x-www-form-urlencoded encoding works', () => {
    let v = new StringWithSubstitutions();

    let input1: IInput = {
        id: "input1",
        value: "text=3&b=4\nsecondline"
    }

    let inputs = [input1];

    v.set("key={{input1.value}}")

    v.substituteInputValues(inputs, "application/x-www-form-urlencoded");

    expect(v.get()).toEqual("key=text%3D3%26b%3D4%0Asecondline");
})

test('unknown content type no escaping', () => {
    let v = new StringWithSubstitutions();

    let input1: IInput = {
        id: "input1",
        value: "text=3&b=4\nsecondline"
    }

    let inputs = [input1];

    v.set("key={{input1.value}}")

    v.substituteInputValues(inputs, "unknown");

    expect(v.get()).toEqual("key=text=3&b=4\nsecondline");
})