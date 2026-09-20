@echo off
rem ============================================================================
rem  CH32H417 逻辑分析仪固件升级工具 —— Windows 一键构建
rem
rem  通过 MSYS2 (D:\msys64) 的 MINGW64 环境调用 build.sh
rem  需要已安装：
rem      pacman -S mingw-w64-x86_64-qt5-static mingw-w64-x86_64-hidapi
rem ============================================================================
setlocal

if "%MSYS2_ROOT%"=="" set "MSYS2_ROOT=D:\msys64"
set "PROJECT_DIR=%~dp0"

if not exist "%MSYS2_ROOT%\msys2_shell.cmd" (
    echo [ERROR] 未找到 MSYS2: %MSYS2_ROOT%\msys2_shell.cmd
    echo         请设置环境变量 MSYS2_ROOT 指向 MSYS2 安装目录。
    goto :failed
)

echo [INFO] MSYS2      : %MSYS2_ROOT%
echo [INFO] 工程目录   : %PROJECT_DIR%
echo [INFO] 开始构建 ...
echo.

"%MSYS2_ROOT%\msys2_shell.cmd" -mingw64 -here -defterm -no-start -c "bash ./build.sh"
if errorlevel 1 goto :failed

echo.
echo [OK] 构建完成，输出目录：%PROJECT_DIR%build
echo.
pause
exit /b 0

:failed
echo.
echo [FAILED] 构建失败
echo.
pause
exit /b 1
