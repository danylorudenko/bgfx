#include <bx/uint32_t.h>
#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"
#include "assimp-importer.h"

namespace
{

float g_Vertices[] =
{
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
     0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
     0.0f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f
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
            .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Float)
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

            // testing assimp importer
            myfunc();


            bgfx::frame();
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

