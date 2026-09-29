param([switch]$Live)
$ErrorActionPreference = 'Stop'
$projectRoot = Split-Path -Parent $PSScriptRoot
$testRoot = Join-Path $projectRoot ('.artifacts\tests-' + [guid]::NewGuid().ToString('N'))
dotnet build (Join-Path $PSScriptRoot 'ChatGPTMulti.Tests.csproj') -c Release
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
$runner = Join-Path $PSScriptRoot 'bin\Release\net10.0-windows\ChatGPTMulti.Tests.exe'
& $runner core $testRoot
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
& $runner restart $testRoot
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
& $runner split (Join-Path $testRoot 'splits')
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
& $runner split-restart (Join-Path $testRoot 'splits')
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
if ($Live) {
    & $runner live (Join-Path $testRoot 'live')
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
}
Write-Host "Tests passed. Isolated test data: $testRoot"
