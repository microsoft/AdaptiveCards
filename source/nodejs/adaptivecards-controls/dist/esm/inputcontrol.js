export class InputControl {
    validateRootElement(rootElement) {
        // Do nothing - all root element types are valid.
    }
    keyDown(e) {
        // Do nothing in base implementation
    }
    get rootElement() {
        return this._rootElement;
    }
    attach(rootElement) {
        this.validateRootElement(rootElement);
        this._rootElement = rootElement;
        this._rootElement.onkeydown = (e) => { this.keyDown(e); };
    }
}
//# sourceMappingURL=inputcontrol.js.map