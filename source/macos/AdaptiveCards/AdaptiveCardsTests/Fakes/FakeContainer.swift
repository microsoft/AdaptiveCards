import AdaptiveCards_bridge

class FakeContainer: ACSContainer {
    public var style: ACSContainerStyle = .default
    public var verticalContentAlignment: ACSVerticalContentAlignment = .top
    public var bleed: Bool = false
    public var backgroundImage: ACSBackgroundImage?
    public var minHeight: NSNumber?
    public var selectAction: ACSBaseActionElement?
    public var items: [ACSBaseCardElement] = []
    public var padding: Bool = false
    
    open override func getStyle() -> ACSContainerStyle {
        return style
    }

    open override func setStyle(_ value: ACSContainerStyle) {
        style = value
    }

    open override func getVerticalContentAlignment() -> ACSVerticalContentAlignment {
        return verticalContentAlignment
    }

    open override func setVerticalContentAlignment(_ value: ACSVerticalContentAlignment) {
        verticalContentAlignment = value
    }

    open override func getBleed() -> Bool {
        return bleed
    }
    
    open override func setBleed(_ value: Bool) {
        bleed = value
    }
    
    open override func getBackgroundImage() -> ACSBackgroundImage? {
        return backgroundImage
    }
    
    open override func setBackgroundImage(_ value: ACSBackgroundImage?) {
        backgroundImage = value
    }
    
    open override func getMinHeight() -> NSNumber? {
        return minHeight
    }

    open override func setMinHeight(_ value: NSNumber?) {
        minHeight = value
    }
    
    open override func getSelectAction() -> ACSBaseActionElement? {
        return selectAction
    }
    
    open override func setSelectAction(_ value: ACSBaseActionElement?) {
        selectAction = value
    }
    
    open override func getItems() -> [ACSBaseCardElement] {
        return items
    }
    
    open override func getPadding() -> Bool {
        return padding
    }
}
extension FakeContainer {
    static func make(style: ACSContainerStyle = .default, verticalContentAlignment: ACSVerticalContentAlignment = .top, bleed: Bool = false, backgroundImage: ACSBackgroundImage? = nil, minHeight: NSNumber? = 0, selectAction: ACSBaseActionElement? = .none, items: [ACSBaseCardElement] = [], padding: Bool = false) -> FakeContainer {
        let fakeContainer = FakeContainer()
        fakeContainer.style = style
        fakeContainer.verticalContentAlignment = verticalContentAlignment
        fakeContainer.bleed = bleed
        fakeContainer.backgroundImage = backgroundImage
        fakeContainer.minHeight = minHeight
        fakeContainer.selectAction = selectAction
        fakeContainer.items = items
        fakeContainer.padding = padding
        return fakeContainer
    }
}

