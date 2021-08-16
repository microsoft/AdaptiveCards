// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCardVisualizer.ViewModel
{
    public class ErrorViewModel : IComparable<ErrorViewModel>
    {
        public string Message { get; set; }

        public ErrorViewModelType Type { get; set; }

        public ErrorViewModelPositionInfo Position { get; set; }

        public int CompareTo(ErrorViewModel other)
        {
            // Errors go first
            if ((this.Type == ErrorViewModelType.Error || this.Type == ErrorViewModelType.ErrorButRenderAllowed)
                && other.Type == ErrorViewModelType.Warning)
            {
                return -1;
            }

            // Warnings go last
            if (this.Type == ErrorViewModelType.Warning &&
                (other.Type == ErrorViewModelType.Error || other.Type == ErrorViewModelType.ErrorButRenderAllowed))
            {
                return 1;
            }

            // If same type, compare on position
            if (Position == null)
            {
                return other.Position != null ? -1 : 0;
            }

            return Position.CompareTo(other.Position);
        }

        public bool Equals(ErrorViewModel other)
        {
            return Message.Equals(other.Message)
                && Type == other.Type
                && ((Position == null && other.Position == null) || (Position != null && other.Position != null && Position.Equals(other.Position)));
        }
    }

    public enum ErrorViewModelType
    {
        Error, ErrorButRenderAllowed, Warning
    }
    public sealed class ErrorViewModelPositionInfo : IComparable<ErrorViewModelPositionInfo>
    {
        public int LineNumber { get; set; }

        internal static readonly ErrorViewModelPositionInfo Default = new ErrorViewModelPositionInfo()
        {
            LineNumber = 0
        };

        public bool Equals(ErrorViewModelPositionInfo other)
        {
            return LineNumber == other.LineNumber;
        }

        public int CompareTo(ErrorViewModelPositionInfo other)
        {
            if (other == null)
            {
                return 1;
            }

            return this.LineNumber.CompareTo(other.LineNumber);
        }
    }
}
