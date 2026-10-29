// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { Choice, FilteredChoiceSet } from "../../card-elements";

// Minimal DOM stand-in (the adaptivecards tests run in the node environment). Like a real document,
// getElementById searches the elements attached under body, in document order, and does not look
// inside shadow roots.
class FakeClassList {
    private readonly _classes = new Set<string>();

    add(...classNames: string[]) {
        classNames.forEach((className) => this._classes.add(className));
    }

    remove(...classNames: string[]) {
        classNames.forEach((className) => this._classes.delete(className));
    }

    contains(className: string) {
        return this._classes.has(className);
    }

    get length() {
        return this._classes.size;
    }
}

class FakeElement {
    readonly children: FakeElement[] = [];
    readonly classList = new FakeClassList();
    readonly style: { [key: string]: string } = {};
    id = "";
    className = "";
    type = "";
    value = "";
    tabIndex = 0;
    clickCount = 0;
    isShadowHost = false;
    onclick?: () => void;
    onmousemove?: () => void;
    onkeydown?: (event: { key: string; preventDefault: () => void }) => void;
    private _text = "";

    get innerText(): string {
        return this.children.length > 0
            ? this.children.map((child) => child.innerText).join("")
            : this._text;
    }

    set innerText(value: string) {
        this._text = value;
    }

    get firstChild() {
        return this.children[0];
    }

    appendChild(child: FakeElement) {
        this.children.push(child);
        return child;
    }

    append(...children: FakeElement[]) {
        children.forEach((child) => this.appendChild(child));
    }

    removeChild(child: FakeElement) {
        this.children.splice(this.children.indexOf(child), 1);
        return child;
    }

    contains(element: FakeElement): boolean {
        return this.children.some((child) => child === element || child.contains(element));
    }

    hasChildNodes() {
        return this.children.length > 0;
    }

    scrollIntoView() {}

    focus() {}

    click() {
        this.clickCount++;
        this.onclick?.();
    }
}

class FakeDocument {
    readonly body = new FakeElement();

    createElement() {
        return new FakeElement();
    }

    getElementById(id: string): FakeElement | null {
        const find = (element: FakeElement): FakeElement | null => {
            for (const child of element.children) {
                if (child.id === id) {
                    return child;
                }

                const match = child.isShadowHost ? null : find(child);

                if (match) {
                    return match;
                }
            }

            return null;
        };

        return find(this.body);
    }
}

const highlightedClassName = "ac-choiceSetInput-choice-highlighted";
const originalDocument = (globalThis as any).document;

function renderFilteredChoiceSet(options: { shadowRoot?: boolean; decoyId?: string } = {}) {
    const fakeDocument = new FakeDocument();
    (globalThis as any).document = fakeDocument;

    // An element that precedes the choice set in the document and uses the id of its first choice
    const decoy = fakeDocument.createElement();
    if (options.decoyId) {
        decoy.id = options.decoyId;
    }
    fakeDocument.body.appendChild(decoy);

    const choiceSet = new FilteredChoiceSet(1, [
        new Choice("Alpha", "a"),
        new Choice("Beta", "b"),
        new Choice("Charlie", "c")
    ]);
    choiceSet.render();

    const renderedElement = choiceSet.renderedElement as unknown as FakeElement;

    if (options.shadowRoot) {
        const shadowHost = fakeDocument.createElement();
        shadowHost.isShadowHost = true;
        shadowHost.appendChild(renderedElement);
        fakeDocument.body.appendChild(shadowHost);
    } else {
        fakeDocument.body.appendChild(renderedElement);
    }

    const textInput = choiceSet.textInput as unknown as FakeElement;
    const dropdown = choiceSet.dropdown as unknown as FakeElement;
    const pressKey = (key: string) => textInput.onkeydown?.({ key, preventDefault: () => {} });
    const filter = (value: string) => {
        textInput.value = value;
        choiceSet.processChoices();
    };

    return { choiceSet, textInput, dropdown, decoy, pressKey, filter };
}

afterEach(() => {
    (globalThis as any).document = originalDocument;
});

describe("FilteredChoiceSet", () => {
    test("selects the highlighted choice with the keyboard", () => {
        const { textInput, dropdown, pressKey, filter } = renderFilteredChoiceSet();

        filter("a");
        expect(dropdown.children.map((choice) => choice.innerText)).toEqual([
            "Alpha",
            "Beta",
            "Charlie"
        ]);

        pressKey("ArrowDown");
        pressKey("ArrowDown");
        expect(dropdown.children[1].className).toContain("ac-choiceSetInput-choice");
        expect(dropdown.children[1].classList.contains(highlightedClassName)).toBe(true);
        expect(dropdown.children[0].classList.contains(highlightedClassName)).toBe(false);

        pressKey("Enter");
        expect(textInput.value).toBe("Beta");
    });

    test("wraps around and supports ArrowUp", () => {
        const { textInput, pressKey, filter } = renderFilteredChoiceSet();

        filter("a");
        pressKey("ArrowUp");
        pressKey("Enter");
        expect(textInput.value).toBe("Charlie");
    });

    test("selects a choice highlighted with the mouse", () => {
        const { textInput, dropdown, pressKey, filter } = renderFilteredChoiceSet();

        filter("a");
        dropdown.children[2].onmousemove?.();
        pressKey("Enter");
        expect(textInput.value).toBe("Charlie");
    });

    test("uses the current choices after the filter changes", () => {
        const { textInput, pressKey, filter } = renderFilteredChoiceSet();

        filter("a");
        pressKey("ArrowDown");
        filter("char");
        pressKey("ArrowDown");
        pressKey("Enter");
        expect(textInput.value).toBe("Charlie");
    });

    test("selects fetched choices with the keyboard", () => {
        const { choiceSet, textInput, pressKey, filter } = renderFilteredChoiceSet();

        filter("del");
        choiceSet.processResponse("del", [{ title: "Delta", value: "d" }]);
        pressKey("ArrowDown");
        pressKey("Enter");
        expect(textInput.value).toBe("Delta");
    });

    test("is not redirected to another element that uses the id of a choice", () => {
        const { textInput, dropdown, decoy, pressKey, filter } = renderFilteredChoiceSet({
            decoyId: "ac-choiceSetInput-1-choice-0"
        });

        filter("a");
        pressKey("ArrowDown");
        pressKey("Enter");

        expect(decoy.clickCount).toBe(0);
        expect(decoy.classList.length).toBe(0);
        expect(dropdown.children[0].clickCount).toBe(1);
        expect(textInput.value).toBe("Alpha");
    });

    test("works when its elements cannot be found by id (shadow root)", () => {
        const { textInput, pressKey, filter } = renderFilteredChoiceSet({ shadowRoot: true });

        filter("a");
        pressKey("ArrowDown");
        pressKey("Enter");
        expect(textInput.value).toBe("Alpha");
    });
});
