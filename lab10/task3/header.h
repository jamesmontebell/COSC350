#define NOT_READY -1
#define FILLED 0 // when sender fills data
#define TAKEN 1 // when receiver takes data
#define GO 2 // when sender keeps sending
#define STOP 3 // when sender stops sending data
#define MUTEX 0
#define FULL 1
#define EMPTY 2
#define N 5

union semun1{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

struct Memory{
	int status;
	int gostop;
	int numbers[5];
};
