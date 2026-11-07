@echo off
call "C:\Users\Ryan\miniconda3\Scripts\activate.bat" "C:\Users\Ryan\miniconda3\envs\deep-learning-a2"
if errorlevel 1 (
  echo Could not activate the A2 environment.
  pause
  exit /b 1
)
cd /d "%~dp0A2\code"
echo A2 environment ready. Run: python tests.py
cmd /k
