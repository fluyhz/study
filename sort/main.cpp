#include <iostream>
#include "stdlib.h"
#include "sort.h"
#include <sys/time.h>
#include "string.h"
using namespace std;

void insert_sort(int aa[], int len) {
	for(int i=1;i<len;++i) {
		int key = aa[i];
		int k = i-1;
		while(k>=0 && aa[k]>key) {
			aa[k+1] = aa[k];
			--k;
		}
		aa[k+1] = key;
	}
}

void merge_sort(int aa[], int len) {
	int* bb = new int[len];
	for(int i=0;i<len;++i)
		bb[i] = aa[i];
	merge(aa,bb,0,len-1);
	delete[] bb;
}

void merge(int aa[], int bb[], int left, int right) {
	if(left >= right)
		return;
	int mid = (left+right)/2;
	merge(bb,aa,left,mid);
	merge(bb,aa,mid+1,right);
	merge1(bb,aa,left,right,mid);
}

void merge1(int aa[], int bb[], int left, int right, int mid) {
	int il = left;
	int ir = mid+1;
	for(int i=left;i<right+1;++i) {
		if(aa[il]<aa[ir] && il<mid+1)
			bb[i] = aa[il++];
		else if(ir<right+1)
			bb[i] = aa[ir++];
		else
			bb[i] = aa[il++];
	}
}

void bubble_sort(int aa[], int len) {
	for(int i=0;i<len;++i) {
		for(int j=len;j>i;--j) {
			if(aa[j] < aa[j-1]) {
				int itemp = aa[j];
				aa[j] = aa[j-1];
				aa[j-1] = itemp;
			}
		}
	}
}

void quick_sort(int aa[], int left, int right) {
	if(left >= right)
		return;
	int i = left;
	int j = right;
	int key = aa[i];
	int itemp;
	while(i<j) {
		while(i<j && aa[i]<=key)i++;
		itemp = aa[i];
		aa[i] = aa[j];
		aa[j] = itemp;
		while(i<j && aa[j]>=key)j--;
		itemp = aa[j];
		aa[j] = aa[i];
		aa[i] = itemp;
	}
	quick_sort(aa,left,i-1);
	quick_sort(aa,i+1,right);
}

void outPrint(int aa[], int len) {
	for(int i=0;i<len;++i) {
		cout<<aa[i]<<" ";
	}
	cout<<endl;
}

void randArray(int aa[], int len, int range) {
	srand((unsigned) time(NULL));
	for(int i=0;i<len;++i)
		aa[i] = rand()%range;
}

int main(int argc, char* argv[]) {
	int len = 10;
	int type = 0;
	if(argc == 1)
		cout<<"We use insert_sort now!"<<endl;
	if(argc >= 2){
		if(strcmp(argv[1],"insert") == 0){
			type = 0;
			cout<<"You choose insert_sort!"<<endl;
		} else if(strcmp(argv[1],"merge") == 0){
			type = 1;
			cout<<"You choose merge_sort!"<<endl;
		} else if(strcmp(argv[1],"bubble") == 0){
			type = 2;
			cout<<"You choose bubble_sort!"<<endl;
		} else if(strcmp(argv[1],"quick") == 0){
			type = 3;
			cout<<"You choose quick_sort!"<<endl;
		} else {
			cout<<"Error:you can input insert, merge, bubble or quick to sort!"<<endl;
			return -1;
		}
	}
	if(argc == 3) {
		len = atoi(argv[2]);
		len = (len <= 0)?10:len;
	}
	timeval ts,te;
	int *aa = new int[len];// = {3,7,3,5,8,12,32,6,15,10};
	randArray(aa, len, 10000);
	if(len <= 100){
		cout<<"Before sort:"<<endl;
		outPrint(aa,len);
	}
	gettimeofday(&ts,NULL);
	if(type == 0)
		insert_sort(aa,len);
	else if(type == 1)
		merge_sort(aa,len);
	else if(type == 2)
		bubble_sort(aa,len);
	else
		quick_sort(aa,0,len-1);
	gettimeofday(&te,NULL);
	if(len <= 100){
		cout<<"After sort:"<<endl;
		outPrint(aa,len);
	}
	long dt = (te.tv_sec - ts.tv_sec) * 1000000 + (te.tv_usec-ts.tv_usec);
	cout<<"Using time "<<dt<<"us!"<<endl;
	delete[] aa;
	return 0;
}
