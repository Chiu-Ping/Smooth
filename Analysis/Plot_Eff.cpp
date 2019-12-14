#include <TGraph.h> 
#include <iostream>
#include <TCanvas.h>
#include <TAxis.h>

void Plot_Eff()
{
	ifstream ffile;
	ffile.open("/home/shenqiuping/RPC_Anal/DAQ2/Run/eff.txt",ios::in);
	if(!ffile.is_open())
	{
		std::cout << "Could NOT open the file eff.txt!" << std::endl;
		std::cout << "Program terminating.\n";
		exit(EXIT_FAILURE); 
	}
	
	Int_t Num_V=7;
	Double_t V[Num_V];
	Double_t Eff_ustc[Num_V],Eff_sjtu[Num_V];
	
	//while(!ffile)
	//{ 
		for(int i=0;i<Num_V;++i)
		{
			//ffile.getline();
			ffile >> V[i] >> Eff_ustc[i] >> Eff_sjtu[i]; 
		}
	TCanvas *c = new TCanvas("c","",600,600);

	TGraph *eff_u = new TGraph(Num_V,V,Eff_ustc); 
	  auto eff_s = new TGraph(Num_V,V,Eff_sjtu);
	c->cd();
	c->GetFrame()->SetLineWidth(5);
	c->GetFrame()->SetBorderSize(2);
	
	eff_u->SetLineColor(4);
	eff_u->SetMarkerStyle(23);
//	eff_u->Draw("AC*");
//	eff_u->GetXaxis()->SetTitle("High Voltage [V]");
//   	eff_u->GetYaxis()->SetTitle("Efficiency");
	eff_u->SetLineWidth(2);

	eff_s->SetLineColor(3);
	eff_s->SetMarkerStyle(21);
//	eff_s->Draw("CP");
	eff_s->SetLineWidth(2);
//	eff_s->GetXaxis()->SetTitleSize(0.05); 
//	eff_s->GetYaxis()->SetTitleSize(0.05);

	TMultiGraph *mg=new TMultiGraph();
	mg->Add(eff_u);
	mg->Add(eff_s);
		
	TAxis *axisx = mg->GetXaxis();	
	auto axisy	= mg->GetYaxis();	
	axisx->SetRangeUser(6000,8000);
	axisy->SetRangeUser(0,1);
	axisx->SetTitle("High Voltage [V]");
	axisy->SetTitle("Efficiency");
	axisx->SetTitleSize(0.05); 
	axisy->SetTitleSize(0.05);
	axisx->SetTickLength(0.03);
	axisy->SetTickLength(0.03);
	
	
	
	mg->Draw("ALP");

	TLegend *legend = new TLegend(.75,.80,.95,.95);
	legend->AddEntry(eff_u, "USTC");
	legend->AddEntry(eff_s, "SJTU");
	//legend->SetLineSize(2);
	legend->Draw(); 

	c->SaveAs("Eff_Curve.png");
	c->SaveAs("Eff_Curve.jpg");
}
