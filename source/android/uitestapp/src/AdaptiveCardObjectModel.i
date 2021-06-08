/* Copyright (c) Microsoft Corporation. All rights reserved. */
/* Licensed under the MIT License. */
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

%{
#include "pch.h"
#include <memory>
#include "../../../shared/cpp/ObjectModel/Enums.h"
#include "../../../shared/cpp/ObjectModel/BaseCardElement.h"
#include "../../../shared/cpp/ObjectModel/BaseActionElement.h"
#include "../../../shared/cpp/ObjectModel/Container.h"
#include "../../../shared/cpp/ObjectModel/TextBlock.h"
#include "../../../shared/cpp/ObjectModel/Image.h"
#include "../../../shared/cpp/ObjectModel/ImageSet.h"
#include "../../../shared/cpp/ObjectModel/Column.h"
#include "../../../shared/cpp/ObjectModel/ColumnSet.h"
#include "../../../shared/cpp/ObjectModel/Fact.h"
#include "../../../shared/cpp/ObjectModel/FactSet.h"
#include "../../../shared/cpp/ObjectModel/InputChoice.h"
#include "../../../shared/cpp/ObjectModel/InputChoiceSet.h"
#include "../../../shared/cpp/ObjectModel/AdaptiveCard.h"
#include "../../../shared/cpp/ObjectModel/AdaptiveCardParseException.h"
#include "../../../shared/cpp/ObjectModel/HostConfig.h"
%}

%shared_ptr(AdaptiveCards::BaseCardElement)
%shared_ptr(AdaptiveCards::BaseActionElement)
%shared_ptr(AdaptiveCards::Container)
%shared_ptr(AdaptiveCards::TextBlock)
%shared_ptr(AdaptiveCards::Image)
%shared_ptr(AdaptiveCards::ImageSet)
%shared_ptr(AdaptiveCards::Column)
%shared_ptr(AdaptiveCards::ColumnSet)
%shared_ptr(AdaptiveCards::Fact)
%shared_ptr(AdaptiveCards::FactSet)
%shared_ptr(AdaptiveCards::InputChoiceSet)
%shared_ptr(AdaptiveCards::AdaptiveCard)

// Allow C++ exceptions to be handled in Java
%typemap(throws, throws="java.io.IOException") AdaptiveCards::AdaptiveCardParseException {
  jclass excep = jenv->FindClass("java/io/IOException");
  if (excep)
    jenv->ThrowNew(excep, $1.what());
  return $null;
}

// Force the CustomException Java class to extend java.lang.Exception
%typemap(javabase) AdaptiveCards::AdaptiveCardParseException "java.lang.Exception";

// Override getMessage()
%typemap(javacode) AdaptiveCards::AdaptiveCardParseException %{
  public String getMessage() {
    return what();
  }
%}

%template(BaseCardElementVector) std::vector<std::shared_ptr<AdaptiveCards::BaseCardElement> >;
%template(ImageVector) std::vector<std::shared_ptr<AdaptiveCards::Image> >;
%template(FactVector) std::vector<std::shared_ptr<AdaptiveCards::Fact> >;
%template(ColumnVector) std::vector<std::shared_ptr<AdaptiveCards::Column> >;

%template(EnableSharedFromThisContainer) std::enable_shared_from_this<AdaptiveCards::Container>;

%exception AdaptiveCards::Container::dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
    $action
    if (!result) {
        jclass excep = jenv->FindClass("java/lang/ClassCastException");
        if (excep) {
            jenv->ThrowNew(excep, "dynamic_cast exception");
        }
    }
}
%extend AdaptiveCards::Container {
    static AdaptiveCards::Container *dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
        return dynamic_cast<AdaptiveCards::Container *>(baseCardElement);
    }
};

%exception AdaptiveCards::TextBlock::dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
    $action
    if (!result) {
        jclass excep = jenv->FindClass("java/lang/ClassCastException");
        if (excep) {
            jenv->ThrowNew(excep, "dynamic_cast exception");
        }
    }
}
%extend AdaptiveCards::TextBlock {
    static AdaptiveCards::TextBlock *dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
        return dynamic_cast<AdaptiveCards::TextBlock *>(baseCardElement);
    }
};

