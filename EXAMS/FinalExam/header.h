//header.h

#define NOT_READY -1
#define FILLED 0
#define TAKEN 1
#define GO 2
#define STOP 3

struct student {
        int value1;
        int value2;
};

struct Memory {
        int status;
        int gostop;
        struct student data;
};

