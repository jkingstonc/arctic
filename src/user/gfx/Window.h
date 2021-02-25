#pragma once

#include <util/Ref.h>
#include <util/String.h>
#include <util/Malloc.h>


#include <user/gfx/Theme.h>
#include <user/gfx/Context.h>

namespace GFX{

    class Window{
    public:
        Ref<Window> create(){
            Window* window = (Window*)malloc(sizeof(Window));
            return Ref<Window>(window);
        }

        Ref<Window> create(String title, Ref<Context> context){
            Window* window = (Window*)malloc(sizeof(Window));
            window->set_title(title);
            window->context = context;
            return Ref<Window>(window);
        }

        void set_title(String title){
            m_title=title;
        }

        Ref<Context> context(){
            return m_context;
        }

    private:
        Ref<Context> m_context;
        WinTheme m_theme;
        String m_title;
    };

}
