@echo off

set jqPath=%1
set podStatusJsonPath=%2
set podSelector=%3
set podReplicas=%4
set podDescriptionName=%5

set prevReason=null

:check

kubectl get pods -l %podSelector% -o=jsonpath="{.items}" > %podStatusJsonPath%

type %podStatusJsonPath% | %jqPath% -r ".[] | select(.status.phase == \"Running\")" -e > nil
set isPodPhaseRunning=%ERRORLEVEL%
type %podStatusJsonPath% | %jqPath% -r ".[] | .status.containerStatuses[0].state | has(\"running\")" -e > nil
set isContainerRunning=%ERRORLEVEL%
set readyCount=0
for /f "delims=" %%i in ('type %podStatusJsonPath% ^| %jqPath% -r ".[] | .status.conditions[] | (.type == \"Ready\" and .status == \"True\")" ^| find /c "true"') do (set /a readyCount=%%i)

if %isPodPhaseRunning% == 0 (
    if %isContainerRunning% == 0 (
        if %readyCount% == %podReplicas% (
            echo %podDescriptionName% pod is ready
            EXIT /B 0
        )
    )
)

type %podStatusJsonPath% | %jqPath% -r ".[] | .status.containerStatuses[0].state.waiting | has(\"message\")" -e > nul
set hasMessage=%ERRORLEVEL%

if %hasMessage% == 0 (
    echo ERROR: Something wrong with %podDescriptionName% pod >&2
    goto errorexit
)
goto recheck

:recheck
for /f "delims=" %%a in ('type %podStatusJsonPath% ^| %jqPath% -r ".[] | .status.containerStatuses[0].state.waiting.reason"') do set reason=%%a
if not %reason% == %prevReason% (
    if not %reason% == null (
        echo Waiting for %podDescriptionName% pod to be ready: %reason%
        set prevReason=%reason%
    )
)
timeout /t 1 /nobreak 1>nul 2>&1
goto check

:errorexit
echo ERROR: Please check the pod status %podStatusJsonPath%>&2
EXIT /B 1

