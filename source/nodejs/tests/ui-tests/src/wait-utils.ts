// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

import { TestUtils } from "./test-utils";

export class WaitUntil 
{

    static async customWait(timeoutMs: number, successFunction: Function, params: any) : Promise<void> 
    {
        let milisPassed : number = 0;

        while (milisPassed < timeoutMs)
        {
            let successFunctionResult = await successFunction(params);
            if (successFunctionResult === true)
            {
                break;
            }
            milisPassed += 100;
            await TestUtils.getInstance().delay(100);
        }
    }
}