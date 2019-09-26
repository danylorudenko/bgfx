#include "bgfx/bgfx.h"
#include "Window.hpp"

Window g_MainWindow;

LRESULT MyProcHandler(HWND handle, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return ::DefWindowProcA(handle, message, wparam, lparam);
}

void mainLoop();

int main()
{
	HINSTANCE hInstance = GetModuleHandleA(NULL);

	g_MainWindow = Window{ hInstance, "MyWindow", 800, 600, "MyWindowClass", &MyProcHandler, nullptr };

	bgfx::Resolution resolution;
	resolution.width = 800;
	resolution.height = 600;
	resolution.format = bgfx::TextureFormat::RGBA8;
	resolution.numBackBuffers = 2;

	bgfx::Init initStruct{};
	initStruct.type = bgfx::RendererType::Vulkan;
	initStruct.resolution = resolution;
	initStruct.debug = true;
	initStruct.profile = true;
	initStruct.platformData.nwh = window.NativeHandle();



	bgfx::init(initStruct);

	mainLoop();

	bgfx::shutdown();

	return 0;
}

void mainLoop()
{
	MSG message{};
	message.message = WM_NULL;

	while (message.message != WM_QUIT) {
		if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else {
			// update
		}
	}
}

