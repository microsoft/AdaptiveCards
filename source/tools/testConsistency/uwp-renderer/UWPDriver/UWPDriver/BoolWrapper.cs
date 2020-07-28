// Copyright (c) Microsoft Corporation. All rights reserved. 
// Licensed under the MIT License. 

namespace UWPDriver
{
    // This class allows us to create a boolean object that can be passed around by reference. We use this bool object 
    // in our bitmap timer class
    public class BoolWrapper
    {
        public bool boolVal { get; set; }
        public BoolWrapper(bool boolVal)
        {
            this.boolVal = boolVal;
        }
    }
}
