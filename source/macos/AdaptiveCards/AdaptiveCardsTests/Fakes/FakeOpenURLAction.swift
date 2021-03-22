import AdaptiveCards_bridge

class FakeOpenURLAction: ACSOpenUrlAction {
    public var url: String?
    public var title: String?
    public var iconUrl: String?
    public var style: String?
    
    override func getUrl() -> String? {
        return url
    }
    
    override func setUrl(_ value: String?) {
        url = value
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

extension FakeOpenURLAction {
    static func make(url: String? = nil, title: String? = "", iconUrl: String? = "", style: String? = "") -> FakeOpenURLAction {
        let fakeShowCardAction = FakeOpenURLAction()
        fakeShowCardAction.url = url
        fakeShowCardAction.title = title
        fakeShowCardAction.iconUrl = iconUrl
        fakeShowCardAction.style = style
        return fakeShowCardAction
    }
}

