@testable import AdaptiveCards
import AdaptiveCards_bridge
import XCTest

class RichTextBlockRendererTests: XCTestCase {
    private var hostConfig: FakeHostConfig!
    private var richTextBlock: FakeRichTextBlock!
    private var richTextBlockRenderer: RichTextBlockRenderer!
    private var resourceResolver: FakeResourceResolver!
    private let sampleText = "Hello world!"
    private let renderConfig: RenderConfig = .default
    
    
    override func setUpWithError() throws {
        try super.setUpWithError()
        hostConfig = .make()
        richTextBlock = FakeRichTextBlock.make()
        richTextBlockRenderer = RichTextBlockRenderer()
        resourceResolver = FakeResourceResolver()
    }
    
    func testRendererSetsText() {
        let textRun = FakeTextRun.make(text: sampleText)
        
        richTextBlock = .make(textRun: textRun)
        
        let textView = renderTextView()
        XCTAssertEqual(textView.string, sampleText)
        XCTAssertTrue(resourceResolver.textResolverCalled)
    }
    
    func testRendererRightAlignsText() {
        let textRun = FakeTextRun.make(text: sampleText)
        
        richTextBlock = .make(textRun: textRun, horizontalAlignment: ACSHorizontalAlignment.right)
        
        let textView = renderTextView()
        XCTAssertEqual(textView.alignment, NSTextAlignment.right)
    }
    
    func testRendererCenterAlignsText() {
        let textRun = FakeTextRun.make(text: sampleText)
        
        richTextBlock = .make(textRun: textRun, horizontalAlignment: ACSHorizontalAlignment.center)
        
        let textView = renderTextView()
        XCTAssertEqual(textView.alignment, NSTextAlignment.center)
    }
    
    func testRendererDefaultTextColorAlpha() {
        let textRun = FakeTextRun.make(text: sampleText, textColor: ACSForegroundColor.default)

        richTextBlock = .make(textRun: textRun)

        let textView = renderTextView()
        XCTAssertEqual(textView.textColor, NSColor.init(red: 0, green: 0, blue: 0, alpha: 1))
    }
    
    func testRendererSetsUnderline() {
        let textRun = FakeTextRun.make(text: sampleText, underline: true)

        richTextBlock = .make(textRun: textRun)
        let textView = renderTextView()
        
        if renderConfig.supportsSchemeV1_3 {
            XCTAssert(isStringAttributePresent(attrString: textView.attributedString(), attr: .underlineStyle))
        }
    }
    
    func testRendererSetsStrikethrough() {
        let textRun = FakeTextRun.make(text: sampleText, strikethrough: true)

        richTextBlock = .make(textRun: textRun)
        let textView = renderTextView()
        
        XCTAssert(isStringAttributePresent(attrString: textView.attributedString(), attr: .strikethroughStyle))
    }
    
    func testSelectActionTargetIsSet() {
        var textRun: FakeTextRun!
        var textView: ACRTextView!
        
        textRun = .make(text: sampleText, selectAction: FakeSubmitAction.make())
        richTextBlock = .make(textRun: textRun)
        textView = renderTextView()
        
        XCTAssertNotNil(attributeValue(for: .selectAction, in: textView.attributedString()))
        XCTAssertTrue(attributeValue(for: .selectAction, in: textView.attributedString()) is ActionSubmitTarget)
        XCTAssertTrue(textView.target is ActionSubmitTarget)
        
        textRun = .make(text: sampleText, selectAction: FakeOpenURLAction.make())
        richTextBlock = .make(textRun: textRun)
        textView = renderTextView()
        
        XCTAssertNotNil(attributeValue(for: .selectAction, in: textView.attributedString()))
        XCTAssertTrue(attributeValue(for: .selectAction, in: textView.attributedString()) is ActionOpenURLTarget)
        XCTAssertTrue(textView.target is ActionOpenURLTarget)
        
        textRun = .make(text: sampleText, selectAction: FakeToggleVisibilityAction.make())
        richTextBlock = .make(textRun: textRun)
        textView = renderTextView()
        
        XCTAssertNotNil(attributeValue(for: .selectAction, in: textView.attributedString()))
        XCTAssertTrue(attributeValue(for: .selectAction, in: textView.attributedString()) is ActionToggleVisibilityTarget)
        XCTAssertTrue(textView.target is ActionToggleVisibilityTarget)
        
        // ShowCard Action is not available as a SelectAction
        textRun = .make(text: sampleText, selectAction: FakeShowCardAction.make())
        richTextBlock = .make(textRun: textRun)
        textView = renderTextView()
        
        XCTAssertNil(attributeValue(for: .selectAction, in: textView.attributedString()))
        XCTAssertNil(textView.target)
    }
    
    private func isStringAttributePresent(attrString: NSAttributedString, attr: NSAttributedString.Key) -> Bool {
        return attributeValue(for: attr, in: attrString) != nil
    }
    
    private func attributeValue(for key: NSAttributedString.Key, in attrString: NSAttributedString) -> Any? {
        let range = NSRange(location: 0, length: attrString.length)
        return attrString.attribute(key, at: 0, longestEffectiveRange: nil, in: range)
    }
    

    private func renderTextView() -> ACRTextView {
        let rootView = FakeRootView()
        rootView.resolverDelegate = resourceResolver
        let view = richTextBlockRenderer.render(element: richTextBlock, with: hostConfig, style: .default, rootView: rootView, parentView: NSView(), inputs: [], config: .default)
        
        XCTAssertTrue(view is ACRTextView)
        guard let textView = view as? ACRTextView else { fatalError() }
        return textView
    }
}
