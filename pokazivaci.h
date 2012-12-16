#ifndef RED_POKAZIVACI_UKLJUCENO
#define RED_POKAZIVACI_UKLJUCENO

struct moj_klijent {
	char ime[30],prezime[40];
	int datum;
	float r_tek;
	float r_dev;
	int a,b, p,t;
};

struct qu {
	moj_klijent k;
	qu *sljedeci;
};

struct que {
	qu *front, *rear;
};

typedef qu element;
typedef que moj_red;

moj_klijent FrontQ(moj_red *Q) {
	return Q->front->sljedeci->k;
}
void EnQueueQ(moj_klijent x, moj_red *Q) {
	Q->rear->sljedeci = new element;
	Q->rear = Q->rear->sljedeci;
	Q->rear->sljedeci = NULL;
	Q->rear->k = x;
}
void DeQueueQ(moj_red *Q) {
	element *pom = Q->front;
	Q->front = pom->sljedeci;
	delete pom;
}
void InitQ(moj_red *Q) {
	Q->front = new element;
	Q->rear = Q->front;
}
bool IsEmptyQ(moj_red *Q) {
	if(Q->rear==Q->front)
		return true;
	else
		return false;
}

#endif // RED_POKAZIVACI_UKLJUCENO

// hackerma3x (2012)
