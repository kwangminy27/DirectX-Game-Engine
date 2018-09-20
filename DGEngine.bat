cd "%~dp0"

xcopy DGEngine\Inc\*.h Engine\Inc\ /d /s /y
xcopy DGEngine\Inc\*.inl Engine\Inc\ /d /s /y
xcopy DGEngine\Bin\*.* Engine\Bin\ /d /s /y /exclude:C:\Users\kwang\source\repos\DIRECT~1\extension.txt
xcopy DGEngine\Bin\*.* DGClient\Bin\ /d /s /y /exclude:C:\Users\kwang\source\repos\DIRECT~1\extension.txt