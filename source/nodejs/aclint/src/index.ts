#!/usr/bin/env node

import * as yargs from 'yargs';
import * as fs from 'fs';
import * as path from 'path';
import * as ac from 'adaptivecards';
import * as chalk from 'chalk';

const argv = yargs.options({
    v: { type: 'boolean', default: false, alias: "verbose"}
})
    .usage('Usage: $0 <file or path> [options]')
    .help('h')
    .alias('h', 'help')
    .argv;

const verbose : boolean = argv.v;

enum TestState {
    Skipped,
    Passed,
    Mixed,
    Failed,
    __LENGTH // must be last item in enum
}

/**
* Generate a reasonable icon to represent a TestState
* @param {TestState} state - State to map to icon.
* @return {string} string containing appropriate icon
*/
function iconFromTestState(state: TestState) : string {
    switch(state) {
        case TestState.Passed: {
            return "✔";
        }
        case TestState.Failed: {
            return "❌";
        }
        case TestState.Mixed: {
            return "〰";
        }
        case TestState.Skipped: {
            return "⛔";
        }
        default: {
            throw "Unexpected TestState";
        }
    }
}

class TestResult
{
    constructor(public filename: string, public result: TestState, public validationErrors?: ac.ValidationFailure[], public error? : Error) {
        if (error && result != TestState.Failed) {
            throw "invalid pass state";
        }
    }
}

/**
* Run tests on supplied filesystem path.
* @summary If supplied item indicates a file, test the file. If item indicates a directory, recursively test items within it.
* @param {string} fsitem - Path to test
* @return {Promise<TestResult[]>} Promise for results
*/
async function testFileOrDir(fsitem : string) : Promise<TestResult[]> {
    return new Promise((resolve, reject) => {
        setImmediate(() => {
            // determine if fsitem is a dir or a file, and test accordingly
            fs.promises.stat(fsitem).then(async (fileNode) => {
                if (fileNode.isDirectory()) {
                    if (verbose) console.log(chalk.grey(`${fsitem} is a directory`));
                    return testDir(fsitem);
                } else {
                    if (verbose) console.log(chalk.grey(`${fsitem} is a file`));
                    return testFile(fsitem);
                }
            }).then((results) => {
                // cast as TestResult[] since testFile returns a scalar
                resolve(results as TestResult[]);
            }).catch((err) => {
                reject(err);
            });
        });
    });
}

/**
* Run tests on an individual file
* @summary Automatically skips non-json files. Attempts to parse the file and then supplies warnings and errors back out
* @param {string} filename - File to test
* @return {Promise<TestResult>} Promise for file's result
*/
async function testFile(filename : string) : Promise<TestResult> {
    return new Promise((resolve) => {
        setImmediate(() => {
            // only test files that end in .json
            if (path.extname(filename) !== ".json") {
                if (verbose) console.log(chalk.grey(`skipping non-card file: ${filename}`));
                resolve(new TestResult(filename, TestState.Skipped));
                return;
            }
            if (verbose) console.log(chalk.grey(`Testing ${filename}`));

            // load and test card
            fs.promises.readFile(filename).then((cardBuffer) => {
                let cardJson = JSON.parse(cardBuffer.toString());
                let testCard = new ac.AdaptiveCard();
                testCard.parse(cardJson);
                let validateProperties = testCard.validateProperties();
                return validateProperties.failures;
            }).then((validationErrors) => {
                // determine pass state from warnings (errors are caught in .catch() below)
                let testState : TestState;
                if (validationErrors.length === 0) {
                    testState = TestState.Passed;
                } else {
                    testState = TestState.Mixed;
                }
                resolve(new TestResult(filename, testState, validationErrors));
            }).catch((err) => {
                resolve(new TestResult(filename, TestState.Failed, [], err));
            });
        });
    });
}

/**
* Recursively test files within a directory
* @param {string} dirname - Directory to test
* @return {Promise<TestResult[]>} Promise for results
*/
async function testDir(dirname : string) : Promise<TestResult[]> {
    return new Promise((resolve, reject) => {
        setImmediate(() => {
            if (verbose) console.log(chalk.grey(`Testing directory: ${dirname}`));

            // enumerate items in the supplied directory
            fs.promises.readdir(dirname).then((currDir) => {
                let futureResults : Promise<TestResult[]>[] = [];

                // for every item in the current dir
                currDir.forEach(item => {
                    // kick off test of item
                    let currentItem = path.join(dirname, item);
                    if (verbose) console.log(chalk.grey(currentItem));
                    futureResults.push(testFileOrDir(path.normalize(currentItem)));
                });
                return futureResults;
            }).then((futureResults) => {
                // wait for tests to finish
                return Promise.all(futureResults);
            }).then((results) => {
                // merge result sets
                let finalResults : TestResult[] = [];
                results.forEach((result) => {
                    finalResults = finalResults.concat(result);
                });
                resolve(finalResults);
            }).catch((err) => {
                reject(err);
            });
        });
    });
}

/**
* Extracts work to do from commandline, then kicks off tests
* @return {Promise<TestResult[]>} Promise for results
*/
async function testItemsInArgv() : Promise<TestResult[]> {
    return new Promise(resolve => {
        setImmediate(() => {
            let futureResults : Promise<TestResult[]>[] = [];

            // iterate through paths passed on commandline
            argv._.forEach(fileOrPath => {
                // and then kick off tests for same
                futureResults.push(testFileOrDir(fileOrPath));
            });

            // once all of the tests have completed, merge the results into a single array
            Promise.all(futureResults).then((results) => {
                let finalResults : TestResult[] = [];
                results.forEach((result) => {
                    finalResults = finalResults.concat(result);
                });
                resolve(finalResults);
            }).catch((err) => {
                console.log(err.message);
            });
        });
    });
}

async function main()
{
    return testItemsInArgv();
}

main().then((testResults) => {
    if (testResults.length === 0) {
        console.log("No files were tested.");
    }

    // testResultCount tracks count of results per result type
    let testResultCount : number[] = [];
    for (let i = 0; i < TestState.__LENGTH; ++i) {
        testResultCount[i] = 0;
    }

    // sort results to put skipped/passed results at the top of output
    testResults.sort((left, right) => {
        return left.result - right.result;
    });

    for (let testResult of testResults) {
        // track result count
        testResultCount[testResult.result]++;

        let fileString = `${iconFromTestState(testResult.result)} ${testResult.filename}`;
        if (testResult.result === TestState.Passed) {
            console.log(chalk.grey(fileString));
        } else {
            console.log(fileString);
        }

        // print error state for failed tests
        if (testResult.error) {
            console.log(chalk.red(`▶\tERROR: ${testResult.error.message}`));
        }

        // print any warnings associated with this result
        if (testResult.validationErrors?.length) {
            testResult.validationErrors.forEach((errorCollections) => {
                errorCollections.errors.forEach((error) => {
                    console.log(chalk.yellow(`▶\twarning: ${error.message}`));
                });
            });
        }

        // newline to make it easier to read non-passing tests
        if (testResult.result !== TestState.Passed) {
            console.log();
        }
    }

    // finally, print summary
    for (let i = 0; i < TestState.__LENGTH; ++i) {
        console.log(`${TestState[i]} ${iconFromTestState(i as TestState)}:\t${testResultCount[i]}`);
    }
    console.log(`Total ⬡:\t${testResults.length}`);
}).catch((err) => {
    console.log(chalk.red("Unhandled error: " + err));
});
