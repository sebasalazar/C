# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_DISTDIR=dist
CND_BUILDDIR=build


# Object Directory
OBJECTDIR=${CND_BUILDDIR}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/aes.o \
	${OBJECTDIR}/rsa.o \
	${OBJECTDIR}/utils.o \
	${OBJECTDIR}/hash.o \
	${OBJECTDIR}/cifrado.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
#DEBUG
CFLAGS=-Wall -g3
#Sin Debug
#CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lssl -lcrypto -ldl

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f Makefile ${CND_DISTDIR}/cryptoapp

${CND_DISTDIR}/cryptoapp: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}
	${LINK.c} -o ${CND_DISTDIR}/cryptoapp ${OBJECTFILES} ${LDLIBSOPTIONS} 
	${RM} -fr ${CND_BUILDDIR}
	${RM} -fr core


${OBJECTDIR}/main.o: main.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(CC) $(CFLAGS) -c -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.c
	
	
${OBJECTDIR}/aes.o: aes.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(CC) $(CFLAGS) -c -MMD -MP -MF $@.d -o ${OBJECTDIR}/aes.o aes.c
	
${OBJECTDIR}/rsa.o: rsa.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(CC) $(CFLAGS) -c -MMD -MP -MF $@.d -o ${OBJECTDIR}/rsa.o rsa.c
	
${OBJECTDIR}/utils.o: utils.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(CC) $(CFLAGS) -c -MMD -MP -MF $@.d -o ${OBJECTDIR}/utils.o utils.c

${OBJECTDIR}/hash.o: hash.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(CC) $(CFLAGS) -c -MMD -MP -MF $@.d -o ${OBJECTDIR}/hash.o hash.c

${OBJECTDIR}/cifrado.o: cifrado.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(CC) $(CFLAGS) -c -MMD -MP -MF $@.d -o ${OBJECTDIR}/cifrado.o cifrado.c

# Clean Targets
clean: ${CLEAN_SUBPROJECTS}
	${RM} -fr ${CND_BUILDDIR}
	${RM} -fr ${CND_DISTDIR}
	${RM} -fr core

# Subprojects
.clean-subprojects:


