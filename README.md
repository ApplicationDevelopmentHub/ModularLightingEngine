# ModularLightingEngine
Modular C++ real-time lighting engine that explores XR-relevant rendering constraints through clean abstraction of lighting models, scene data, and rendering backends.

A modular C++ lighting and rendering engine designed to explore real-time illumination concepts relevant to XR systems. The engine cleanly separates scene representation, lighting models, and rendering backends, allowing light sources and shading models to be added or swapped at runtime without changing core engine logic.

The project emphasizes architectural patterns (Strategy, Bridge, Factory) to manage hardware variability, runtime behavior changes, and resource creation—mirroring challenges in XR rendering pipelines such as platform abstraction, performance constraints, and extensibility.

Core features include multiple light types, interchangeable shading models, a scene graph–based layout, and a headless rendering path for validation and testing. The engine is structured to remain renderer-agnostic while supporting a real-time OpenGL backend, making it suitable for experimentation with XR-oriented rendering constraints.
