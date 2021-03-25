import AdaptiveCards_bridge

class FakeChoiceSetInput: ACSChoiceSetInput {
    public var isMultiSelect: Bool = false
    public var choiceSetStyle: ACSChoiceSetStyle = .compact
    public var choices: [ACSChoiceInput] = []
    public var placeholder: String?
    public var value: String?
    public var wrap: Bool = false
    public var id: String? = ""
    
    open override func getIsMultiSelect() -> Bool {
        return isMultiSelect
    }
    
    open override func setIsMultiSelect(_ isMultiSelect: Bool) {
        self.isMultiSelect = isMultiSelect
    }
    
    open override func getChoiceSetStyle() -> ACSChoiceSetStyle {
        return choiceSetStyle
    }
    
    open override func setChoiceSetStyle(_ value: ACSChoiceSetStyle) {
        choiceSetStyle = value
    }
    
    open override func getChoices() -> [ACSChoiceInput] {
        return choices
    }
    
    open override func setPlaceholder(_ value: String) {
        placeholder = value
    }

    open override func getPlaceholder() -> String? {
        return placeholder
    }

    open override func getValue() -> String? {
        return value
    }

    open override func setValue(_ value: String) {
        self.value = value
    }
    
    open override func getWrap() -> Bool {
        return wrap
    }

    open override func setWrap(_ value: Bool) {
        wrap = value
    }
    
    override func getId() -> String? {
        return id
    }
}
extension FakeChoiceSetInput {
    static func make(isMultiSelect: Bool = false, value: String = "1", choices: [ACSChoiceInput] = [], wrap: Bool = false, choiceSetStyle: ACSChoiceSetStyle = .expanded, placeholder: String? = "") -> FakeChoiceSetInput {
        let fakeChoiceSetInput = FakeChoiceSetInput()
        fakeChoiceSetInput.placeholder = placeholder
        fakeChoiceSetInput.value = value
        fakeChoiceSetInput.choiceSetStyle = choiceSetStyle
        fakeChoiceSetInput.choices = choices
        fakeChoiceSetInput.isMultiSelect = isMultiSelect
        fakeChoiceSetInput.wrap = wrap
        return fakeChoiceSetInput
    }
}

