#include <iostream>

#include <cstring>
#include <ctime>
#include <cstdlib>

/*#include "pokazivaci.h" // */ #include "polje.h"

using namespace std;

void ispisi_ga(moj_klijent & mk)
	{
		cout << "........................................." << endl;
		cout << "Ime: " << mk.ime << endl;
		cout << "Prezime: "<< mk.prezime << endl;
		
		cout << "Datum rodjenja: " << mk.datum << endl;
		
		if(mk.p==1) 	 cout << "Prioritet: Umirovljenici" << endl;
		else if(mk.p==2) cout << "Prioritet: Invalidi" << endl;
		else if(mk.p==3) cout << "Prioritet: Trudnice" << endl;
		else if(mk.p==4) cout << "Prioritet: VIP klijenti" << endl;
		else if(mk.p==5) cout << "Prioritet: Ostali klijenti" << endl;
		else if(mk.p==6) cout << "Prioritet: Nisu klijenti" << endl;
		
		if(mk.t==1) 	 cout << "Vrsta transakcije: Uplata" << endl;
		else if(mk.t==2) cout << "Vrsta transakcije: Isplata" << endl;
		else if(mk.t==3) cout << "Vrsta transakcije: Placanje racuna" << endl;
		else if(mk.t==4) cout << "Vrsta transakcije: Krediti" << endl;
		
		cout << "Stanje na tekucem: " << mk.r_tek << endl;
		cout << "Stanje na deviznom: " << mk.r_dev << endl;
	}

int generiraj_zapise(moj_red * redek)
	{
		int gen_broj;
		
		cout << "Broj zapisa za generirati: ";
		cin>>gen_broj;
		
		moj_klijent nov;
		for(int i=0; i<gen_broj; i++)
			{
				nov.a = rand()%401+100;
				nov.b = rand()%401+100;
				nov.p = rand()%6+1;
				nov.t = rand()%4+1;
				if(nov.p==6) nov.t=3;
				EnQueueQ(nov,redek);
			}
		
		return gen_broj;
	}

void novi_klijenti_unos(moj_red * glavni,moj_red * gen)
	{
		moj_klijent nov;
		while(!IsEmptyQ(gen))
			{
				nov = FrontQ(gen);
				cout << endl;
				cout << "Ime: "; cin>>nov.ime;
				cout << "Prezime: "; cin>>nov.prezime;
				cout << "Datum: "; cin>>nov.datum;
				cout << "Tekuci: "; cin>>nov.r_tek;
				cout << "Devizni: "; cin>>nov.r_dev;
				EnQueueQ(nov,glavni);
				DeQueueQ(gen);
			}
			
		moj_red * pom_redek = new moj_red;
		
		InitQ(pom_redek);
		
		moj_klijent mk;
		while(!IsEmptyQ(glavni))
			{
				mk = FrontQ(glavni);
				EnQueueQ(mk,pom_redek);
				DeQueueQ(glavni);
			}
		while(!IsEmptyQ(pom_redek))
			{
				mk = FrontQ(pom_redek);
				if(mk.r_dev>10000) {
					ispisi_ga(mk);
				}
				EnQueueQ(mk,glavni);
				DeQueueQ(pom_redek);
			}
		delete pom_redek;
	}

void brzi_red_simuliraj(moj_red * glavni)
	{
		moj_red * pom_redek = new moj_red;
		
		InitQ(pom_redek);
		
		moj_klijent mk;
		cout <<endl<< ">> U brzom redu su slijedeci klijenti"<<endl;
		while(!IsEmptyQ(glavni))
			{
				mk = FrontQ(glavni);
				if(mk.t==3)
					{
						ispisi_ga(mk);
					}
				else
					{
						EnQueueQ(mk,pom_redek);
					}
				DeQueueQ(glavni);
			}
		cout <<endl<< ">> U glavnom redu su ostali slijedeci klijenti"<<endl;
		while(!IsEmptyQ(pom_redek))
			{
				mk = FrontQ(pom_redek);
				ispisi_ga(mk);
				EnQueueQ(mk,glavni);
				DeQueueQ(pom_redek);
			}
		delete pom_redek;
	}

void izbrisi_nepotrebne(moj_red * glavni)
	{
		moj_red * pom_redek = new moj_red;
		
		InitQ(pom_redek);
		
		moj_klijent mk;
		cout <<endl<< ">> Iz glavnog reda izasli su slijedeci klijenti"<<endl;
		while(!IsEmptyQ(glavni))
			{
				mk = FrontQ(glavni);
				if((mk.p==4 && mk.datum>=1982 && mk.t==1 && mk.r_tek<100) || (mk.p==1 && mk.t==2 && (mk.r_tek+mk.r_dev)>5000))
					{
						ispisi_ga(mk);
					}
				else
					{
						EnQueueQ(mk,pom_redek);
					}
				DeQueueQ(glavni);
			}
		cout <<endl<< ">> U glavnom redu su ostali slijedeci klijenti"<<endl;
		while(!IsEmptyQ(pom_redek))
			{
				mk = FrontQ(pom_redek);
				ispisi_ga(mk);
				EnQueueQ(mk,glavni);
				DeQueueQ(pom_redek);
			}
		delete pom_redek;
	}

