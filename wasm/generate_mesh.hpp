#include <iostream>
#include <math.h>
#include<fstream>
#include <cmath>




struct node {
	double x, y;
	int BC = 0;
	double tq;
};


struct GlobalElement {
	double W, H, nE, nN;
	int nH, nW, psc;
	// double Ro, Cp, alfa, T_alfa;
	double T_alfa;
	double t_calkowity, delta_t;
	GlobalElement() {
		// fstream plik;
		// plik.open("data.txt", ios::in);
		// if (plik.good()) {

		// 	plik >> W;
		// 	plik >> H;
		// 	plik >> nW;
		// 	plik >> nH;
		// 	plik >> psc;
		// 	plik >> Ro;
		// 	plik >> Cp;
		// 	plik >> alfa;
		// 	plik >> T_alfa;
		// 	plik >> t_calkowity;
		// 	plik >> delta_t;
		
		W=0.100;
		 H=0.100;
		 nW=4;
		 nH=4;
		 psc=2;
		//  Ro=7800;
		// Cp=700;
		//  alfa=300;
		 T_alfa=1200;
		 t_calkowity=500;
		 delta_t=50;
			nN = nH * nW;
			nE = (nH - 1) * (nW - 1);

		// }
		// else throw 1;
	}

};

struct Element4 {
	double* eta;
	double* ksi;
	double* waga1;
	double* waga2;
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

	void daneHC(int psc) {
		int rozmiar = psc * psc;
		
			ksi = new double[rozmiar];
			eta = new double[rozmiar];
		
			waga1 = new double[rozmiar];
			waga2 = new double[rozmiar];
			for (int i = 0; i < rozmiar; i++) {

				ksi[i] = 0;
				eta[i] = 0;
				waga1[i] = 0;
				waga2[i] = 0;

			}
			
			if (psc == 2)
			{
				double ksi_2psc[4] = { -(sqrt(3.0) / 3.0), (sqrt(3.0) / 3.0), (sqrt(3.0) / 3.0), -(sqrt(3.0) / 3.0) };
				for (int i = 0; i < 4; i++)
				{
					ksi[i] = ksi_2psc[i];
				}
				double eta_2psc[4] = { -(sqrt(3.0) / 3.0), -(sqrt(3.0) / 3.0), (sqrt(3.0) / 3.0), (sqrt(3.0) / 3.0) };
				for (int i = 0; i < 4; i++)
				{
					eta[i] = eta_2psc[i];
				}
				double waga1_2psc[4] = { 1,1,1,1 };
				double waga2_2psc[4] = { 1,1,1,1 };
				for (int i = 0; i < 4; i++)
				{
					waga1[i] = waga1_2psc[i];
				}
				for (int i = 0; i < 4; i++)
				{
					waga2[i] = waga2_2psc[i];
				}
			}
			if (psc == 3)
			{
				double ksi_3psc[9] = { -sqrt(0.6), 0., sqrt(0.6), -sqrt(0.6), 0., sqrt(0.6), -sqrt(0.6), 0., sqrt(0.6) }; //x
				double eta_3psc[9] = { -sqrt(0.6), -sqrt(0.6), -sqrt(0.6), 0, 0, 0, sqrt(0.6), sqrt(0.6), sqrt(0.6) };   //y
				double waga1_3psc[9] = { 5.0 / 9.0, 8.0 / 9.0, 5.0 / 9.0, 5.0 / 9.0, 8.0 / 9.0, 5.0 / 9.0, 5.0 / 9.0, 8.0 / 9.0, 5.0 / 9.0 };
				double waga2_3psc[9] = { 5.0 / 9.0, 5.0 / 9.0, 5.0 / 9.0, 8.0 / 9.0, 8.0 / 9.0, 8.0 / 9.0, 5.0 / 9.0, 5.0 / 9.0, 5.0 / 9.0 };
				for (int i = 0; i < 9; i++)
				{
					
					ksi[i] = ksi_3psc[i];
					eta[i] = eta_3psc[i];
					waga1[i] = waga1_3psc[i];
					waga2[i] = waga2_3psc[i];
				}

			}
			if (psc == 4)
			{
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
			
				double waga1_4psc[16] = {
				(18 + sqrt(30)) / 36,(18 - sqrt(30)) / 36,(18 + sqrt(30)) / 36,(18 - sqrt(30)) / 36,
				(18 + sqrt(30)) / 36,(18 - sqrt(30)) / 36,(18 + sqrt(30)) / 36,(18 - sqrt(30)) / 36,
				(18 + sqrt(30)) / 36,(18 - sqrt(30)) / 36,(18 + sqrt(30)) / 36,(18 - sqrt(30)) / 36,
				(18 + sqrt(30)) / 36,(18 - sqrt(30)) / 36,(18 + sqrt(30)) / 36,(18 - sqrt(30)) / 36 };

				double waga2_4psc[16] = {
					(18 + sqrt(30)) / 36,(18 + sqrt(30)) / 36,(18 + sqrt(30)) / 36,(18 + sqrt(30)) / 36,
					(18 - sqrt(30)) / 36,(18 - sqrt(30)) / 36,(18 - sqrt(30)) / 36,(18 - sqrt(30)) / 36,
					(18 + sqrt(30)) / 36,(18 + sqrt(30)) / 36,(18 + sqrt(30)) / 36,(18 + sqrt(30)) / 36,
					(18 - sqrt(30)) / 36,(18 - sqrt(30)) / 36,(18 - sqrt(30)) / 36,(18 - sqrt(30)) / 36
				};
				for (int i = 0; i < 16; i++)
				{

					ksi[i] = ksi_4psc[i];
					eta[i] = eta_4psc[i];
					waga1[i] = waga1_4psc[i];
					waga2[i] = waga2_4psc[i];
				}

			}
	}

	void pow_4(int psc) {
		if (psc == 2) {
			for (int i = 0; i < 4; i++)
			{
				waga[i] = 1;
			}
			
					ksi_bok1[0] = (-(1.0 / sqrt(3.0)));
					ksi_bok1[1] = ((1.0 / sqrt(3.0)));

					ksi_bok2[0] = 1;
					ksi_bok2[1] = 1;

					ksi_bok3[0] = (-(1.0 / sqrt(3.0)));
					ksi_bok3[1] = ((1.0 / sqrt(3.0)));

					ksi_bok4[0] = (-1);
					ksi_bok4[1] = (-1);

					eta_bok1[0] = (-1);
					eta_bok1[1] = (-1);
					
					eta_bok2[0] = (-(1.0 / sqrt(3.0)));
					eta_bok2[1] = ((1.0 / sqrt(3.0)));
					
					eta_bok3[0] = 1;
					eta_bok3[1] = 1;

					eta_bok4[0] = (1.0 / sqrt(3.0));
					eta_bok4[1] = (-1.0 / sqrt(3.0));
		
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

		
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 4; j++)
				{
					tabN_bok_1[i][j] = 0;
					tabN_bok_2[i][j] = 0;
					tabN_bok_3[i][j] = 0;
					tabN_bok_4[i][j] = 0;
				}
		

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
// extern "C" double* solve(int w);
std::vector<int> solve(double alfa, double cp, double ro, double cond);
// using namespace emscripten;

// EMSCRIPTEN_BINDINGS(my_module) {
//         emscripten::function("runCalculation", &solve);
// }








