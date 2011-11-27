INCLUDES="-I /home/dalmir/Dropbox/Microcontrollers/picnix/ -I../"
BUILD_DIR=build
TARGET=main
ARCH=-mpic16
CHIP=-p18f4550
LKR="-Wl,-s,/home/dalmir/storage/github/led_cube/custom_linker.lkr"

echo "Making..."

if [ ! -d $BUILD_DIR ]; then
    mkdir $BUILD_DIR
fi

rm $BUILD_DIR/*.c
rm $BUILD_DIR/*.h
cp *.c $BUILD_DIR
cp *.h $BUILD_DIR

cd $BUILD_DIR
echo "Entering in the build dir (${BUILD_DIR})"

echo -n "Compiling..."
sdcc --opt-code-size $LKR $TARGET.c $INCLUDES $ARCH $CHIP

echo "ok."

cp $TARGET.hex ..

cd ..
echo "Exiting the build dir (${BUILD_DIR})"

echo "done."

