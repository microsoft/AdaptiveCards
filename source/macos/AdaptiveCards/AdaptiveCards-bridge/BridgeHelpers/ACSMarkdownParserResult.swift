import Foundation

@objcMembers
open class ACSMarkdownParserResult: NSObject {
    public let parsedString: String
    public let htmlData: Data?
    
    public var isHTML: Bool {
        return htmlData != nil
    }

    public init(parsedString: String, htmlData: Data?) {
        self.parsedString = parsedString
        self.htmlData = htmlData
    }
}
