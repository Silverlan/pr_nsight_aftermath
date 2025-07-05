// SPDX-FileCopyrightText: (c) 2024 Silverlan <opensource@pragma-engine.com>
// SPDX-License-Identifier: MIT

#include "pr_module.hpp"
#include <pragma/lua/luaapi.h>
#include "crash_handler.hpp"
#include <pragma/console/conout.h>
#include <pragma/engine.h>
#include <luainterface.hpp>

import util_zip;
#pragma optimize("", off)
static CallbackHandle g_dumpDebugInfoHandle;
extern "C" {
// Called after the module has been loaded
DLLEXPORT bool pragma_attach(std::string &outErr)
{
	initialize_gpu_crash_tracker();
	g_dumpDebugInfoHandle = pragma::get_engine()->AddCallback("DumpDebugInformation", FunctionCallback<void, std::reference_wrapper<uzip::ZIPFile>>::Create([](std::reference_wrapper<uzip::ZIPFile> zipFile) {
		auto *tracker = get_gpu_crash_tracker();
		if(tracker == nullptr)
			return;
		// Give the tracker some time to collect crash dump infos
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
		std::string err;
		if(!tracker->WaitForCompletion(err))
			Con::cerr << "Failed to wait for GPU crash dump completion: " << err << Con::endl;
		auto files = tracker->GetCrashDumpFiles();
		for(auto &filePath : files) {
			auto f = filemanager::open_file<VFilePtrReal>(filePath.GetString(), filemanager::FileMode::Read | filemanager::FileMode::Binary);
			if(f) {
				std::vector<uint8_t> data;
				data.resize(f->GetSize());
				f->Read(data.data(), data.size());
				zipFile.get().AddFile(std::string {filePath.GetFileName()}, data.data(), data.size());
			}
			f = {};
			// We don't need the files anymore
			filemanager::remove_file(filePath.GetString());
		}
	}));
	return true;
}

// Called when the module is about to be unloaded
DLLEXPORT void pragma_detach()
{
	if(g_dumpDebugInfoHandle.IsValid())
		g_dumpDebugInfoHandle.Remove();
	release_gpu_crash_tracker();
}
};
