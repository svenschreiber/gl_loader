#include <windows.h>

#include "gl_loader/opengl.h"
#include "gl_loader/win32_opengl.c"

static int running = 1;

LRESULT CALLBACK
win32_window_proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam) {
    LRESULT result = 0;

    switch (message) {
        case WM_QUIT:
        case WM_DESTROY:
        case WM_CLOSE: {
            running = 0;
        } break;

        case WM_PAINT: {
            PAINTSTRUCT ps;
            BeginPaint(window, &ps);
            EndPaint(window, &ps);
        } break;

        default: {
            result = DefWindowProc(window, message, wparam, lparam);
        } break;
    }

    return result;
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prev_instance, LPSTR command_line, int show_code) {   

    WNDCLASSA window_class = {0};
    {
        window_class.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        window_class.lpfnWndProc = win32_window_proc;
        window_class.hInstance = instance;
        window_class.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
        window_class.hCursor = LoadCursor(0, IDC_ARROW);
        window_class.lpszClassName = "WindowClass";
    }

    if (RegisterClass(&window_class) == 0)
        return -1;

    HWND window = CreateWindowA(window_class.lpszClassName,
                                "OpenGL Example Window",
                                WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                                CW_USEDEFAULT, CW_USEDEFAULT,
                                800, 600,
                                0, 0, instance, 0);

    if (window == 0)
        return -1;
    
    HDC window_dc = GetDC(window);
    HGLRC opengl_rc;
			
    win32_create_opengl_context(&opengl_rc, window_dc);
    load_gl_functions();
    
    ShowWindow(window, show_code);
    UpdateWindow(window);

    glClearColor(0.2f, 0.2f, 0.25f, 0.0f);
    
    while (running) {
        MSG message;
        while (PeekMessage(&message, 0, 0, 0, PM_REMOVE)) {
            TranslateMessage(&message);
            DispatchMessageA(&message);
        }

        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-0.5f, -0.5f, 0.0f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f( 0.5f, -0.5f, 0.0f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f( 0.0f,  0.5f, 0.0f);
        
        glEnd();

        wglSwapLayerBuffers(window_dc, WGL_SWAP_MAIN_PLANE);
    }

    wglMakeCurrent(window_dc, 0);
    wglDeleteContext(opengl_rc);

    return 0;
}
