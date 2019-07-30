// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
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
using AdaptiveCardVisualizer.ViewModel;
using Windows.ApplicationModel;

namespace AdaptiveCardVisualizer.Helpers
{
    public static class PayloadValidator
    {
        public static async Task<List<ErrorViewModel>> ValidateAsync(string payload)
        {
            List<ErrorViewModel> errors = new List<ErrorViewModel>();

            JObject parsedObject = null;

            try
            {
                parsedObject = JObject.Parse(payload);
            }
            catch (JsonReaderException ex)
            {
                errors.Add(new ErrorViewModel()
                {
                    Message = "Parse error: " + ex.Message,
                    Type = ErrorViewModelType.Error
                });
            }
            catch (Exception ex)
            {
                errors.Add(new ErrorViewModel()
                {
                    Message = "Parse error: " + ex.ToString(),
                    Type = ErrorViewModelType.Error
                });
            }

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

                        foreach (var error in validationErrors)
                        {

                            var err = error;
                            if (err.ChildErrors.Count > 0)
                            {
                                err = error.ChildErrors.Last();
                            }
                            var distinct = error.ChildErrors.Distinct().ToArray();

                            var finalErrors = GetLowestMostErrors(error).Distinct(new ErrorEqualityComparer()).ToArray();

                            var typeError = finalErrors.FirstOrDefault(i => i.Path.EndsWith(".type") && i.ErrorType == ErrorType.Enum);
                            if (typeError != null)
                            {
                                JObject definitions = jsonSchema.ExtensionData["definitions"] as JObject;
                                JObject definition = definitions[typeError.Value.ToString()] as JObject;
                                if (definition != null)
                                {
                                    bool loggedErrorForType = false;
                                    var errorsSpecificToType = finalErrors.Where(i => object.Equals(i.Schema.Description, definition["description"]?.ToString())).ToArray();
                                    if (errorsSpecificToType.Length > 0)
                                    {
                                        foreach (var typeErrorChild in errorsSpecificToType)
                                        {
                                            if (typeErrorChild.ErrorType == ErrorType.Required && typeErrorChild.Message.StartsWith("Required properties are missing from object:"))
                                            {
                                                errors.Add(new ErrorViewModel()
                                                {
                                                    Message = typeErrorChild.Message.Replace("Required properties are missing from object:", $"Required properties are missing from {typeError.Value}:"),
                                                    Type = ErrorViewModelType.ErrorButRenderAllowed,
                                                    Position = GetPositionInfo(typeErrorChild)
                                                });
                                                loggedErrorForType = true;
                                            }
                                        }
                                    }

                                    foreach (var parseTypeError in finalErrors.Where(i => i.ErrorType == ErrorType.Type))
                                    {
                                        errors.Add(new ErrorViewModel()
                                        {
                                            Message = parseTypeError.Message.Replace("Invalid type", $"Invalid value type on {typeError.Value}.{GetPropertyName(parseTypeError)}"),
                                            Type = ErrorViewModelType.ErrorButRenderAllowed,
                                            Position = GetPositionInfo(typeError)
                                        });
                                        loggedErrorForType = true;
                                    }

                                    if (!loggedErrorForType)
                                    {
                                        errors.Add(new ErrorViewModel()
                                        {
                                            Message = "Unknown properties or values inside " + typeError.Value.ToString(),
                                            Type = ErrorViewModelType.Warning,
                                            Position = GetPositionInfo(typeError)
                                        });
                                    }
                                    continue;
                                }

                                errors.Add(new ErrorViewModel()
                                {
                                    Message = "Invalid type: " + typeError.Value.ToString(),
                                    Type = ErrorViewModelType.Warning,
                                    Position = GetPositionInfo(typeError)
                                });
                            }
                        }
                    }
                }
            }

            return errors;
        }

        private static string GetPropertyName(ValidationError error)
        {
            return error.Path.Split('.').LastOrDefault();
        }

        private static ErrorViewModelPositionInfo GetPositionInfo(ValidationError error)
        {
            return new ErrorViewModelPositionInfo()
            {
                LineNumber = error.LineNumber
            };
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
            var schemasFolder = await Package.Current.InstalledLocation.GetFolderAsync("Schemas");
            var versionFolders = await schemasFolder.GetFoldersAsync();

            List<Tuple<Version, StorageFolder>> versions = new List<Tuple<Version, StorageFolder>>();
            foreach (var folder in versionFolders)
            {
                if (Version.TryParse(folder.Name, out Version result))
                {
                    versions.Add(new Tuple<Version, StorageFolder>(result, folder));
                }
            }

            var latestFolder = versions.OrderByDescending(i => i.Item1).First().Item2;

            var file = await latestFolder.GetFileAsync("adaptive-card.json");
            return await FileIO.ReadTextAsync(file);
        }
    }
}
