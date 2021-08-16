// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Collections.Generic;
using System.Collections.ObjectModel;
using UWPTestLibrary;

namespace AdaptiveCardTestApp.ViewModels
{
    public class TestResultsCategoryViewModel : BindableBase
    {
        public ObservableCollection<TestResultViewModel> Results { get; }

        private string _name;
        /// <summary>
        /// The display name, including the count, like "Failed (4)"
        /// </summary>
        public string DisplayNameWithCount
        {
            get { return $"{_name} ({Results.Count})"; }
        }

        public TestResultsCategoryViewModel(string categoryName, IEnumerable<TestResultViewModel> results)
        {
            _name = categoryName;
            Results = new ObservableCollection<TestResultViewModel>(results);
            Results.CollectionChanged += Results_CollectionChanged;
        }

        private void Results_CollectionChanged(object sender, System.Collections.Specialized.NotifyCollectionChangedEventArgs e)
        {
            NotifyPropertyChanged(nameof(DisplayNameWithCount));
        }
    }
}
