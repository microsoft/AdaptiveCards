//
//  ACRSearchBar.h
//  AdaptiveCards
//
//  Created by Jyoti Kukreja on 12/01/23.
//  Copyright © 2023 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface ACRSearchBar: UITextField <UITextFieldDelegate>

-(UITextField *)buildCustomSearchBarWithPlaceholder:(NSString *)placeholder;

@end
