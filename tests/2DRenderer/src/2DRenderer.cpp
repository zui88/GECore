#include "Layer.h"

#define ENTRY_POINT
#include "GECore/Core/EntryPoint.h"

// For entry point MANDATORY!!!
std::unique_ptr<GECore::Application> GECore::CreateApplication() {
  auto app = std::make_unique<GECore::Application>("2D Renderer");
  app->pushLayer<TestLayer>();
  return std::move(app);
}
