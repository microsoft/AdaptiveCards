// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer;

import io.adaptivecards.renderer.typeaheadsearch.BackIconParams;
import io.adaptivecards.renderer.typeaheadsearch.CrossIconParams;
import io.adaptivecards.renderer.typeaheadsearch.ErrorStateParams;
import io.adaptivecards.renderer.typeaheadsearch.ITypeAheadIconParams;
import io.adaptivecards.renderer.typeaheadsearch.ITypeAheadStateParams;
import io.adaptivecards.renderer.typeaheadsearch.NoResultStateParams;
import io.adaptivecards.renderer.typeaheadsearch.SearchIconParams;
import io.adaptivecards.renderer.typeaheadsearch.StartSearchingStateParams;
import io.adaptivecards.renderer.typeaheadsearch.TickIconParams;

public interface ITypeAheadCustomParams {
    default SearchIconParams getSearchIconParams()
    {
        return new SearchIconParams();
    }

    default CrossIconParams getCrossIconParams()
    {
        return new CrossIconParams();
    }

    default TickIconParams getTickIconParams()
    {
        return new TickIconParams();
    }

    default BackIconParams getBackIconParams()
    {
        return new BackIconParams();
    }

    default StartSearchingStateParams getStartSearchingStateParams()
    {
        return new StartSearchingStateParams();
    }

    default ErrorStateParams getErrorStateParams()
    {
        return new ErrorStateParams();
    }

    default NoResultStateParams getNoResultStateParams()
    {
        return new NoResultStateParams();
    }

    default String getScreenTitle()
    {
        return "Search";
    }
}
