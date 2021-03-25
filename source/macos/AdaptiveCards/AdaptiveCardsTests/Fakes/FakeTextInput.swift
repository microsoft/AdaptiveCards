import AdaptiveCards_bridge

class FakeInputText: ACSTextInput {
    public var placeholderString: String?
    public var value: String?
    public var isMultiline: Bool = false
    public var maxLength: NSNumber?
    public var style: ACSTextInputStyle = .text
    public var inlineAction: ACSBaseActionElement? = .none
    public var regexString: String?
    public var id: String? = ""
    public var visibility: Bool = true
    
    override func getPlaceholder() -> String? {
        return placeholderString
    }
    
    override func setPlaceholder(_ value: String) {
        placeholderString = value
    }
    
    override func getValue() -> String? {
        return value
    }
    
    override func setValue(_ value: String) {
        self.value = value
    }
    
    override func getIsMultiline() -> Bool {
        return isMultiline
    }
    
    override func setIsMultiline(_ value: Bool) {
        isMultiline = value
    }
    
    override func getMaxLength() -> NSNumber? {
        return maxLength
    }
    
    override func setMaxLength(_ value: NSNumber) {
        maxLength = value
    }
    
    override func getStyle() -> ACSTextInputStyle {
        return style
    }
    
    override func setTextInputStyle(_ value: ACSTextInputStyle) {
        style = value
    }
    
    override func getInlineAction() -> ACSBaseActionElement? {
        return inlineAction
    }
    
    override func setInlineAction(_ action: ACSBaseActionElement) {
        inlineAction = action
    }
    
    override func getRegex() -> String? {
        return regexString
    }
    
    override func setRegex(_ value: String) {
        regexString = value
    }
    
    override func getId() -> String? {
        return id
    }
    
    override func getIsVisible() -> Bool {
        return visibility
    }
}

extension FakeInputText {
    static func make(placeholderString: String? = "", value: String? = "", isMultiline: Bool = false, maxLength: NSNumber? = 0, style: ACSTextInputStyle = .text, inlineAction: ACSBaseActionElement? = .none, regexString: String? = "") -> FakeInputText {
        let fakeInputText = FakeInputText()
        fakeInputText.placeholderString = placeholderString
        fakeInputText.value = value
        fakeInputText.isMultiline = isMultiline
        fakeInputText.maxLength = maxLength
        fakeInputText.style = style
        fakeInputText.inlineAction = inlineAction
        fakeInputText.regexString = regexString
        return fakeInputText
    }
}

