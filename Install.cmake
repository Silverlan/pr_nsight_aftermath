set(INSTALL_PATH "modules/nsight_aftermath/")
pr_install_targets(pr_nsight_aftermath INSTALL_DIR "${INSTALL_PATH}")

pr_install_binary(nsight_aftermath WIN "GFSDK_Aftermath_Lib.x64.dll" LIN "libGFSDK_Aftermath_Lib.x64.so" INSTALL_DIR "${INSTALL_PATH}")
