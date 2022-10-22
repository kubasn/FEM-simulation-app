#include <iostream>
#include <math.h>
#include<fstream>
#include <cmath>

using namespace std;



struct node {
	double x, y;
	int BC = 0;
	double tq;
};


struct GlobalElement {
	double W, H, nE, nN;
	int nH, nW, psc;
	double Ro, Cp, alfa, T_alfa;
	double t_calkowity, delta_t;
	GlobalElement() {
		fstream plik;
		plik.open("dane.txt", ios::in);
		if (plik.good()) {

			plik >> W;
			plik >> H;
			plik >> nW;
			plik >> nH;
			plik >> psc;
			plik >> Ro;
			plik >> Cp;
			plik >> alfa;
			plik >> T_alfa;
			plik >> t_calkowity;
			plik >> delta_t;
			nN = nH * nW;
			nE = (nH - 1) * (nW - 1);

		}
		else throw 1;
	}

};

struct Element4 {
	double ksi[4] = { -(sqrt(3.0) / 3.0), (sqrt(3.0) / 3.0), (sqrt(3.0) / 3.0), -(sqrt(3.0) / 3.0) };//////////{ -pc,pc,pc,-pc }; //e
	double eta[4] = { -(sqrt(3.0) / 3.0), -(sqrt(3.0) / 3.0), (sqrt(3.0) / 3.0), (sqrt(3.0) / 3.0) };
	double ksi_3psc[9] = { -sqrt(0.6), 0., sqrt(0.6), -sqrt(0.6), 0., sqrt(0.6), -sqrt(0.6), 0., sqrt(0.6) }; //x
	double eta_3psc[9] = { -sqrt(0.6), -sqrt(0.6), -sqrt(0.6), 0, 0, 0, sqrt(0.6), sqrt(0.6), sqrt(0.6) };   //y
	double ksi_4psc[16] = {
	-sqrt(3.0 / 7.0 - (2.0 / 7.0) * sqrt(6.0 / 5.0)),-sqrt(3.0 / 7.0 + (2.0 / 7.0) * sqrt(6.0 / 5.0)),
	sqrt(3.0 / 7.0 - (2.0 / 7.0) * sqrt(6.0 / 5.0)),sqrt(3.0 / 7.0 + (2.0 / 7.0) * sqrt(6.0 / 5.0)),

	-sqrt(3.0 / 7.0 - (2.0 / 7.0) * sqrt(6.0 / 5.0)),-sqrt(3.0 / 7.0 + (2.0 / 7.0) * sqrt(6.0 / 5.0)),
	sqrt(3.0 / 7.0 - (2.0 / 7.0) * sqrt(6.0 / 5.0)),sqrt(3.0 / 7.0 + (2.0 / 7.0) * sqrt(6.0 / 5.0)),

	-sqrt(3.0 / 7.0 - (2.0 / 7.0) * sqrt(6.0 / 5.0)),-sqrt(3.0 / 7.0 + (2.0 / 7.0) * sqrt(6.0 / 5.0)),
	sqrt(3.0 / 7.0 - (2.0 / 7.0) * sqrt(6.0 / 5.0)),sqrt(3.0 / 7.0 + (2.0 / 7.0) * sqrt(6.0 / 5.0)),

	-sqrt(3.0 / 7.0 - (2.0 / 7.0) * sqrt(6.0 / 5.0)),-sqrt(3.0 / 7.0 + (2.0 / 7.0) * sqrt(6.0 / 5.0)),
	sqrt(3.0 / 7.0 - (2.0 / 7.0) * sqrt(6.0 / 5.0)),sqrt(3.0 / 7.0 + (2.0 / 7.0) * sqrt(6.0 / 5.0)) };
	double eta_4psc[16] = {
	-sqrt(3.0 / 7.0 - (2.0 / 7.0) * sqrt(6.0 / 5.0)),-sqrt(3.0 / 7.0 - (2.0 / 7.0) * sqrt(6.0 / 5.0)),
	-sqrt(3.0 / 7.0 - (2.0 / 7.0) * sqrt(6.0 / 5.0)),-sqrt(3.0 / 7.0 - (2.0 / 7.0) * sqrt(6.0 / 5.0)),
	-sqrt(3.0 / 7.0 + (2.0 / 7.0) * sqrt(6.0 / 5.0)),-sqrt(3.0 / 7.0 + (2.0 / 7.0) * sqrt(6.0 / 5.0)),
	-sqrt(3.0 / 7.0 + (2.0 / 7.0) * sqrt(6.0 / 5.0)),-sqrt(3.0 / 7.0 + (2.0 / 7.0) * sqrt(6.0 / 5.0)),
	sqrt(3.0 / 7.0 - (2.0 / 7.0) * sqrt(6.0 / 5.0)),sqrt(3.0 / 7.0 - (2.0 / 7.0) * sqrt(6.0 / 5.0)),
	sqrt(3.0 / 7.0 - (2.0 / 7.0) * sqrt(6.0 / 5.0)),sqrt(3.0 / 7.0 - (2.0 / 7.0) * sqrt(6.0 / 5.0)),
	sqrt(3.0 / 7.0 + (2.0 / 7.0) * sqrt(6.0 / 5.0)),sqrt(3.0 / 7.0 + (2.0 / 7.0) * sqrt(6.0 / 5.0)),
	sqrt(3.0 / 7.0 + (2.0 / 7.0) * sqrt(6.0 / 5.0)),sqrt(3.0 / 7.0 + (2.0 / 7.0) * sqrt(6.0 / 5.0)),
	};
	/*
	double** tabN_bok_1;
	tabN_bok_1 = (double**)malloc(psc_1 * sizeof(double*));
	for (int i = 0; i < psc_1; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			tabN_bok_1[i] = new double[4];
		}
	}
	*/
	//tabN_bok1[4][4]
	double waga[4] = { 0,0,0,0 };
	double tabN_bok_1[4][4] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	double tabN_bok_2[4][4] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	double tabN_bok_3[4][4] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	double tabN_bok_4[4][4] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	double ksi_bok1[4] = { 0,0,0,0 };
	double ksi_bok2[4] = { 0,0,0,0 };
	double ksi_bok3[4] = { 0,0,0,0 };
	double ksi_bok4[4] = { 0,0,0,0 };

