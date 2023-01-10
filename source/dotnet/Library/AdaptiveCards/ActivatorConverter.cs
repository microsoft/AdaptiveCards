// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json.Converters;
using System;

namespace AdaptiveCards
{
    internal class ActivatorConverter<T>: CustomCreationConverter<T>
    {
        public override T Create(Type objectType)
        {
            return Activator.CreateInstance<T>();
        }
    }
}
