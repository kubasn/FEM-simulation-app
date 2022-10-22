#include <stdio.h>
#include <iostream>
#include <math.h>
#include<fstream>
#include <cmath>
#include "generate_mesh.hpp"

using namespace std;

double pc = 1 / (sqrt(3));
double wynik[4][4];

//double X3[4]={0,4,4,0};
//double Y3[4]={0,0,6,6};
int psc_1 = 0;
void psc_return(int psc)
{
	psc_1 = psc;
}
double dNdX[4];
double dNdY[4];
double macierzX[4][4];
double macierzY[4][4];
double H1[4][4];
double H2[4][4];
double H3[4][4];
double H4[4][4];
double H[4][4];
double C[4][4] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
double P_local[4] = { 0,0,0,0 };
double Hbc_local[4][4] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
double jacobianMATRIX[2][2];
double jacobianMATRIXodwrotna[2][2];
double waga1_2psc[4] = { 1,1,1,1 };
double waga2_2psc[4] = { 1,1,1,1 };
double waga1_3psc[9] = { 5.0 / 9.0, 8.0 / 9.0, 5.0 / 9.0, 5.0 / 9.0, 8.0 / 9.0, 5.0 / 9.0, 5.0 / 9.0, 8.0 / 9.0, 5.0 / 9.0 };
double waga2_3psc[9] = { 5.0 / 9.0, 5.0 / 9.0, 5.0 / 9.0, 8.0 / 9.0, 8.0 / 9.0, 8.0 / 9.0, 5.0 / 9.0, 5.0 / 9.0, 5.0 / 9.0 };
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

struct SOE {
	int nE;  //e lementow
	int nN;  //l wezlow
	element* Elem;
	double** C_global;
	double* P_global;
	double** H_global;
	double** HBC_global;
	double* T_global;
	double** H_zastepcze;
	double* P_zastepcze;


	void licz_macierzeGlobal() {
		cout << nN << " " << nE;
		H_global = new double* [nN];
		for (int i = 0; i < nN; i++)
		{
		
				H_global[i] = new double[nN];
			
		}

		//double H_global[16][16];  //nE*nE
		for (int i = 0; i < nN; i++) {
			for (int j = 0; j < nN; j++) {
				H_global[i][j] = 0;
			}
		}
		//hbc_global
		HBC_global = new double* [nN];
		for (int i = 0; i < nN; i++)
		{
		
				HBC_global[i] = new double[nN];
			
		}

		//double HBC_global[16][16];  //nE*nE
		for (int i = 0; i < nN; i++) {
			for (int j = 0; j < nN; j++) {
				HBC_global[i][j] = 0;
			}
		}

		//i= elem      
		for (int e = 0; e < nE; e++) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					H_global[Elem[e].ID[i]][Elem[e].ID[j]] += Elem[e].H_local[i][j];
				}
			}
		}
		//double** C_global;
		C_global = new double* [nN];
		for (int i = 0; i < nN; i++)
		{
				C_global[i] = new double[nN];
		
		}

		//double H_global[16][16];  //nE*nE
		for (int i = 0; i < nN; i++) {
			for (int j = 0; j < nN; j++) {
				C_global[i][j] = 0;
			}
		}
		//i= elem      
		for (int e = 0; e < nE; e++) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					C_global[Elem[e].ID[i]][Elem[e].ID[j]] += Elem[e].C_local[i][j];
				}
			}
		}
	
		//hbc global
		//i= elem      
		for (int e = 0; e < nE; e++) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					HBC_global[Elem[e].ID[i]][Elem[e].ID[j]] += Elem[e].HBC_local[i][j] + Elem[e].H_local[i][j];
				}
			}
		}
	
		P_global = new double[nN];

		for (int i = 0; i < nN; i++) {

			P_global[i] = 0;

		}
		for (int e = 0; e < nE; e++) {
			for (int i = 0; i < 4; i++) {
				P_global[Elem[e].ID[i]] += Elem[e].P_local[i];
			}
		}

		//delete[] P_global;
		//delete[] H_global;
		//delete[] HBC_global;
	//	delete[] C_global;
	}
	void inicjalizuj() {
		P_zastepcze = new double[nN];
		for (int i = 0; i < nN; i++) {

			P_zastepcze[i] = 0;
		}
		H_zastepcze = new double* [nN];
		for (int i = 0; i < nN; i++)
		{
			H_zastepcze[i] = new double[nN];

		}

		//double H_global[16][16];  //nE*nE
		for (int i = 0; i < nN; i++) {
			for (int j = 0; j < nN; j++) {
				H_zastepcze[i][j] = 0;
			}
		}
	}
	void Gauss() {
		T_global = new double[nN];
		for (int i = 0; i < nN; i++) {

			T_global[i] = 0;
		}

		for (int i = 0; i < nN - 1; i++)
		{
			for (int j = i + 1; j < nN; j++)
			{

				double q = -H_zastepcze[j][i] / H_zastepcze[i][i];
				for (int k = i; k <= nN; k++)
				{
					H_zastepcze[j][k] += q * H_zastepcze[i][k];
				}
				P_zastepcze[j] += q * P_zastepcze[i];
			}
		}

		T_global[nN] = P_zastepcze[nN - 1] / H_zastepcze[nN - 1][nN - 1];//+10;
		for (int i = nN - 1; i >= 0; i--)
		{
			double pom = 0;
			for (int j = i + 1; j < nN; j++)
			{
				pom += H_zastepcze[i][j] * T_global[j];
			}
			T_global[i] = (P_zastepcze[i] - pom) / H_zastepcze[i][i];

		}
		for (int i = 0; i < nN; i++)
		{
			T_global[i] *= -1;
		}
		cout << "Macierz Gt" << endl;
		for (int i = 0; i < nN; i++)
		{
			cout << "Gt " << i + 1 << " = " << T_global[i] << endl;
		}

	}
};