	double eta_bok1[4] = { 0,0,0,0 };
	double eta_bok2[4] = { 0,0,0,0 };
	double eta_bok3[4] = { 0,0,0,0 };
	double eta_bok4[4] = { 0,0,0,0 };

	/*
		double waga[2] = { 0,0};
		double tabN_bok_1[2][4] = { 0,0,0,0,0,0,0,0 };
		double tabN_bok_2[2][4] = { 0,0,0,0,0,0,0,0 };
		double tabN_bok_3[2][4] = { 0,0,0,0,0,0,0,0 };
		double tabN_bok_4[2][4] = { 0,0,0,0,0,0,0,0 };
		double ksi_bok1[2] = { 0,0 };
		double ksi_bok2[2] = { 0,0 };
		double ksi_bok3[2] = { 0,0 };
		double ksi_bok4[2] = { 0,0 };

		double eta_bok1[2] = { 0,0 };
		double eta_bok2[2] = { 0,0 };
		double eta_bok3[2] = { 0,0 };
		double eta_bok4[2] = { 0,0 };
	*/

	void pow_4(int psc) {
		if (psc == 2) {
			for (int i = 0; i < 4; i++)
			{
				waga[i] = 1;
			}
			for (int i = 0; i < 2; i++)
			{
				if (i == 0) {
					ksi_bok1[i] = (-(1.0 / sqrt(3.0)));
					ksi_bok2[i] = 1;
					ksi_bok3[i] = (-(1.0 / sqrt(3.0)));
					ksi_bok4[i] = (-1);

					eta_bok1[i] = (-1);
					eta_bok2[i] = (-(1.0 / sqrt(3.0)));
					eta_bok3[i] = 1;
					eta_bok4[i] = (1.0 / sqrt(3.0));
				}
				if (i == 1) {
					ksi_bok1[i] = ((1.0 / sqrt(3.0)));
					ksi_bok2[i] = 1;
					ksi_bok3[i] = ((1.0 / sqrt(3.0)));
					ksi_bok4[i] = (-1);

					eta_bok1[i] = (-1);
					eta_bok2[i] = ((1.0 / sqrt(3.0)));
					eta_bok3[i] = 1;
					eta_bok4[i] = (-1.0 / sqrt(3.0));
				}
			}
			/*
			 ksi_bok1[2] = { -(1/sqrt(3.0)),(1 / sqrt(3.0)) };
			 ksi_bok2[2] = { 1,1 };
			 ksi_bok3[2] = { -(1/sqrt(3.0)),(1 / sqrt(3.0)) };
			 ksi_bok4[2] = { -1,-1 };
			double eta_bok1[2] = { -1,-1};
			double eta_bok2[2] = { -(1/sqrt(3.0)), (1/sqrt(3.0))};
			double eta_bok3[2] = { 1,1};
			double eta_bok4[2] = { (1/sqrt(3.0)), -(1 /sqrt(3.0))};
			*/

			for (int i = 0; i < 2; i++) {
				tabN_bok_1[i][0] = 0.5 * (1 - ksi_bok1[i]);
				tabN_bok_1[i][1] = 0.5 * (1 + ksi_bok1[i]);
				tabN_bok_1[i][2] = 0;
				tabN_bok_1[i][3] = 0;
			}
			for (int i = 0; i < 2; i++) {
				tabN_bok_2[i][0] = 0;
				tabN_bok_2[i][1] = 0.5 * (1 - eta_bok2[i]);
				tabN_bok_2[i][2] = 0.5 * (1 + eta_bok2[i]);
				tabN_bok_2[i][3] = 0;
			}
			for (int i = 0; i < 2; i++) {
				tabN_bok_3[i][0] = 0;
				tabN_bok_3[i][1] = 0;
				tabN_bok_3[i][2] = 0.5 * (1 - ksi_bok3[i]);
				tabN_bok_3[i][3] = 0.5 * (1 + ksi_bok3[i]);
			}
			for (int i = 0; i < 2; i++) {
				tabN_bok_4[i][0] = 0.5 * (1 - eta_bok4[i]);
				tabN_bok_4[i][1] = 0;
				tabN_bok_4[i][2] = 0;
				tabN_bok_4[i][3] = 0.5 * (1 + eta_bok4[i]);
			}

		}

		if (psc == 3) {
			waga[0] = 5.0 / 9.0;
			waga[1] = 8.0 / 9.0;
			waga[2] = 5.0 / 9.0;
			ksi_bok1[0] = -sqrt(3.0 / 5.0);
			ksi_bok1[1] = 0.0;
			ksi_bok1[2] = sqrt(3.0 / 5.0);
			ksi_bok2[0] = 1.0;
			ksi_bok2[1] = 1.0,
				ksi_bok2[2] = 1.0;
			ksi_bok3[0] = sqrt(3.0 / 5.0);
			ksi_bok3[1] = 0.0;
			ksi_bok3[2] = -sqrt(3.0 / 5.0);
			ksi_bok4[0] = -1.0;
			ksi_bok4[1] = -1.0,
				ksi_bok4[2] = -1.0;

			eta_bok1[0] = -1.0;
			eta_bok1[1] = -1.0;
			eta_bok1[2] = -1.0;
			eta_bok2[0] = -sqrt(3.0 / 5.0);
			eta_bok2[1] = 0.0,
				eta_bok2[2] = sqrt(3.0 / 5.0);
			eta_bok3[0] = 1.0;
			eta_bok3[1] = 1.0;
			eta_bok3[2] = 1.0;
			eta_bok4[0] = sqrt(3.0 / 5.0);
			eta_bok4[1] = 0.0,
				eta_bok4[2] = -sqrt(3.0 / 5.0);

			//ksi_bok2[3] = { 1.0,1.0,1.0 };
			 //ksi_bok3[3] = { sqrt(3.0 / 5.0), 0.0, -sqrt(3.0 / 5.0) };
			 //ksi_bok4[3] = { -1.0,-1.0,-1.0 };

			 //eta_bok1[3] = { -1.0,-1.0,-1.0 };
			 //eta_bok2[3] = { -sqrt(3.0 / 5.0), 0.0,  sqrt(3.0 / 5.0) };
			// eta_bok3[3] = { 1.0,1.0,1.0 };
			// eta_bok4[3] = { sqrt(3.0 / 5.0), 0.0, -sqrt(3.0 / 5.0) };
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 4; j++)
				{
					tabN_bok_1[i][j] = 0;
					tabN_bok_2[i][j] = 0;
					tabN_bok_3[i][j] = 0;
					tabN_bok_4[i][j] = 0;
				}
				// tabN_bok_1[3][4] = { 0,0,0,0,0,0,0,0 };
				 //tabN_bok_2[3][4] = { 0,0,0,0,0,0,0,0 };
				 //tabN_bok_3[3][4] = { 0,0,0,0,0,0,0,0 };
				 //tabN_bok_4[3][4] = { 0,0,0,0,0,0,0,0 };

				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 4; j++) {
						if (j == 0) tabN_bok_1[i][j] = 0.5 * (1 - ksi_bok1[i]);
						if (j == 1) tabN_bok_1[i][j] = 0.5 * (1 + ksi_bok1[i]);
						if (j == 2) tabN_bok_1[i][j] = 0;
						if (j == 3) tabN_bok_1[i][j] = 0;
					}
				}

				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 4; j++) {
						if (j == 0) tabN_bok_2[i][j] = 0;
						if (j == 1) tabN_bok_2[i][j] = 0.5 * (1 - eta_bok2[i]);
						if (j == 2) tabN_bok_2[i][j] = 0.5 * (1 + eta_bok2[i]);
						if (j == 3) tabN_bok_2[i][j] = 0;
					}
				}

				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 4; j++) {
						if (j == 0) tabN_bok_3[i][j] = 0;
						if (j == 1) tabN_bok_3[i][j] = 0;
						if (j == 2) tabN_bok_3[i][j] = 0.5 * (1 - ksi_bok3[i]);
						if (j == 3) tabN_bok_3[i][j] = 0.5 * (1 + ksi_bok3[i]);
					}
				}

				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 4; j++) {
						if (j == 0) tabN_bok_4[i][j] = 0.5 * (1 - eta_bok4[i]);
						if (j == 1) tabN_bok_4[i][j] = 0;
						if (j == 2) tabN_bok_4[i][j] = 0;
						if (j == 3) tabN_bok_4[i][j] = 0.5 * (1 + eta_bok4[i]);
					}
				}


			}
		}
		if (psc == 4) {
			waga[0] = ((18.0 + sqrt(30.0)) / 36.0);
			waga[1] = ((18.0 - sqrt(30.0)) / 36.0);
			waga[2] = ((18.0 + sqrt(30.0)) / 36.0);
			waga[3] = ((18.0 - sqrt(30.0)) / 36.0);

			ksi_bok1[0] = -1.0 * sqrt((3.0 / 7.0) - ((2.0 / 7.0) * sqrt(6.0 / 5.0)));
			ksi_bok1[1] = -1.0 * sqrt((3.0 / 7.0) + ((2.0 / 7.0) * sqrt(6.0 / 5.0)));
			ksi_bok1[2] = sqrt((3.0 / 7.0) - ((2.0 / 7.0) * sqrt(6.0 / 5.0)));
			ksi_bok1[3] = sqrt((3.0 / 7.0) + ((2.0 / 7.0) * sqrt(6.0 / 5.0)));

			ksi_bok2[0] = 1.0;
			ksi_bok2[1] = 1.0,
				ksi_bok2[2] = 1.0;
			ksi_bok2[3] = 1.0;

			ksi_bok3[0] = sqrt((3.0 / 7.0) - ((2.0 / 7.0) * sqrt(6.0 / 5.0)));
			ksi_bok3[1] = sqrt((3.0 / 7.0) + ((2.0 / 7.0) * sqrt(6.0 / 5.0)));
			ksi_bok3[2] = -1.0 * sqrt((3.0 / 7.0) - ((2.0 / 7.0) * sqrt(6.0 / 5.0)));
			ksi_bok3[3] = -1.0 * sqrt((3.0 / 7.0) + ((2.0 / 7.0) * sqrt(6.0 / 5.0)));  //????

			ksi_bok4[0] = -1.0;
			ksi_bok4[1] = -1.0,
				ksi_bok4[2] = -1.0;
			ksi_bok4[3] = -1.0;

			eta_bok1[0] = -1.0;
			eta_bok1[1] = -1.0;
			eta_bok1[2] = -1.0;
			eta_bok1[3] = -1.0;

			eta_bok2[0] = -1.0 * sqrt((3.0 / 7.0) - ((2.0 / 7.0) * sqrt(6.0 / 5.0)));
			eta_bok2[1] = -1.0 * sqrt((3.0 / 7.0) + ((2.0 / 7.0) * sqrt(6.0 / 5.0)));
			eta_bok2[2] = sqrt((3.0 / 7.0) - ((2.0 / 7.0) * sqrt(6.0 / 5.0)));
			eta_bok2[3] = sqrt((3.0 / 7.0) + ((2.0 / 7.0) * sqrt(6.0 / 5.0)));
			eta_bok3[0] = 1.0;
			eta_bok3[1] = 1.0;
			eta_bok3[2] = 1.0;
			eta_bok4[3] = 1.0;

			eta_bok4[0] = sqrt((3.0 / 7.0) - ((2.0 / 7.0) * sqrt(6.0 / 5.0)));
			eta_bok4[1] = sqrt((3.0 / 7.0) + ((2.0 / 7.0) * sqrt(6.0 / 5.0)));
			eta_bok4[2] = -1.0 * sqrt((3.0 / 7.0) - ((2.0 / 7.0) * sqrt(6.0 / 5.0)));
			eta_bok4[3] = -1.0 * sqrt((3.0 / 7.0) + ((2.0 / 7.0) * sqrt(6.0 / 5.0)));

			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (j == 0) tabN_bok_1[i][j] = 0.5 * (1 - ksi_bok1[i]);
					if (j == 1) tabN_bok_1[i][j] = 0.5 * (1 + ksi_bok1[i]);
					if (j == 2) tabN_bok_1[i][j] = 0;
					if (j == 3) tabN_bok_1[i][j] = 0;
				}
			}

			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (j == 0) tabN_bok_2[i][j] = 0;
					if (j == 1) tabN_bok_2[i][j] = 0.5 * (1 - eta_bok2[i]);
					if (j == 2) tabN_bok_2[i][j] = 0.5 * (1 + eta_bok2[i]);
					if (j == 3) tabN_bok_2[i][j] = 0;
				}
			}

			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (j == 0) tabN_bok_3[i][j] = 0;
					if (j == 1) tabN_bok_3[i][j] = 0;
					if (j == 2) tabN_bok_3[i][j] = 0.5 * (1 + ksi_bok3[i]);
					if (j == 3) tabN_bok_3[i][j] = 0.5 * (1 - ksi_bok3[i]);
				}
			}

			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (j == 0) tabN_bok_4[i][j] = 0.5 * (1 - eta_bok4[i]);
					if (j == 1) tabN_bok_4[i][j] = 0;
					if (j == 2) tabN_bok_4[i][j] = 0;
					if (j == 3) tabN_bok_4[i][j] = 0.5 * (1 + eta_bok4[i]);
				}
			}




		}
	}
};



    struct element //do zapisania wynikow ostatecznych
{
	int ID[4] = { 0,0,0,0 };
	double H_local[4][4] = { {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0} };
	double C_local[4][4] = { {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0} };
	double HBC_local[4][4] = { {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0} };
	double P_local[4] = { 0,0,0,0 };
};

////////////funkcje

void matrixH(node Node[], element Element[], int e, int pc, int psc);
void licz_C(node Node[], element Element[], int e, int pc, double ro, double cp, int psc);
void Hbc(node Node[], element Element[], int e, int pc, double alfa, double cp, int psc);
void wektor_P(node Node[], element Element[], int e, int pc, int psc, int alfa, int Talfa);
void oblicz_macierzeLocal(node ND[], element Elem[]);
void solve();







