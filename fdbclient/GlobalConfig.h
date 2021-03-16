/*
 * GlobalConfig.h
 *
 * This source file is part of the FoundationDB open source project
 *
 * Copyright 2013-2021 Apple Inc. and the FoundationDB project authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "fdbclient/CommitTransaction.h"
#include "fdbclient/FDBTypes.h"

// Used to store a list of mutations made to the global configuration at a
// specific version.
struct VersionHistory {
	constexpr static FileIdentifier file_identifier = 5863456;

	Version version;
	Standalone<VectorRef<MutationRef>> mutations;

	bool operator<(const VersionHistory& other) const { return version < other.version; }

	int expectedSize() const { return sizeof(version) + mutations.expectedSize(); }

	template <typename Ar>
	void serialize(Ar& ar) {
		// The version is not serialized because this object is only sent over
		// the network during a write. In this case, the version is included in
		// the key, while this object will be written to the value.
		serializer(ar, mutations);
	}
};
