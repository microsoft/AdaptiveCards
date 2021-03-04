@testable import AdaptiveCards
import AdaptiveCards_bridge
import XCTest

class ImageRendererTests: XCTestCase {
    private var hostConfig: FakeHostConfig!
    private var fakeImageView: FakeImageView!
    private var imageRenderer: ImageRenderer!
    let sampleURL = "https://messagecardplayground.azurewebsites.net/assets/TxP_Flight.png"
    
    override func setUpWithError() throws {
        try super.setUpWithError()
        hostConfig = .make()
        fakeImageView = .make()
        imageRenderer = ImageRenderer()
    }
    
    // This needs to be refactored when Resource Resolver is implemented
    func testRendererSetsImage() {
        fakeImageView = .make(url: sampleURL)
        
        let contentView = renderImageView()
        XCTAssertTrue(contentView.imageView == nil)
    }
    
    func testRendererSetsBackgroundColor() {
        let color = "#FFAACC"
        fakeImageView = .make(backgroundColor: color)
        
        let contentView = renderImageView()
        let imageView = contentView.imageView
        let colorHex = ColorUtils.color(from: color) ?? NSColor.black
        XCTAssertEqual(imageView?.layer?.backgroundColor, colorHex.cgColor)
    }
    
    func testRendererSetsImageStyle() {
        fakeImageView = .make(imageStyle: .person)
        
        let contentView = renderImageView()
        let imageView = contentView.imageView
        let radius = imageView?.image?.size.width ?? 0
        XCTAssertEqual(imageView?.layer?.cornerRadius, radius/2)
    }
    
    func testRendererSetsPixelWidth() {
        fakeImageView = .make(imageSize: .small)
        
        let sz = CGSize.init(width: hostConfig.imageSizes?.smallSize.intValue ?? 0, height: hostConfig.imageSizes?.smallSize.intValue ?? 0)
        
        let contentView = renderImageView()
        let imageView = contentView.imageView
        XCTAssertEqual(imageView?.image?.size.width, sz.width)
    }
    
    func testRendererSetsPixelHeight() {
        fakeImageView = .make(imageSize: .medium)
        
        let sz = CGSize.init(width: hostConfig.imageSizes?.mediumSize.intValue ?? 0, height: hostConfig.imageSizes?.mediumSize.intValue ?? 0)
        
        let contentView = renderImageView()
        let imageView = contentView.imageView
        XCTAssertEqual(imageView?.image?.size.height, sz.height)
    }

    private func renderImageView() -> ACRContentHoldingView {
        let view = imageRenderer.render(element: fakeImageView, with: hostConfig, style: .default, rootView: NSView(), parentView: NSView(), inputs: [])
        
        XCTAssertTrue(view is ACRContentHoldingView)
        guard let contentView = view as? ACRContentHoldingView else { fatalError() }
        return contentView
    }
}
