// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
export interface TransformOptions {
	primaryTypeNames?: string[];
	defaultPrimaryTypeName?: string;
	typePropertyName?: string;
	allowAdditionalProperties?: boolean;
	allowCustomEnums?: boolean;
	allowCustomTypes?: boolean;
	enforceEnumCaseSensitivity?: boolean;
}