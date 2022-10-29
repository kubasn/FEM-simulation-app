#include <stdio.h>
#include <emscripten/emscripten.h>
#include <emscripten/bind.h>
#include <iostream>
#include <vector>
#include <math.h>
#include<fstream>
#include <cmath>
#include "generate_mesh.hpp"
using namespace emscripten;

double pc = 1 / (sqrt(3));
//double N[4]={1/(4*(1-pc)*(1-pc)),1/(4*(1+pc)*(1-pc)),1/(4*(1+pc)*(1+pc)),1/(4*(1-pc)*(1+pc))};
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

double C[4][4] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
double P_local[4] = { 0,0,0,0 };

double jacobianMATRIX[2][2];
double jacobianMATRIXodwrotna[2][2];

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

void matrixH(node Node[], element Element[], int e, int pc, int psc,int cond) {
	Element4 elem4;
	elem4.daneHC(psc);
	int rozmiar = psc * psc;

	double** tabKSI;
	double** tabETA;
	double* dxksi;
	double* dxeta;
	double* dyksi;
	double* dyeta;
	dxksi = new double[rozmiar];
	dxeta = new double[rozmiar];
	dyksi = new double[rozmiar];
	dyeta = new double[rozmiar];

	for (int i = 0; i < rozmiar; i++) {

		dxksi[i] = 0;
		dxeta[i] = 0;
		dyksi[i] = 0;
		dyeta[i] = 0;
	}

	tabKSI = new double* [rozmiar];
	for (int i = 0; i < rozmiar; i++)
	{
		tabKSI[i] = new double[4];

	}
	tabETA = new double* [rozmiar];
	for (int i = 0; i < rozmiar; i++)
	{
		tabETA[i] = new double[4];

	}
 
	for (int i = 0; i < rozmiar; i++) {
		for (int j = 0; j < 4; j++)
		{
			tabETA[i][j] = 0;
			tabKSI[i][j] = 0;
		}
	}



	for (int i = 0; i < rozmiar; i++) {
		tabKSI[i][0] = -0.25 * (1 - elem4.eta[i]);
		tabKSI[i][1] = 0.25 * (1 - elem4.eta[i]);
		tabKSI[i][2] = 0.25 * (1 + elem4.eta[i]);
		tabKSI[i][3] = -0.25 * (1 + elem4.eta[i]);
	}
	for (int i = 0; i < rozmiar; i++) {
		tabETA[i][0] = -0.25 * (1 - elem4.ksi[i]);
		tabETA[i][1] = -0.25 * (1 + elem4.ksi[i]);
		tabETA[i][2] = 0.25 * (1 + elem4.ksi[i]);
		tabETA[i][3] = 0.25 * (1 - elem4.ksi[i]);
	}
	
	

	for (int j = 0; j < 4; j++) {
		dxksi[pc] = dxksi[pc] + tabKSI[pc][j] * Node[Element[e].ID[j]].x;
	}

	for (int j = 0; j < 4; j++) {
		dyeta[pc] = dyeta[pc] + tabETA[pc][j] * Node[Element[e].ID[j]].y;
	}

	for (int j = 0; j < 4; j++) {
		dxeta[pc] = dxeta[pc] + tabETA[pc][j] * Node[Element[e].ID[j]].x; //tu nie dziala
	}

	for (int j = 0; j < 4; j++) {
		dyksi[pc] = dyksi[pc] + tabKSI[pc][j] * Node[Element[e].ID[j]].y;
	}

	jacobianMATRIX[0][0] = dxksi[pc];
	jacobianMATRIX[0][1] = dyksi[pc];
	jacobianMATRIX[1][0] = dxeta[pc];
	jacobianMATRIX[1][1] = dyeta[pc];

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
			Element[e].H_local[j][k] += (macierzX[j][k] + macierzY[j][k]) * cond * wyznacznik * elem4.waga1[pc] * elem4.waga2[pc];
		}
	}

	for (int i = 0; i < rozmiar; i++) {
		delete[] tabKSI[i];
		delete[] tabETA[i];


	}
	
	delete[] dxksi;
	delete[] dxeta;
	delete[]  dyksi;
	delete[] dyeta;
	delete[] tabKSI;
	delete[] tabETA;
	delete[] elem4.eta;
	delete[] elem4.ksi;
	delete[] elem4.waga1;
	delete[] elem4.waga2;
	
}