%exception AdaptiveCards::Image::dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
    $action
    if (!result) {
        jclass excep = jenv->FindClass("java/lang/ClassCastException");
        if (excep) {
            jenv->ThrowNew(excep, "dynamic_cast exception");
        }
    }
}
%extend AdaptiveCards::Image {
    static AdaptiveCards::Image *dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
        return dynamic_cast<AdaptiveCards::Image *>(baseCardElement);
    }
};

%exception AdaptiveCards::ImageSet::dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
    $action
    if (!result) {
        jclass excep = jenv->FindClass("java/lang/ClassCastException");
        if (excep) {
            jenv->ThrowNew(excep, "dynamic_cast exception");
        }
    }
}
%extend AdaptiveCards::ImageSet {
    static AdaptiveCards::ImageSet *dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
        return dynamic_cast<AdaptiveCards::ImageSet *>(baseCardElement);
    }
};

%exception AdaptiveCards::Column::dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
    $action
    if (!result) {
        jclass excep = jenv->FindClass("java/lang/ClassCastException");
        if (excep) {
            jenv->ThrowNew(excep, "dynamic_cast exception");
        }
    }
}
%extend AdaptiveCards::Column {
    static AdaptiveCards::Column *dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
        return dynamic_cast<AdaptiveCards::Column *>(baseCardElement);
    }
};

%exception AdaptiveCards::ColumnSet::dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
    $action
    if (!result) {
        jclass excep = jenv->FindClass("java/lang/ClassCastException");
        if (excep) {
            jenv->ThrowNew(excep, "dynamic_cast exception");
        }
    }
}
%extend AdaptiveCards::ColumnSet {
    static AdaptiveCards::ColumnSet *dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
        return dynamic_cast<AdaptiveCards::ColumnSet *>(baseCardElement);
    }
};

%exception AdaptiveCards::FactSet::dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
    $action
    if (!result) {
        jclass excep = jenv->FindClass("java/lang/ClassCastException");
        if (excep) {
            jenv->ThrowNew(excep, "dynamic_cast exception");
        }
    }
}
%extend AdaptiveCards::FactSet {
    static AdaptiveCards::FactSet *dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
        return dynamic_cast<AdaptiveCards::FactSet *>(baseCardElement);
    }
};

%exception AdaptiveCards::InputChoiceSet::dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
    $action
    if (!result) {
        jclass excep = jenv->FindClass("java/lang/ClassCastException");
        if (excep) {
            jenv->ThrowNew(excep, "dynamic_cast exception");
        }
    }
}
%extend AdaptiveCards::InputChoiceSet {
    static AdaptiveCards::InputChoiceSet *dynamic_cast(AdaptiveCards::BaseCardElement *baseCardElement) {
        return dynamic_cast<AdaptiveCards::InputChoiceSet *>(baseCardElement);
    }
};

%include "../../../shared/cpp/ObjectModel/pch.h"
%include "../../../shared/cpp/ObjectModel/Enums.h"
%include "../../../shared/cpp/ObjectModel/BaseCardElement.h"
%include "../../../shared/cpp/ObjectModel/BaseActionElement.h"
%include "../../../shared/cpp/ObjectModel/Container.h"
%include "../../../shared/cpp/ObjectModel/TextBlock.h"
%include "../../../shared/cpp/ObjectModel/Image.h"
%include "../../../shared/cpp/ObjectModel/ImageSet.h"
%include "../../../shared/cpp/ObjectModel/Column.h"
%include "../../../shared/cpp/ObjectModel/ColumnSet.h"
%include "../../../shared/cpp/ObjectModel/Fact.h"
%include "../../../shared/cpp/ObjectModel/FactSet.h"
%include "../../../shared/cpp/ObjectModel/InputChoice.h"
%include "../../../shared/cpp/ObjectModel/InputChoiceSet.h"
%include "../../../shared/cpp/ObjectModel/AdaptiveCard.h"
%include "../../../shared/cpp/ObjectModel/AdaptiveCardParseException.h"
%include "../../../shared/cpp/ObjectModel/HostConfig.h"
