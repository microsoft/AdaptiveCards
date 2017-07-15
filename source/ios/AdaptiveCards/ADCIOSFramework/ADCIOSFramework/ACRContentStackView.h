//
//  ACRContentStackView
//  ACRContentStackView.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ACRContentStackView: UIView

@property UIStackView* stackView;

- (void)addArrangedSubview:(UIView *) view;

- (void) config;

@end
