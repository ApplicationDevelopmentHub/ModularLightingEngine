#pragma once

#include <deque>
#include <cstddef>

class FrameTimingHistory {
public:
    static constexpr size_t MaxSamples = 120;

    explicit FrameTimingHistory(float warmupSeconds = 10.0f);

    void Push(float cpuMs, float gpuMs, float deltaSeconds);

    float GetElapsedSeconds() const;

    // Current frame
    float GetCurrentCPU() const;
    float GetCurrentGPU() const;

    float GetCurrentFPS() const;

    // Rolling averages
    float GetAvgCPU() const;
    float GetAvgGPU() const;

    // Worst after warmup
    float GetWorstCPU() const;
    float GetWorstGPU() const;
    float GetWorstFPS() const;

    bool HasData() const;
    bool IsWarmupComplete() const;

private:
    std::deque<float> cpuTimesMs;
    std::deque<float> gpuTimesMs;

    float worstCPU = 0.0f;
    float worstGPU = 0.0f;

    float elapsedSeconds = 0.0f;
    float warmupSeconds=0.0f;

    static float Average(const std::deque<float>& values);
};