double detJ()
{
	return jacobianMATRIX[0][0] * jacobianMATRIX[1][1] - jacobianMATRIX[1][0] * jacobianMATRIX[0][1];
}
void jacobianMINUSjeden()
{
	double wyznaczik = detJ();
	jacobianMATRIXodwrotna[0][0] = jacobianMATRIX[1][1] / wyznaczik;
	jacobianMATRIXodwrotna[0][1] = -jacobianMATRIX[0][1] / wyznaczik;
	jacobianMATRIXodwrotna[1][0] = -jacobianMATRIX[1][0] / wyznaczik;
	jacobianMATRIXodwrotna[1][1] = jacobianMATRIX[0][0] / wyznaczik;
}



//////2psc 

void matrixH(node Node[], element Element[], int e, int pc, int psc) {
	if (psc == 2) {
		Element4 elem4;
		//inicjalizacja zmiennych zerami
		double dxksi[4] = { 0,0,0,0 };
		double dyeta[4] = { 0,0,0,0 };
		double dxeta[4] = { 0,0,0,0 };
		double dyksi[4] = { 0,0,0,0 };


		double tabKSI[4][4] = { -0.25 * (1 - elem4.eta[0]), 0.25 * (1 - elem4.eta[0]), 0.25 * (1 + elem4.eta[0]), -0.25 * (1 + elem4.eta[0]),
		 -0.25 * (1 - elem4.eta[1]), 0.25 * (1 - elem4.eta[1]), 0.25 * (1 + elem4.eta[1]), -0.25 * (1 + elem4.eta[1]),
		 -0.25 * (1 - elem4.eta[2]), 0.25 * (1 - elem4.eta[2]), 0.25 * (1 + elem4.eta[2]), -0.25 * (1 + elem4.eta[2]),
		 -0.25 * (1 - elem4.eta[3]), 0.25 * (1 - elem4.eta[3]), 0.25 * (1 + elem4.eta[3]), -0.25 * (1 + elem4.eta[3])
		}; // dN1/dE , dN2/dE , dN3/dE , dN4/dE



		double tabETA[4][4] = {
		 {-0.25 * (1 - elem4.ksi[0]), -0.25 * (1 + elem4.ksi[0]), 0.25 * (1 + elem4.ksi[0]), 0.25 * (1 - elem4.ksi[0])},
		 {-0.25 * (1 - elem4.ksi[1]), -0.25 * (1 + elem4.ksi[1]), 0.25 * (1 + elem4.ksi[1]), 0.25 * (1 - elem4.ksi[1])},
		 {-0.25 * (1 - elem4.ksi[2]), -0.25 * (1 + elem4.ksi[2]), 0.25 * (1 + elem4.ksi[2]), 0.25 * (1 - elem4.ksi[2])},
		 {-0.25 * (1 - elem4.ksi[3]), -0.25 * (1 + elem4.ksi[3]), 0.25 * (1 + elem4.ksi[3]), 0.25 * (1 - elem4.ksi[3])}
		}; // dN1/dN , dN2/dN , dN3/dN , dN4/dN

		jacobianMATRIX[0][0] = Node[Element[e].ID[0]].x * tabKSI[pc][0] + Node[Element[e].ID[1]].x * tabKSI[pc][1] + Node[Element[e].ID[2]].x * tabKSI[pc][2] + Node[Element[e].ID[3]].x * tabKSI[pc][3];
		jacobianMATRIX[0][1] = Node[Element[e].ID[0]].y * tabKSI[pc][0] + Node[Element[e].ID[1]].y * tabKSI[pc][1] + Node[Element[e].ID[2]].y * tabKSI[pc][2] + Node[Element[e].ID[3]].y * tabKSI[pc][3];
		jacobianMATRIX[1][0] = Node[Element[e].ID[0]].x * tabETA[pc][0] + Node[Element[e].ID[1]].x * tabETA[pc][1] + Node[Element[e].ID[2]].x * tabETA[pc][2] + Node[Element[e].ID[3]].x * tabETA[pc][3];
		jacobianMATRIX[1][1] = Node[Element[e].ID[0]].y * tabETA[pc][0] + Node[Element[e].ID[1]].y * tabETA[pc][1] + Node[Element[e].ID[2]].y * tabETA[pc][2] + Node[Element[e].ID[3]].y * tabETA[pc][3];

		double wyznacznik = detJ();
		////////odwrotna macierz Jacobiego//////////
		jacobianMINUSjeden();

		//pochodne
		dNdX[0] = (tabKSI[pc][0] * jacobianMATRIXodwrotna[0][0] + jacobianMATRIXodwrotna[0][1] * (tabETA[pc][0]));
		dNdX[1] = (tabKSI[pc][1] * jacobianMATRIXodwrotna[0][0] + jacobianMATRIXodwrotna[0][1] * (tabETA[pc][1]));
		dNdX[2] = (tabKSI[pc][2] * jacobianMATRIXodwrotna[0][0] + jacobianMATRIXodwrotna[0][1] * (tabETA[pc][2]));
		dNdX[3] = (tabKSI[pc][3] * jacobianMATRIXodwrotna[0][0] + jacobianMATRIXodwrotna[0][1] * (tabETA[pc][3]));

		dNdY[0] = ((tabKSI[pc][0] * (-jacobianMATRIXodwrotna[1][0]) + tabETA[pc][0] * jacobianMATRIXodwrotna[1][1]));
		dNdY[1] = ((tabKSI[pc][1] * (-jacobianMATRIXodwrotna[1][0]) + tabETA[pc][1] * jacobianMATRIXodwrotna[1][1]));
		dNdY[2] = ((tabKSI[pc][2] * (-jacobianMATRIXodwrotna[1][0]) + tabETA[pc][2] * jacobianMATRIXodwrotna[1][1]));
		dNdY[3] = ((tabKSI[pc][3] * (-jacobianMATRIXodwrotna[1][0]) + tabETA[pc][3] * jacobianMATRIXodwrotna[1][1]));

		for (int k = 0; k < 4; k++)
		{
			for (int j = 0; j < 4; j++)
			{
				macierzX[k][j] = dNdX[k] * dNdX[j];
				macierzY[k][j] = dNdY[k] * dNdY[j];
			}

		}

		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				Element[e].H_local[j][k] += (macierzX[j][k] + macierzY[j][k]) * 25 * wyznacznik;
			}
		}
		if (pc == 3) {
		
			
		}
	}


	if (psc == 3) {
		Element4 elem4;
		//inicjalizacja zmiennych zerami
		double dxksi_3psc[9] = { 0,0,0,0,0,0,0,0,0 };
		double dyeta_3psc[9] = { 0,0,0,0,0,0,0,0,0 };
		double dxeta_3psc[9] = { 0,0,0,0,0,0,0,0,0 };
		double dyksi_3psc[9] = { 0,0,0,0,0,0,0,0,0 };

		double tabETA[9][4];
		double tabKSI[9][4];
		for (int i = 0; i < 9; i++) {
			tabKSI[i][0] = -0.25 * (1 - elem4.eta_3psc[i]);
			tabKSI[i][1] = 0.25 * (1 - elem4.eta_3psc[i]);
			tabKSI[i][2] = 0.25 * (1 + elem4.eta_3psc[i]);
			tabKSI[i][3] = -0.25 * (1 + elem4.eta_3psc[i]);
		}
		for (int i = 0; i < 9; i++) {
			tabETA[i][0] = -0.25 * (1 - elem4.ksi_3psc[i]);
			tabETA[i][1] = -0.25 * (1 + elem4.ksi_3psc[i]);
			tabETA[i][2] = 0.25 * (1 + elem4.ksi_3psc[i]);
			tabETA[i][3] = 0.25 * (1 - elem4.ksi_3psc[i]);
		}


		for (int j = 0; j < 4; j++) {
			dxksi_3psc[pc] = dxksi_3psc[pc] + tabKSI[pc][j] * Node[Element[e].ID[j]].x;
		}

		for (int j = 0; j < 4; j++) {
			dyeta_3psc[pc] = dyeta_3psc[pc] + tabETA[pc][j] * Node[Element[e].ID[j]].y;
		}

		for (int j = 0; j < 4; j++) {
			dxeta_3psc[pc] = dxeta_3psc[pc] + tabETA[pc][j] * Node[Element[e].ID[j]].x; //tu nie dziala
		}

		for (int j = 0; j < 4; j++) {
			dyksi_3psc[pc] = dyksi_3psc[pc] + tabKSI[pc][j] * Node[Element[e].ID[j]].y;
		}

		jacobianMATRIX[0][0] = dxksi_3psc[pc];
		jacobianMATRIX[0][1] = dyksi_3psc[pc];
		jacobianMATRIX[1][0] = dxeta_3psc[pc];
		jacobianMATRIX[1][1] = dyeta_3psc[pc];


		//cout << "Wyznacznik Jacobiego dla " << pc + 1 << " punktu calkowania: " << endl;
		//cout << detJ() << endl;
		double wyznacznik = detJ();
		////////odwrotna macierz Jacobiego//////////
		jacobianMINUSjeden();
		dNdX[0] = (tabKSI[pc][0] * jacobianMATRIXodwrotna[0][0] + jacobianMATRIXodwrotna[0][1] * (tabETA[pc][0]));
		dNdX[1] = (tabKSI[pc][1] * jacobianMATRIXodwrotna[0][0] + jacobianMATRIXodwrotna[0][1] * (tabETA[pc][1]));
		dNdX[2] = (tabKSI[pc][2] * jacobianMATRIXodwrotna[0][0] + jacobianMATRIXodwrotna[0][1] * (tabETA[pc][2]));
		dNdX[3] = (tabKSI[pc][3] * jacobianMATRIXodwrotna[0][0] + jacobianMATRIXodwrotna[0][1] * (tabETA[pc][3]));

		dNdY[0] = ((tabKSI[pc][0] * (-jacobianMATRIXodwrotna[1][0]) + tabETA[pc][0] * jacobianMATRIXodwrotna[1][1]));
		dNdY[1] = ((tabKSI[pc][1] * (-jacobianMATRIXodwrotna[1][0]) + tabETA[pc][1] * jacobianMATRIXodwrotna[1][1]));
		dNdY[2] = ((tabKSI[pc][2] * (-jacobianMATRIXodwrotna[1][0]) + tabETA[pc][2] * jacobianMATRIXodwrotna[1][1]));
		dNdY[3] = ((tabKSI[pc][3] * (-jacobianMATRIXodwrotna[1][0]) + tabETA[pc][3] * jacobianMATRIXodwrotna[1][1]));

		for (int k = 0; k < 4; k++)
		{
			for (int j = 0; j < 4; j++)
			{
				macierzX[k][j] = dNdX[k] * dNdX[j];
				macierzY[k][j] = dNdY[k] * dNdY[j];
			}

		}


		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				Element[e].H_local[j][k] += (macierzX[j][k] + macierzY[j][k]) * 25 * wyznacznik * waga1_3psc[pc] * waga2_3psc[pc];
			}
		}
	
	}
	if (psc == 4) {
		Element4 elem4;
		//inicjalizacja zmiennych zerami
		double dxksi_3psc[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
		double dyeta_3psc[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
		double dxeta_3psc[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
		double dyksi_3psc[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

		double tabETA[16][4];
		double tabKSI[16][4];
		for (int i = 0; i < 16; i++) {
			tabKSI[i][0] = -0.25 * (1 - elem4.eta_3psc[i]);
			tabKSI[i][1] = 0.25 * (1 - elem4.eta_3psc[i]);
			tabKSI[i][2] = 0.25 * (1 + elem4.eta_3psc[i]);
			tabKSI[i][3] = -0.25 * (1 + elem4.eta_3psc[i]);
		}
		for (int i = 0; i < 16; i++) {
			tabETA[i][0] = -0.25 * (1 - elem4.ksi_3psc[i]);
			tabETA[i][1] = -0.25 * (1 + elem4.ksi_3psc[i]);
			tabETA[i][2] = 0.25 * (1 + elem4.ksi_3psc[i]);
			tabETA[i][3] = 0.25 * (1 - elem4.ksi_3psc[i]);
		}


		for (int j = 0; j < 4; j++) {
			dxksi_3psc[pc] = dxksi_3psc[pc] + tabKSI[pc][j] * Node[Element[e].ID[j]].x;
		}

		for (int j = 0; j < 4; j++) {
			dyeta_3psc[pc] = dyeta_3psc[pc] + tabETA[pc][j] * Node[Element[e].ID[j]].y;
		}

		for (int j = 0; j < 4; j++) {
			dxeta_3psc[pc] = dxeta_3psc[pc] + tabETA[pc][j] * Node[Element[e].ID[j]].x; //tu nie dziala
		}

		for (int j = 0; j < 4; j++) {
			dyksi_3psc[pc] = dyksi_3psc[pc] + tabKSI[pc][j] * Node[Element[e].ID[j]].y;
		}

		jacobianMATRIX[0][0] = dxksi_3psc[pc];
		jacobianMATRIX[0][1] = dyksi_3psc[pc];
		jacobianMATRIX[1][0] = dxeta_3psc[pc];
		jacobianMATRIX[1][1] = dyeta_3psc[pc];


		double wyznacznik = detJ();
		////////odwrotna macierz Jacobiego//////////
		jacobianMINUSjeden();
		dNdX[0] = (tabKSI[pc][0] * jacobianMATRIXodwrotna[0][0] + jacobianMATRIXodwrotna[0][1] * (tabETA[pc][0]));
		dNdX[1] = (tabKSI[pc][1] * jacobianMATRIXodwrotna[0][0] + jacobianMATRIXodwrotna[0][1] * (tabETA[pc][1]));
		dNdX[2] = (tabKSI[pc][2] * jacobianMATRIXodwrotna[0][0] + jacobianMATRIXodwrotna[0][1] * (tabETA[pc][2]));
		dNdX[3] = (tabKSI[pc][3] * jacobianMATRIXodwrotna[0][0] + jacobianMATRIXodwrotna[0][1] * (tabETA[pc][3]));

		dNdY[0] = ((tabKSI[pc][0] * (-jacobianMATRIXodwrotna[1][0]) + tabETA[pc][0] * jacobianMATRIXodwrotna[1][1]));
		dNdY[1] = ((tabKSI[pc][1] * (-jacobianMATRIXodwrotna[1][0]) + tabETA[pc][1] * jacobianMATRIXodwrotna[1][1]));
		dNdY[2] = ((tabKSI[pc][2] * (-jacobianMATRIXodwrotna[1][0]) + tabETA[pc][2] * jacobianMATRIXodwrotna[1][1]));
		dNdY[3] = ((tabKSI[pc][3] * (-jacobianMATRIXodwrotna[1][0]) + tabETA[pc][3] * jacobianMATRIXodwrotna[1][1]));

		for (int k = 0; k < 4; k++)
		{
			for (int j = 0; j < 4; j++)
			{
				macierzX[k][j] = dNdX[k] * dNdX[j];
				macierzY[k][j] = dNdY[k] * dNdY[j];
			}

		}
		

		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				Element[e].H_local[j][k] += (macierzX[j][k] + macierzY[j][k]) * 25 * wyznacznik * waga1_3psc[pc] * waga2_3psc[pc];
			}
		}
	
	}
}

void licz_C(node Node[], element Element[], int e, int pc, double ro, double cp, int psc) {
	Element4 elem4;
	if (psc == 2) {
		double dxksi_2psc[4] = { 0,0,0,0 };
		double dyeta_2psc[4] = { 0,0,0,0 };
		double dxeta_2psc[4] = { 0,0,0,0 };
		double dyksi_2psc[4] = { 0,0,0,0 };

		double tabETA[4][4];
		double tabKSI[4][4];
		for (int i = 0; i < 4; i++) {
			tabKSI[i][0] = -0.25 * (1 - elem4.eta[i]);
			tabKSI[i][1] = 0.25 * (1 - elem4.eta[i]);
			tabKSI[i][2] = 0.25 * (1 + elem4.eta[i]);
			tabKSI[i][3] = -0.25 * (1 + elem4.eta[i]);
		}
		for (int i = 0; i < 4; i++) {
			tabETA[i][0] = -0.25 * (1 - elem4.ksi[i]);
			tabETA[i][1] = -0.25 * (1 + elem4.ksi[i]);
			tabETA[i][2] = 0.25 * (1 + elem4.ksi[i]);
			tabETA[i][3] = 0.25 * (1 - elem4.ksi[i]);
		}


		for (int j = 0; j < 4; j++) {
			dxksi_2psc[pc] = dxksi_2psc[pc] + tabKSI[pc][j] * Node[Element[e].ID[j]].x;
		}

		for (int j = 0; j < 4; j++) {
			dyeta_2psc[pc] = dyeta_2psc[pc] + tabETA[pc][j] * Node[Element[e].ID[j]].y;
		}

		for (int j = 0; j < 4; j++) {
			dxeta_2psc[pc] = dxeta_2psc[pc] + tabETA[pc][j] * Node[Element[e].ID[j]].x; //tu nie dziala
		}

		for (int j = 0; j < 4; j++) {
			dyksi_2psc[pc] = dyksi_2psc[pc] + tabKSI[pc][j] * Node[Element[e].ID[j]].y;
		}

		jacobianMATRIX[0][0] = dxksi_2psc[pc];
		jacobianMATRIX[0][1] = dyksi_2psc[pc];
		jacobianMATRIX[1][0] = dxeta_2psc[pc];
		jacobianMATRIX[1][1] = dyeta_2psc[pc];

		double wyznacznik = detJ();
		double dNxdNT[4][4];
		double N[4][4];
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (j == 0) N[i][j] = 0.25 * (1 - elem4.ksi[i]) * (1 - elem4.eta[i]);
				if (j == 1) N[i][j] = 0.25 * (1 + elem4.ksi[i]) * (1 - elem4.eta[i]);
				if (j == 2) N[i][j] = 0.25 * (1 + elem4.ksi[i]) * (1 + elem4.eta[i]);
				if (j == 3) N[i][j] = 0.25 * (1 - elem4.ksi[i]) * (1 + elem4.eta[i]);
			}
		}
		for (int k = 0; k < 4; k++)
		{
			for (int j = 0; j < 4; j++) {
				dNxdNT[k][j] = N[pc][k] * N[pc][j];
			}
		}
		for (int k = 0; k < 4; k++) {
			for (int j = 0; j < 4; j++) {
				Element[e].C_local[k][j] += ((dNxdNT[k][j]) * cp * ro * wyznacznik) * waga1_2psc[pc] * waga2_2psc[pc];
			}
		}
		
	}
	else if (psc == 3) {

		double dxksi_3psc[9] = { 0,0,0,0,0,0,0,0,0 };
		double dyeta_3psc[9] = { 0,0,0,0,0,0,0,0,0 };
		double dxeta_3psc[9] = { 0,0,0,0,0,0,0,0,0 };
		double dyksi_3psc[9] = { 0,0,0,0,0,0,0,0,0 };

		double tabETA[9][4];
		double tabKSI[9][4];
		for (int i = 0; i < 9; i++) {
			tabKSI[i][0] = -0.25 * (1 - elem4.eta_3psc[i]);
			tabKSI[i][1] = 0.25 * (1 - elem4.eta_3psc[i]);
			tabKSI[i][2] = 0.25 * (1 + elem4.eta_3psc[i]);
			tabKSI[i][3] = -0.25 * (1 + elem4.eta_3psc[i]);
		}
		for (int i = 0; i < 9; i++) {
			tabETA[i][0] = -0.25 * (1 - elem4.ksi_3psc[i]);
			tabETA[i][1] = -0.25 * (1 + elem4.ksi_3psc[i]);
			tabETA[i][2] = 0.25 * (1 + elem4.ksi_3psc[i]);
			tabETA[i][3] = 0.25 * (1 - elem4.ksi_3psc[i]);
		}


		for (int j = 0; j < 4; j++) {
			dxksi_3psc[pc] = dxksi_3psc[pc] + tabKSI[pc][j] * Node[Element[e].ID[j]].x;
		}

		for (int j = 0; j < 4; j++) {
			dyeta_3psc[pc] = dyeta_3psc[pc] + tabETA[pc][j] * Node[Element[e].ID[j]].y;
		}

		for (int j = 0; j < 4; j++) {
			dxeta_3psc[pc] = dxeta_3psc[pc] + tabETA[pc][j] * Node[Element[e].ID[j]].x; //tu nie dziala
		}

		for (int j = 0; j < 4; j++) {
			dyksi_3psc[pc] = dyksi_3psc[pc] + tabKSI[pc][j] * Node[Element[e].ID[j]].y;
		}

		jacobianMATRIX[0][0] = dxksi_3psc[pc];
		jacobianMATRIX[0][1] = dyksi_3psc[pc];
		jacobianMATRIX[1][0] = dxeta_3psc[pc];
		jacobianMATRIX[1][1] = dyeta_3psc[pc];


		//cout << "Wyznacznik Jacobiego dla " << pc + 1 << " punktu calkowania: " << endl;
		//cout << detJ() << endl;
		double wyznacznik = detJ();

		//do tego jest ok!

		double dNxdNT[4][4];
		double N[9][4];
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 4; j++) {
				if (j == 0) N[i][j] = 0.25 * (1 - elem4.ksi_3psc[i]) * (1 - elem4.eta_3psc[i]);
				if (j == 1) N[i][j] = 0.25 * (1 + elem4.ksi_3psc[i]) * (1 - elem4.eta_3psc[i]);
				if (j == 2) N[i][j] = 0.25 * (1 + elem4.ksi_3psc[i]) * (1 + elem4.eta_3psc[i]);
				if (j == 3) N[i][j] = 0.25 * (1 - elem4.ksi_3psc[i]) * (1 + elem4.eta_3psc[i]);
			}
		}
		for (int k = 0; k < 4; k++)
		{
			for (int j = 0; j < 4; j++) {
				dNxdNT[k][j] = N[pc][k] * N[pc][j];
			}
		}
		for (int k = 0; k < 4; k++) {
			for (int j = 0; j < 4; j++) {
				Element[e].C_local[k][j] += ((dNxdNT[k][j]) * cp * ro * wyznacznik) * waga1_3psc[pc] * waga2_3psc[pc];
			}
		}
	}
	else if (psc == 4) {
		double dxksi_4psc[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
		double dyeta_4psc[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
		double dxeta_4psc[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
		double dyksi_4psc[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

		double tabETA[16][4];
		double tabKSI[16][4];
		for (int i = 0; i < 16; i++) {
			tabKSI[i][0] = -0.25 * (1 - elem4.eta_4psc[i]);
			tabKSI[i][1] = 0.25 * (1 - elem4.eta_4psc[i]);
			tabKSI[i][2] = 0.25 * (1 + elem4.eta_4psc[i]);
			tabKSI[i][3] = -0.25 * (1 + elem4.eta_4psc[i]);
		}
		for (int i = 0; i < 16; i++) {
			tabETA[i][0] = -0.25 * (1 - elem4.ksi_4psc[i]);
			tabETA[i][1] = -0.25 * (1 + elem4.ksi_4psc[i]);
			tabETA[i][2] = 0.25 * (1 + elem4.ksi_4psc[i]);
			tabETA[i][3] = 0.25 * (1 - elem4.ksi_4psc[i]);
		}


		for (int j = 0; j < 4; j++) {
			dxksi_4psc[pc] = dxksi_4psc[pc] + tabKSI[pc][j] * Node[Element[e].ID[j]].x;
		}

		for (int j = 0; j < 4; j++) {
			dyeta_4psc[pc] = dyeta_4psc[pc] + tabETA[pc][j] * Node[Element[e].ID[j]].y;
		}

		for (int j = 0; j < 4; j++) {
			dxeta_4psc[pc] = dxeta_4psc[pc] + tabETA[pc][j] * Node[Element[e].ID[j]].x; //tu nie dziala
		}

		for (int j = 0; j < 4; j++) {
			dyksi_4psc[pc] = dyksi_4psc[pc] + tabKSI[pc][j] * Node[Element[e].ID[j]].y;
		}

		jacobianMATRIX[0][0] = dxksi_4psc[pc];
		jacobianMATRIX[0][1] = dyksi_4psc[pc];
		jacobianMATRIX[1][0] = dxeta_4psc[pc];
		jacobianMATRIX[1][1] = dyeta_4psc[pc];

		double wyznacznik = detJ();

		//do tego jest ok!

		double dNxdNT[4][4];
		double N[16][4];
		for (int i = 0; i < 16; i++) {
			for (int j = 0; j < 4; j++) {
				if (j == 0) N[i][j] = 0.25 * (1 - elem4.ksi_4psc[i]) * (1 - elem4.eta_4psc[i]);
				if (j == 1) N[i][j] = 0.25 * (1 + elem4.ksi_4psc[i]) * (1 - elem4.eta_4psc[i]);
				if (j == 2) N[i][j] = 0.25 * (1 + elem4.ksi_4psc[i]) * (1 + elem4.eta_4psc[i]);
				if (j == 3) N[i][j] = 0.25 * (1 - elem4.ksi_4psc[i]) * (1 + elem4.eta_4psc[i]);
			}
		}
		for (int k = 0; k < 4; k++)
		{
			for (int j = 0; j < 4; j++) {
				dNxdNT[k][j] = N[pc][k] * N[pc][j];
			}
		}
		for (int k = 0; k < 4; k++) {
			for (int j = 0; j < 4; j++) {
				Element[e].C_local[k][j] += ((dNxdNT[k][j]) * cp * ro * wyznacznik) * waga1_4psc[pc] * waga2_4psc[pc];
			}
		}
		
	}
}
void Hbc(node Node[], element Element[], int e, int pc, double alfa, double cp, int psc) {
	//if(psc==2)
	Element4 elem4;
	psc_return(psc);
	elem4.pow_4(psc);

	double detJ;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Hbc_local[i][j] = 0;
		}
	}

	double bok1[4][4] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	double bok2[4][4] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	double bok3[4][4] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	double bok4[4][4] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	//node* ND = new node[4][2];
	node bok_ND[4][2];

	//tu trzeba poprawic
	for (int i = 0; i < 4; i++) {
		if (i == 3) {
			if (((Node[Element[e].ID[i]]).BC == 1) && ((Node[Element[e].ID[0]]).BC == 1)) {
				bok_ND[i][0] = (Node[Element[e].ID[3]]);
				bok_ND[i][1] = Node[Element[e].ID[(0)]];
			}
		}
		else if (((Node[Element[e].ID[i]]).BC == 1) && ((Node[Element[e].ID[(i + 1)]]).BC == 1)) {
			bok_ND[i][0] = (Node[Element[e].ID[i]]);
			bok_ND[i][1] = Node[Element[e].ID[(i + 1)]];
		}
	}

	if (bok_ND[0][0].BC != 0 && bok_ND[0][1].BC != 0) {
		double N_Nt_bok1[4][4] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		N_Nt_bok1[0][0] = elem4.tabN_bok_1[pc][0] * elem4.tabN_bok_1[pc][0];
		N_Nt_bok1[0][1] = elem4.tabN_bok_1[pc][0] * elem4.tabN_bok_1[pc][1];
		N_Nt_bok1[1][0] = elem4.tabN_bok_1[pc][1] * elem4.tabN_bok_1[pc][0];
		N_Nt_bok1[1][1] = elem4.tabN_bok_1[pc][1] * elem4.tabN_bok_1[pc][1];

		detJ = (sqrt(pow(bok_ND[0][1].x - bok_ND[0][0].x, 2) + pow(bok_ND[0][1].y - bok_ND[0][0].y, 2)) / 2);
		
		for (int k = 0; k < 4; k++) {
			for (int l = 0; l < 4; l++) {
				bok1[k][l] = N_Nt_bok1[k][l] * detJ * alfa * elem4.waga[pc];
			}
		}
	}
	//bok 2
	if (bok_ND[1][0].BC != 0 && bok_ND[1][1].BC != 0) {
		double N_Nt_bok2[4][4] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		N_Nt_bok2[1][1] = elem4.tabN_bok_2[pc][1] * elem4.tabN_bok_2[pc][1];
		N_Nt_bok2[1][2] = elem4.tabN_bok_2[pc][1] * elem4.tabN_bok_2[pc][2];
		N_Nt_bok2[2][1] = elem4.tabN_bok_2[pc][2] * elem4.tabN_bok_2[pc][1];
		N_Nt_bok2[2][2] = elem4.tabN_bok_2[pc][2] * elem4.tabN_bok_2[pc][2];
		
		detJ = (sqrt(pow(bok_ND[1][1].x - bok_ND[1][0].x, 2) + pow(bok_ND[1][1].y - bok_ND[1][0].y, 2)) / 2);
	//	cout << "wyznaczik" << detJ << endl;
		for (int k = 0; k < 4; k++) {
			for (int l = 0; l < 4; l++) {
				bok2[k][l] = N_Nt_bok2[k][l] * detJ * alfa * elem4.waga[pc];
			}
		}
	}
	//bok 3
	if (bok_ND[2][0].BC != 0 && bok_ND[2][1].BC != 0) {
		double N_Nt_bok3[4][4] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		N_Nt_bok3[2][2] = elem4.tabN_bok_3[pc][2] * elem4.tabN_bok_3[pc][2];
		N_Nt_bok3[2][3] = elem4.tabN_bok_3[pc][2] * elem4.tabN_bok_3[pc][3];
		N_Nt_bok3[3][2] = elem4.tabN_bok_3[pc][3] * elem4.tabN_bok_3[pc][2];
		N_Nt_bok3[3][3] = elem4.tabN_bok_3[pc][3] * elem4.tabN_bok_3[pc][3];

		detJ = (sqrt(pow(bok_ND[2][1].x - bok_ND[2][0].x, 2) + pow(bok_ND[2][1].y - bok_ND[2][0].y, 2)) / 2);
		//cout << "wyznaczik" << detJ << endl;
		for (int k = 0; k < 4; k++) {
			for (int l = 0; l < 4; l++) {
				bok3[k][l] = N_Nt_bok3[k][l] * detJ * alfa * elem4.waga[pc];
			}
		}
	}
	//bok 4
	if (bok_ND[3][0].BC != 0 && bok_ND[3][1].BC != 0) {
		double N_Nt_bok4[4][4] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		N_Nt_bok4[0][0] = elem4.tabN_bok_4[pc][0] * elem4.tabN_bok_4[pc][0];
		N_Nt_bok4[0][3] = elem4.tabN_bok_4[pc][0] * elem4.tabN_bok_4[pc][3];
		N_Nt_bok4[3][0] = elem4.tabN_bok_4[pc][3] * elem4.tabN_bok_4[pc][0];
		N_Nt_bok4[3][3] = elem4.tabN_bok_4[pc][3] * elem4.tabN_bok_4[pc][3];

		detJ = (sqrt(pow(bok_ND[3][1].x - bok_ND[3][0].x, 2) + pow(bok_ND[3][1].y - bok_ND[3][0].y, 2)) / 2);
		//cout << "wyznaczik" << detJ << endl;
		for (int k = 0; k < 4; k++) {
			for (int l = 0; l < 4; l++) {
				bok4[k][l] = N_Nt_bok4[k][l] * detJ * alfa * elem4.waga[pc];
			}
		}
	}


	for (int k = 0; k < 4; k++) {
		for (int l = 0; l < 4; l++) {
			Hbc_local[k][l] = bok1[k][l] + bok2[k][l] + bok3[k][l] + bok4[k][l];
		
		}
	}

	//delete[] bok_ND;
}


void wektor_P(node Node[], element Element[], int e, int pc, int psc, int alfa, int Talfa) {
	Element4 elem4;
	psc_return(psc);
	node bok_ND[4][2];
	elem4.pow_4(psc);
	double detJ;
	double bok1[4] = { 0,0,0,0 };
	double bok2[4] = { 0,0,0,0 };
	double bok3[4] = { 0,0,0,0 };
	double bok4[4] = { 0,0,0,0 };
	for (int i = 0; i < 4; i++) {
		if (i == 3) {
			if (((Node[Element[e].ID[i]]).BC == 1) && ((Node[Element[e].ID[0]]).BC == 1)) {
				bok_ND[i][0] = (Node[Element[e].ID[3]]);
				bok_ND[i][1] = Node[Element[e].ID[(0)]];
			}
		}
		else if (((Node[Element[e].ID[i]]).BC == 1) && ((Node[Element[e].ID[(i + 1)]]).BC == 1)) {
			bok_ND[i][0] = (Node[Element[e].ID[i]]);
			bok_ND[i][1] = Node[Element[e].ID[(i + 1)]];
		}
	}

	//bok 1
	if (bok_ND[0][0].BC != 0 && bok_ND[0][1].BC != 0) {
		double N_Nt_bok1[4] = { 0, 0, 0, 0 };
		N_Nt_bok1[0] = elem4.tabN_bok_1[pc][0];
		N_Nt_bok1[1] = elem4.tabN_bok_1[pc][1];
		N_Nt_bok1[2] = 0;
		N_Nt_bok1[3] = 0;
	
		detJ = (sqrt(pow(bok_ND[0][1].x - bok_ND[0][0].x, 2) + pow(bok_ND[0][1].y - bok_ND[0][0].y, 2)) / 2);
		for (int k = 0; k < 4; k++) {
			bok1[k] = -N_Nt_bok1[k] * detJ * alfa * elem4.waga[pc] * Talfa;
		}
	}
	//bok 2
	if (bok_ND[1][0].BC != 0 && bok_ND[1][1].BC != 0) {
		double N_Nt_bok2[4] = { 0, 0, 0, 0 };
		N_Nt_bok2[0] = 0;
		N_Nt_bok2[1] = elem4.tabN_bok_2[pc][1];
		N_Nt_bok2[2] = elem4.tabN_bok_2[pc][2];
		N_Nt_bok2[3] = 0;
	
		detJ = (sqrt(pow(bok_ND[1][1].x - bok_ND[1][0].x, 2) + pow(bok_ND[1][1].y - bok_ND[1][0].y, 2)) / 2);
		for (int k = 0; k < 4; k++) {

			bok2[k] = -N_Nt_bok2[k] * detJ * alfa * elem4.waga[pc] * Talfa;
		}
	}
	//bok 3
	if (bok_ND[2][0].BC != 0 && bok_ND[2][1].BC != 0) {
		double N_Nt_bok3[4] = { 0, 0, 0, 0 };
		N_Nt_bok3[0] = 0;
		N_Nt_bok3[1] = 0;
		N_Nt_bok3[2] = elem4.tabN_bok_3[pc][2];
		N_Nt_bok3[3] = elem4.tabN_bok_3[pc][3];

		detJ = (sqrt(pow(bok_ND[2][1].x - bok_ND[2][0].x, 2) + pow(bok_ND[2][1].y - bok_ND[2][0].y, 2)) / 2);
		//cout << "wyznaczik" << detJ << endl;
		for (int k = 0; k < 4; k++) {
			bok3[k] = -N_Nt_bok3[k] * detJ * alfa * elem4.waga[pc] * Talfa;
		}
	}
	//bok 4
	if (bok_ND[3][0].BC != 0 && bok_ND[3][1].BC != 0) {
		double N_Nt_bok4[4] = { 0, 0, 0, 0 };
		N_Nt_bok4[0] = elem4.tabN_bok_4[pc][0];
		N_Nt_bok4[1] = 0;
		N_Nt_bok4[2] = 0;
		N_Nt_bok4[3] = elem4.tabN_bok_4[pc][3];

		detJ = (sqrt(pow(bok_ND[3][1].x - bok_ND[3][0].x, 2) + pow(bok_ND[3][1].y - bok_ND[3][0].y, 2)) / 2);
		//cout << "wyznaczik" << detJ << endl;
		for (int k = 0; k < 4; k++) {
			bok4[k] = -N_Nt_bok4[k] * detJ * alfa * elem4.waga[pc] * Talfa;
		}
	}

	for (int k = 0; k < 4; k++) {
		P_local[k] = bok1[k] + bok2[k] + bok3[k] + bok4[k];
	}

}

void oblicz_macierzeLocal(node ND[], element Elem[])
{
	GlobalElement global;
	int nE = global.nE;
	int nN = global.nN;

	double ro = global.Ro;
	double cp = global.Cp;
	int psc = global.psc;
	double alfa = global.alfa;
	double T_alfa = global.T_alfa;
	for (int e = 0; e < nE; e++)
	{
		for (int i = 0; i < psc*psc; i++) {
			licz_C(ND, Elem, e, i, ro, cp, psc);

		}
	}
	for (int e = 0; e < nE; e++)
	{
		for (int i = 0; i < psc * psc; i++) {
			matrixH(ND, Elem, e, i, psc);

		}
	}
	for (int e = 0; e < nE; e++)
	{
		for (int i = 0; i < psc; i++) {
			Hbc(ND, Elem, e, i, alfa, cp, psc);
			for (int j = 0; j < 4; j++)
				for (int k = 0; k < 4; k++)
				{
					Elem[e].HBC_local[j][k] += Hbc_local[j][k];
				}
		}

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				Elem[e].HBC_local[i][j] = Elem[e].HBC_local[i][j]; //Elem[e].H_local[i][j] + ;
			}
		}
	}

	for (int e = 0; e < nE; e++)
	{

		for (int i = 0; i < psc; i++) {
			wektor_P(ND, Elem, e, i, psc, alfa, T_alfa);
			for (int j = 0; j < 4; j++)
				Elem[e].P_local[j] += P_local[j];
		}

	}
}



