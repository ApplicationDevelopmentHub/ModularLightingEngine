#pragma once
class IWindow {
public:
	virtual ~IWindow() = default;
	virtual bool Create(int width,int height, const char* title)=0;
	virtual void PollEvents() = 0;
	virtual void SwapBuffers() = 0;
	virtual bool ShouldClose() = 0;
	virtual void* GetNativeHandle() const = 0;
private:
};
