import AdaptiveCards_bridge

class FakeChoiceInput: ACSChoiceInput {
    public var title: String?
    public var value: String?
    
    
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
    
}
extension FakeChoiceInput {
    static func make(title: String? = "Red", value: String = "1") -> FakeChoiceInput {
        let fakeChoiceInput = FakeChoiceInput()
        
        fakeChoiceInput.title = title
        fakeChoiceInput.value = value
        
        return fakeChoiceInput
    }
}

