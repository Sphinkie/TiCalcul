@ECHO -------------------------
@ECHO SETUP generation
@ECHO -------------------------

del .\packages\sphinkie.ticalcul\data\vc_redist.x64.exe
C:\Qt\Tools\QtInstallerFramework\4.9\bin\binarycreator --offline-only -c config/config.xml -p packages TiCalculSetup

pause

REM Operation Testeur:
REM C:\Qt\Tools\QtInstallerFramework\4.9\bin\devtool operation <binary> DO,Copy,<source>,<target>