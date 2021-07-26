import AdaptiveCards_bridge

class FakeSubmitAction: ACSSubmitAction {
    public var dataJson: String = ""
    public var associatedInputs: ACSAssociatedInputs = .none
    public var title: String?
    public var iconUrl: String?
    public var style: String?
    public var inputText: ACSTextInput?

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
    
    override func getTitle() -> String? {
        return title
    }
    
    override func setTitle(_ value: String) {
        title = value
    }
    
    override func getIconUrl() -> String? {
        return iconUrl
    }
    
    override func setIconUrl(_ value: String) {
        iconUrl = value
    }
    
    override func getStyle() -> String? {
        return style
    }
    
    override func setStyle(_ value: String) {
        style = value
    }
}

extension FakeSubmitAction {
    static func make(dataJson: String = "", associatedInputs: ACSAssociatedInputs = .none, title: String? = "", iconUrl: String? = "", style: String? = "", inputText: ACSTextInput? = nil) -> FakeSubmitAction {
        let fakeSubmitAction = FakeSubmitAction()
        fakeSubmitAction.inputText = inputText
        fakeSubmitAction.dataJson = dataJson
        fakeSubmitAction.associatedInputs = associatedInputs
        fakeSubmitAction.title = title
        fakeSubmitAction.iconUrl = iconUrl
        fakeSubmitAction.style = style
        return fakeSubmitAction
    }
}
