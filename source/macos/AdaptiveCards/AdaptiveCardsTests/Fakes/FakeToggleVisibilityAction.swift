import AdaptiveCards_bridge

class FakeToggleVisibilityAction: ACSToggleVisibilityAction {
    public var targetElements: [ACSToggleVisibilityTarget] = []
    public var title: String?
    public var iconUrl: String?
    public var style: String?
    
    override func getTargetElements() -> [ACSToggleVisibilityTarget] {
        return targetElements
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
    
    override func getType() -> ACSActionType {
        return .toggleVisibility
    }
}

extension FakeToggleVisibilityAction {
    static func make(targetElements: [ACSToggleVisibilityTarget] = [], title: String? = "", iconUrl: String? = "", style: String? = "", inputText: ACSTextInput? = nil) -> FakeToggleVisibilityAction {
        let fakeToggleVisibilityAction = FakeToggleVisibilityAction()
        fakeToggleVisibilityAction.targetElements = targetElements
        fakeToggleVisibilityAction.title = title
        fakeToggleVisibilityAction.iconUrl = iconUrl
        fakeToggleVisibilityAction.style = style
        return fakeToggleVisibilityAction
    }
}
