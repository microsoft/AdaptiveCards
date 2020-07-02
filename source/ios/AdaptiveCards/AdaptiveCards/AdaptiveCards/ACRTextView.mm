//
//  ACRTextView
//  ACRTextView.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRTextView.h"
#import "ACOBaseCardElementPrivate.h"
#import "TextInput.h"

@implementation ACRTextView

- (instancetype)initWithFrame:(CGRect)frame element:(ACOBaseCardElement *)element
{
    self = [super initWithFrame:frame];
    if (self) {
        self.font = [UIFont preferredFontForTextStyle:UIFontTextStyleBody];
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
    } else if ([_placeholderText length]) {
        self.text = _placeholderText;
        self.textColor = [UIColor lightGrayColor];
    }

    self.isRequired = inputBlck->GetIsRequired();
    self.delegate = self;
    self.id = [NSString stringWithCString:inputBlck->GetId().c_str()
                                 encoding:NSUTF8StringEncoding];
    [self registerForKeyboardNotifications];

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
    if (self.isRequired && !self.hasText) {
        if (error) {
            *error = [NSError errorWithDomain:ACRInputErrorDomain code:ACRInputErrorValueMissing userInfo:nil];
        }
        return NO;
    } else {
        return YES;
    }
}

- (void)getInput:(NSMutableDictionary *)dictionary
{
    dictionary[self.id] = ([_placeholderText isEqualToString:self.text]) ? @"" : self.text;
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
    return self.frame.size;
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
    if (_placeholderText && [textView.text isEqualToString:_placeholderText]) {
        textView.text = @"";
        if (@available(iOS 13.0, *)) {
            textView.textColor = UIColor.labelColor;
        } else {
            // Fallback on earlier versions
            textView.textColor = [UIColor blackColor];
        }
    }
    [textView becomeFirstResponder];
}
- (void)textViewDidEndEditing:(UITextView *)textView
{
    if (![textView.text length]) {
        textView.text = _placeholderText;
        if (@available(iOS 13.0, *)) {
            textView.textColor = UIColor.placeholderTextColor;
        } else {
            // Fallback on earlier versions
            textView.textColor = [UIColor lightGrayColor];
        }
    }
    [textView resignFirstResponder];
}

@end
