import AdaptiveCards_bridge

class FakeActionSet: ACSActionSet {
    public var actions: [ACSBaseActionElement] = []

    open override func getActions() -> [ACSBaseActionElement] {
        return actions
    }
}
extension FakeActionSet {
    static func make(actions: [ACSBaseActionElement] = []) -> FakeActionSet {
        let fakeActionSet = FakeActionSet()
        fakeActionSet.actions = actions
        return fakeActionSet
    }
}

