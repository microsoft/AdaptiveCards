@testable import AdaptiveCards
import AdaptiveCards_bridge
import XCTest

class ImageRendererTests: XCTestCase {
    private var hostConfig: FakeHostConfig!
    private var image: FakeImage!
    private var imageRenderer: ImageRenderer!
    private var fakeACRView: ACRView!
    let sampleURL = "https://messagecardplayground.azurewebsites.net/assets/TxP_Flight.png"
    
    override func setUpWithError() throws {
        try super.setUpWithError()
        hostConfig = .make(imageSizes: ACSImageSizesConfig(smallSize: 30, mediumSize: 60, largeSize: 120))
        image = .make()
        imageRenderer = ImageRenderer()
        fakeACRView = ACRView(style: .default, hostConfig: hostConfig, renderConfig: .default)
    }
    
    func testRendererSetsImage() {
        image = .make(url: sampleURL)
        
        let contentView = renderImageView()
        XCTAssertTrue(contentView.subviews.first is NSImageView)
    }
    
    func testRendererSetsBackgroundColor() {
        let color = "#FFAACC"
        image = .make(url: sampleURL, backgroundColor: color)
        
        let contentView = renderImageView()
        guard let imageView = contentView.subviews.first as? NSImageView else { return XCTFail() }
        let colorHex = ColorUtils.color(from: color) ?? NSColor.black
        XCTAssertEqual(imageView.layer?.backgroundColor, colorHex.cgColor)
    }
    
    func testRendererSetsImageStyle() {
        image = .make(imageStyle: .person)
        
        let contentView = renderImageView()
        contentView.layout()
        guard let imageView = contentView.subviews.first as? NSImageView else { return XCTFail() }
        XCTAssertNotNil(imageView.layer?.mask)
        XCTAssertEqual(imageView.layer?.mask?.bounds, imageView.bounds)
    }
    
    func testRendererSetsSmallSize() {
        image = .make(imageSize: .small)
        
        let sz = CGSize(width: hostConfig.imageSizes?.smallSize.intValue ?? 0, height: hostConfig.imageSizes?.smallSize.intValue ?? 0)
        
        let contentView = renderImageView()
        XCTAssertEqual(contentView.imageProperties?.contentSize.width, sz.width)
    }
    
    func testRendererSetsMediumSize() {
        image = .make(imageSize: .medium)
        
        let sz = CGSize(width: hostConfig.imageSizes?.mediumSize.intValue ?? 0, height: hostConfig.imageSizes?.mediumSize.intValue ?? 0)
        
        let contentView = renderImageView()
        XCTAssertEqual(contentView.imageProperties?.contentSize.width, sz.width)
    }
    
    func testRendererSetsLargeMediumSize() {
        image = .make(imageSize: .large)
        
        let sz = CGSize(width: hostConfig.imageSizes?.largeSize.intValue ?? 0, height: hostConfig.imageSizes?.largeSize.intValue ?? 0)
        
        let contentView = renderImageView()
        XCTAssertEqual(contentView.imageProperties?.contentSize.width, sz.width)
    }
    
    func testRendererSetsPixelWidth() {
        let width : NSNumber = 50
        image = .make(pixelWidth: width)
        
        let contentView = renderImageView()
        XCTAssertEqual(contentView.imageProperties?.contentSize.width, CGFloat(truncating: width))
    }
    
    func testRendererSetsPixelHeight() {
        let height : NSNumber = 50
        image = .make(pixelHeight: height)
        
        let contentView = renderImageView()
        XCTAssertEqual(contentView.imageProperties?.contentSize.height, CGFloat(truncating: height))
    }
    
    func testRendererSetsExplicitWidthWhenImageSizeIsAlsoGiven() {
        let width : NSNumber = 50
        image = .make(imageSize: .large, pixelWidth: width)
        
        let contentView = renderImageView()
        XCTAssertEqual(contentView.imageProperties?.contentSize.width, CGFloat(truncating: width))
    }
    
    func testRendererSetsExplicitHeightWhenImageSizeIsAlsoGiven() {
        let height : NSNumber = 50
        image = .make(imageSize: .large, pixelHeight: height)
        
        let contentView = renderImageView()
        XCTAssertEqual(contentView.imageProperties?.contentSize.height, CGFloat(truncating: height))
    }
    
    func testRendererSetsExplicitDimensionWhenImageSizeIsAlsoGiven() {
        let width : NSNumber = 50
        let height : NSNumber = 50
        image = .make(imageSize: .large, pixelWidth: width, pixelHeight: height)
        
        let contentView = renderImageView()
        XCTAssertEqual(contentView.imageProperties?.contentSize.width, CGFloat(truncating: width))
        XCTAssertEqual(contentView.imageProperties?.contentSize.height, CGFloat(truncating: height))
    }
    
    func testRendererSetsExplicitDimensions() {
        let height : NSNumber = 100
        image = .make(pixelHeight: height)
        
        let contentView = renderImageView()
        XCTAssertEqual(contentView.imageProperties?.hasExplicitDimensions, true)
    }
    
    func testSelectActionTargetIsSet() {
        var imageView: ACRImageWrappingView!
        
        image = .make(selectAction: FakeSubmitAction.make())
        imageView = renderImageView()
        
        XCTAssertNotNil(imageView.target)
        XCTAssertTrue(imageView.target is ActionSubmitTarget)
        
        image = .make(selectAction: FakeOpenURLAction.make())
        imageView = renderImageView()
        
        XCTAssertNotNil(imageView.target)
        XCTAssertTrue(imageView.target is ActionOpenURLTarget)
        
        image = .make(selectAction: FakeToggleVisibilityAction.make())
        imageView = renderImageView()
        
        XCTAssertNotNil(imageView.target)
        XCTAssertTrue(imageView.target is ActionToggleVisibilityTarget)
        
        // ShowCard Action is not available as a SelectAction
        image = .make(selectAction: FakeShowCardAction.make())
        imageView = renderImageView()
    
        XCTAssertNil(imageView.target)
    }
    
    private func renderImageView() -> ACRImageWrappingView {
        let view = imageRenderer.render(element: image, with: hostConfig, style: .default, rootView: fakeACRView, parentView: fakeACRView, inputs: [], config: .default)
        
        XCTAssertTrue(view is ACRImageWrappingView)
        guard let contentView = view as? ACRImageWrappingView else { fatalError() }
        return contentView
    }
}
