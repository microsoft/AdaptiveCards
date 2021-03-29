@testable import AdaptiveCards
import AdaptiveCards_bridge
import XCTest

class TextBlockRendererTests: XCTestCase {
    private var hostConfig: FakeHostConfig!
    private var textBlock: FakeTextBlock!
    private var textBlockRenderer: TextBlockRenderer!
    
    override func setUpWithError() throws {
        try super.setUpWithError()
        hostConfig = .make()
        textBlock = .make()
        textBlockRenderer = TextBlockRenderer()
    }
    
    func testRendererSetsText() {
        let text = "Hello world!"
        textBlock = .make(text: text)
        
        let textView = renderTextView()
        XCTAssertEqual(textView.string, text)
    }
    
    func testRendererSetsMarkdownText() {
        let markdownText = "**Hello** _world!_"
        textBlock = .make(text: markdownText)
        
        let textView = renderTextView()
        XCTAssertEqual(textView.string, "Hello world!")
    }
    
    func testRendererSetsWrap() {
        textBlock = .make(wrap: true)
        
        let textView = renderTextView()
        XCTAssertEqual(textView.textContainer?.maximumNumberOfLines ?? -1, 0)
        
        textBlock = .make(wrap: false)
        let textView2 = renderTextView()
        XCTAssertEqual(textView2.textContainer?.maximumNumberOfLines ?? -1, 1)
    }
    
    func testRendererSetsMaxLines() {
        textBlock = .make(wrap: true, maxLines: 2)
        let textView = renderTextView()
        XCTAssertEqual(textView.textContainer?.maximumNumberOfLines ?? -1, 2)
    }
    
    func testRendererSetsMaxLines_wrapFalse() {
        textBlock = .make(wrap: false, maxLines: 2)
        let textView = renderTextView()
        XCTAssertEqual(textView.textContainer?.maximumNumberOfLines ?? -1, 1)
    }
    
    func testRendererSetsHorizontalAlignment() {
        textBlock = .make(text: "Hello world!", horizontalAlignment: .right)
        var textView = renderTextView()
        var attributedString = textView.attributedString()
        guard let paragraphStyle = attributedString.attribute(.paragraphStyle, at: 0, effectiveRange: nil) as? NSParagraphStyle else { return XCTFail() }
        XCTAssertEqual(paragraphStyle.alignment, .right)
        
        textBlock = .make(text: "Hello world!", horizontalAlignment: .center)
        textView = renderTextView()
        attributedString = textView.attributedString()
        guard let paragraphStyle2 = attributedString.attribute(.paragraphStyle, at: 0, effectiveRange: nil) as? NSParagraphStyle else { return XCTFail() }
        XCTAssertEqual(paragraphStyle2.alignment, .center)
    }
    
    func testRendererSetsRequiredProperties() {
        let textView = renderTextView()
        
        XCTAssertFalse(textView.isEditable) // Should be disbled
        XCTAssertEqual(textView.textContainerInset, .zero)
        XCTAssertTrue(textView.textContainer?.widthTracksTextView ?? false) // Needed for wrapping text
        XCTAssertEqual(textView.backgroundColor, .clear)
    }
    
    private func renderTextView() -> ACRTextView {
        let view = textBlockRenderer.render(element: textBlock, with: hostConfig, style: .default, rootView: FakeRootView(), parentView: NSView(), inputs: [])
        
        XCTAssertTrue(view is ACRTextView)
        guard let textView = view as? ACRTextView else { fatalError() }
        return textView
    }
}
