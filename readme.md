# SCC Source File Info Export

This hooks into `scc.exe` to export script source file info for use with the redscript decompiler.

It replaces `tools/redmod/bin/redlexer_native.dll` and expects the old one to exist at `tools/redmod/bin/old/redlexer_native.dll`.

You can use the VS Code launch to install the .dll file and run the `scc` command, or copy it over and run it yourself (it creates a `final.redscripts` in the redmod directory):

    scc.exe -compile "C:\Program Files (x86)\Steam\steamapps\common\Cyberpunk 2077\tools\redmod\scripts\" "C:\Program Files (x86)\Steam\steamapps\common\Cyberpunk 2077\tools\redmod\final.redscripts" -rttiSchemaPath "C:\Program Files (x86)\Steam\steamapps\common\Cyberpunk 2077\tools\redmod\metadata.json" -Wnone -threads 4 -no-testonly -no-breakpoint -profile=off 