void matrix_C(node Node[], element Element[], int e, int pc, double ro, double cp, int psc) {
	
	Element4 elem4;
	elem4.daneHC(psc);
	int rozmiar = psc * psc;

	double** tabKSI;
	double** tabETA;
	double** N;
	double* dxksi;
	double* dxeta;
	double* dyksi;
	double* dyeta;
	dxksi = new double[rozmiar];
	dxeta = new double[rozmiar];
	dyksi = new double[rozmiar];
	dyeta = new double[rozmiar];

	for (int i = 0; i < rozmiar; i++) {

		dxksi[i] = 0;
		dxeta[i] = 0;
		dyksi[i] = 0;
		dyeta[i] = 0;
	}

	tabKSI = new double* [rozmiar];
	for (int i = 0; i < rozmiar; i++)
	{
		tabKSI[i] = new double[4];

	}
	tabETA = new double* [rozmiar];
	for (int i = 0; i < rozmiar; i++)
	{
		tabETA[i] = new double[4];

	}
	N = new double* [rozmiar];
	for (int i = 0; i < rozmiar; i++)
	{
		N[i] = new double[4];

	}

	for (int i = 0; i < rozmiar; i++) {
		for (int j = 0; j < 4; j++)
		{
			tabETA[i][j] = 0;
			tabKSI[i][j] = 0;
			N[i][j] = 0;
		}
	}


	for (int i = 0; i < rozmiar; i++) {
		tabKSI[i][0] = -0.25 * (1 - elem4.eta[i]);
		tabKSI[i][1] = 0.25 * (1 - elem4.eta[i]);
		tabKSI[i][2] = 0.25 * (1 + elem4.eta[i]);
		tabKSI[i][3] = -0.25 * (1 + elem4.eta[i]);
	}
	for (int i = 0; i < rozmiar; i++) {
		tabETA[i][0] = -0.25 * (1 - elem4.ksi[i]);
		tabETA[i][1] = -0.25 * (1 + elem4.ksi[i]);
		tabETA[i][2] = 0.25 * (1 + elem4.ksi[i]);
		tabETA[i][3] = 0.25 * (1 - elem4.ksi[i]);
	}



	for (int j = 0; j < 4; j++) {
		dxksi[pc] = dxksi[pc] + tabKSI[pc][j] * Node[Element[e].ID[j]].x;
	}

	for (int j = 0; j < 4; j++) {
		dyeta[pc] = dyeta[pc] + tabETA[pc][j] * Node[Element[e].ID[j]].y;
	}

	for (int j = 0; j < 4; j++) {
		dxeta[pc] = dxeta[pc] + tabETA[pc][j] * Node[Element[e].ID[j]].x; //tu nie dziala
	}

	for (int j = 0; j < 4; j++) {
		dyksi[pc] = dyksi[pc] + tabKSI[pc][j] * Node[Element[e].ID[j]].y;
	}

	jacobianMATRIX[0][0] = dxksi[pc];
	jacobianMATRIX[0][1] = dyksi[pc];
	jacobianMATRIX[1][0] = dxeta[pc];
	jacobianMATRIX[1][1] = dyeta[pc];

	double wyznacznik = detJ();

	double dNxdNT[4][4];
	for (int i = 0; i < rozmiar; i++) {
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
			Element[e].C_local[k][j] += ((dNxdNT[k][j]) * cp * ro * wyznacznik) * elem4.waga1[pc] * elem4.waga2[pc];
		}
	}

	for (int i = 0; i < rozmiar; i++) {
		delete[] tabKSI[i];
		delete[] tabETA[i];
		delete[] N[i];
	}

	delete[] N;
	delete[] dxksi;
	delete[] dxeta;
	delete[]  dyksi;
	delete[] dyeta;
