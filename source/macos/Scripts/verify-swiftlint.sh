if which swiftlint >/dev/null; then
    swiftlint --strict
else
    echo "error: SwiftLint not installed, download from https://github.com/realm/SwiftLint"
fi