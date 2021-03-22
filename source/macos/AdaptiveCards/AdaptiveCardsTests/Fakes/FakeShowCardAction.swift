import AdaptiveCards_bridge

class FakeShowCardAction: ACSShowCardAction {
    public var card: ACSAdaptiveCard?
    public var title: String?
    public var iconUrl: String?
    public var style: String?
    
    override func getCard() -> ACSAdaptiveCard? {
        return card
    }
    
    override func setCard(_ card: ACSAdaptiveCard) {
        self.card = card
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

extension FakeShowCardAction {
    static func make(card: ACSAdaptiveCard? = nil, title: String? = "", iconUrl: String? = "", style: String? = "") -> FakeShowCardAction {
        let fakeShowCardAction = FakeShowCardAction()
        fakeShowCardAction.card = card
        fakeShowCardAction.title = title
        fakeShowCardAction.iconUrl = iconUrl
        fakeShowCardAction.style = style
        return fakeShowCardAction
    }
}
