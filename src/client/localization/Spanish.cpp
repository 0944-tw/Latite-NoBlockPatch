#include "pch.h"
#include "Spanish.h"

Spanish::Spanish() {
    Spanish::strings = {
        { "intro.welcome", L"�Bienvenidos a Latite Client!" },
        { "intro.menubutton", L"Apret�n " + util::StrToWStr(util::KeyToString(Latite::get().getMenuKey().value)) + L" en un mundo o servidor abrir el men� de mods" }
    };
}

std::wstring Spanish::getString(std::string id) {
    return Spanish::strings.at(id);
}