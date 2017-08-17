#include "shmcom.h"
using namespace std;

int main(int argc, char **argv){
	int shmid;
	shmid = shmget(memkey,memsize,0666|IPC_CREAT);
	if(shmid > 0){
		cout<<"create share memory with id "<<shmid<<endl;
	} else {
		cout<<"create share memory failed!"<<endl;
	}
	void *ptr = shmat(shmid,0,0);
	if(ptr == (void*)-1){
		cout<<"get ptr failed!"<<endl;
	}
	char str[20] = "hello world!";
	memcpy((void*)ptr,str,20);
	if(shmdt(ptr) == -1){
		cout<<"shmat failed!"<<endl;
	}
}
