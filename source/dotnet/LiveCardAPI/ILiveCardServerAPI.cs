using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LiveCardAPI
{
    public interface ILiveCardServerAPI
    {
        Task OnActivate();

        Task OnDeactivate();

        Task OnFocus(string id);

        Task OnBlur(string id);

        Task OnKey(string id, string key);

        Task OnClick(string id);

        Task OnDoubleClick(string id);

        Task OnTextChanged(string id, string text);

        Task OnSelectionChanged(string id, int[] selectedIndices);

        Task OnMouseEnter(string id);

        Task OnMouseLeave(string id);
    }
}
