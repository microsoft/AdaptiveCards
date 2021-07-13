import AdaptiveCards_bridge

class FakeAdaptiveCard: ACSAdaptiveCard {
    public var version: String?
    public var fallbackText: String?
    public var backgroundImage: ACSBackgroundImage?
    public var speak: String?
    public var style: ACSContainerStyle = .default
    public var language: String?
    public var verticalContentAlignment: ACSVerticalContentAlignment = .top
    public var height: ACSHeightType = .auto
    public var minHeight: NSNumber = 0
    public var selectAction: ACSBaseActionElement?
    public var body: [ACSBaseCardElement] = []
    public var actions: [ACSBaseActionElement] = []
    
    override func getVersion() -> String? {
        return version
    }
    
    override func getFallbackText() -> String? {
        return fallbackText
    }
    
    override func getBackgroundImage() -> ACSBackgroundImage? {
        return backgroundImage
    }
    
    override func getSpeak() -> String? {
        return speak
    }
    
    override func getStyle() -> ACSContainerStyle {
        return style
    }
    
    override func getLanguage() -> String? {
        return language
    }
    
    override func getVerticalContentAlignment() -> ACSVerticalContentAlignment {
        return verticalContentAlignment
    }
    
    override func getHeight() -> ACSHeightType {
        return height
    }
    
    override func getMinHeight() -> NSNumber? {
        return minHeight
    }
    
    override func getSelectAction() -> ACSBaseActionElement? {
        return selectAction
    }
    
    override func getBody() -> [ACSBaseCardElement] {
        return body
    }
    
    override func getActions() -> [ACSBaseActionElement] {
        return actions
    }
    
    override func getInternalId() -> ACSInternalId? {
        return FakeInternalId(hash: hashValue as NSNumber)
    }
}

extension FakeAdaptiveCard {
    static func make(version: String? = "", fallbackText: String? = "", backgroundImage: ACSBackgroundImage? = nil, speak: String? = "", style: ACSContainerStyle = .default, language: String? = "", verticalContentAlignment: ACSVerticalContentAlignment = .top, height: ACSHeightType = .auto, minHeight: NSNumber = 0, selectAction: ACSBaseActionElement? = nil, body: [ACSBaseCardElement] = [], actions: [ACSBaseActionElement] = []) -> FakeAdaptiveCard {
        let fakeCard = FakeAdaptiveCard()
        fakeCard.version = version
        fakeCard.fallbackText = fallbackText
        fakeCard.backgroundImage = backgroundImage
        fakeCard.speak = speak
        fakeCard.style = style
        fakeCard.language = language
        fakeCard.verticalContentAlignment = verticalContentAlignment
        fakeCard.height = height
        fakeCard.minHeight = minHeight
        fakeCard.selectAction = selectAction
        fakeCard.body = body
        fakeCard.actions = actions
        return fakeCard
    }
}
