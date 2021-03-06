/*
 * Copyright (C) 2018 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "runtime/command_stream/command_stream_receiver.h"
#include "runtime/command_stream/linear_stream.h"
#include "runtime/helpers/kernel_commands.h"
#include "runtime/helpers/timestamp_packet.h"
#include "runtime/memory_manager/memory_manager.h"
#include "runtime/utilities/tag_allocator.h"

using namespace OCLRT;

TimestampPacketContainer::TimestampPacketContainer(MemoryManager *memoryManager) : memoryManager(memoryManager){};

void TimestampPacketContainer::add(Node *timestampPacketNode) {
    timestampPacketNodes.push_back(timestampPacketNode);
}

TimestampPacketContainer::~TimestampPacketContainer() {
    for (auto &node : timestampPacketNodes) {
        memoryManager->getTimestampPacketAllocator()->returnTag(node);
    }
}

void TimestampPacketContainer::swapNodes(TimestampPacketContainer &timestampPacketContainer) {
    timestampPacketNodes.swap(timestampPacketContainer.timestampPacketNodes);
}

void TimestampPacketContainer::resolveDependencies(bool clearAllDependencies) {
    std::vector<Node *> pendingNodes;

    for (auto &node : timestampPacketNodes) {
        if (node->tag->canBeReleased() || clearAllDependencies) {
            memoryManager->getTimestampPacketAllocator()->returnTag(node);
        } else {
            pendingNodes.push_back(node);
        }
    }

    std::swap(timestampPacketNodes, pendingNodes);
}

void TimestampPacketContainer::assignAndIncrementNodesRefCounts(TimestampPacketContainer &timestampPacketContainer) {
    timestampPacketNodes = timestampPacketContainer.timestampPacketNodes;
    for (auto &node : timestampPacketNodes) {
        node->incRefCount();
    }
}

void TimestampPacketContainer::makeResident(CommandStreamReceiver &commandStreamReceiver) {
    for (auto &node : timestampPacketNodes) {
        commandStreamReceiver.makeResident(*node->getGraphicsAllocation());
    }
}
