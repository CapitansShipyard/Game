HEADERS += \
    fighter.h \
    common.h \
    arena.h \
    sqlite3.h \
    base64.h \
    database.h \
    population.h \
    service.h

SOURCES += \
    arena.cpp \
    sqlite3.c \
    base64.cpp \
    database.cpp \
    population.cpp \
    fighter.cpp \
    service.cpp \
    common.cpp

LIBS += -L/lib64 -l:libdl.so.2
