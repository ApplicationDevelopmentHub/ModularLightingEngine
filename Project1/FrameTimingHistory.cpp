#include "FrameTimingHistory.h"
#include <algorithm>

FrameTimingHistory::FrameTimingHistory(float warmupSeconds)
    : warmupSeconds(warmupSeconds) {
}

void FrameTimingHistory::Push(float cpuMs, float gpuMs, float deltaSeconds) {
    elapsedSeconds += deltaSeconds;

    cpuTimesMs.push_back(cpuMs);
    gpuTimesMs.push_back(gpuMs);

    if (cpuTimesMs.size() > MaxSamples)
        cpuTimesMs.pop_front();

    if (gpuTimesMs.size() > MaxSamples)
        gpuTimesMs.pop_front();

    // Only track worst AFTER warmup
    if (elapsedSeconds >= warmupSeconds) {
        worstCPU = std::max(worstCPU, cpuMs);
        worstGPU = std::max(worstGPU, gpuMs);
    }
}

float FrameTimingHistory::GetCurrentCPU() const {
    return cpuTimesMs.empty() ? 0.0f : cpuTimesMs.back();
}

float FrameTimingHistory::GetCurrentGPU() const {
    return gpuTimesMs.empty() ? 0.0f : gpuTimesMs.back();
}

float FrameTimingHistory::GetCurrentFPS() const {
    float ms = GetCurrentCPU();
    return ms > 0.0f ? 1000.0f / ms : 0.0f;
}

float FrameTimingHistory::GetAvgCPU() const {
    return Average(cpuTimesMs);
}

float FrameTimingHistory::GetAvgGPU() const {
    return Average(gpuTimesMs);
}

float FrameTimingHistory::GetWorstCPU() const {
    return worstCPU;
}

float FrameTimingHistory::GetWorstGPU() const {
    return worstGPU;
}

float FrameTimingHistory::GetWorstFPS() const {
    float worst = std::max(worstCPU, worstGPU);
    return worst > 0.0f ? 1000.0f / worst : 0.0f;
}

bool FrameTimingHistory::HasData() const {
    return !cpuTimesMs.empty();
}

bool FrameTimingHistory::IsWarmupComplete() const {
    return elapsedSeconds >= warmupSeconds;
}

float FrameTimingHistory::Average(const std::deque<float>& values) {
    if (values.empty()) return 0.0f;
    float sum = 0.0f;
    for (float v : values) sum += v;
    return sum / static_cast<float>(values.size());
}

float FrameTimingHistory::GetElapsedSeconds() const {
    return elapsedSeconds;
}