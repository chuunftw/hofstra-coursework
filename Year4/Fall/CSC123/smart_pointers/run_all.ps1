$ErrorActionPreference = 'Stop'
$compiler = Get-Command g++ -ErrorAction Stop
$buildDir = Join-Path $PSScriptRoot 'build'
New-Item -ItemType Directory -Path $buildDir -Force | Out-Null
$lessons = Get-ChildItem -LiteralPath $PSScriptRoot -Filter '*.cpp' | Sort-Object Name
if ($lessons.Count -eq 0) { throw 'No lesson files found.' }
foreach ($lesson in $lessons) {
    $outputFile = Join-Path $buildDir ($lesson.BaseName + '.exe')
    Write-Host ("Checking " + $lesson.Name)
    & $compiler.Source -std=c++17 -Wall -Wextra -Werror -pedantic $lesson.FullName -o $outputFile
    if ($LASTEXITCODE -ne 0) { throw ("Compile failed: " + $lesson.Name) }
    & $outputFile
    if ($LASTEXITCODE -ne 0) { throw ("Run failed: " + $lesson.Name) }
}
Write-Host ("All " + $lessons.Count + " lessons passed.")
