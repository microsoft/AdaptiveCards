using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using Newtonsoft.Json.Schema;
using Newtonsoft.Json.Serialization;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using Windows.Storage;

namespace AdaptiveCards.Rendering.UWP.Helpers
{
    public static class PayloadValidator
    {
        public static async void ValidateAsync(string payload)
        {
            JObject parsedObject = null;

            try
            {
                parsedObject = JObject.Parse(payload);
            }
            catch (JsonReaderException ex) { }
            catch (Exception ex) { }

            if (parsedObject != null)
            {
                string schema = null;
                try
                {
                    schema = await GetSchemaAsync();
                }
                catch { }

                if (schema != null)
                {
                    JSchema jsonSchema = null;

                    try
                    {
                        jsonSchema = JSchema.Parse(schema);
                    }
                    catch
                    {
                        // We don't report this error to user, it's a coding error
                        if (Debugger.IsAttached)
                        {
                            Debugger.Break();
                        }
                    }

                    if (jsonSchema != null)
                    {
                        parsedObject.IsValid(jsonSchema, out IList<ValidationError> validationErrors);
                    }
                }
            }
        }

        private static string GetPropertyName(ValidationError error)
        {
            return error.Path.Split('.').LastOrDefault();
        }

        private class ErrorEqualityComparer : IEqualityComparer<ValidationError>
        {
            public bool Equals(ValidationError x, ValidationError y)
            {
                return x.Message.Equals(y.Message)
                    && x.LineNumber == y.LineNumber
                    && x.LinePosition == y.LinePosition
                    && x.ErrorType == y.ErrorType
                    && x.Path == y.Path
                    && x.ChildErrors.Count == y.ChildErrors.Count;
            }

            public int GetHashCode(ValidationError obj)
            {
                return (obj.Message
                    + obj.LineNumber.ToString()
                    + obj.LinePosition.ToString()
                    + obj.ErrorType.ToString()
                    + obj.Path
                    + obj.ChildErrors.Count.ToString()).GetHashCode();
            }
        }

        private static IEnumerable<ValidationError> GetLowestMostErrors(ValidationError error)
        {
            if (error.ChildErrors.Count == 0)
            {
                yield return error;
                yield break;
            }

            foreach (var child in error.ChildErrors)
            {
                foreach (var lowest in GetLowestMostErrors(child))
                {
                    yield return lowest;
                }
            }
        }

        private static IEnumerable<ValidationError> GetAllErrors(ValidationError error)
        {
            yield return error;
            foreach (var descendant in GetDescendantErrors(error))
            {
                yield return descendant;
            }
        }

        private static IEnumerable<ValidationError> GetDescendantErrors(ValidationError error)
        {
            foreach (var child in error.ChildErrors)
            {
                yield return child;

                foreach (var descendant in GetDescendantErrors(child))
                {
                    yield return descendant;
                }
            }
        }

        private static Task<string> _getSchemaTask;
        private static Task<string> GetSchemaAsync()
        {
            if (_getSchemaTask == null)
            {
                _getSchemaTask = GetSchemaHelperAsync();
            }

            return _getSchemaTask;
        }

        private static async Task<string> GetSchemaHelperAsync()
        {
            var file = await StorageFile.GetFileFromApplicationUriAsync(new Uri("ms-appx:///Schemas/adaptive-card.json"));
            return await FileIO.ReadTextAsync(file);
        }
    }
}
