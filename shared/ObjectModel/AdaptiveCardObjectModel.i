/* File : AdaptiveCardObjectModel.i */

namespace std {
    template <class T> class enable_shared_from_this {
    public:
        shared_ptr<T> shared_from_this();
    protected:
        enable_shared_from_this();
        enable_shared_from_this(const enable_shared_from_this &);
        ~enable_shared_from_this();        
    };
}

%module AdaptiveCardObjectModel

%include <std_string.i>
%include <std_shared_ptr.i>
%include <std_vector.i>

%shared_ptr(AdaptiveCards::BaseCardElement)
%shared_ptr(AdaptiveCards::Container)
%shared_ptr(AdaptiveCards::TextBlock)
%shared_ptr(AdaptiveCards::AdaptiveCard)

%template(BaseCardElementVector) std::vector<std::shared_ptr<AdaptiveCards::BaseCardElement> >; 
%template(EnableSharedFromThisContainer) std::enable_shared_from_this<AdaptiveCards::Container>;

%{
#include "pch.h"
#include "Enums.h"
#include "BaseCardElement.h"
#include "Container.h"
#include "TextBlock.h"
#include "AdaptiveCard.h"
%}

#include "pch.h"
%include "Enums.h"
%include "BaseCardElement.h"
%include "Container.h"
%include "TextBlock.h"
%include "AdaptiveCard.h"

