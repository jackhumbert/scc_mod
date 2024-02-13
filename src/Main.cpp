#include "Proxies/redlexer_native.hpp"
#include "red/red.hpp"
#include <DetourTransaction.hpp>
#include <winuser.h>

using namespace red;

struct IDK {
  uint64_t unk00;
  uint64_t unk08;
  uint64_t unk10;
  uint64_t unk18;
  uint64_t unk20;
  uint64_t unk28;
  uint64_t unk30;
  uint64_t unk38;
};

struct ScriptCompiledUnk170 {
  HashMap<Name, ScriptedDataClass*> classMap; // 9070 - ChoiceTypeWrapper
  HashMap<Name, ScriptedDataFunction*> functionMap; // 1105 - GetLocalizedItemNameByString
  HashMap<Name, ScriptedDataTypeRef*> typeMap; // 13641 - inkWidgetRef
  DynArray<ScriptedDataFileInfo *> fileInfos; // 1830 script files
  DynArray<ScriptedDataFunction *> functions; // 1005
  DynArray<ScriptedDataEnum*> enums; // 774 enums (396 imported)
  DynArray<IScriptDataObject*> unkC0; // empty
  DynArray<ScriptedDataClass*> classes; // 8296 classes (2513 imported)
  DynArray<ScriptedDataTypeRef*> types; // 13642
  DynArray<IDK> unkF0; // 3510
};

bool ready = false;
DynArray<ScriptedDataFileInfo *> * fileInfos;
std::vector<ScriptedDataEnum*> enums;

/// @pattern 40 55 53 56 57 41 55 41 56 41 57 48 8D AC 24 40 FF FF FF 48 81 EC C0 01 00 00 48 8B F9 4C 8B EA
/// @rva 0x73CE0
/// @rva 0x82180
/// @rva 0x82460
bool __fastcall SaveCompiledScripts(ScriptCompiledUnk170 *a1, __int64 a2);

auto SaveCompiledScripts_Original =
    reinterpret_cast<decltype(&SaveCompiledScripts)>(
        reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr)) + 0x82460);

bool __fastcall SaveCompiledScripts(ScriptCompiledUnk170 *a1, __int64 a2) {
  // Name name_ {
  //   .hash = 0
  // };
  // name_.ToString();
  fileInfos = &a1->fileInfos;

  for (const auto &func : a1->functions) {
    if (!func->parent) {
      auto found = false;
      for (const auto &file : *fileInfos) {
        if (file->filename == *func->sourceFile) {
          func->parent = file;
          found = true;
          break;
        }
      }
      if (!found) {
        __debugbreak();
      }
    }
  }

  ready = true;
  auto result = SaveCompiledScripts_Original(a1, a2);
  ready = false;
  return result;
}

// ScriptedDataClass::GetParent && ScriptedDataEnum::GetParent
/// @pattern 33 C0 C3
/// @rva 0x2C2B0
/// @rva 0x38110
/// @rva 0x38180
__int64 __fastcall UserMathErrorFunction(uintptr_t * a1);

auto UserMathErrorFunction_Original =
    reinterpret_cast<decltype(&UserMathErrorFunction)>(
        reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr)) + 0x38180);

__int64 __fastcall UserMathErrorFunction(uintptr_t * a1) {
  if (ready && a1) {
    if (*a1 == ScriptedDataClass::VFT + reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr))) {
      // ScriptedDataClass
      auto cls = reinterpret_cast<ScriptedDataClass*>(a1);

      for (const auto &file : *fileInfos) {
        if (file->filename == *cls->sourceFile) {
          return (__int64)file;
        }
      }
    } else if (*a1 == ScriptedDataEnum::VFT + reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr))) {
      // ScriptedDataEnum
      auto e = reinterpret_cast<ScriptedDataEnum*>(a1);
      // also runs for GetInternalType, so need to keep track
      if (std::find(enums.begin(), enums.end(), e) == enums.end()) {
        enums.emplace_back(e);
        for (const auto &file : *fileInfos) {
          if (file->filename == *e->sourceFile) {
            return (__int64)file;
          }
        }
      }
    }
  }
  return UserMathErrorFunction_Original(a1);
}

BOOL APIENTRY DllMain(HMODULE aModule, DWORD aReason, LPVOID aReserved) {
  switch (aReason) {
  case DLL_PROCESS_ATTACH: {
    DisableThreadLibraryCalls(aModule);

    try {
      if (!redlexer::LoadOriginal()) {
        return FALSE;
      }
      //            MessageBoxA(nullptr, "Things worked!", "SCC MOD",
      //            MB_ICONINFORMATION | MB_OK);

      DetourTransaction transaction;
      if (!transaction.IsValid()) {
        return false;
      }

      auto base = reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr));

      auto success = DetourAttach(&SaveCompiledScripts_Original,
                                  SaveCompiledScripts) == NO_ERROR;
      auto success2 = DetourAttach(&UserMathErrorFunction_Original,
                                  UserMathErrorFunction) == NO_ERROR;

      if (success && success2) {
        return transaction.Commit();
      }

    } catch (const std::exception &e) {
      auto message = fmt::format(
          "An exception occured in SCC Mod's loader.\n\n{}", e.what());
      MessageBoxA(nullptr, message.c_str(), "SCC MOD", MB_ICONERROR | MB_OK);
    } catch (...) {
      MessageBox(nullptr, L"An unknown exception occured in SCC Mod's loader.",
                 L"SCC Mod", MB_ICONERROR | MB_OK);
    }

    break;
  }
  case DLL_PROCESS_DETACH: {
    break;
  }
  }

  return TRUE;
}