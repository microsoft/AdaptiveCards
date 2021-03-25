import AdaptiveCards_bridge

class FakeInputDate: ACSDateInput {
    public var value: String?
    public var placeholder: String?
    public var max: String?
    public var min: String?
    public var id: String? = ""
    public var visibility: Bool = true

    open override func getValue() -> String? {
        return value
    }
    
    open override func setValue(_ value: String?) {
        self.value = value
    }
    
    open override func getPlaceholder() -> String? {
        return placeholder
    }
    
    override func setPlaceholder(_ value: String) {
        placeholder = value
    }
    
    override func getMax() -> String? {
        return max
    }
    
    override func setMax(_ value: String?) {
        max = value
    }
    
    override func getMin() -> String? {
        return min
    }
    
    override func setMin(_ value: String?) {
        min = value
    }
    
    override func getId() -> String? {
        return id
    }
    
    override func getIsVisible() -> Bool {
        return visibility
    }
}

extension FakeInputDate {
    static func make(value: String? = "", placeholder: String? = "", max: String? = "", min: String? = "") -> FakeInputDate {
        let fakeInputDate = FakeInputDate()
        fakeInputDate.value = value
        fakeInputDate.placeholder = placeholder
        fakeInputDate.max = max
        fakeInputDate.min = min
        return fakeInputDate
    }
}
