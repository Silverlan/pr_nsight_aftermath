// SPDX-FileCopyrightText: (c) 2025 Silverlan <opensource@pragma-engine.com>
// SPDX-License-Identifier: MIT

#pragma once

// Helper macro for checking Nsight Aftermath results and throwing exception
// in case of a failure.
#define AFTERMATH_CHECK_ERROR(FC)                                                                                                                                                                                                                                                                \
	[&]() {                                                                                                                                                                                                                                                                                      \
		GFSDK_Aftermath_Result _result = FC;                                                                                                                                                                                                                                                     \
		if(!GFSDK_Aftermath_SUCCEED(_result)) {                                                                                                                                                                                                                                                  \
			util::debug::show_message_prompt(AftermathErrorMessage(_result), util::debug::MessageBoxButtons::Ok, "Aftermath Error");                                                                                                                                                             \
			exit(1);                                                                                                                                                                                                                                                                             \
		}                                                                                                                                                                                                                                                                                        \
	}()
