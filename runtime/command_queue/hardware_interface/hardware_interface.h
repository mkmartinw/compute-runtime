/*
 * Copyright (c) 2018, Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once
#include "runtime/command_queue/command_queue.h"
#include "runtime/built_ins/built_ins.h"
#include "runtime/context/context.h"
#include "runtime/event/perf_counter.h"
#include "runtime/indirect_heap/indirect_heap.h"
#include "runtime/kernel/kernel.h"
#include "runtime/command_stream/linear_stream.h"
#include "runtime/event/hw_timestamps.h"
#include "runtime/command_stream/preemption.h"
#include "runtime/device_queue/device_queue_hw.h"
#include "runtime/helpers/dispatch_info.h"
#include "runtime/helpers/kernel_commands.h"
#include "runtime/helpers/task_information.h"
#include "runtime/helpers/timestamp_packet.h"
#include "runtime/program/kernel_info.h"
#include "runtime/utilities/vec.h"

namespace OCLRT {

using WALKER_HANDLE = void *;

template <typename GfxFamily>
class HardwareInterface {
  public:
    using INTERFACE_DESCRIPTOR_DATA = typename GfxFamily::INTERFACE_DESCRIPTOR_DATA;

    void dispatchWalker(
        CommandQueue &commandQueue,
        const MultiDispatchInfo &multiDispatchInfo,
        cl_uint numEventsInWaitList,
        const cl_event *eventWaitList,
        KernelOperation **blockedCommandsData,
        HwTimeStamps *hwTimeStamps,
        OCLRT::HwPerfCounter *hwPerfCounter,
        TimestampPacket *previousTimestampPacket,
        TimestampPacket *currentTimestampPacket,
        PreemptionMode preemptionMode,
        bool blockQueue,
        uint32_t commandType = 0);

    virtual void getDefaultDshSpace(
        const size_t &offsetInterfaceDescriptorTable,
        CommandQueue &commandQueue,
        const MultiDispatchInfo &multiDispatchInfo,
        size_t &totalInterfaceDescriptorTableSize,
        OCLRT::Kernel *parentKernel,
        OCLRT::IndirectHeap *dsh,
        OCLRT::LinearStream *commandStream) = 0;

    virtual INTERFACE_DESCRIPTOR_DATA *obtainInterfaceDescriptorData(
        WALKER_HANDLE pCmdData) = 0;

    virtual void setOffsetCrossThreadData(
        WALKER_HANDLE pCmdData,
        size_t &offsetCrossThreadData,
        uint32_t &interfaceDescriptorIndex) = 0;

    virtual void dispatchWorkarounds(
        OCLRT::LinearStream *commandStream,
        CommandQueue &commandQueue,
        OCLRT::Kernel &kernel,
        const bool &enable) = 0;

    virtual void dispatchProfilingPerfStartCommands(
        const OCLRT::DispatchInfo &dispatchInfo,
        const MultiDispatchInfo &multiDispatchInfo,
        HwTimeStamps *hwTimeStamps,
        OCLRT::HwPerfCounter *hwPerfCounter,
        OCLRT::LinearStream *commandStream,
        CommandQueue &commandQueue) = 0;

    virtual void dispatchProfilingPerfEndCommands(
        HwTimeStamps *hwTimeStamps,
        OCLRT::HwPerfCounter *hwPerfCounter,
        OCLRT::LinearStream *commandStream,
        CommandQueue &commandQueue) = 0;
};

template <typename GfxFamily>
class BaseInterfaceVersion : public HardwareInterface<GfxFamily> {
    using INTERFACE_DESCRIPTOR_DATA = typename GfxFamily::INTERFACE_DESCRIPTOR_DATA;

    void getDefaultDshSpace(
        const size_t &offsetInterfaceDescriptorTable,
        CommandQueue &commandQueue,
        const MultiDispatchInfo &multiDispatchInfo,
        size_t &totalInterfaceDescriptorTableSize,
        OCLRT::Kernel *parentKernel,
        OCLRT::IndirectHeap *dsh,
        OCLRT::LinearStream *commandStream) override;

    INTERFACE_DESCRIPTOR_DATA *obtainInterfaceDescriptorData(
        WALKER_HANDLE pCmdData) override;

    void setOffsetCrossThreadData(
        WALKER_HANDLE pCmdData,
        size_t &offsetCrossThreadData,
        uint32_t &interfaceDescriptorIndex) override;

    void dispatchWorkarounds(
        OCLRT::LinearStream *commandStream,
        CommandQueue &commandQueue,
        OCLRT::Kernel &kernel,
        const bool &enable) override;

    void dispatchProfilingPerfStartCommands(
        const OCLRT::DispatchInfo &dispatchInfo,
        const MultiDispatchInfo &multiDispatchInfo,
        HwTimeStamps *hwTimeStamps,
        OCLRT::HwPerfCounter *hwPerfCounter,
        OCLRT::LinearStream *commandStream,
        CommandQueue &commandQueue) override;

    void dispatchProfilingPerfEndCommands(
        HwTimeStamps *hwTimeStamps,
        OCLRT::HwPerfCounter *hwPerfCounter,
        OCLRT::LinearStream *commandStream,
        CommandQueue &commandQueue) override;
};

} // namespace OCLRT