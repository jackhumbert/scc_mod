# SCC Source File Info Export

This setup runs `scc.exe` to export script source file info for use with the redscript decompiler ([namely this branch](https://github.com/jackhumbert/redscript/tree/full-decompile) - a binary of this is included at `tools/redscript-cli.exe`) to generate fully decompiled redscript files.

The workflow replaces `tools/redmod/bin/redlexer_native.dll` and expects the old one to exist at `tools/redmod/bin/redlexer_native_real.dll` - the CMake target `compile` does this all automatically (including putting the old one back in place).

Below is the compile command you can run manually to test it out (it creates a `final.redscripts` in the redmod directory):

    scc.exe -compile "C:\Program Files (x86)\Steam\steamapps\common\Cyberpunk 2077\tools\redmod\scripts\" "C:\Program Files (x86)\Steam\steamapps\common\Cyberpunk 2077\tools\redmod\final.redscripts" -rttiSchemaPath "C:\Program Files (x86)\Steam\steamapps\common\Cyberpunk 2077\tools\redmod\metadata.json" -Wnone -threads 4 -no-testonly -no-breakpoint -profile=off 

The `decompile` target uses the included `tools/redscript-cli.exe` to decompile the compiled `final.redscripts` into `redscripts/`.