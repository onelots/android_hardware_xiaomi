/*
 * SPDX-FileCopyrightText: 2026 The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <android/hardware/sensors/2.1/types.h>

#include <atomic>

/*
 * Under-display light sensors pick up light emitted by the panel, which the vendor compensation
 * fails to fully remove with bright content on screen. When a rear light sensor is available, it
 * is driven along with the front one, and light events report the brighter of both readings.
 */
namespace android::hardware::sensors::xiaomi {

inline bool isFrontLightSensor(const V2_1::SensorInfo& sensor) {
    return sensor.type == V2_1::SensorType::LIGHT &&
           !(sensor.flags & V1_0::SensorFlagBits::WAKE_UP);
}

inline bool isRearLightSensor(const V2_1::SensorInfo& sensor) {
    return sensor.typeAsString == "xiaomi.sensor.back_lux" &&
           !(sensor.flags & V1_0::SensorFlagBits::WAKE_UP);
}

// Latest rear reading, reset whenever the front sensor is toggled.
inline std::atomic<float> gRearLux = 0;

}  // namespace android::hardware::sensors::xiaomi
