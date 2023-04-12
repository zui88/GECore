#include "MyLayer.h"

#define ENTRY_POINT
#include "GECore/Core/EntryPoint.h"

struct BatchRendering : public GECore::Application {};

// For entry point MANDATORY!!!
std::unique_ptr<GECore::Application> GECore::CreateApplication() {
  auto app = std::make_unique<BatchRendering>();
  app->pushLayer<MyLayer>();
  return std::move(app);
}
