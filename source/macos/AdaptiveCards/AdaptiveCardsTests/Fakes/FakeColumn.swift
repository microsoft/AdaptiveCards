import AdaptiveCards_bridge

class FakeColumn: ACSColumn {
    var width: String?
    var pixelWidth: NSNumber?
    var items: [ACSBaseCardElement] = []
    var style: ACSContainerStyle = .default
    var verticalContentAlignment: ACSVerticalContentAlignment = .top
    var minHeight: NSNumber?
    var bleed: Bool = false
    var spacing: ACSSpacing = .default
    var separator: Bool = false
    var id: String? = ""
    var backgroundImage: ACSBackgroundImage?
    var selectAction: ACSBaseActionElement?
    
    override func getWidth() -> String? {
        return width
    }
    
    override func setWidth(_ value: String) {
        width = value
    }
    
    override func getPixelWidth() -> NSNumber? {
        return pixelWidth
    }
    
    override func setPixelWidth(_ value: NSNumber) {
        pixelWidth = value
    }
    
    override func getItems() -> [ACSBaseCardElement] {
        return items
    }
    
    override func getStyle() -> ACSContainerStyle {
        return style
    }
    
    override func setStyle(_ value: ACSContainerStyle) {
        style = value
    }
    
    override func getVerticalContentAlignment() -> ACSVerticalContentAlignment {
        return verticalContentAlignment
    }
    
    override func setVerticalContentAlignment(_ value: ACSVerticalContentAlignment) {
        verticalContentAlignment = value
    }
    
    override func getMinHeight() -> NSNumber? {
        return minHeight
    }
    
    override func setMinHeight(_ value: NSNumber) {
        minHeight = value
    }
    
    override func getBleed() -> Bool {
        return bleed
    }
    
    override func setBleed(_ value: Bool) {
        bleed = value
    }
    
    override func getSpacing() -> ACSSpacing {
        return spacing
    }
    
    override func setSpacing(_ value: ACSSpacing) {
        spacing = value
    }
    
    override func getSeparator() -> Bool {
        return separator
    }
    
    override func setSeparator(_ value: Bool) {
        separator = value
    }
    
    override func getBackgroundImage() -> ACSBackgroundImage? {
        return backgroundImage
    }
    
    override func getSelectAction() -> ACSBaseActionElement? {
        return selectAction
    }
    
    override func getId() -> String? {
        return id
    }
}

extension FakeColumn {
    static func make(width: String? = "", pixelWidth: NSNumber? = 0, items: [ACSBaseCardElement] = [], style: ACSContainerStyle = .default, verticalContentAlignment: ACSVerticalContentAlignment = .top, minHeight: NSNumber? = nil, bleed: Bool = false, spacing: ACSSpacing = .default, separator: Bool = false, backgroundImage: ACSBackgroundImage? = nil, selectAction: ACSBaseActionElement? = nil) -> FakeColumn {
        let fakeColumn = FakeColumn()
        fakeColumn.width = width
        fakeColumn.pixelWidth = pixelWidth
        fakeColumn.items = items
        fakeColumn.style = style
        fakeColumn.verticalContentAlignment = verticalContentAlignment
        fakeColumn.minHeight = minHeight
        fakeColumn.bleed = bleed
        fakeColumn.spacing = spacing
        fakeColumn.separator = separator
        fakeColumn.backgroundImage = backgroundImage
        fakeColumn.selectAction = selectAction
        return fakeColumn
    }
}
