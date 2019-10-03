//#include "bgfx/bgfx.h"
//#include "Window.hpp"
//
//Window g_MainWindow;
//
//LRESULT MyProcHandler(HWND handle, UINT message, WPARAM wparam, LPARAM lparam)
//{
//    switch (message)
//    {
//    case WM_DESTROY:
//        PostQuitMessage(0);
//        return 0;
//    }
//
//    return ::DefWindowProcA(handle, message, wparam, lparam);
//}
//
//void mainLoop();
//void mainUpdate();
//
//int main()
//{
//    HINSTANCE hInstance = GetModuleHandleA(NULL);
//
//    g_MainWindow = Window{ hInstance, "MyWindow", 800, 600, "MyWindowClass", &MyProcHandler, nullptr };
//
//    bgfx::Resolution resolution;
//    resolution.width = 800;
//    resolution.height = 600;
//    resolution.format = bgfx::TextureFormat::RGBA8;
//    resolution.numBackBuffers = 2;
//
//    bgfx::Init initStruct{};
//    initStruct.type = bgfx::RendererType::Vulkan;
//    initStruct.resolution = resolution;
//    initStruct.debug = true;
//    initStruct.profile = true;
//    initStruct.platformData.nwh = g_MainWindow.NativeHandle();
//
//
//
//    bgfx::init(initStruct);
//
//    mainLoop();
//
//    bgfx::shutdown();
//
//    return 0;
//}
//
//void mainLoop()
//{
//    MSG message{};
//    message.message = WM_NULL;
//
//    while (message.message != WM_QUIT) {
//        if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE)) {
//            TranslateMessage(&message);
//            DispatchMessage(&message);
//        }
//        else {
//            mainUpdate();
//            bgfx::frame();
//        }
//    }
//}
//
//void mainUpdate()
//{
//
//}
//

/*
 * Copyright 2011-2019 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include <bx/uint32_t.h>
#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"

namespace
{

float g_Vertices[] =
{
    -0.5f, -0.5f, 0.0f, 0xff000000,
     0.5f, -0.5f, 0.0f, 0xffff0000,
     0.0f,  0.5f, 0.0f, 0x0000ff00
};

bgfx::VertexBufferHandle g_VertexBuffer;
bgfx::ProgramHandle g_Program;

class ExampleHelloWorld : public entry::AppI
{
public:
    ExampleHelloWorld(const char* _name, const char* _description, const char* _url)
        : entry::AppI(_name, _description, _url)
    {
    }

    void init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) override
    {
        Args args(_argc, _argv);

        m_width = _width;
        m_height = _height;
        m_debug = BGFX_DEBUG_TEXT;
        m_reset = BGFX_RESET_VSYNC;

        bgfx::Init init;
        init.type = args.m_type;
        init.vendorId = args.m_pciId;
        init.resolution.width = m_width;
        init.resolution.height = m_height;
        init.resolution.reset = m_reset;
        bgfx::init(init);

        // Enable debug text.
        bgfx::setDebug(m_debug);

        // Set view 0 clear state.
        bgfx::setViewClear(0
            , BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
            , 0x303030ff
            , 1.0f
            , 0
        );

        imguiCreate();

        bgfx::VertexLayout vLayout;
        vLayout
            .begin()
            .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
            .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8)
            .end();

        //bgfx::VertexLayoutHandle vLayoutHandle = bgfx::createVertexLayout(vLayout);
        //bgfx::makeRef(mem, size)
        g_VertexBuffer = bgfx::createVertexBuffer(bgfx::makeRef(g_Vertices, sizeof(g_Vertices)), vLayout);
        g_Program = loadProgram("vs_triangle", "fs_triangle");
    }

    virtual int shutdown() override
    {
        imguiDestroy();

        bgfx::destroy(g_VertexBuffer);
        bgfx::destroy(g_Program);

        // Shutdown bgfx.
        bgfx::shutdown();

        return 0;
    }

    bool update() override
    {
        if (!entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState))
        {
            imguiBeginFrame(m_mouseState.m_mx
                , m_mouseState.m_my
                , (m_mouseState.m_buttons[entry::MouseButton::Left] ? IMGUI_MBUT_LEFT : 0)
                | (m_mouseState.m_buttons[entry::MouseButton::Right] ? IMGUI_MBUT_RIGHT : 0)
                | (m_mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
                , m_mouseState.m_mz
                , uint16_t(m_width)
                , uint16_t(m_height)
            );

            showExampleDialog(this);

            imguiEndFrame();

            bgfx::touch(0);

            bgfx::setViewRect(0, 0, 0, (uint16_t)m_width, (uint16_t)m_height);
            bgfx::setVertexBuffer(0, g_VertexBuffer);
            bgfx::setState(BGFX_STATE_DEFAULT);
            bgfx::submit(0, g_Program);


            bgfx::frame();

            ////////////////
            //// Set view 0 default viewport.
            //bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height));
            //
            //// This dummy draw call is here to make sure that view 0 is cleared
            //// if no other draw calls are submitted to view 0.
            //bgfx::touch(0);
            //
            //// Use debug font to print information about this example.
            //bgfx::dbgTextClear();
            ////bgfx::dbgTextImage(
            ////    bx::max<uint16_t>(uint16_t(m_width / 2 / 8), 20) - 20
            ////    , bx::max<uint16_t>(uint16_t(m_height / 2 / 16), 6) - 6
            ////    , 40
            ////    , 12
            ////    , s_logo
            ////    , 160
            ////);
            //bgfx::dbgTextPrintf(0, 1, 0x0f, "Color can be changed with ANSI \x1b[9;me\x1b[10;ms\x1b[11;mc\x1b[12;ma\x1b[13;mp\x1b[14;me\x1b[0m code too.");
            //
            //bgfx::dbgTextPrintf(80, 1, 0x0f, "\x1b[;0m    \x1b[;1m    \x1b[; 2m    \x1b[; 3m    \x1b[; 4m    \x1b[; 5m    \x1b[; 6m    \x1b[; 7m    \x1b[0m");
            //bgfx::dbgTextPrintf(80, 2, 0x0f, "\x1b[;8m    \x1b[;9m    \x1b[;10m    \x1b[;11m    \x1b[;12m    \x1b[;13m    \x1b[;14m    \x1b[;15m    \x1b[0m");
            //
            //const bgfx::Stats* stats = bgfx::getStats();
            //bgfx::dbgTextPrintf(0, 2, 0x0f, "Backbuffer %dW x %dH in pixels, debug text %dW x %dH in characters."
            //    , stats->width
            //    , stats->height
            //    , stats->textWidth
            //    , stats->textHeight
            //);
            //
            //// Advance to next frame. Rendering thread will be kicked to
            //// process submitted rendering primitives.
            //bgfx::frame();

            return true;
        }

        return false;
    }

    entry::MouseState m_mouseState;

    uint32_t m_width;
    uint32_t m_height;
    uint32_t m_debug;
    uint32_t m_reset;
};

} // namespace

ENTRY_IMPLEMENT_MAIN(
    ExampleHelloWorld
    , "user-userproject0"
    , "All kind of stuff here."
    , nullptr
);

