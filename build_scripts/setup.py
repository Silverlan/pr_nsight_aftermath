import os
import subprocess
from sys import platform
import tarfile
from pathlib import Path
import urllib.request
import config

if build_all:
	os.chdir(deps_dir)

	########## NVIDIA Nsight Aftermath SDK ##########
	nsight_aftermath_root = deps_dir +"/NVIDIA_Nsight_Aftermath_SDK_2024.3.0.24312"
	if not Path(nsight_aftermath_root).is_dir():
		print_msg("NVIDIA Nsight Aftermath SDK not found. Downloading...")
		mkpath(nsight_aftermath_root)
		os.chdir(nsight_aftermath_root)
		if platform == "win32":
			http_extract("https://developer.nvidia.com/downloads/assets/tools/secure/nsight-aftermath-sdk/2024_3_0/windows/NVIDIA_Nsight_Aftermath_SDK_2024.3.0.24312.zip")
		else:
			http_extract("https://developer.nvidia.com/downloads/assets/tools/secure/nsight-aftermath-sdk/2024_3_0/linux/NVIDIA_Nsight_Aftermath_SDK_2024.3.0.24312.tgz",format="tar.gz")
		os.chdir(deps_dir)

	copy_prebuilt_binaries(nsight_aftermath_root +"/lib/x64/", "nsight_aftermath")
	copy_prebuilt_headers(nsight_aftermath_root +"/include", "nsight_aftermath")
