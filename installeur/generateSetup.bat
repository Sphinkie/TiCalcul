@ECHO -------------------------
@ECHO SETUP generation
@ECHO -------------------------

REM Qt Installer Framework v4.6
REM C:\Qt\QtIFW-4.6.1\bin\binarycreator --offline-only -c config/config.xml -p packages TiCalculSetup

REM Qt Installer Framework v4.9
C:\Qt\Tools\QtInstallerFramework\4.9\bin\binarycreator --offline-only -c config/config.xml -p packages TiCalculSetup

pause

REM Operation Testeur:
REM C:\Qt\Tools\QtInstallerFramework\4.9\bin\devtool operation <binary> DO,Copy,<source>,<target>