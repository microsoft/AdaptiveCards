using System.Collections.Generic;
using System.Linq;
using UWPTestLibrary;

namespace AdaptiveCardTestApp.ViewModels
{
    public class TestResultsViewModel
    {
        public TestResultsCategoryViewModel Passed { get; }
        public TestResultsCategoryViewModel Failed { get; }
        public TestResultsCategoryViewModel ImageAndJsonFailed { get; }
        public TestResultsCategoryViewModel JsonFailed { get; }
        public TestResultsCategoryViewModel FailedButSourceWasChanged { get; }
        public TestResultsCategoryViewModel PassedButSourceWasChanged { get; }
        public TestResultsCategoryViewModel New { get; }
        public TestResultsCategoryViewModel Leaked { get; }

        public TestResultsViewModel(IEnumerable<TestResultViewModel> results)
        {
            Passed = new TestResultsCategoryViewModel("Passed", results.Where(i => i.Status == TestStatus.Passed));
            Failed = new TestResultsCategoryViewModel("Image Comparison Failed", results.Where(i => i.Status == TestStatus.Failed));
            JsonFailed = new TestResultsCategoryViewModel("Json Roundtrip Failed", results.Where(i => i.Status == TestStatus.JsonFailed));
            ImageAndJsonFailed = new TestResultsCategoryViewModel("Image Comparison and Json Roundtrip Failed", results.Where(i => i.Status == TestStatus.ImageAndJsonFailed));
            FailedButSourceWasChanged = new TestResultsCategoryViewModel("Failed/source changed", results.Where(i => i.Status == TestStatus.FailedButSourceWasChanged));
            PassedButSourceWasChanged = new TestResultsCategoryViewModel("Passed/source changed", results.Where(i => i.Status == TestStatus.PassedButSourceWasChanged));
            Leaked = new TestResultsCategoryViewModel("Leaked", results.Where(i => i.TestResult.IsLeaked == true));
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
                JsonFailed.Results.Remove(item);
                ImageAndJsonFailed.Results.Remove(item);
                FailedButSourceWasChanged.Results.Remove(item);
                PassedButSourceWasChanged.Results.Remove(item);
                New.Results.Remove(item);
                Leaked.Results.Remove(item);

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