delete[] tabKSI;
delete[] tabETA;
delete[] elem4.eta;
delete[] elem4.ksi;
delete[] elem4.waga1;
delete[] elem4.waga2;


}
void Hbc(node Node[], element Element[], int e, int pc, double alfa, double cp, int psc) {

	Element4 elem4;
	elem4.pow_4(psc);
	
	double detJ = 0;
	double detJ2 = 0;
	double detJ3 = 0;
	double detJ4 = 0;

	double bok1[4][4] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	double bok2[4][4] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	double bok3[4][4] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	double bok4[4][4] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	double N_Nt_bok1[4][4] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	double N_Nt_bok2[4][4] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	double N_Nt_bok3[4][4] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	double N_Nt_bok4[4][4] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	node bok_ND[4][2];


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

	if (bok_ND[0][0].BC == 1 && bok_ND[0][1].BC == 1) {
		
		N_Nt_bok1[0][0] = elem4.tabN_bok_1[pc][0] * elem4.tabN_bok_1[pc][0];
		N_Nt_bok1[0][1] = elem4.tabN_bok_1[pc][0] * elem4.tabN_bok_1[pc][1];
		N_Nt_bok1[1][0] = elem4.tabN_bok_1[pc][1] * elem4.tabN_bok_1[pc][0];
		N_Nt_bok1[1][1] = elem4.tabN_bok_1[pc][1] * elem4.tabN_bok_1[pc][1];
		detJ = (sqrt(pow(bok_ND[0][1].x - bok_ND[0][0].x, 2) + pow(bok_ND[0][1].y - bok_ND[0][0].y, 2)) / 2);

		for (int k = 0; k < 4; k++) {
			for (int l = 0; l < 4; l++) {
				bok1[k][l] = N_Nt_bok1[k][l] * detJ;
			}
		}
	}
	//bok 2
	if (bok_ND[1][0].BC == 1 && bok_ND[1][1].BC == 1) {
		
		N_Nt_bok2[1][1] = elem4.tabN_bok_2[pc][1] * elem4.tabN_bok_2[pc][1];
		N_Nt_bok2[1][2] = elem4.tabN_bok_2[pc][1] * elem4.tabN_bok_2[pc][2];
		N_Nt_bok2[2][1] = elem4.tabN_bok_2[pc][2] * elem4.tabN_bok_2[pc][1];
		N_Nt_bok2[2][2] = elem4.tabN_bok_2[pc][2] * elem4.tabN_bok_2[pc][2];
		detJ = (sqrt(pow(bok_ND[1][1].x - bok_ND[1][0].x, 2) + pow(bok_ND[1][1].y - bok_ND[1][0].y, 2)) / 2);

		for (int k = 0; k < 4; k++) {
			for (int l = 0; l < 4; l++) {
				bok2[k][l] = N_Nt_bok2[k][l] * detJ;
			}
		}
	}
	//bok 3
	if (bok_ND[2][0].BC == 1 && bok_ND[2][1].BC == 1) {
		
		N_Nt_bok3[2][2] = elem4.tabN_bok_3[pc][2] * elem4.tabN_bok_3[pc][2];
		N_Nt_bok3[2][3] = elem4.tabN_bok_3[pc][2] * elem4.tabN_bok_3[pc][3];
		N_Nt_bok3[3][2] = elem4.tabN_bok_3[pc][3] * elem4.tabN_bok_3[pc][2];
		N_Nt_bok3[3][3] = elem4.tabN_bok_3[pc][3] * elem4.tabN_bok_3[pc][3];
		detJ = (sqrt(pow(bok_ND[2][1].x - bok_ND[2][0].x, 2) + pow(bok_ND[2][1].y - bok_ND[2][0].y, 2)) / 2);

		for (int k = 0; k < 4; k++) {
			for (int l = 0; l < 4; l++) {
				bok3[k][l] = N_Nt_bok3[k][l] * detJ ;
			}
		}
	}
	//bok 4
	if (bok_ND[3][0].BC == 1 && bok_ND[3][1].BC == 1) {
		
		N_Nt_bok4[0][0] = elem4.tabN_bok_4[pc][0] * elem4.tabN_bok_4[pc][0];
		N_Nt_bok4[0][3] = elem4.tabN_bok_4[pc][0] * elem4.tabN_bok_4[pc][3];
		N_Nt_bok4[3][0] = elem4.tabN_bok_4[pc][3] * elem4.tabN_bok_4[pc][0];
		N_Nt_bok4[3][3] = elem4.tabN_bok_4[pc][3] * elem4.tabN_bok_4[pc][3];
		detJ = (sqrt(pow(bok_ND[3][1].x - bok_ND[3][0].x, 2) + pow(bok_ND[3][1].y - bok_ND[3][0].y, 2)) / 2);
	
		for (int k = 0; k < 4; k++) {
			for (int l = 0; l < 4; l++) {
				bok4[k][l] = N_Nt_bok4[k][l] * detJ;
			}
		}
	}


	for (int k = 0; k < 4; k++) {
		for (int l = 0; l < 4; l++) {
			Element[e].HBC_local[k][l] += elem4.waga[pc]*alfa*(bok1[k][l] + bok2[k][l] + bok3[k][l] + bok4[k][l]);

		}
	}

	//delete[] bok_ND;
}


