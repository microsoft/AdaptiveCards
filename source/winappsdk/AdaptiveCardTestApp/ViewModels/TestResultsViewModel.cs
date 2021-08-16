// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Linq;
using UWPTestLibrary;

namespace AdaptiveCardTestApp.ViewModels
{
    public class TestResultsViewModel
    {
        public TestResultsCategoryViewModel Passed { get; }
        public TestResultsCategoryViewModel Failed { get; }
        public TestResultsCategoryViewModel PassedButSourceWasChanged { get; }
        public TestResultsCategoryViewModel New { get; }
        public TestResultsCategoryViewModel Leaked { get; }

        public TestResultsViewModel(IEnumerable<TestResultViewModel> results)
        {
            Passed = new TestResultsCategoryViewModel("Passed", results.Where(i => i.Status.IsPassingStatus() && i.Status.OriginalMatched));
            PassedButSourceWasChanged = new TestResultsCategoryViewModel("Passed (source changed)", results.Where(i => i.Status.IsPassingStatus() && !i.Status.OriginalMatched));
            Failed = new TestResultsCategoryViewModel("Failed", results.Where(i => !i.Status.IsPassingStatus() && !i.Status.NewCard));
            Leaked = new TestResultsCategoryViewModel("Leaked", results.Where(i => i.TestResult.IsLeaked == true));
            New = new TestResultsCategoryViewModel("New", results.Where(i => i.Status.NewCard));

            foreach (var r in results)
            {
                r.PropertyChanged += TestResultViewModel_PropertyChanged;
            }
        }

        private void TestResultViewModel_PropertyChanged(object sender, System.ComponentModel.PropertyChangedEventArgs e)
        {
            TestResultViewModel item = sender as TestResultViewModel;

            if (e.PropertyName == nameof(TestResultViewModel.Status))
            {
                Passed.Results.Remove(item);
                Failed.Results.Remove(item);
                PassedButSourceWasChanged.Results.Remove(item);
                New.Results.Remove(item);
                Leaked.Results.Remove(item);

                if (item.Status.IsPassingStatus() && item.Status.OriginalMatched)
                {
                    Passed.Results.Add(item);
                }
                else if (item.Status.IsPassingStatus() && !item.Status.OriginalMatched)
                {
                    PassedButSourceWasChanged.Results.Add(item);
                }
                else
                {
                    Failed.Results.Add(item);
                }
            }
        }
    }
}
