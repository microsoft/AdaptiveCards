@testable import AdaptiveCards
import AdaptiveCards_bridge
import XCTest

class ImageRendererTests: XCTestCase {
    private var hostConfig: FakeHostConfig!
    private var fakeImageView: FakeImage!
    private var imageRenderer: ImageRenderer!
    private var fakeACRView: ACRView!
    let sampleURL = "https://messagecardplayground.azurewebsites.net/assets/TxP_Flight.png"
    
    override func setUpWithError() throws {
        try super.setUpWithError()
        hostConfig = .make(imageSizes: ACSImageSizesConfig(smallSize: 30, mediumSize: 60, largeSize: 120))
        fakeImageView = .make()
        imageRenderer = ImageRenderer()
        fakeACRView = ACRView(style: .default, hostConfig: hostConfig)
    }
    
    func testRendererSetsImage() {
        fakeImageView = .make(url: sampleURL)
        
        let contentView = renderImageView()
        XCTAssertTrue(contentView.imageView != nil)
    }
    
    func testRendererSetsBackgroundColor() {
        let color = "#FFAACC"
        fakeImageView = .make(url: sampleURL, backgroundColor: color)
        
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
    
    func testRendererSetsSmallSize() {
        fakeImageView = .make(imageSize: .small)
        
        let sz = CGSize(width: hostConfig.imageSizes?.smallSize.intValue ?? 0, height: hostConfig.imageSizes?.smallSize.intValue ?? 0)
        
        let contentView = renderImageView()
        XCTAssertEqual(contentView.imageProperties?.contentSize.width, sz.width)
    }
    
    func testRendererSetsMediumSize() {
        fakeImageView = .make(imageSize: .medium)
        
        let sz = CGSize(width: hostConfig.imageSizes?.mediumSize.intValue ?? 0, height: hostConfig.imageSizes?.mediumSize.intValue ?? 0)
        
        let contentView = renderImageView()
        XCTAssertEqual(contentView.imageProperties?.contentSize.width, sz.width)
    }
    
    func testRendererSetsLargeMediumSize() {
        fakeImageView = .make(imageSize: .large)
        
        let sz = CGSize(width: hostConfig.imageSizes?.largeSize.intValue ?? 0, height: hostConfig.imageSizes?.largeSize.intValue ?? 0)
        
        let contentView = renderImageView()
        XCTAssertEqual(contentView.imageProperties?.contentSize.width, sz.width)
    }
    
    func testRendererSetsPixelWidth() {
        let width : NSNumber = 50
        fakeImageView = .make(pixelWidth: width)
        
        let contentView = renderImageView()
        XCTAssertEqual(contentView.imageProperties?.contentSize.width, CGFloat(truncating: width))
    }
    
    func testRendererSetsExplicitDimensions() {
        let height : NSNumber = 100
        fakeImageView = .make(pixelHeight: height)
        
        let contentView = renderImageView()
        XCTAssertEqual(contentView.imageProperties?.hasExplicitDimensions, true)
    }

    private func renderImageView() -> ACRContentHoldingView {
        let view = imageRenderer.render(element: fakeImageView, with: hostConfig, style: .default, rootView: fakeACRView, parentView: fakeACRView, inputs: [])
        
        XCTAssertTrue(view is ACRContentHoldingView)
        guard let contentView = view as? ACRContentHoldingView else { fatalError() }
        return contentView
    }
}
