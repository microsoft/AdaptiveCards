//
//  ACRTextView
//  ACRTextView.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACOBaseCardElementPrivate.h"
#import "ACRTextView.h"
#import "TextInput.h"

const NSInteger kACRTextView = 0x4143525456;

@implementation ACRTextView

- (instancetype)initWithFrame:(CGRect)frame element:(ACOBaseCardElement *)element
{
    self = [super initWithFrame:frame];
    if (self) {
        std::shared_ptr<BaseCardElement> elem = [element element];
        std::shared_ptr<TextInput> inputBlck = std::dynamic_pointer_cast<TextInput>(elem);
        _maxLength = inputBlck->GetMaxLength();
        _placeholderText = [[NSString alloc] initWithCString:inputBlck->GetPlaceholder().c_str() encoding:NSUTF8StringEncoding];
        if(inputBlck->GetValue().size()){
            self.text = [[NSString alloc] initWithCString:inputBlck->GetValue().c_str() encoding:NSUTF8StringEncoding];
        } else if([_placeholderText length]){
            self.text = _placeholderText;
            self.textColor = [UIColor lightGrayColor];
        }
        self.tag = kACRTextView;
        [self.layer setCornerRadius:5.0f];
        [self registerForKeyboardNotifications];
    }
    return self;
}

-(BOOL)textViewShouldEndEditing:(UITextView *)textView {
    [textView resignFirstResponder];
    return YES;
}

- (void)registerForKeyboardNotifications
{
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(keyboardWasShown:)
                                                 name:UIKeyboardDidShowNotification object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(keyboardWillBeHidden:)
                                                 name:UIKeyboardWillHideNotification object:nil];
    
}
// Called when the UIKeyboardDidShowNotification is sent.
- (void)keyboardWasShown:(NSNotification*)aNotification
{
    self.scrollEnabled = YES;
}

// Called when the UIKeyboardWillHideNotification is sent
- (void)keyboardWillBeHidden:(NSNotification*)aNotification
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
    dictionary[self.id] = ([_placeholderText isEqualToString:self.text])? @"" : self.text;
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
    if (!_maxLength){
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
        textView.textColor = [UIColor blackColor];
    }
    [textView becomeFirstResponder];
}
- (void)textViewDidEndEditing:(UITextView *)textView
{
    if (![textView.text length]) {
        textView.text = _placeholderText;
        textView.textColor = [UIColor lightGrayColor];
    }
    [textView resignFirstResponder];
}

@end
