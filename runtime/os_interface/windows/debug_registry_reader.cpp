/*
 * Copyright (C) 2017-2018 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "runtime/os_interface/debug_settings_manager.h"
#include "runtime/utilities/debug_settings_reader.h"
#include <stdint.h>
#include "runtime/os_interface/windows/windows_wrapper.h"
#include "runtime/os_interface/windows/registry_reader.h"

namespace OCLRT {

SettingsReader *SettingsReader::createOsReader(bool userScope) {
    return new RegistryReader(userScope);
}

bool RegistryReader::getSetting(const char *settingName, bool defaultValue) {
    return getSetting(settingName, static_cast<int32_t>(defaultValue)) ? true : false;
}

int32_t RegistryReader::getSetting(const char *settingName, int32_t defaultValue) {
    HKEY Key;
    DWORD value = defaultValue;
    DWORD success = ERROR_SUCCESS;

    success = RegOpenKeyExA(igdrclHkeyType,
                            igdrclRegKey.c_str(),
                            0,
                            KEY_READ,
                            &Key);

    if (ERROR_SUCCESS == success) {
        DWORD regType;
        DWORD size = sizeof(ULONG);

        success = RegQueryValueExA(Key,
                                   settingName,
                                   NULL,
                                   &regType,
                                   (LPBYTE)&value,
                                   &size);
        RegCloseKey(Key);
        value = ERROR_SUCCESS == success ? value : defaultValue;
    }

    return value;
}

std::string RegistryReader::getSetting(const char *settingName, const std::string &value) {
    HKEY Key;
    DWORD success = ERROR_SUCCESS;
    bool retFlag = false;
    std::string keyValue = value;

    success = RegOpenKeyExA(igdrclHkeyType,
                            igdrclRegKey.c_str(),
                            0,
                            KEY_READ,
                            &Key);

    if (ERROR_SUCCESS == success) {
        DWORD regType = REG_NONE;
        DWORD regSize = 0;

        success = RegQueryValueExA(Key,
                                   settingName,
                                   NULL,
                                   &regType,
                                   NULL,
                                   &regSize);

        if (success == ERROR_SUCCESS && regType == REG_SZ) {
            char *regData = new char[regSize];
            success = RegQueryValueExA(Key,
                                       settingName,
                                       NULL,
                                       &regType,
                                       (LPBYTE)regData,
                                       &regSize);

            keyValue.assign(regData);
            delete[] regData;
            retFlag = true;
        } else if (success == ERROR_SUCCESS && regType == REG_BINARY) {
            std::unique_ptr<wchar_t[]> regData(new wchar_t[regSize]);
            success = RegQueryValueExA(Key,
                                       settingName,
                                       NULL,
                                       &regType,
                                       (LPBYTE)regData.get(),
                                       &regSize);

            size_t charsConverted = 0;
            std::unique_ptr<char[]> convertedData(new char[regSize]);

            wcstombs_s(&charsConverted, convertedData.get(), regSize, regData.get(), regSize);

            keyValue.assign(convertedData.get());
            retFlag = true;
        }

        RegCloseKey(Key);
    }
    return keyValue;
}
}; // namespace OCLRT
