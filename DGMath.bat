cd "%~dp0"

xcopy DGMath\Inc\*.h Math\Inc\ /d /s /y
xcopy DGMath\Inc\*.inl Math\Inc\ /d /s /y
xcopy DGMath\Bin\*.* Math\Bin\ /d /s /y /exclude:C:\Users\kwang\source\repos\DIRECT~1\extension.txt
xcopy DGMath\Bin\*.* DGEngine\Bin\ /d /s /y /exclude:C:\Users\kwang\source\repos\DIRECT~1\extension.txt
xcopy DGMath\Bin\*.* DGClient\Bin\ /d /s /y /exclude:C:\Users\kwang\source\repos\DIRECT~1\extension.txt