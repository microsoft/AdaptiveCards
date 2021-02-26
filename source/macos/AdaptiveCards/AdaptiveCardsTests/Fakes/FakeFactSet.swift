import AdaptiveCards_bridge

class FakeFactSet: ACSFactSet {
    public var factArray: [FakeFacts] = []
    
    override func getFacts() -> [ACSFact] {
        return factArray
    }
}

extension FakeFactSet {
    static func make(factArray: [FakeFacts] = []) -> FakeFactSet {
        let fakeFactSet = FakeFactSet()
        fakeFactSet.factArray = factArray
        return fakeFactSet
    }
}
