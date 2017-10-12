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
        public ObservableCollection<TestResultViewModel> Passed { get; }

        public ObservableCollection<TestResultViewModel> Failed { get; }

        public ObservableCollection<TestResultViewModel> New { get; }

        public TestResultViewModel[] Results { get; }

        public TestResultsViewModel(IEnumerable<TestResultViewModel> results)
        {
            Passed = new ObservableCollection<TestResultViewModel>(results.Where(i => i.Status == TestStatus.Passed));
            Failed = new ObservableCollection<TestResultViewModel>(results.Where(i => i.Status == TestStatus.Failed));
            New = new ObservableCollection<TestResultViewModel>(results.Where(i => i.Status == TestStatus.New));

            Results = results.ToArray();

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
                Passed.Remove(item);
                Failed.Remove(item);
                New.Remove(item);

                switch (item.Status)
                {
                    case TestStatus.Passed:
                        Passed.Add(item);
                        break;
                }
            }
        }
    }
}