float postotak_od_30_posto;
void otvori_novi_salter_da_ne_bude_guzva(moj_red * glavni,int broj_mk=0,int v1=true)
	{
		if(v1)
			{
				if(IsEmptyQ(glavni))
					{
						cout << endl << ">> Ovi 'pametniji' sto su otisli u novi red" << endl;
						postotak_od_30_posto = broj_mk - ((float)broj_mk / 100 * 30);
						return;
					}	
				moj_klijent mk = FrontQ(glavni);
				DeQueueQ(glavni);
				++broj_mk;
				otvori_novi_salter_da_ne_bude_guzva(glavni,broj_mk);
				
				if(broj_mk>postotak_od_30_posto)
					{
						ispisi_ga(mk);
						--broj_mk;
					}
				else
					{
						--broj_mk;
						EnQueueQ(mk,glavni);
						if(broj_mk==0)
							{
								otvori_novi_salter_da_ne_bude_guzva(glavni,0,false);
								return;
							}
					}
			}
		else
			{
				if(IsEmptyQ(glavni))
					{
						cout << endl << ">> Klijenti ostali u glavnom redu" << endl;
						return;
					}
				moj_klijent mk = FrontQ(glavni);
				DeQueueQ(glavni);
				otvori_novi_salter_da_ne_bude_guzva(glavni,0,false);
				ispisi_ga(mk);
				EnQueueQ(mk,glavni);
			}
	}

void ispis_glavni_da_vidim_ko_mi_je_sve_doso(moj_red * glavni)
	{
		moj_red * pom_redek = new moj_red;
		
		InitQ(pom_redek);
		
		moj_klijent mk;
		while(!IsEmptyQ(glavni))
			{
				mk = FrontQ(glavni);
				EnQueueQ(mk,pom_redek);
				DeQueueQ(glavni);
			}
		cout <<endl<< "U glavnom redu su slijedeci klijenti"<<endl;
		while(!IsEmptyQ(pom_redek))
			{
				mk = FrontQ(pom_redek);
				ispisi_ga(mk);
				EnQueueQ(mk,glavni);
				DeQueueQ(pom_redek);
			}
		delete pom_redek;
	}

int main()
	{
		int od;
		srand(time(0));
		rand();
		
		moj_red * GLAVNI_RED = new moj_red;
		moj_red * GENERIRANI_RED = new moj_red;
		
		InitQ(GLAVNI_RED);
		InitQ(GENERIRANI_RED);
		
		int koliko_nas_ima = 0;
		
		do
			{
				cout << "Izbornik" << endl;
				cout << "-------------------------------" << endl;
				cout << " 1. Generiraj nove klijente" << endl;
				cout << " 2. Dodaj nove klijent u red";
				if(koliko_nas_ima>0)
					cout << " (" << koliko_nas_ima << ")" << endl;
				else cout << endl;
				cout << " 3. Prebaci klijente u brzi red" << endl;
				cout << " 4. Izbrisi nepotrebne iz reda" << endl;
				cout << " 5. Otvori novi salter" << endl;
				cout << "-------------------------------" << endl;
				cout << " 6. Tko je sve u glavnom redu?" << endl;
				cout << " 0. Izlaz" << endl;
				cout << "-------------------------------" << endl;
				cout << "Odabir: ";
				cin >> od;
				
				cout << endl << endl;
				
				switch(od)
					{
						case 0:
							break;
						
						case 1:
							koliko_nas_ima += generiraj_zapise(GENERIRANI_RED);
							break;
						
						case 2:
							if(IsEmptyQ(GENERIRANI_RED))
								{
									cout<<"Nema generiranih :) "<<endl;
									break;
								}
							novi_klijenti_unos(GLAVNI_RED,GENERIRANI_RED);
							koliko_nas_ima = 0;
							break;
						
						case 3:
							if(IsEmptyQ(GLAVNI_RED))
								{
									cout<<"Nema klijenata :) "<<endl;
									break;
								}
							brzi_red_simuliraj(GLAVNI_RED);
							break;
						
						case 4:
							if(IsEmptyQ(GLAVNI_RED))
								{
									cout<<"Nema klijenata :) "<<endl;
									break;
								}
							izbrisi_nepotrebne(GLAVNI_RED);
							break;
						
						case 5:
							if(IsEmptyQ(GLAVNI_RED))
								{
									cout<<"Nema klijenata :) "<<endl;
									break;
								}
							otvori_novi_salter_da_ne_bude_guzva(GLAVNI_RED);
							break;
						
						case 6:
							if(IsEmptyQ(GLAVNI_RED))
								{
									cout<<"Nitko :) "<<endl;
									break;
								}
							ispis_glavni_da_vidim_ko_mi_je_sve_doso(GLAVNI_RED);
							break;
						
						default: cout << "Krivi unos!" << endl;
					}
				
				cout << endl;
			}
		while(od!=0);
		
		
		system("pause");
		return 0;
	}

// hackerma3x (2012)
