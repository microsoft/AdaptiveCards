// DO NOT EDIT - Auto generated
// Generated with swift_fake_viewmodel.j2

open class ACSFakeMarkDownEmphasisHtmlGenerator: ACSMarkDownEmphasisHtmlGenerator {

    open override func isRightEmphasis() -> Bool {
        return true
    }

    open override func isLeftEmphasis() -> Bool {
        return true
    }

    open override func isLeftAndRightEmphasis() -> Bool {
        return true
    }

    open override func pushItalicTag() {
    }

    open override func pushBoldTag() {
    }

    open override func isMatch(token: ACSMarkDownEmphasisHtmlGenerator) -> Bool {
        return true
    }

    open override func isSameType(token: ACSMarkDownEmphasisHtmlGenerator) -> Bool {
        return true
    }

    open override func isDone() -> Bool {
        return true
    }

    open override func getNumberOfUnusedDelimiters() -> NSNumber? {
        return 0
    }

    open override func generateTags(token: ACSMarkDownEmphasisHtmlGenerator) -> Bool {
        return true
    }

    open override func reverseDirectionType() {
    }

    open override func adjustEmphasisCounts(leftOver: NSNumber, rightToken: ACSMarkDownEmphasisHtmlGenerator) -> NSNumber? {
        return 0
    }

}
