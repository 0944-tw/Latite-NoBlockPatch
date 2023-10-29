#include "pch.h"
#include "ClientInstance.h"
#include "util/Util.h"

SDK::ClientInstance* SDK::ClientInstance::instance = nullptr;

SDK::ClientInstance* SDK::ClientInstance::get() {
    if (!instance) {
        static auto sig = Signatures::Misc::clientInstance.result;
        uintptr_t evalPtr = *reinterpret_cast<uintptr_t*>(sig);
        if (!evalPtr) return nullptr;
        evalPtr = *reinterpret_cast<uintptr_t*>(evalPtr);

#ifdef LATITE_BETA
        int offs = Latite::get().cInstOffs + 0x10;
        if (SDK::internalVers == V1_19_51) {
            offs = Latite::get().cInstOffs2 + 0x10;
        }
#else
        int offs = 0x58;
        if (SDK::internalVers == SDK::V1_19_51) offs = 0x48;
#endif

        evalPtr = *reinterpret_cast<uintptr_t*>(evalPtr + offs);
        if (SDK::internalVers > SDK::V1_19_51) instance = *reinterpret_cast<ClientInstance**>(evalPtr);
        else instance = reinterpret_cast<ClientInstance*>(evalPtr);
    }
    return instance;
}

SDK::BlockSource* SDK::ClientInstance::getRegion() {
    if (SDK::internalVers == SDK::V1_18_12 || SDK::internalVers == SDK::V1_19_51) {
        return memory::callVirtual<BlockSource*>(this, 0x17);
    }
    return memory::callVirtual<BlockSource*>(this, 0x1A);
}


SDK::LocalPlayer* SDK::ClientInstance::getLocalPlayer() {
#ifdef LATITE_BETA
    int offs = Latite::get().plrOffs;
    if (SDK::internalVers <= V1_19_51) {
        offs = Latite::get().cInstOffs2;
    }

    return memory::callVirtual<LocalPlayer*>(this, offs);
#else
    if (SDK::internalVers == SDK::V1_18_12 || SDK::internalVers == SDK::V1_19_51) {
        return memory::callVirtual<LocalPlayer*>(this, 0x18);
    }
    return memory::callVirtual<LocalPlayer*>(this, 0x1B);
#endif
}

SDK::GuiData* SDK::ClientInstance::getGuiData() {
    switch (internalVers) {
    case VLATEST:
        return util::directAccess<GuiData*>(this, 0x560);
    case V1_18_12:
        return memory::callVirtual<GuiData*>(this, 0xCE);
    case V1_19_51:
        return util::directAccess<GuiData*>(this, 0x500);
    }
    return nullptr;
}

void SDK::ClientInstance::grabCursor() {
    if (internalVers == V1_18_12) {
        // 1.18.12
        memory::callVirtual<void>(this, 0x116);
        return;
    }
    reinterpret_cast<void(__fastcall*)(void*)>(Signatures::ClientInstance_grabCursor.result)(this);
}

//vtable call:
//48 8b 80 ? ? ? ? 48 8b ce ff 15 ? ? ? ? 84 db
void SDK::ClientInstance::releaseCursor() {
    if (internalVers == V1_18_12) {
        // 1.18.12
        memory::callVirtual<void>(this, 0x117);
        return;
    }
    reinterpret_cast<void(__fastcall*)(void*)>(Signatures::ClientInstance_releaseCursor.result)(this);
}
