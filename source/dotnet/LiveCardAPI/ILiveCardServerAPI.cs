using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LiveCardAPI
{
    public interface ILiveCardServerAPI
    {
        Task FireActivate();

        Task FireDeactivate();

        Task FireFocus(string id);

        Task FireBlur(string id);

        Task FireKey(string id, string key);

        Task FireClick(string id);

        Task FireTextChanged(string id, string text);

        Task FireSelectionChanged(string id, int[] selectedIndices);

        Task FireMouseEnter(string id);

        Task FireMouseLeave(string id);
    }
}
