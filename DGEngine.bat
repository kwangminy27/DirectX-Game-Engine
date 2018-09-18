cd "%~dp0"

xcopy DGEngine\Inc\*.h Engine\Inc\ /d /y
xcopy DGEngine\Inc\*.inl Engine\Inc\ /d /y
xcopy DGEngine\Bin\*.* Engine\Bin\ /d /y /exclude:C:\Users\kwang\source\repos\DIRECT~1\extension.txt
xcopy DGEngine\Bin\*.* DGClient\Bin\ /d /y /exclude:C:\Users\kwang\source\repos\DIRECT~1\extension.txt