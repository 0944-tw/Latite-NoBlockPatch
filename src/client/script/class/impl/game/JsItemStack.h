#pragma once
#include "../../JsClass.h"
#include "sdk/common/world/Item.h"
#include "sdk/common/world/ItemStack.h"

class JsItemStack : public JsClass {
protected:
	static JsValueRef CALLBACK jsConstructor(JsValueRef callee, bool isConstructor,
		JsValueRef* arguments, unsigned short argCount, void* callbackState) {
		auto thi = reinterpret_cast<JsItemStack*>(callbackState);

		if (!isConstructor) return thi->errConstructCall();

		Chakra::ThrowError(thi->name + std::wstring(L" cannot be constructed"));
		return JS_INVALID_REFERENCE;
	}

	static JsValueRef CALLBACK toStringCallback(JsValueRef callee, bool isConstructor,
		JsValueRef* arguments, unsigned short argCount, void* callbackState) {
		auto thi = reinterpret_cast<JsItemStack*>(callbackState);
		auto item = ToItemStack(arguments[0]);
		std::string add = std::format("{} (name={}, aux={})", util::WStrToStr(thi->name), item->getHoverName(), item->aux);
		return Chakra::MakeString(L"[object " + util::StrToWStr(add) + L"]");
	}
public:
	JsItemStack(class JsScript* owner) : JsClass(owner, L"ItemStack") {
		createConstructor(jsConstructor, this);
	}

	JsValueRef construct(SDK::ItemStack* item, bool del) {
		JsValueRef obj;
		if (del) {
			JS::JsCreateExternalObject(item, [](void* obj) {
				delete obj;
				}, &obj);
		}
		else {
			JS::JsCreateExternalObject(item, [](void*) {
				}, &obj);
		}
		JS::JsSetPrototype(obj, getPrototype());
		return obj;
	}

	void prepareFunctions() override {
		Chakra::DefineFunc(prototype, toStringCallback, L"toString", this);
	};

	static SDK::ItemStack* ToItemStack(JsValueRef obj) {
		SDK::ItemStack* stack = nullptr;
		JS::JsGetExternalData(obj, reinterpret_cast<void**>(&stack));
		return stack;
	}
};