#pragma once
class IInspectorEditable {
public:
    virtual ~IInspectorEditable() = default;

    virtual const char* GetLabel() const = 0;

    // Draw ImGui controls into a temporary buffer
    virtual void DrawInspectorUI() = 0;

    // Whether Apply should be enabled
    virtual bool HasPendingChanges() const = 0;

    // Commit buffered changes into engine data
    virtual void ApplyChanges() = 0;

    virtual bool WantsDelete() const { return false; } //for deletion
};

