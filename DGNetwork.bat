cd "%~dp0"

xcopy DGNetwork\Inc\*.h Network\Inc\ /d /s /y
xcopy DGNetwork\Inc\*.inl Network\Inc\ /d /s /y
xcopy DGNetwork\Bin\*.* Network\Bin\ /d /s /y /exclude:C:\Users\kwang\source\repos\DIRECT~1\extension.txt
xcopy DGNetwork\Bin\*.* DGClient\Bin\ /d /s /y /exclude:C:\Users\kwang\source\repos\DIRECT~1\extension.txt
xcopy DGNetwork\Bin\*.* DGServer\Bin\ /d /s /y /exclude:C:\Users\kwang\source\repos\DIRECT~1\extension.txt
xcopy DGNetwork\Bin\*.* DGEngine\Bin\ /d /s /y /exclude:C:\Users\kwang\source\repos\DIRECT~1\extension.txt