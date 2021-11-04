// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
const v10TestCases: string[] = ["Scenarios/ActivityUpdate"];
const v11TestCases: string[] = [];
const v12TestCases: string[] = [];
const v13TestCases: string[] = ["Elements/Input.Text.ErrorMessage"];
const v14TestCases: string[] = [];
const v15TestCases: string[] = [];

function fixTestCases(list: string[], versionNumber: string) {
    const fixedTestCasesList: string[] = [];

    list.forEach((element) => {
        let fixedTestCase: string = "v" + versionNumber + "/" + element;

        if (!fixedTestCase.endsWith(".json")) {
            fixedTestCase += ".json";
        }

        fixedTestCasesList.push(fixedTestCase);
    });

    return fixedTestCasesList;
}

export function getTestCasesList() {
    let testCasesList: string[] = [];

    testCasesList = testCasesList.concat(fixTestCases(v10TestCases, "1.0"),
        fixTestCases(v11TestCases, "1.1"),
        fixTestCases(v12TestCases, "1.2"),
        fixTestCases(v13TestCases, "1.3"),
        fixTestCases(v14TestCases, "1.4"),
        fixTestCases(v15TestCases, "1.5"));

    return testCasesList;
}
