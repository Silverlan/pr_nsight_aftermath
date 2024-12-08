/* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this
* file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef __NSIGHT_AFTERMATH_HPP__
#define __NSIGHT_AFTERMATH_HPP__

#include <map>
#include <mutex>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <cinttypes>
#include <vulkan/vulkan.h>
#include <pragma/debug/debug_utils.hpp>
#include <sharedutils/util_path.hpp>
#include <sharedutils/magic_enum.hpp>
#include <GFSDK_Aftermath.h>
#include <GFSDK_Aftermath_GpuCrashDump.h>
#include <GFSDK_Aftermath_GpuCrashDumpDecoding.h>

//*********************************************************
// Some std::to_string overloads for some Nsight Aftermath
// API types.
//

namespace std {
	template<typename T>
	inline std::string to_hex_string(T n)
	{
		std::stringstream stream;
		stream << std::setfill('0') << std::setw(2 * sizeof(T)) << std::hex << n;
		return stream.str();
	}

	inline std::string to_string(GFSDK_Aftermath_Result result) { return std::string("0x") + to_hex_string(static_cast<uint32_t>(result)); }

	inline std::string to_string(const GFSDK_Aftermath_ShaderDebugInfoIdentifier &identifier) { return to_hex_string(identifier.id[0]) + "-" + to_hex_string(identifier.id[1]); }

	inline std::string to_string(const GFSDK_Aftermath_ShaderBinaryHash &hash) { return to_hex_string(hash.hash); }
} // namespace std

inline const char *aftermath_result_to_string(GFSDK_Aftermath_Result result)
{
	switch(result) {
	case GFSDK_Aftermath_Result_Success:
		return "Success";
	case GFSDK_Aftermath_Result_NotAvailable:
		return "NotAvailable";
	case GFSDK_Aftermath_Result_Fail:
		return "Fail";
	case GFSDK_Aftermath_Result_FAIL_VersionMismatch:
		return "VersionMismatch";
	case GFSDK_Aftermath_Result_FAIL_NotInitialized:
		return "NotInitialized";
	case GFSDK_Aftermath_Result_FAIL_InvalidAdapter:
		return "InvalidAdapter";
	case GFSDK_Aftermath_Result_FAIL_InvalidParameter:
		return "InvalidParameter";
	case GFSDK_Aftermath_Result_FAIL_Unknown:
		return "Unknown";
	case GFSDK_Aftermath_Result_FAIL_ApiError:
		return "ApiError";
	case GFSDK_Aftermath_Result_FAIL_NvApiIncompatible:
		return "NvApiIncompatible";
	case GFSDK_Aftermath_Result_FAIL_GettingContextDataWithNewCommandList:
		return "GettingContextDataWithNewCommandList";
	case GFSDK_Aftermath_Result_FAIL_AlreadyInitialized:
		return "AlreadyInitialized";
	case GFSDK_Aftermath_Result_FAIL_D3DDebugLayerNotCompatible:
		return "D3DDebugLayerNotCompatible";
	case GFSDK_Aftermath_Result_FAIL_DriverInitFailed:
		return "DriverInitFailed";
	case GFSDK_Aftermath_Result_FAIL_DriverVersionNotSupported:
		return "DriverVersionNotSupported";
	case GFSDK_Aftermath_Result_FAIL_OutOfMemory:
		return "OutOfMemory";
	case GFSDK_Aftermath_Result_FAIL_GetDataOnBundle:
		return "GetDataOnBundle";
	case GFSDK_Aftermath_Result_FAIL_GetDataOnDeferredContext:
		return "GetDataOnDeferredContext";
	case GFSDK_Aftermath_Result_FAIL_FeatureNotEnabled:
		return "FeatureNotEnabled";
	case GFSDK_Aftermath_Result_FAIL_NoResourcesRegistered:
		return "NoResourcesRegistered";
	case GFSDK_Aftermath_Result_FAIL_ThisResourceNeverRegistered:
		return "ThisResourceNeverRegistered";
	case GFSDK_Aftermath_Result_FAIL_NotSupportedInUWP:
		return "NotSupportedInUWP";
	case GFSDK_Aftermath_Result_FAIL_D3dDllNotSupported:
		return "D3dDllNotSupported";
	case GFSDK_Aftermath_Result_FAIL_D3dDllInterceptionNotSupported:
		return "D3dDllInterceptionNotSupported";
	case GFSDK_Aftermath_Result_FAIL_Disabled:
		return "Disabled";
	case GFSDK_Aftermath_Result_FAIL_NotSupportedOnContext:
		return "NotSupportedOnContext";
	default:
		return "Unknown";
	}
}

inline const char *aftermath_result_to_string(GFSDK_Aftermath_CrashDump_Status status)
{
	switch(status) {
	case GFSDK_Aftermath_CrashDump_Status_NotStarted:
		return "NotStarted";
	case GFSDK_Aftermath_CrashDump_Status_CollectingData:
		return "CollectingData";
	case GFSDK_Aftermath_CrashDump_Status_CollectingDataFailed:
		return "CollectingDataFailed";
	case GFSDK_Aftermath_CrashDump_Status_InvokingCallback:
		return "InvokingCallback";
	case GFSDK_Aftermath_CrashDump_Status_Finished:
		return "Finished";
	case GFSDK_Aftermath_CrashDump_Status_Unknown:
		return "Unknown";
	}
	return "Unknown";
}

inline std::string AftermathErrorMessage(GFSDK_Aftermath_Result result)
{
	switch(result) {
	case GFSDK_Aftermath_Result_FAIL_DriverVersionNotSupported:
		return "Unsupported driver version - requires an NVIDIA R495 display driver or newer.";
	default:
		return "Aftermath Error " + std::string {aftermath_result_to_string(result)};
	}
}

// Helper macro for checking Nsight Aftermath results and throwing exception
// in case of a failure.
#define AFTERMATH_CHECK_ERROR(FC)                                                                                                                                                                                                                                                                \
	[&]() {                                                                                                                                                                                                                                                                                      \
		GFSDK_Aftermath_Result _result = FC;                                                                                                                                                                                                                                                     \
		if(!GFSDK_Aftermath_SUCCEED(_result)) {                                                                                                                                                                                                                                                  \
			pragma::debug::show_message_prompt(AftermathErrorMessage(_result), pragma::debug::MessageBoxButtons::Ok, "Aftermath Error");                                                                                                                                                         \
			exit(1);                                                                                                                                                                                                                                                                             \
		}                                                                                                                                                                                                                                                                                        \
	}()

#endif