////////////////////////////////////////
void solve() {
	GlobalElement global;
	int nE, nN, psc;
	nE = global.nE;
	nN = global.nN;
	psc = global.psc;
	double ro = global.Ro;
	double cp = global.Cp;
	double alfa = global.alfa;
	double T_alfa = global.T_alfa;
	double t_calkowity = global.t_calkowity;
	double delta_t = global.delta_t;

	node* ND = new node[nN];
	element* Elem = new element[nE];
	int number = 0;
	//uzupełnienie węzłów
	//tutaj troszke innaczej
	for (int i = 0; i < global.nW; i++)
	{
		for (int j = 0; j < global.nH; j++)
		{
			ND[number].x = i * (global.W) / (global.nW - 1);
			ND[number].y = j * (global.H) / (global.nH - 1);
			number++;
		}
	}
	number = 0;


	//uzupełnienie elementów
	//????
	for (int i = 0; i < nE + global.nW - 2; i++)
	{
		if (((i + 1) % global.nH == 0 && i != 0)) //|| (i % global.nH == 0))
		{

			continue;
		}


		Elem[number].ID[0] = i;
		Elem[number].ID[1] = Elem[number].ID[0] + global.nH;
		Elem[number].ID[2] = Elem[number].ID[1] + 1;
		Elem[number].ID[3] = Elem[number].ID[0] + 1;

		number++;
	}

	for (int i = 0; i < nE; i++) {
		cout << "Element: " << (i + 1) << " ma wezly :" << endl;
		for (int j = 0; j < 4; j++) {
			cout << "Wezel " << Elem[i].ID[j] + 1 << " : ";
			cout << "x= " << ND[Elem[i].ID[j]].x << " y: " << ND[Elem[i].ID[j]].y << endl;
		}
	}
	//BC

	for (int i = 0; i < nE; i++) {
		for (int j = 0; j < 4; j++) {
		
			if (ND[Elem[i].ID[j]].x == 0 || ND[Elem[i].ID[j]].x > (global.W - 0.001) || ND[Elem[i].ID[j]].y == 0 || ND[Elem[i].ID[j]].y > (global.H - 0.001))
				ND[Elem[i].ID[j]].BC = 1;

		}
	}

	for (int i = 0; i < nE; i++) {
		for (int j = 0; j < 4; j++) {
			cout << ND[Elem[i].ID[j]].BC;
		}
		cout << endl;
	}
	

	
	SOE soe;
	soe.nE = nE;
	soe.nN = nN;
	soe.Elem = Elem;
	//soe.licz_macierzeGlobal();
	int tq = 100.0;
	//initial temp
	
	for (int i = 0; i < nN; i++)
	{
		ND[i].tq = tq;
	}
	
	cout << "test";
	

	double deltatau = delta_t;
	int nt = t_calkowity / delta_t;
	double*  min_temp;
	double* max_temp;

	min_temp = new double[nt];

	for (int i = 0; i < nt; i++) {

		min_temp[i] = 0;

	}
	max_temp = new double[nt];
	for (int i = 0; i < nt; i++) {

		max_temp[i] = 0;

	}


	for (int w = 0; w < 3; w++) {
		
		for (int e = 0; e < nE; e++)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					Elem[e].C_local[i][j] = 0;
					Elem[e].HBC_local[i][j] = 0;
					Elem[e].H_local[i][j] = 0;
					Elem[e].P_local[i] = 0;
				}
			}
		}
		
		oblicz_macierzeLocal(ND, Elem);
		soe.licz_macierzeGlobal();
		soe.inicjalizuj();
		cout << nN;
		cout << "iteracja nr." << w;
		for (int i = 0; i < nN; i++)
		{
			for (int j = 0; j < nN; j++)
			{
				soe.H_zastepcze[i][j] = soe.HBC_global[i][j] + (soe.C_global[i][j] / deltatau);
				soe.P_zastepcze[i] += -((soe.C_global[i][j] / deltatau) * ND[j].tq);

			
			}
			//cout  << soe.P_zastepcze[i] << " ";
			soe.P_zastepcze[i] += soe.P_global[i];
		}
		for (int i = 0; i < nN; i++) {
			cout << soe.P_zastepcze[i] << " " << endl;
		}

		soe.Gauss();
		cout << "temp";
		//w
		min_temp[w] = soe.T_global[0];
		max_temp[w] = soe.T_global[0];
		for (int i = 0; i < nN; i++) {
			ND[i].tq = soe.T_global[i];
			if (min_temp[w] > soe.T_global[i])
				min_temp[w] = soe.T_global[i];
			if (max_temp[w] < soe.T_global[i])
				max_temp[w] = soe.T_global[i];
			
			
			cout << ND[i].tq << " ";


		}
		

		for (int i = 0; i < nN; i++)
		{
			for (int j = 0; j < nN; j++) {
				soe.H_zastepcze[i][j] = 0;
				soe.C_global[i][j] = 0;
				soe.H_global[i][j] = 0;
				soe.HBC_global[i][j] = 0;
			}
		}

	}
	cout << endl;
	for (int i = 0; i < nt; i++) {
		cout << min_temp[i] << " : " << max_temp[i] << endl;
	}

	cout << endl;
	//delete[] ND;
	//delete[] Elem;
}