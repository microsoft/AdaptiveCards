import AdaptiveCards_bridge

class FakeColumnSet: ACSColumnSet {
    var columns: [ACSColumn] = []
    var style: ACSContainerStyle = .default
    
    override func getColumns() -> [ACSColumn] {
        return columns
    }
    
    override func getStyle() -> ACSContainerStyle {
        return style
    }
    
    override func setStyle(_ value: ACSContainerStyle) {
        style = value
    }
}

extension FakeColumnSet {
    static func make(columns: [ACSColumn] = [], style: ACSContainerStyle = .default) -> FakeColumnSet {
        let fakeColumnSet = FakeColumnSet()
        fakeColumnSet.columns = columns
        fakeColumnSet.style = style
        return fakeColumnSet
    }
}
