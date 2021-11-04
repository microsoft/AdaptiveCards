//
//  ACRTextView
//  ACRTextView.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRTextView.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACRInputLabelView.h"
#import "TextInput.h"
#import "UtiliOS.h"

@implementation ACRTextView {
    BOOL _isShowingPlaceholder;
}

- (instancetype)initWithFrame:(CGRect)frame element:(ACOBaseCardElement *)element
{
    self = [super initWithFrame:frame];
    if (self) {
        self.font = [UIFont preferredFontForTextStyle:UIFontTextStyleBody];
        if (@available(iOS 13.0, *)) {
            _placeholderColor = [UIColor placeholderTextColor];
        } else {
            // Fallback on earlier versions
            _placeholderColor = [UIColor lightGrayColor];
        }
        [self configWithSharedModel:element];
    }
    return self;
}

- (void)configWithSharedModel:(ACOBaseCardElement *)element
{
    std::shared_ptr<BaseCardElement> elem = [element element];
    std::shared_ptr<TextInput> inputBlck = std::dynamic_pointer_cast<TextInput>(elem);
    _maxLength = inputBlck->GetMaxLength();
    _placeholderText = [[NSString alloc] initWithCString:inputBlck->GetPlaceholder().c_str() encoding:NSUTF8StringEncoding];
    if (inputBlck->GetValue().size()) {
        self.text = [[NSString alloc] initWithCString:inputBlck->GetValue().c_str() encoding:NSUTF8StringEncoding];
        _isShowingPlaceholder = NO;
    } else if ([_placeholderText length]) {
        self.text = _placeholderText;
        self.textColor = _placeholderColor;
        _isShowingPlaceholder = YES;
    }

    self.isRequired = inputBlck->GetIsRequired();
    self.delegate = self;
    self.id = [NSString stringWithCString:inputBlck->GetId().c_str()
                                 encoding:NSUTF8StringEncoding];
    [self registerForKeyboardNotifications];

    self.frame = [self computeBoundingRect];

    CGRect frame = CGRectMake(0, 0, self.frame.size.width, 30);
    UIToolbar *toolBar = [[UIToolbar alloc] initWithFrame:frame];
    UIBarButtonItem *flexSpace = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace target:nil action:nil];
    UIBarButtonItem *doneButton = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone target:self action:@selector(dismissKeyboard)];
    [toolBar setItems:@[ doneButton, flexSpace ] animated:NO];
    [toolBar sizeToFit];
    self.inputAccessoryView = toolBar;
}

- (BOOL)textViewShouldEndEditing:(UITextView *)textView
{
    [textView resignFirstResponder];
    return YES;
}

- (void)registerForKeyboardNotifications
{
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(keyboardWasShown:)
                                                 name:UIKeyboardDidShowNotification
                                               object:nil];

    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(keyboardWillBeHidden:)
                                                 name:UIKeyboardWillHideNotification
                                               object:nil];
}
// Called when the UIKeyboardDidShowNotification is sent.
- (void)keyboardWasShown:(NSNotification *)aNotification
{
    self.scrollEnabled = YES;
}

// Called when the UIKeyboardWillHideNotification is sent
- (void)keyboardWillBeHidden:(NSNotification *)aNotification
{
    self.scrollEnabled = NO;
}

- (BOOL)validate:(NSError **)error
{
    return [ACRInputLabelView commonTextUIValidate:self.isRequired hasText:self.hasText predicate:self.regexPredicate text:self.text error:error];
}

- (void)getInput:(NSMutableDictionary *)dictionary
{
    dictionary[self.id] = _isShowingPlaceholder ? @"" : self.text;
}

- (void)setFocus:(BOOL)shouldBecomeFirstResponder view:(UIView * _Nullable)view {
    [ACRInputLabelView commonSetFocus:shouldBecomeFirstResponder view:view];
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    [self resignFirstResponder];
    return YES;
}

- (void)dismissKeyboard
{
    [self resignFirstResponder];
}

- (CGSize)intrinsicContentSize
{
    return [self computeBoundingRect].size;
}

- (BOOL)textView:(UITextView *)textView shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text;
{
    if (!_maxLength) {
        return YES;
    }
    
    if (range.length + range.location > textView.text.length) {
        return NO;
    }
    
    NSUInteger newLength = [textView.text length] + [text length] - range.length;
    return newLength <= _maxLength;
}

- (void)textViewDidBeginEditing:(UITextView *)textView
{
    if (_isShowingPlaceholder) {
        textView.text = @"";
        if (@available(iOS 13.0, *)) {
            textView.textColor = [UIColor labelColor];
        } else {
            // Fallback on earlier versions
            textView.textColor = [UIColor blackColor];
        }
        _isShowingPlaceholder = NO;
    }
    [textView becomeFirstResponder];
}
- (void)textViewDidEndEditing:(UITextView *)textView
{
    if (![textView.text length]) {
        textView.text = _placeholderText;
        textView.textColor = _placeholderColor;
        _isShowingPlaceholder = YES;
    }
    [textView resignFirstResponder];
}

- (CGRect)computeBoundingRect
{
    BOOL bRemove = NO;

    if (![self.text length]) {
        self.text = @"placeholder text";
        bRemove = YES;
    }
    CGRect boundingrect = [self.layoutManager lineFragmentRectForGlyphAtIndex:0 effectiveRange:nil];
    boundingrect.size.height *= 4;
    self.frame = boundingrect;
    
    if (bRemove) {
        self.text = @"";
    }
    return boundingrect;
}

- (void)setPlaceholderColor:(UIColor *)placeholderColor
{
    _placeholderColor = placeholderColor;
    if (_isShowingPlaceholder) {
        self.textColor = placeholderColor;
    }
}

@synthesize hasValidationProperties;

@synthesize id;

@synthesize isRequired;

@synthesize hasVisibilityChanged;

@end
