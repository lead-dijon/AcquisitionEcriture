set PATH=C:\Qt\5.15.2\msvc2019_64\bin;%PATH%


del   /S /Q "C:\pbard\Scientifique\Projets\AcquisitionEcriture\Programmes\logs\*"
del   /S /Q "C:\pbard\Scientifique\Projets\AcquisitionEcriture\Programmes\results\*"

del   /S /Q "C:\pbard\Scientifique\Projets\AcquisitionEcriture\Programmes\AcquisitionEcriture64\*"
rmdir /S /Q "C:\pbard\Scientifique\Projets\AcquisitionEcriture\Programmes\AcquisitionEcriture64\"


mkdir       "C:\pbard\Scientifique\Projets\AcquisitionEcriture\Programmes\AcquisitionEcriture64\"
mkdir       "C:\pbard\Scientifique\Projets\AcquisitionEcriture\Programmes\AcquisitionEcriture64\logs\"
mkdir       "C:\pbard\Scientifique\Projets\AcquisitionEcriture\Programmes\AcquisitionEcriture64\results\"


xcopy /S /Y /V "C:\pbard\Scientifique\Projets\AcquisitionEcriture\Programmes\release\AcquisitionEcriture.exe" "C:\pbard\Scientifique\Projets\AcquisitionEcriture\Programmes\AcquisitionEcriture64\"

xcopy    /Y /V "C:\pbard\Scientifique\Projets\AcquisitionEcriture\Programmes\Labels.csv" "C:\pbard\Scientifique\Projets\AcquisitionEcriture\Programmes\AcquisitionEcriture64\"
xcopy /S /Y /V "C:\pbard\Scientifique\Projets\AcquisitionEcriture\Programmes\cfg\*" "C:\pbard\Scientifique\Projets\AcquisitionEcriture\Programmes\AcquisitionEcriture64\cfg\"


windeployqt.exe "C:\pbard\Scientifique\Projets\AcquisitionEcriture\Programmes\AcquisitionEcriture64"
