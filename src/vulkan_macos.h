#ifndef VULKAN_MACOS_H
#define VULKAN_MACOS_H

#include <iostream>
#include <vector>
#include <vulkan/vulkan.h>

#ifndef VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME
#define VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME
"VK_KHR_portability_enumeration"
#endif

#ifndef VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME
#define VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME
    "VK_KHR_get_physical_device_properties2"
#endif

#ifndef VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME
#define VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME "VK_KHR_portability_subset"
#endif

#ifndef VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR
#define VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR 0x00000001U
#endif

#ifdef __APPLE__

    // Adds required instance extensions for macOS.
    inline void
    addMacOSInstanceRequiredExtensions(std::vector<const char *> &extensions) {
  extensions.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
  extensions.push_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
}

// Sets instance creation flags required for macOS.
inline void setMacOSInstanceCreateFlags(VkInstanceCreateInfo &createInfo) {
  std::cout << "Configuring for macOS: Enabling Portability Enumeration."
            << std::endl;
  createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
}

// Adds required device extensions for macOS.
inline void
addMacOSDeviceRequiredExtensions(std::vector<const char *> &deviceExtensions) {
  deviceExtensions.push_back(VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME);
}

#else

inline void
addMacOSInstanceRequiredExtensions(std::vector<const char *> & /*extensions*/) {
}

inline void setMacOSInstanceCreateFlags(VkInstanceCreateInfo & /*createInfo*/) {
}

inline void addMacOSDeviceRequiredExtensions(
    std::vector<const char *> & /*deviceExtensions*/) {}

#endif // __APPLE__

#endif // VULKAN_MACOS_H