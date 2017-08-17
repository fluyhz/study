#include "shmcom.h"
using namespace std;

int main(int argc, char ** argv){
	int shmid;
	shmid = shmget(memkey,memsize,0666|IPC_CREAT);
	if(shmid > 0){
		cout<<"create share memory with id "<<shmid<<endl;
	} else {
		cout<<"create share memory failed!"<<endl;
	}
	void *ptr = shmat(shmid,0,0);
	if(ptr == (void*)-1 ){
		cout<<"get ptr failed!"<<endl;
	}
	cout<<(char*)ptr<<endl;
	if(shmdt(ptr) == -1){
		cout<<"shmdt failed"<<endl;
	}
	if(shmctl(shmid,IPC_RMID,0) == -1){
		cout<<"delete failed!"<<endl;
	}
}
