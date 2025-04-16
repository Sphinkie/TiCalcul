@ECHO -------------------------
@ECHO SETUP generation
@ECHO -------------------------

C:\Qt\Tools\QtInstallerFramework\4.9\bin\binarycreator --offline-only -c config/config.xml -p packages TiCalculSetup

pause

REM Operation Testeur:
REM C:\Qt\Tools\QtInstallerFramework\4.9\bin\devtool operation <binary> DO,Copy,<source>,<target>