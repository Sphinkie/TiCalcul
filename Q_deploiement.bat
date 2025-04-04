@echo Run me in Qt Creator terminal .. "run environnement"

windeployqt --release  .\installeur\packages\sphinkie.ticalcul\data

REM OPTIONS:
REM --pdb :
REM  --dir <directory>                   Use directory instead of binary directory 
REM  --libdir <path>                     Copy libraries to path.
REM  --plugindir <path>                  Copy plugins to path.
REM  --release                           Assume release binaries.
REM  --pdb                               Deploy .pdb files (MSVC).
REM  --compiler-runtime                  Deploy compiler runtime (Desktop only).  
REM
REM ARGUMENT:
REM  [files]                             Binaries or directory containing the binary
REM 
REM EXEMPLE:
REM   windeployqt --pdb tiCalcul.exe --verbose 1 --dir . --plugindir plugins --compiler-runtime


