import AdaptiveCards_bridge

class FakeBackgroundImage: ACSBackgroundImage {
    private var url: String?
    private var fillMode: ACSImageFillMode = .cover
    private var verticalAlignment: ACSVerticalAlignment = .top
    private var horizontalAlignment: ACSHorizontalAlignment = .center
    
    
    override func getUrl() -> String? {
        return url
    }
    
    override func setUrl(_ value: String) {
        url = value
    }
    
    override func getFillMode() -> ACSImageFillMode {
        return fillMode
    }
    
    override func setFillMode(_ value: ACSImageFillMode) {
        fillMode = value
    }
    
    override func getVerticalAlignment() -> ACSVerticalAlignment {
        return verticalAlignment
    }
    
    override func setVerticalAlignment(_ value: ACSVerticalAlignment) {
        verticalAlignment = value
    }
    
    override func setHorizontalAlignment(_ value: ACSHorizontalAlignment) {
        horizontalAlignment = value
    }
    
    override func getHorizontalAlignment() -> ACSHorizontalAlignment {
        return horizontalAlignment
    }
   
}

extension FakeBackgroundImage {
    static func make(url: String = "", fillMode: ACSImageFillMode = .cover, verticalAlignment: ACSVerticalAlignment = .top, horizontalAlignment: ACSHorizontalAlignment = .center) -> FakeBackgroundImage {
        let fakeBackgroundImage = FakeBackgroundImage()
        fakeBackgroundImage.url = url
        fakeBackgroundImage.fillMode = fillMode
        fakeBackgroundImage.verticalAlignment = verticalAlignment
        fakeBackgroundImage.horizontalAlignment = horizontalAlignment
        return fakeBackgroundImage
    }
}

