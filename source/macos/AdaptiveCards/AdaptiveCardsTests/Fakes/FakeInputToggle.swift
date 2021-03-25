import AdaptiveCards_bridge

class FakeInputToggle: ACSToggleInput {
    public var title: String?
    public var value: String?
    public var valueOn: String?
    public var valueOff: String?
    public var wrap: Bool = false
    public var id: String? = ""
    public var label: String? = ""
    public var visibility: Bool = true
    
    open override func getTitle() -> String? {
        return title
    }

    open override func setTitle(_ value: String) {
        title = value
    }

    open override func getValue() -> String? {
        return value
    }

    open override func setValue(_ value: String) {
        self.value = value
    }

    open override func getValueOn() -> String? {
        return valueOn
    }
    
    open override func setValueOn(_ value: String) {
        valueOn = value
    }
    
    open override func getValueOff() -> String? {
        return valueOff
    }
    
    open override func setValueOff(_ value: String) {
        valueOff = value
    }
    
    open override func getWrap() -> Bool {
        return wrap
    }

    open override func setWrap(_ value: Bool) {
        wrap = value
    }
    
    open override func getType() -> ACSCardElementType {
        return .toggleInput
    }
    
    open override func getSeparator() -> Bool {
        return false
    }
    
    open override func getId() -> String? {
        return id
    }
    
    override func getIsVisible() -> Bool {
        return visibility
    }
    
    override func getLabel() -> String? {
        return label
    }
}
extension FakeInputToggle {
    static func make(title: String? = "", value: String = "false", valueOn: String = "true", valueOff: String = "false", wrap: Bool = false) ->FakeInputToggle {
        let fakeInputToggle = FakeInputToggle()
        fakeInputToggle.title = title
        fakeInputToggle.value = value
        fakeInputToggle.valueOn = valueOn
        fakeInputToggle.valueOff = valueOff
        fakeInputToggle.wrap = wrap
        return fakeInputToggle
    }
}
