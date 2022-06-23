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

# ReflecMenu 한국어 번역

이 프로젝트는 리플렉비트 기체를 가지고 계신분들을 위해 만들어진 프로젝트입니다.

리플렉비트 기체에 따로 USB 마우스 또는 키보드를 설치하여 게임 버전을 변경하지 않고 기체의 터치패널을 이용하여 게임 버전을 선택할 수 있습니다.

이 프로그램은 Windows XPE 에서 실행되기 때문에 Visual Studio 2017 버전을 이용하여 빌드를 하셔야합니다.
또한, x64로 컴파일을 할 시 리플렉비트 기체에서 실행이 불가능하기 때문에 x86으로 컴파일을 하셔야합니다.

프로그램 사용법은 다음과 같습니다.

1. ReflecMenu를 XPE 32비트에서 실행할 수 있게 컴파일
2. games.ini 작성 -> 작성 방법은 아래 작성해두었습니다.
3. ReflecMenu.exe 파일과 games.ini 파일을 같이 리플렉비트 기체로 옮기기
4. 리플렉비트 기체 작동 시 프로그램이 켜질 수 있도록 .bat 파일 작성 후 기체 작동 시 .bat 파일 실행시키도록 설정
5. 게임 즐기기

games.ini 작성방법은 다음과 같습니다.
1. visual studio code 혹은 다른 텍스트 편집기를 실행합니다.
2. 다음 예시를 복사 후 붙여넣기를 합니다.
```
[Colette]
launch=D:\MBR-colette\contents\gamestart.bat

[Groovin'!!]
launch=D:\MBR-groovin\contents\gamestart.bat

[Volzza]
launch=D:\MBR-volzza\contents\gamestart.bat
```
3. launch= 부분에 gamestart.bat 파일의 경로를 적습니다.
4. 끝

프로그램 작동 배치파일 작성방법은 다음과 같습니다.
1. visual studio code 혹은 다른 텍스트 편집기를 실행합니다.
2. 다음 문장을 복사 후 붙여넣기를 합니다.
```
ReflecMenu.exe games.ini
```
3. 끝

게임 파일 혹은 덤프파일은 알아서 구하세요.
