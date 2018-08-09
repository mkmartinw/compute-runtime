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

#include "unit_tests/api/cl_build_program_tests.inl"
#include "unit_tests/api/cl_clone_kernel_tests.inl"
#include "unit_tests/api/cl_compile_program_tests.inl"
#include "unit_tests/api/cl_create_buffer_tests.inl"
#include "unit_tests/api/cl_create_command_queue_tests.inl"
#include "unit_tests/api/cl_create_command_queue_with_properties_tests.inl"
#include "unit_tests/api/cl_create_context_from_type_tests.inl"
#include "unit_tests/api/cl_create_context_tests.inl"
#include "unit_tests/api/cl_create_image_tests.inl"
#include "unit_tests/api/cl_create_kernel_tests.inl"
#include "unit_tests/api/cl_create_kernels_in_program_tests.inl"
#include "unit_tests/api/cl_create_perf_counters_command_queue_tests.inl"
#include "unit_tests/api/cl_create_pipe_tests.inl"
#include "unit_tests/api/cl_create_program_with_binary_tests.inl"
#include "unit_tests/api/cl_create_program_with_built_in_kernels_tests.inl"
#include "unit_tests/api/cl_create_sampler_tests.inl"
#include "unit_tests/api/cl_create_sampler_with_properties_tests.inl"
#include "unit_tests/api/cl_create_sub_buffer_tests.inl"
#include "unit_tests/api/cl_create_sub_devices_tests.inl"
#include "unit_tests/api/cl_create_user_event_tests.inl"
#include "unit_tests/api/cl_enqueue_barrier_tests.inl"
#include "unit_tests/api/cl_enqueue_barrier_with_wait_list_tests.inl"
#include "unit_tests/api/cl_enqueue_copy_buffer_rect_tests.inl"
#include "unit_tests/api/cl_enqueue_copy_buffer_to_image_tests.inl"
#include "unit_tests/api/cl_enqueue_copy_image_tests.inl"
#include "unit_tests/api/cl_enqueue_copy_image_to_buffer_tests.inl"
#include "unit_tests/api/cl_enqueue_fill_buffer_tests.inl"
#include "unit_tests/api/cl_enqueue_fill_image_tests.inl"
#include "unit_tests/api/cl_enqueue_image_tests.inl"
#include "unit_tests/api/cl_enqueue_map_buffer_tests.inl"
#include "unit_tests/api/cl_enqueue_map_image_tests.inl"
#include "unit_tests/api/cl_enqueue_marker_tests.inl"
#include "unit_tests/api/cl_enqueue_marker_with_wait_list_tests.inl"
#include "unit_tests/api/cl_enqueue_migrate_mem_objects_tests.inl"
#include "unit_tests/api/cl_enqueue_native_kernel_tests.inl"
#include "unit_tests/api/cl_enqueue_nd_range_kernel_tests.inl"
#include "unit_tests/api/cl_enqueue_read_buffer_rect_tests.inl"
#include "unit_tests/api/cl_enqueue_read_buffer_tests.inl"
#include "unit_tests/api/cl_enqueue_read_image_tests.inl"
#include "unit_tests/api/cl_enqueue_svm_free_tests.inl"
#include "unit_tests/api/cl_enqueue_svm_map_tests.inl"
#include "unit_tests/api/cl_enqueue_svm_mem_fill_tests.inl"
#include "unit_tests/api/cl_enqueue_svm_memcpy_tests.inl"
#include "unit_tests/api/cl_enqueue_svm_migrate_mem_tests.inl"
#include "unit_tests/api/cl_enqueue_svm_unmap_tests.inl"
#include "unit_tests/api/cl_enqueue_task_tests.inl"
#include "unit_tests/api/cl_enqueue_unmap_mem_object_tests.inl"
#include "unit_tests/api/cl_enqueue_wait_for_events_tests.inl"
#include "unit_tests/api/cl_enqueue_write_buffer_rect_tests.inl"
#include "unit_tests/api/cl_enqueue_write_buffer_tests.inl"
#include "unit_tests/api/cl_enqueue_write_image_tests.inl"
#include "unit_tests/api/cl_finish_tests.inl"
#include "unit_tests/api/cl_flush_tests.inl"
#include "unit_tests/api/cl_get_context_info_tests.inl"
#include "unit_tests/api/cl_get_device_and_host_timer.inl"
#include "unit_tests/api/cl_get_device_ids_tests.inl"
#include "unit_tests/api/cl_get_device_info_tests.inl"
#include "unit_tests/api/cl_get_event_profiling_info_tests.inl"
#include "unit_tests/api/cl_get_extension_function_address_for_platform_tests.inl"
#include "unit_tests/api/cl_get_extension_function_address_tests.inl"
#include "unit_tests/api/cl_get_image_info_tests.inl"
#include "unit_tests/api/cl_get_image_params_tests.inl"
#include "unit_tests/api/cl_get_kernel_arg_info_tests.inl"
#include "unit_tests/api/cl_get_kernel_info_tests.inl"
#include "unit_tests/api/cl_get_kernel_sub_group_info_khr_tests.inl"
#include "unit_tests/api/cl_get_kernel_sub_group_info_tests.inl"
#include "unit_tests/api/cl_get_kernel_work_group_info_tests.inl"
#include "unit_tests/api/cl_get_mem_object_info_tests.inl"
#include "unit_tests/api/cl_get_pipe_info_tests.inl"
#include "unit_tests/api/cl_get_platform_ids_tests.inl"
#include "unit_tests/api/cl_get_platform_info_tests.inl"
#include "unit_tests/api/cl_get_program_build_info_tests.inl"
#include "unit_tests/api/cl_get_program_info_tests.inl"
#include "unit_tests/api/cl_get_supported_image_formats_tests.inl"
#include "unit_tests/api/cl_icd_get_platform_ids_khr_tests.inl"
#include "unit_tests/api/cl_intel_accelerator_tests.inl"
#include "unit_tests/api/cl_intel_motion_estimation.inl"
#include "unit_tests/api/cl_link_program_tests.inl"
#include "unit_tests/api/cl_release_command_queue_tests.inl"
#include "unit_tests/api/cl_release_context_tests.inl"
#include "unit_tests/api/cl_release_event_tests.inl"
#include "unit_tests/api/cl_release_kernel_tests.inl"
#include "unit_tests/api/cl_release_mem_obj_tests.inl"
#include "unit_tests/api/cl_release_program_tests.inl"
#include "unit_tests/api/cl_retain_mem_obj_tests.inl"
#include "unit_tests/api/cl_retain_release_command_queue_tests.inl"
#include "unit_tests/api/cl_retain_release_context_tests.inl"
#include "unit_tests/api/cl_retain_release_device_tests.inl"
#include "unit_tests/api/cl_retain_release_sampler_tests.inl"
#include "unit_tests/api/cl_set_default_device_command_queue_tests.inl"
#include "unit_tests/api/cl_set_event_callback_tests.inl"
#include "unit_tests/api/cl_set_kernel_arg_svm_pointer_tests.inl"
#include "unit_tests/api/cl_set_kernel_exec_info_tests.inl"
#include "unit_tests/api/cl_set_mem_object_destructor_callback_tests.inl"
#include "unit_tests/api/cl_set_performance_configuration_tests.inl"
#include "unit_tests/api/cl_svm_alloc_tests.inl"
#include "unit_tests/api/cl_svm_free_tests.inl"
#include "unit_tests/api/cl_unload_compiler_tests.inl"
#include "unit_tests/api/cl_unload_platform_compiler_tests.inl"