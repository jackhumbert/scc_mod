#pragma once

#include "dynArray.hpp"
#include "hashMap.hpp"
#include "name.hpp"
#include "scriptDataLoader.hpp"
#include "string.hpp"

namespace red {

struct IScriptDataObject {
  enum class EMetaType {
    TypeRef = 0,       // 40
    Class = 1,         // A0
    NamedValue = 2,    // 48
    Enum = 3,          // 48
    Bitfield = 4,      //
    Function = 5,      // E0
    FunctionParam = 6, // 48
    FunctionLocal = 7, // 48
    Property = 8,      // C8
    ScriptFile = 9     // 58
  };

  enum class EVisibility : uint8_t { Public = 0, Protected = 1, Private = 2 };

  virtual void *GetAllocator();    // 00
  virtual ~IScriptDataObject();    // 08
  virtual EMetaType GetMetaType(); // 10
  virtual void sub_18();
  virtual void *GetParent();       // 20
  virtual void *GetInternalType(); // 28
  virtual void sub_30();
  virtual void *Write(void *stream); // 38
  virtual void *Read(void *stream);  // 40

  Name name;          // 08
  uint64_t unk10;     // 10
  String *sourceFile; // 18
  uint64_t *unk20;    // 20
};
static_assert(sizeof(IScriptDataObject) == 0x28);

struct ScriptedDataClass;
// Type ref objects are only valid at global scope
struct ScriptedDataTypeRef : IScriptDataObject {

  enum class EScriptType : int {
    Simple = 0x0,
    Cls = 0x1,
    Handle = 0x2,
    WeakHandle = 0x3,
    Array = 0x4,
    NativeArray = 0x5
  };
  uint64_t unk28;                // 28
  ScriptedDataClass *m_internal; // 30
  uint32_t arraySize;            // 38 - used if type == 5
  EScriptType type;              // 3C - set to 1 on init
};
static_assert(sizeof(ScriptedDataTypeRef) == 0x40);

// Class are only valid at global scope (for now)
struct ScriptedDataClass : IScriptDataObject {
  // constexpr static const uintptr_t VFT = 0x2F4FA0;
  // constexpr static const uintptr_t VFT = 0x4A4730;
  constexpr static const uintptr_t VFT = 0x4A4850;

  ScriptedDataClass *parent;                // 30
  DynArray<IScriptDataObject *> properties; // 38
  DynArray<IScriptDataObject *> overrides;  // 48
  DynArray<IScriptDataObject *> functions;  // 58
  HashMap<Name, String> unk68;              // 68
  uint64_t flags1;                          // unk98
  uint64_t flags2;                          // unk99 &= 0x80
};
static_assert(sizeof(ScriptedDataClass) == 0xA0);

// NamedValues are only valid at enum/bitfield scope
struct ScriptedDataNamedValue : IScriptDataObject {};

// Enums are only valid at global scope (for now)
struct ScriptedDataEnum : IScriptDataObject {
  // constexpr static const uintptr_t VFT = 0x2F5040;
  // constexpr static const uintptr_t VFT = 0x4A47D0;
  constexpr static const uintptr_t VFT = 0x4A48F0;
  DynArray<IScriptDataObject *> unk30;
};

// Bitfields are only valid at global scope (for now)
struct ScriptedDataBitfield : IScriptDataObject {};

// Functions are only allowed in global scope and classes
struct ScriptedDataFunction : IScriptDataObject {
  // constexpr static const uintptr_t VFT = 0x2F5130;

  enum class Flags1 : uint8_t {
    is_static = 0x1,
    is_exec = 0x2,
    is_timer = 0x4,
    is_final = 0x8,
    is_native = 0x10,
    // mask 0x20
    unk20 = 0x40,
    unk80 = 0x80
  };

  enum class Flags2 : uint8_t {
    is_operator = 0x1,
    is_cast = 0x2,
    is_implicit_cast = 0x4,
    unk8000 = 0x8,
    unk1_0000 = 0x10,
    unk2_0000 = 0x20,
    is_thread_safe = 0x40,
    unk200_0000 = 0x80
  };

  enum class Flags3 : uint8_t {
    unk10_0000 = 0x1,
    unk20_0000 = 0x2,
    is_quest = 0x2,
    unk80_0000 = 0x8,
    unk100_0000 = 0x10,
    unk200_0000 = 0x20,
    unk400_0000 = 0x40,
    // mask 0x80
  };

  enum class Flags4 : uint8_t { is_callack = 0x80 };

