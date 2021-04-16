@testable import AdaptiveCards
import AdaptiveCards_bridge
import XCTest

class ACRNumericTestFieldTests: XCTestCase {
    private var numericView: ACRNumericTextField!
    override func setUp() {
        super.setUp()
        numericView = ACRNumericTextField()
        numericView.inputString = "20"
    }
    
    func testInvalidCharacterInputEnd() {
        numericView.textField.stringValue = "20a"
        let object = Notification(name: NSNotification.Name.init("NSControlTextDidChangeNotification"), object: numericView.textField)
        numericView.controlTextDidChange(object)
        XCTAssertEqual(numericView.inputString, "20.0")
    }
    
    func testInvalidCharacterInputMiddle() {
        numericView.textField.stringValue = "2a0"
        let object = Notification(name: NSNotification.Name.init("NSControlTextDidChangeNotification"), object: numericView.textField)
        numericView.controlTextDidChange(object)
        XCTAssertEqual(numericView.inputString, "20.0")
    }
    
    func testInvalidCharacterInputFirst() {
        numericView.textField.stringValue = "a20"
        let object = Notification(name: NSNotification.Name.init("NSControlTextDidChangeNotification"), object: numericView.textField)
        numericView.controlTextDidChange(object)
        XCTAssertEqual(numericView.inputString, "20.0")
    }
    
    func testValidCharacterInput() {
        numericView.textField.stringValue = "250"
        let object = Notification(name: NSNotification.Name.init("NSControlTextDidChangeNotification"), object: numericView.textField)
        numericView.controlTextDidChange(object)
        XCTAssertEqual(numericView.inputString, "250.0")
    }
    
    func testDecimalPointEntered() {
        numericView.textField.stringValue = "2.50"
        let object = Notification(name: NSNotification.Name.init("NSControlTextDidChangeNotification"), object: numericView.textField)
        numericView.controlTextDidChange(object)
        XCTAssertEqual(numericView.inputString, "2.5")
    }
}
