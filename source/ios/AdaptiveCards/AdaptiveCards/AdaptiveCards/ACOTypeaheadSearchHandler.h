//
//  ACOTypeaheadSearchHandler.h
//  AdaptiveCards
//
//  Created by Jyoti Kukreja on 25/01/23.
//  Copyright © 2023 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol ACRTypeaheadSearchProtocol <NSObject>
- (void)updateTypeaheadUIWithSearchText:(NSString*)searchText dynamicChoices:(NSDictionary *)response withError:(NSError *)error;
@end
