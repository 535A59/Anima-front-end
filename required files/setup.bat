icacls "%~dp0data" /grant "everyone":(OI)(CI)M

@REM if %ERRORLEVEL% NEQ 0 (
@REM     'icacls %~dp0data\ /grant "everyone":(OI)(CI)M'
@REM )


@REM @REM Check if the anima.tar image has been extracted completely yet
@REM :loop1
@REM 2>nul (
@REM     >>"%~dp0/ANIMA.tar" (call )
@REM ) && (echo "not ready") || (goto loop1)

@REM  Download Docker onto computer if doesn't exist already

docker --version
if %ERRORLEVEL% NEQ 0 (
    start /w "" "%~dp0/Docker Desktop Installer.exe" --quiet install
)



@REM TO-DO RUN DOCKER AFTER INSTALLATION TO OPEN IT

@REM Load the docker image

docker image inspect try2

if %ERRORLEVEL% NEQ 0 (
    docker load --input "%~dp0/Anima.tar"
)

@REM --- TODO CHANGE NAME OF DOCKER IMAGE ---

docker ps -a | findstr anima-try-2

if %ERRORLEVEL% NEQ 0 (
    docker run -p 80:80 -v "%~dp0/data:/code/data" --name anima-try-2 try2
) else (
    docker restart anima-try-2
)


@REM :loop2
@REM ping 127.0.0.1
@REM if %ERRORLEVEL% NEQ 0 goto loop2