import os
import subprocess
from sys import platform
import tarfile
from pathlib import Path
import urllib.request

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
cmake_args.append("-DCONFIG_BUILD_WITH_NSIGHT_AFTERMATH_SUPPORT=1")
cmake_args.append("-DDEPENDENCY_NSIGHT_AFTERMATH_INCLUDE=" +nsight_aftermath_root +"/include/")

if platform == "win32":
	cmake_args.append("-DDEPENDENCY_NSIGHT_AFTERMATH_LIBRARY=" +nsight_aftermath_root +"/lib/x64/GFSDK_Aftermath_Lib.x64.lib")
else:
	cmake_args.append("-DDEPENDENCY_NSIGHT_AFTERMATH_LIBRARY=" +nsight_aftermath_root +"/lib/x64/libGFSDK_Aftermath_Lib.x64.so")
