// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCards
{
    public abstract class AdaptiveTypedBaseElementConverter : JsonConverter
    {
        protected ParseContext parseContext;
        public ParseContext ParseContext
        {
            get => parseContext;
            set
            {
                parseContext = value;
            }
        }
    }
}
