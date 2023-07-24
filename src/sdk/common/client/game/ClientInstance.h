#pragma once
#include "sdk/util.h"
#include "util/LMath.h"

namespace sdk {
	class ClientInstance {
	public:
		MVCLASS_FIELD(class MinecraftGame*, minecraftGame, 0xC8, 0xA8);
		MVCLASS_FIELD(class Minecraft*, minecraft, 0xD0, 0xC0);
		MVCLASS_FIELD(class LevelRenderer*, levelRenderer, 0xE0, 0xD0);
		MVCLASS_FIELD(Vec2, cursorPos, 0x498, 0x458);

		static ClientInstance* get();
		class LocalPlayer* getLocalPlayer();

		void grabCursor();
		void releaseCursor();
	private:
		static ClientInstance* instance;
	};
}