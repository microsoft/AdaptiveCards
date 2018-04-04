using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCardTestApp.ViewModels
{
    public class TestResultsViewModel
    {
        public TestResultsCategoryViewModel Passed { get; }
        public TestResultsCategoryViewModel Failed { get; }
        public TestResultsCategoryViewModel FailedButSourceWasChanged { get; }
        public TestResultsCategoryViewModel PassedButSourceWasChanged { get; }
        public TestResultsCategoryViewModel New { get; }

        public TestResultsViewModel(IEnumerable<TestResultViewModel> results)
        {
            Passed = new TestResultsCategoryViewModel("Passed", results.Where(i => i.Status == TestStatus.Passed));
            Failed = new TestResultsCategoryViewModel("Failed", results.Where(i => i.Status == TestStatus.Failed));
            FailedButSourceWasChanged = new TestResultsCategoryViewModel("Failed/source changed", results.Where(i => i.Status == TestStatus.FailedButSourceWasChanged));
            PassedButSourceWasChanged = new TestResultsCategoryViewModel("Passed/source changed", results.Where(i => i.Status == TestStatus.PassedButSourceWasChanged));
            New = new TestResultsCategoryViewModel("New", results.Where(i => i.Status == TestStatus.New));

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
                FailedButSourceWasChanged.Results.Remove(item);
                PassedButSourceWasChanged.Results.Remove(item);
                New.Results.Remove(item);

                switch (item.Status)
                {
                    case TestStatus.Passed:
                        Passed.Results.Add(item);
                        break;
                }
            }
        }
    }
}
