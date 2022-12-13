#define NOT_READY -1
#define FILLED 0 // when sender fills data
#define TAKEN 1 // when receiver takes data
#define GO 2 // when sender keeps sending
#define STOP 3 // when sender stops sending data

struct integers{
	int numbers[5];
	int counter;
};

struct Memory{
	int status;
	int gostop;
	struct integers data;
};