void wektor_P(node Node[], element Element[], int e, int pc, int psc, int alfa, int Talfa) {
	Element4 elem4;
	//psc_return(psc);
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
	if (bok_ND[0][0].BC == 1 && bok_ND[0][1].BC == 1) {
		double N_Nt_bok1[4] = { 0, 0, 0, 0 };
		N_Nt_bok1[0] = elem4.tabN_bok_1[pc][0];
		N_Nt_bok1[1] = elem4.tabN_bok_1[pc][1];
		N_Nt_bok1[2] = 0;
		N_Nt_bok1[3] = 0;
		//cout << "boki detJ";
		//cout << bok_ND[0][1].x << bok_ND[0][0].x << bok_ND[0][1].y << bok_ND[0][0].y;
		detJ = (sqrt(pow(bok_ND[0][1].x - bok_ND[0][0].x, 2) + pow(bok_ND[0][1].y - bok_ND[0][0].y, 2)) / 2);
		//cout << "wyznaczik" << detJ << endl;
		for (int k = 0; k < 4; k++) {
			bok1[k] = -N_Nt_bok1[k] * detJ * alfa * elem4.waga[pc] * Talfa;
		}
	}
	//bok 2
	if (bok_ND[1][0].BC == 1 && bok_ND[1][1].BC == 1) {
		double N_Nt_bok2[4] = { 0, 0, 0, 0 };
		N_Nt_bok2[0] = 0;
		N_Nt_bok2[1] = elem4.tabN_bok_2[pc][1];
		N_Nt_bok2[2] = elem4.tabN_bok_2[pc][2];
		N_Nt_bok2[3] = 0;
		//cout << "bok2";
		//cout << bok_ND[1][1].x << bok_ND[1][0].x << bok_ND[1][1].y << bok_ND[1][0].y << endl;
		detJ = (sqrt(pow(bok_ND[1][1].x - bok_ND[1][0].x, 2) + pow(bok_ND[1][1].y - bok_ND[1][0].y, 2)) / 2);
		//cout << "wyznaczik" << detJ << endl;
		for (int k = 0; k < 4; k++) {

			bok2[k] = -N_Nt_bok2[k] * detJ * alfa * elem4.waga[pc] * Talfa;
		}
	}
	//bok 3
	if (bok_ND[2][0].BC == 1 && bok_ND[2][1].BC == 1) {
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
	if (bok_ND[3][0].BC == 1 && bok_ND[3][1].BC == 1) {
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
		//cout << "Element: " << e + 1 << endl;
		for (int i = 0; i < psc * psc; i++) {
			matrix_C(ND, Elem, e, i, ro, cp, psc);

		}
		//cout << endl;
	}
	for (int e = 0; e < nE; e++)
	{
		//cout << "Element: " << e + 1 << endl;
		for (int i = 0; i < psc * psc; i++) {
			matrixH(ND, Elem, e, i, psc,25);

		}
		//cout << endl;
	}
	for (int e = 0; e < nE; e++)
	{
		for (int i = 0; i < psc; i++) {
			Hbc(ND, Elem, e, i, alfa, cp, psc);
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
std::vector<int> solve(int alfa, int cp, int ro, int cond) {
	GlobalElement global;
	int nE, nN, psc;
	nE = global.nE;
	nN = global.nN;
	psc = global.psc;
	// double ro = global.Ro;
	// double cp = global.Cp;
	// double alfa = global.alfa;
	double T_alfa = global.T_alfa;
	double t_calkowity = global.t_calkowity;
	double delta_t = global.delta_t;

	node* ND = new node[nN];
	element* Elem = new element[nE];
	int nr_wezel = 0;
	//uzupełnienie węzłów
	//tutaj troszke innaczej
	for (int i = 0; i < global.nW; i++)
	{
		for (int j = 0; j < global.nH; j++)
		{
			ND[nr_wezel].x = i * (global.W) / (global.nW - 1);
			ND[nr_wezel].y = j * (global.H) / (global.nH - 1);
			nr_wezel++;
		}
	}
	nr_wezel = 0;


	//uzupełnienie elementów

	for (int i = 0; i < nE + global.nW - 2; i++)
	{
		if (((i + 1) % global.nH == 0 && i != 0))
		{
			continue;
		}


		Elem[nr_wezel].ID[0] = i;
		Elem[nr_wezel].ID[1] = Elem[nr_wezel].ID[0] + global.nH;
		Elem[nr_wezel].ID[2] = Elem[nr_wezel].ID[1] + 1;
		Elem[nr_wezel].ID[3] = Elem[nr_wezel].ID[0] + 1;

		nr_wezel++;
	}


	//BC
	double skrElemX = ND[Elem[0].ID[0]].x;
	for (int i = 0; i < nE; i++) {
		for (int j = 0; j < 4; j++) {
			if (skrElemX < ND[Elem[i].ID[j]].x) {
				skrElemX = ND[Elem[i].ID[j]].x;
			}
		
		}
	}

	double skrElemY = ND[Elem[0].ID[0]].y;
	for (int i = 0; i < nE; i++) {
		for (int j = 0; j < 4; j++) {
			if (skrElemY < ND[Elem[i].ID[j]].y) {
				skrElemY = ND[Elem[i].ID[j]].y;
			}
		}
	}
	for (int i = 0; i < nE; i++) {
		for (int j = 0; j < 4; j++) {
			//cout << "Wezel " << Elem[i].ID[j] + 1 << " : ";
			//cout << "x= " << ND[Elem[i].ID[j]].x << " y: " << ND[Elem[i].ID[j]].y << endl;
			if (ND[Elem[i].ID[j]].x == 0 || ND[Elem[i].ID[j]].x == skrElemX || ND[Elem[i].ID[j]].y == 0 || ND[Elem[i].ID[j]].y == skrElemY)
				ND[Elem[i].ID[j]].BC = 1;

		}
	}


	SOE soe;
	soe.nE = nE;
	soe.nN = nN;
	soe.Elem = Elem;
	//soe.licz_macierzeGlobal();
	//initial temp
	int tq = 100.0;

	for (int i = 0; i < nN; i++)
	{
		ND[i].tq = tq;
		//soe.P_zastepcze[i] = 0;
	}



	double deltatau = delta_t;
	int nt = t_calkowity / delta_t;
	std::vector<double>min_temp;
	std::vector<double>max_temp;
	std::vector<int>temp;

	// min_temp = new double[nt];

	for (int i = 0; i < nt; i++) {

		min_temp.push_back(0);

	}
	// max_temp = new double[nt];
	for (int i = 0; i < nt; i++) {
		max_temp.push_back(0);
	}
	
	
	for (int w = 0; w < 10; w++) {
		
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

		for (int i = 0; i < nN; i++)
		{
			for (int j = 0; j < nN; j++)
			{
				soe.H_zastepcze[i][j] = soe.HBC_global[i][j] + (soe.C_global[i][j] / deltatau);
				soe.P_zastepcze[i] += -((soe.C_global[i][j] / deltatau) * ND[j].tq);

				
			}
		
			soe.P_zastepcze[i] += soe.P_global[i];
		}
		
	
		soe.Gauss();
		// cout << "temp";
		
		min_temp[w] = soe.T_global[0];
		max_temp[w] = soe.T_global[0];
		for (int i = 0; i < nN; i++) {
			ND[i].tq = int (soe.T_global[i]);
			temp.push_back(soe.T_global[i]);
			if (min_temp[w] > soe.T_global[i])
				min_temp[w] = soe.T_global[i];
			if (max_temp[w] < soe.T_global[i])
				max_temp[w] = soe.T_global[i];


		//	cout << ND[i].tq << " ";


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

		for (int i = 0; i < nN; i++) {
			delete[] soe.C_global[i];
			delete[] soe.H_global[i];
			delete[] soe.HBC_global[i];
		
		}
		delete[] soe.C_global;
		delete[] soe.H_global;
		delete[] soe.P_global;
		delete[] soe.HBC_global;
		delete[] soe.H_zastepcze;
		delete[] soe.P_zastepcze;
	//	delete[] soe.Elem;
	}
	
	// cout << endl;
	// for (int i = 0; i < nt; i++) {
	// 	cout << min_temp[i] << " : " << max_temp[i] << endl;
	// }

	// cout << endl;
	delete[] ND;
	delete[] Elem;
	// return min_temp;

 	// int n = sizeof(min_temp) / sizeof(min_temp[0]);
	// vector<double> v(min_temp, min_temp + sizeof(min_temp)/sizeof(min_temp[0]));
//   return std::vector<double> vec(begin(min_temp), end(min_temp))
temp.push_back(alfa);
temp.push_back(cp);
temp.push_back(cond);
return temp;
// return v;

//  res;
}


// int main()
// {
// 	// solve();
// 	system("pause");
// }

EMSCRIPTEN_BINDINGS(fem_module)
 {
	    register_vector<int>("temp");
    function("solve", &solve,allow_raw_pointer<arg<0>>());
};