/*
MIT License

Copyright (c) 2021 - 2023 Aryan Baburajan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include <Core/Error.h>

// #include <Core/Window.h>
// #include <Core/Module.h>
// #include <ECS/SceneManager.h>
// #include <Renderer/Renderer.h>
// #include <Core/InputManager.h>
// #include <Editor.h>


namespace DT
{
    enum class ContextType
    {
        Window,
        Module,
        SceneManager,
        Renderer,
        InputManager,
        Editor
    };
    
    class Context
    {
    public:
        // Window window;
        // Module gameModule;
        // SceneManager sceneManager;
        // Renderer renderer;
        // InputManager input;
        // Editor editor;

        std::filesystem::path projectPath;
        std::unordered_map<std::type_index, void*> services;

        // void AttachService(ContextType type, void *service)
        // {
        //     switch (type)
        //     {
        //     case ContextType::Window:
        //         window(context, projectData.value("window", json::object()), &err);
        //         break;
        //     case ContextType::Module:
        //         AttachService((Module *)service);
        //         break;
        //     case ContextType::SceneManager:
        //         AttachService((SceneManager *)service);
        //         break;
        //     case ContextType::Renderer:
        //         AttachService((Renderer *)service);
        //         break;
        //     case ContextType::InputManager:
        //         AttachService((InputManager *)service);
        //         break;
        //     case ContextType::Editor:
        //         AttachService((Editor *)service);
        //         break;
        //     default:
        //         std::cerr << "[FATAL] Unknown context type.\n";
        //         break;
        //     }
        // }

        template <typename T>
        Error AttachService(T *service)
        {
            PROFILE();

            if (services.find(std::type_index(typeid(T))) != services.end())
                return Error("Service " + std::string(typeid(T).name()) + " already attached.\n");
            services[std::type_index(typeid(T))] = service;
            return Error();
        }

        template <typename T>
        ErrorOr<T *> GetService()
        {
            PROFILE();

            if (services.find(std::type_index(typeid(T))) == services.end())
                return ErrorOr<T *>("Service " + std::string(typeid(T).name()) + " not attached.\n");
            return (T *)services[std::type_index(typeid(T))];
        }
    };
}