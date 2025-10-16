# :: Include Paths
INC_PATH="-I${CGT29X_ROOT}/include/c"

# :: Compile Flags
FLAGS="-O1 -gdwarf-3 -DDEBUG"

# ::::: Build Commands ::::::

# :: Build files
${CGT29X_ROOT}/bin/c29clang  ${INC_PATH} ${FLAGS} -c ../*.c

# :: Archive
${CGT29X_ROOT}/bin/c29ar r driverlib.lib *.o

# :: Compile Flags
FLAGS="-O1 -gdwarf-3"

# ::::: Build Commands ::::::

# :: Build files
${CGT29X_ROOT}/bin/c29clang  ${INC_PATH} ${FLAGS} -c ../*.c

# :: Archive
${CGT29X_ROOT}/bin/c29ar r driverlib_release.lib *.o
