@testable import AdaptiveCards
import AdaptiveCards_bridge
import XCTest

class ActionSubmitRendererTests: XCTestCase {
    private var hostConfig: FakeHostConfig!
    private var actionSubmit: FakeSubmitAction!
    private var acrView: ACRView!
    private var delegate: FakeACRViewDelegate!
    private var actionSubmitRenderer: ActionSubmitRenderer!
    
    override func setUpWithError() throws {
        try super.setUpWithError()
        hostConfig = .make()
        actionSubmit = .make()
        acrView = ACRView(style: .default, hostConfig: hostConfig)
        delegate = FakeACRViewDelegate()
        actionSubmitRenderer = ActionSubmitRenderer()
    }
    
    func testRendersChevronButton() {
        let button = renderButton()
        XCTAssertFalse(button.showsChevron)
    }
    
    func testSetsTitle() {
        actionSubmit = .make(title: "Hello world!")
        let button = renderButton()
        XCTAssertEqual(button.title, "Hello world!")
    }
    
    func testSetsTargets() {
        actionSubmit = .make(inputText: FakeInputText.make())
        let button = renderButton()
        guard let target = acrView.targets.first as? ActionSubmitTarget else { return XCTFail() }
        XCTAssertEqual(acrView.targets.count, 1)
        XCTAssertEqual(button.target as! ActionSubmitTarget, target)
    }
    
    func testBasicInputHandler() {
        acrView.delegate = delegate
        let testinputHandler = FakeInputHandlingView()
        testinputHandler.value = "Value"
        testinputHandler.key = "Key"
        testinputHandler.isValid = true
        acrView.addInputHandler(testinputHandler)
        acrView.handleSubmitAction(actionView: NSButton(), dataJson: nil)
        guard let myDelegate = acrView.delegate as? FakeACRViewDelegate else { fatalError() }
        XCTAssertEqual("Value", myDelegate.dict["Key"] as? String)
    }
    
    func testInputHandlerWhenisValidFalse() {
        acrView.delegate = delegate
        let testinputHandler = FakeInputHandlingView()
        testinputHandler.value = "Value"
        testinputHandler.key = "Key"
        testinputHandler.isValid = false
        acrView.addInputHandler(testinputHandler)
        acrView.handleSubmitAction(actionView: NSButton(), dataJson: nil)
        guard let myDelegate = acrView.delegate as? FakeACRViewDelegate else { fatalError() }
        XCTAssertEqual(0, myDelegate.dict.count)
    }
    
    func testInputHandlerWithMultipleValues() {
        acrView.delegate = delegate
        let testinputHandler1 = FakeInputHandlingView()
        testinputHandler1.value = "Value1"
        testinputHandler1.key = "Key1"
        testinputHandler1.isValid = true
        acrView.addInputHandler(testinputHandler1)
        let testinputHandler2 = FakeInputHandlingView()
        testinputHandler2.value = "Value2"
        testinputHandler2.key = "Key2"
        testinputHandler2.isValid = true
        acrView.addInputHandler(testinputHandler2)
        acrView.handleSubmitAction(actionView: NSButton(), dataJson: nil)
        guard let myDelegate = acrView.delegate as? FakeACRViewDelegate else { fatalError() }
        XCTAssertEqual(2, myDelegate.dict.count)
        XCTAssertEqual("Value1", myDelegate.dict["Key1"] as? String)
        XCTAssertEqual("Value2", myDelegate.dict["Key2"] as? String)
    }
    
    func testInputHandlerWithDataJson() {
        acrView.delegate = delegate
        let testinputHandler = FakeInputHandlingView()
        testinputHandler.value = "Value"
        testinputHandler.key = "Key"
        testinputHandler.isValid = true
        acrView.addInputHandler(testinputHandler)
        acrView.handleSubmitAction(actionView: NSButton(), dataJson: "{\"id\":\"1234567890\"}\n")
        guard let myDelegate = acrView.delegate as? FakeACRViewDelegate else { fatalError() }
        XCTAssertEqual(2, myDelegate.dict.count)
        XCTAssertEqual("Value", myDelegate.dict["Key"] as? String)
        XCTAssertEqual("1234567890", myDelegate.dict["id"] as? String)
    }
    
    
    private func renderButton() -> ACRButton {
        let view = actionSubmitRenderer.render(action: actionSubmit, with: hostConfig, style: .default, rootView: acrView, parentView: NSView(), inputs: [])
        
        XCTAssertTrue(view is ACRButton)
        guard let button = view as? ACRButton else { fatalError() }
        return button
    }
}

class FakeInputHandlingView: NSView, InputHandlingViewProtocol {
    var value: String = ""
    
    var key: String = ""
    
    var isValid: Bool = false
    
}

private class FakeACRViewDelegate: ACRViewDelegate {
    var dict: [String: Any] = [:]
    
    func acrView(_ view: ACRView, didSubmitUserResponses dict: [String : Any], actionView: NSView) {
        self.dict = dict
    }
    
    func acrView(_ view: ACRView, didSelectOpenURL url: String, actionView: NSView) { }
}
