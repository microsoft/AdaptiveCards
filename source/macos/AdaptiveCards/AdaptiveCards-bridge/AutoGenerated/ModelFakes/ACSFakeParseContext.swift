// DO NOT EDIT - Auto generated
// Generated with swift_fake_viewmodel.j2

open class ACSFakeParseContext: ACSParseContext {

    open override func pushElement(idJsonProperty: String, internalId: ACSInternalId, isFallback: Bool) {
    }

    open override func popElement() {
    }

    open override func getCanFallbackToAncestor() -> Bool {
        return true
    }

    open override func setCanFallbackToAncestor(value: Bool) {
    }

    open override func setLanguage(value: String) {
    }

    open override func getLanguage() -> String? {
        return nil
    }

    open override func getParentalContainerStyle() -> ACSContainerStyle {
        return CHContainerStyle(rawValue: 0)!
    }

    open override func setParentalContainerStyle(style: ACSContainerStyle) {
    }

    open override func paddingParentInternalId() -> ACSInternalId? {
        return nil
    }

    open override func saveContextForCollectionTypeElement(current: ACSCollectionTypeElement) {
    }

    open override func restoreContextForCollectionTypeElement(current: ACSCollectionTypeElement) {
    }

    open override func getBleedDirection() -> ACSContainerBleedDirection {
        return CHContainerBleedDirection(rawValue: 0)!
    }

    open override func pushBleedDirection(direction: ACSContainerBleedDirection) {
    }

    open override func popBleedDirection() {
    }

    open override func getNearestFallbackId(skipId: ACSInternalId) -> ACSInternalId? {
        return nil
    }

}
