#ifndef RED_POLJE_UKLJUCENO
#define RED_POLJE_UKLJUCENO

struct moj_klijent {
	char ime[30],prezime[40];
	int datum;
	float r_tek;
	float r_dev;
	int a,b, p,t;
};

typedef int element;

struct qu {
	moj_klijent elementi[1000];
	element front, rear;
};

typedef qu moj_red;

int AddOne(int n) { return((n+1)%1000); }

moj_klijent FrontQ(moj_red *Q) {
	return Q->elementi[Q->front];
}
void EnQueueQ(moj_klijent x, moj_red *Q) {
	Q->rear = AddOne(Q->rear);
	Q->elementi[Q->rear] = x;
}
void DeQueueQ(moj_red *Q) {
	Q->front = AddOne(Q->front);
}
void InitQ(moj_red *Q) {
	Q->front = 0;
	Q->rear = 999;
}
bool IsEmptyQ(moj_red *Q) {
	if(AddOne(Q->rear) == Q->front)
		return true;
	else
		return false;
}

#endif // RED_POLJE_UKLJUCENO

// hackerma3x (2012)
