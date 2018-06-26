//
//  ACRTextView
//  ACRTextView.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACOBaseCardElementPrivate.h"
#import "ACRTextView.h"
#import "TextInput.h"

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
    }
    return self;
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
    dictionary[self.id] = self.text;
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    [self resignFirstResponder];
    return YES;
}

- (void)dismissNumPad
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
