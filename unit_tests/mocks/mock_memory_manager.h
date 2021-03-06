/*
 * Copyright (C) 2017-2018 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once
#include "runtime/execution_environment/execution_environment.h"
#include "runtime/memory_manager/os_agnostic_memory_manager.h"

#include "gmock/gmock.h"

namespace OCLRT {

class MockMemoryManager : public OsAgnosticMemoryManager {
  public:
    using MemoryManager::allocateGraphicsMemory;
    using MemoryManager::allocateGraphicsMemoryInPreferredPool;
    using MemoryManager::getAllocationData;
    using MemoryManager::timestampPacketAllocator;
    using OsAgnosticMemoryManager::OsAgnosticMemoryManager;
    MockMemoryManager(ExecutionEnvironment &executionEnvironment) : OsAgnosticMemoryManager(false, false, executionEnvironment){};
    MockMemoryManager() : MockMemoryManager(*(new ExecutionEnvironment)) {
        mockExecutionEnvironment.reset(&executionEnvironment);
    };
    MockMemoryManager(bool enable64pages) : OsAgnosticMemoryManager(enable64pages, false, *(new ExecutionEnvironment)) {
        mockExecutionEnvironment.reset(&executionEnvironment);
    }
    GraphicsAllocation *allocateGraphicsMemory64kb(size_t size, size_t alignment, bool forcePin, bool preferRenderCompressed) override;
    void setDeferredDeleter(DeferredDeleter *deleter);
    void overrideAsyncDeleterFlag(bool newValue);
    GraphicsAllocation *allocateGraphicsMemoryForImage(ImageInfo &imgInfo, Gmm *gmm) override;
    int redundancyRatio = 1;
    bool isAllocationListEmpty();
    GraphicsAllocation *peekAllocationListHead();

    GraphicsAllocation *allocateGraphicsMemoryInDevicePool(const AllocationData &allocationData, AllocationStatus &status) override;
    GraphicsAllocation *allocateGraphicsMemory(size_t size, size_t alignment, bool forcePin, bool uncacheable) override;

    bool allocationCreated = false;
    bool allocation64kbPageCreated = false;
    bool allocationInDevicePoolCreated = false;
    bool failInDevicePool = false;
    bool failInDevicePoolWithError = false;
    bool failInAllocateWithSizeAndAlignment = false;
    bool preferRenderCompressedFlagPassed = false;
    std::unique_ptr<ExecutionEnvironment> mockExecutionEnvironment;
};

class GMockMemoryManager : public MockMemoryManager {
  public:
    GMockMemoryManager(const ExecutionEnvironment &executionEnvironment) : MockMemoryManager(const_cast<ExecutionEnvironment &>(executionEnvironment)){};
    MOCK_METHOD2(cleanAllocationList, bool(uint32_t waitTaskCount, uint32_t allocationUsage));
    // cleanAllocationList call defined in MemoryManager.

    MOCK_METHOD1(populateOsHandles, MemoryManager::AllocationStatus(OsHandleStorage &handleStorage));
    MOCK_METHOD2(allocateGraphicsMemoryForNonSvmHostPtr, GraphicsAllocation *(size_t, void *));

    bool MemoryManagerCleanAllocationList(uint32_t waitTaskCount, uint32_t allocationUsage) { return MemoryManager::cleanAllocationList(waitTaskCount, allocationUsage); }
    MemoryManager::AllocationStatus MemoryManagerPopulateOsHandles(OsHandleStorage &handleStorage) { return OsAgnosticMemoryManager::populateOsHandles(handleStorage); }
};

class MockAllocSysMemAgnosticMemoryManager : public OsAgnosticMemoryManager {
  public:
    MockAllocSysMemAgnosticMemoryManager(ExecutionEnvironment &executionEnvironment) : OsAgnosticMemoryManager(false, false, executionEnvironment) {
        ptrRestrictions = nullptr;
        testRestrictions.minAddress = 0;
    }

    AlignedMallocRestrictions *getAlignedMallocRestrictions() override {
        return ptrRestrictions;
    }

    void *allocateSystemMemory(size_t size, size_t alignment) override {
        constexpr size_t minAlignment = 16;
        alignment = std::max(alignment, minAlignment);
        return alignedMalloc(size, alignment);
    }

    AlignedMallocRestrictions testRestrictions;
    AlignedMallocRestrictions *ptrRestrictions;
};
} // namespace OCLRT
