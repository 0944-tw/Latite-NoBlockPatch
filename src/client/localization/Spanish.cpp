#include "pch.h"
#include "Spanish.h"

Spanish::Spanish() {
    Spanish::strings = {
        { L"intro.welcome", L"�Bienvenidos a Latite Client!" },
        { L"intro.menubutton", L"Apret�n " + util::StrToWStr(util::KeyToString(Latite::get().getMenuKey().value)) + L" en un mundo o servidor abrir el men� de mods" }
    };
}

std::wstring Spanish::getString(std::wstring id) {
    return Spanish::strings.at(id);
}