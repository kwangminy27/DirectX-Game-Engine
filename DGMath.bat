cd "%~dp0"

xcopy DGMath\Inc\*.h Math\Inc\ /d /y
xcopy DGMath\Inc\*.inl Math\Inc\ /d /y
xcopy DGMath\Bin\*.* Math\Bin\ /d /y /exclude:C:\Users\kwang\source\repos\DIRECT~1\extension.txt
xcopy DGMath\Bin\*.* DGClient\Bin\ /d /y /exclude:C:\Users\kwang\source\repos\DIRECT~1\extension.txt