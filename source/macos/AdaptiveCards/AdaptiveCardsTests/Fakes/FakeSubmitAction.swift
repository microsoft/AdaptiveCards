import AdaptiveCards_bridge

class FakeSubmitAction: ACSSubmitAction {
    public var dataJson: String = ""
    public var associatedInputs: ACSAssociatedInputs = .none

    open override func getDataJson() -> String {
        return dataJson
    }
    
    override func setDataJson(_ value: String) {
        dataJson = value
    }
    
    override func getAssociatedInputs() -> ACSAssociatedInputs {
        return associatedInputs
    }
    
    override func setAssociatedInputs(_ value: ACSAssociatedInputs) {
        associatedInputs = value
    }
    
    open override func getType() -> ACSActionType {
        return .submit
    }
}
extension FakeSubmitAction {
    static func make(dataJson: String = "", associatedInputs: ACSAssociatedInputs = .none) -> FakeSubmitAction {
        let fakeSubmitAction = FakeSubmitAction()
        fakeSubmitAction.dataJson = dataJson
        fakeSubmitAction.associatedInputs = associatedInputs
        return fakeSubmitAction
    }
}