  enum class Flags5 : uint8_t {
    is_const = 0x10,
  };

  enum class ExportFlags : uint32_t {
    is_static = 0x1,
    is_exec = 0x2,
    is_timer = 0x4,
    is_final = 0x8,
    is_native = 0x10,
    unk20 = 0x20, // unk1
    is_callback = 0x40,
    is_operator = 0x80,
    has_return_value = 0x100,
    has_base_method = 0x200,
    has_parameters = 0x400,
    has_locals = 0x800,
    has_body = 0x1000,
    is_cast = 0x2000,
    is_implicit_cast = 0x4000,
    is_thread_safe = 0x40000,
    is_const = 0x80000,
    unk10_0000 = 0x100000, // unk2
    unk20_0000 = 0x200000, // unk3
    is_quest = 0x400000,
    unk80_0000 = 0x800000,   // unk4
    unk100_0000 = 0x1000000, // unk5
    unk200_0000 = 0x2000000, // unk6
  };

  struct Body {
    virtual void sub_00();
    virtual void NextInstr();
    virtual void GetByteCode();
    virtual void sub_18();
    virtual void sub_20();
    virtual void sub_28();
    virtual void sub_30();
    virtual void sub_38();
    virtual void sub_40();
    virtual void sub_48();
    virtual void sub_50();
    virtual void sub_58();
    virtual void sub_60();
    virtual void sub_68();
    virtual void sub_70();
    virtual void sub_78();
    virtual void sub_80();
    virtual void sub_88();
    virtual void read4to8();
    virtual void sub_98();
    virtual void sub_A0();
    virtual void sub_A8();
    virtual void sub_B0();
    virtual void sub_B8();
    virtual void sub_C0();
    virtual void sub_C8();
    virtual void sub_D0();
    virtual void sub_D8();
    virtual void sub_E0();

    ScriptDataLoader *stream;
    uint32_t m_pos;
    uint32_t m_size;
    uint64_t unk18;
  };

  uint64_t unk28;
  IScriptDataObject *parent;
  Name unk38;
  DynArray<IScriptDataObject *> params;       // 40
  DynArray<IScriptDataObject *> locals;       // 50
  HashMap<uint32_t, IScriptDataObject> unk60; // 60
  ScriptedDataTypeRef *returnValue;           // 90
  uint64_t unk98;                             // 98
  uint64_t baseMethod;                        // A0
  Flags1 flags1;                              // A8
  Flags2 flags2;                              // A9
  Flags3 flags3;                              // AA
  Flags4 flags4;                              // AB
  Flags5 flags5;                              // AC
  uint64_t unkB0;                             // B0
  uint8_t unkB8;                              // B8
  EVisibility visibility;                     // B9
  DynArray<uint8_t> body;                     // C0
  DynArray<void *> unkD0;                     // D0
};
static_assert(sizeof(ScriptedDataFunction) == 0xE0);

// Properties are only allowed in classes
struct ScriptedDataProperty : IScriptDataObject {
  uint64_t unk28;                          // 28
  void *parent;                            // 30
  uint64_t unk38;                          // 38
  String unk40;                            // 40
  DynArray<String> defaultClasses;         // 60
  DynArray<String> defaultValues;          // 70
  HashMap<Name, String> runtimeProperties; // 90
  uint64_t unkB0;
  uint64_t unkB8;
};
static_assert(sizeof(ScriptedDataProperty) == 0xC0);

// Function locals are only allowed in functions
struct ScriptedDataFunctionLocal : IScriptDataObject {
  uint64_t unk28;                 // 28
  ScriptedDataFunction *function; // 30
  uint64_t unk38;                 // 38
  uint8_t unk40;
};
static_assert(sizeof(ScriptedDataFunctionLocal) == 0x48);

// Function parameters are only allowed in functions
struct ScriptedDataFunctionParam : IScriptDataObject {
  uint64_t unk28;                 // 28
  ScriptedDataFunction *function; // 30
  uint64_t unk38;                 // 38
  uint8_t unk40;
};
static_assert(sizeof(ScriptedDataFunctionParam) == 0x48);

// Script file objects are only valid at global scope
struct ScriptedDataFileInfo : IScriptDataObject {
  uint32_t unk28;  // 28 - 2th
  uint32_t id;     // 2C - 0th
  uint32_t murmur; // 30 - 1th
  uint32_t unk34;  // 34 unused
  String filename; // 38 - 3th
};
static_assert(sizeof(ScriptedDataFileInfo) == 0x58);

} // namespace red
