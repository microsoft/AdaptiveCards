// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
const v10TestCases: string[] = [
    'Elements/Action.ShowCard'
];
const v11TestCases: string[] = [
    'Elements/Container.SelectAction',
    'Elements/Column.SelectAction',
    'Elements/ColumnSet.SelectAction'
];
const v12TestCases: string[] = [];
const v13TestCases: string[] = [
    'Elements/Input.Text.ErrorMessage',
    'Elements/Input.Number.ErrorMessage',
    'Elements/Input.ChoiceSet.ErrorMessage',
    'Elements/Input.Time.ErrorMessage',
    'Elements/Input.Toggle.ErrorMessage'
];
const v14TestCases: string[] = [];
const v15TestCases: string[] = [
    'Scenarios/ActivityUpdate',
    'Elements/Image.SelectAction',
    'Tests/ToggleVisibility.ShowCard.actions',
    'Tests/ToggleVisibility.ShowCard.ActionSet'
];
const v16TestCases: string[] = [
    'Elements/Carousel',
    'Elements/Carousel.ScenarioCards',
    'Elements/Carousel.ScenarioCards.Timer',
    'Tests/Carousel.HostConfig',
    'Tests/Carousel.ForbiddenElements',
    'Tests/Carousel.ForbiddenActions',
    'Tests/Carousel.rtl'
];

function fixTestCases(list: string[], versionNumber: string) {
    const fixedTestCasesList: string[] = [];

    list.forEach((element) => {
        let fixedTestCase: string = 'v' + versionNumber + '/' + element;

        if (!fixedTestCase.endsWith('.json')) {
            fixedTestCase += '.json';
        }

        fixedTestCasesList.push(fixedTestCase);
    });

    return fixedTestCasesList;
}

export function getTestCasesList() {
    let testCasesList: string[] = [];

    testCasesList = testCasesList.concat(
        fixTestCases(v10TestCases, '1.0'),
        fixTestCases(v11TestCases, '1.1'),
        fixTestCases(v12TestCases, '1.2'),
        fixTestCases(v13TestCases, '1.3'),
        fixTestCases(v14TestCases, '1.4'),
        fixTestCases(v15TestCases, '1.5'),
        fixTestCases(v16TestCases, '1.6')
    );

    return testCasesList;
}
