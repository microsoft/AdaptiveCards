// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
namespace AdaptiveCards
{
    // TODO: decide if standard error codes are useful or if this should just be string
    public class AdaptiveWarning
    {
        // TODO #2749: temporary warning code for fallback card. Remove when common set of error codes created and integrated.
        public enum WarningStatusCode { UnsupportedSchemaVersion = 7, InvalidLanguage = 12, MaxActionsExceeded = 13 };

        public AdaptiveWarning(int code, string message)
        {
            Code = code;
            Message = message;
        }

        public int Code { get; set; }

        public string Message { get; set; }
    }
}
