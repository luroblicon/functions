particle compile --target 0.8.0-rc.11 p1 steppermotormove.ino src\Stepper.h src\Stepper.cpp library.properties --saveTo stepperBin.bin
particle flash 2d0038000351353532373238 stepperBin.bin
