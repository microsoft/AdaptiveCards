import AdaptiveCards_bridge

class FakeActionSet: ACSActionSet {
    public var actions: [ACSBaseActionElement] = []
    public var horizontalAlignment: ACSHorizontalAlignment = .left

    open override func getActions() -> [ACSBaseActionElement] {
        return actions
    }
    
    open override func getHorizontalAlignment() -> ACSHorizontalAlignment {
        return horizontalAlignment
    }
    
    open override func setHorizontalAlignment(_ value: ACSHorizontalAlignment) {
        horizontalAlignment = value
    }
}
extension FakeActionSet {
    static func make(actions: [ACSBaseActionElement] = [], aligned alighnment: ACSHorizontalAlignment = .left) -> FakeActionSet {
        let fakeActionSet = FakeActionSet()
        fakeActionSet.actions = actions
        fakeActionSet.horizontalAlignment = alighnment
        return fakeActionSet
    }
}

