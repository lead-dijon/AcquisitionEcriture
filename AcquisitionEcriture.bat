set PATH=C:\Qt\5.15.2\msvc2019_64\bin;%PATH%


del   /S /Q "C:\pbard\Scientifique\Projets\AcquisitionEcriture\Programmes\logs\*"
del   /S /Q "C:\pbard\Scientifique\Projets\AcquisitionEcriture\Programmes\results\*"

del   /S /Q "C:\pbard\Scientifique\Projets\AcquisitionEcriture\Programmes\AcquisitionEcriture\*"
rmdir /S /Q "C:\pbard\Scientifique\Projets\AcquisitionEcriture\Programmes\AcquisitionEcriture\"


mkdir       "C:\pbard\Scientifique\Projets\AcquisitionEcriture\Programmes\AcquisitionEcriture\"
mkdir       "C:\pbard\Scientifique\Projets\AcquisitionEcriture\Programmes\AcquisitionEcriture\logs\"
mkdir       "C:\pbard\Scientifique\Projets\AcquisitionEcriture\Programmes\AcquisitionEcriture\results\"


xcopy /S /Y /V "C:\pbard\Scientifique\Projets\AcquisitionEcriture\Programmes\release\AcquisitionEcriture.exe" "C:\pbard\Scientifique\Projets\AcquisitionEcriture\Programmes\AcquisitionEcriture\"

xcopy /S /Y /V "C:\pbard\Scientifique\Projets\AcquisitionEcriture\Programmes\cfg\*" "C:\pbard\Scientifique\Projets\AcquisitionEcriture\Programmes\AcquisitionEcriture\cfg\"


windeployqt.exe "C:\pbard\Scientifique\Projets\AcquisitionEcriture\Programmes\AcquisitionEcriture"
