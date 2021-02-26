import AdaptiveCards_bridge

class FakeFacts: ACSFact {
    private var title: String?
    private var value: String?
    private var language: String?
    private var titleForDateParsing: ACSDateTimePreparser?
    private var valueForDateParsing: ACSDateTimePreparser?
    
    override func getTitle() -> String? {
        return title
    }
    
    override func setTitle(_ value: String) {
        title = value
    }
    
    override func getValue() -> String? {
        return value
    }
    
    override func setValue(_ value: String) {
        self.value = value
    }
    
    override func getLanguage() -> String? {
        return language
    }
    
    override func setLanguage(_ value: String) {
        language = value
    }
    
    override func getTitleForDateParsing() -> ACSDateTimePreparser? {
        return titleForDateParsing
    }
    
    override func getValueForDateParsing() -> ACSDateTimePreparser? {
        return valueForDateParsing
    }
}

extension FakeFacts {
    static func make(title: String? = "", value: String? = "", language: String? = "", titleForDateParsing: ACSDateTimePreparser? = .none, valueForDateParsing: ACSDateTimePreparser? = .none) -> FakeFacts {
        let fakeFact = FakeFacts()
        fakeFact.title = title
        fakeFact.value = value
        fakeFact.language = language
        fakeFact.titleForDateParsing = titleForDateParsing
        fakeFact.valueForDateParsing = valueForDateParsing
        return fakeFact
    }
}
