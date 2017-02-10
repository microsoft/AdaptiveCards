/* File : AdaptiveCardObjectModel.i */
%module AdaptiveCardObjectModel

%include <std_string.i>
%include <std_shared_ptr.i>
%include <std_vector.i>

%shared_ptr(AdaptiveCards::BaseCardElement)
%shared_ptr(AdaptiveCards::Container)
%shared_ptr(AdaptiveCards::TextBlock)
%shared_ptr(AdaptiveCards::AdaptiveCard)

%template(BaseCardElementVector) std::vector<std::shared_ptr<AdaptiveCards::BaseCardElement> >; 

%{
#include "Enums.h"
#include "BaseCardElement.h"
#include "Container.h"
#include "TextBlock.h"
#include "AdaptiveCard.h"
%}

%include "Enums.h"
%include "BaseCardElement.h"
%include "Container.h"
%include "TextBlock.h"
%include "AdaptiveCard.h"
