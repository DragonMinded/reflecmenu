# ReflecMenu

A launcher menu for Reflec Beat that uses the touch panel to select games.

Includes a Visual Studio 2008 solution that compiles to a static executable which runs on XPE, suitable for use on a Reflec Beat cabinet.

The ini file format is simple. For each game, there should be a section which is the game name. For each section, there should be a "launch" key which points to the full path of the executable or batch file to execute when selecting this option. An example is below:

```
[Colette]
launch=D:\MBR-colette\contents\gamestart.bat

[Groovin'!!]
launch=D:\MBR-groovin\contents\gamestart.bat

[Volzza]
launch=D:\MBR-volzza\contents\gamestart.bat
```

To correctly execute the built code, run the executable with one parameter specifying the location of the INI file. An example invocation is as follows:

```
ReflecMenu.exe games.ini
```